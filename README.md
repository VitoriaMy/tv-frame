# 🛠️ tv-frame — 基於藍牙監聽的隱藏式激光電視電動伸縮架

> **DIY Open-Source Project**
> 透過微控制器（Arduino Nano / ESP32）主動監聽激光電視的藍牙（Bluetooth）連線狀態。  
> 當電視開機並發出藍牙訊號時，系統驅動電動推桿自動展開抽屜；  
> 電視關機藍牙斷開時，自動收回平齊電視櫃。

---

## 目錄 (Table of Contents)

1. [系統架構圖](#一-系統架構圖-system-architecture)
2. [硬體採購清單 (BOM)](#二-硬體採購清單-bom)
3. [硬體接線定義](#三-硬體接線定義-wiring-definition)
4. [核心控制原始碼](#四-核心控制原始碼-arduino-c)
5. [HC-05 綁定電視藍牙 MAC](#五-關鍵配置步驟綁定電視藍牙-mac)

---

## 一、 系統架構圖 (System Architecture)

```
       ┌────────────────────────────────────────────────────────┐
       │                 激光電視 (發射藍牙訊號)                   │
       └───────────────────────────┬────────────────────────────┘
                                   ░ (無線藍牙訊號)
                                   ▼
 ┌──────────────────────────────────────────────────────────────────┐
 │                     【 DIY 控制箱內部 】                         │
 │                                                                  │
 │   ┌───────────────┐  UART   ┌───────────────┐                    │
 │   │  HC-05 藍牙   ├────────►│ Arduino Nano  │                    │
 │   │  (掃描連線)    │         │  (控制核心)   │                    │
 │   └───────────────┘         └───────┬───────┘                    │
 │                                     │ PWM 訊號                   │
 │                                     ▼                            │
 │   ┌───────────────┐  12V 電源   ┌───────────────┐                │
 │   │ 12V 直流電源   ├────────────►│  L298N 驅動板 │               │
 │   └───────────────┘             └───────┬───────┘                │
 │                                         │                        │
 └─────────────────────────────────────────┼────────────────────────┘
                                           ▼
                     ======================================
                     [限位開關A] ◄──  電動推桿  ──► [限位開關B]
                     ======================================
```

---

## 二、 硬體採購清單 (BOM)

| 序號 | 元件名稱 | 建議規格 | 功能說明 |
|:---:|---|---|---|
| 1 | 控制主板 | Arduino Nano 或 ESP32 | 系統邏輯控制核心。 |
| 2 | 藍牙模組 | HC-05 串口藍牙模組 | 設為主機模式，用以監聽電視藍牙狀態（若用 ESP32 則免）。 |
| 3 | 馬達驅動板 | L298N 驅動模組 | 放大電流以驅動 12V 直流馬達。 |
| 4 | 執行機構 | 12V 直流電動推桿（行程 300–400 mm） | 負責抽屜的物理伸縮推拉。 |
| 5 | 安全定位 | 機械式常閉限位開關 (Limit Switch) × 2 | 到達最前端或最底端時物理斷電保護。 |
| 6 | 供電系統 | 12V 5A 直流電源適配器 | 為馬達和控制板供電。 |

---

## 三、 硬體接線定義 (Wiring Definition)

| 起始元件與引腳 | 目標元件與引腳 | 線路類型 | 備註說明 |
|---|---|---|---|
| HC-05 (STATE) | Arduino (D7) | 訊號線 | 監聽藍牙連線狀態（HIGH = 已連，LOW = 斷開）。 |
| Arduino (D5) | L298N (IN1) | PWM / 數字訊號 | 控制推桿前進（展開）。 |
| Arduino (D6) | L298N (IN2) | PWM / 數字訊號 | 控制推桿後退（收起）。 |
| 限位開關 A (OUT) | Arduino (D2) | 訊號線 | 展開極限位置感應（使用內建上拉電阻）。 |
| 限位開關 B (OUT) | Arduino (D3) | 訊號線 | 收起極限位置感應（使用內建上拉電阻）。 |
| L298N (OUT1 / OUT2) | 電動推桿（正 / 負極） | 動力線 | 驅動馬達運作。 |

> **注意**：限位開關使用 Arduino 內建上拉電阻（`INPUT_PULLUP`）。  
> 開關未觸發時引腳讀值為 `HIGH`；觸發（按下）後讀值為 `LOW`，馬達隨即停止。

---

## 四、 核心控制原始碼 (Arduino C++)

原始碼位於 [`src/tv_frame_controller/tv_frame_controller.ino`](src/tv_frame_controller/tv_frame_controller.ino)。

```cpp
/**
 * 激光電視藍牙聯動伸縮架控制程式
 * 適用平台：Arduino Nano / UNO
 * 驅動晶片：L298N
 */

// 定義 L298N 馬達驅動引腳
const int motorPin1 = 5;  // 控制推桿前進
const int motorPin2 = 6;  // 控制推桿後退

// 定義限位開關引腳
const int limitOpen  = 2;  // 展開到位的極限開關
const int limitClose = 3;  // 收起到位的極限開關

// 定義藍牙狀態引腳 (HC-05 的 STATE 引腳)
const int bluetoothStatePin = 7;

bool isExtended = false;  // 紀錄目前推桿是否已展開

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(limitOpen,  INPUT_PULLUP);  // 啟用內建上拉電阻
  pinMode(limitClose, INPUT_PULLUP);
  pinMode(bluetoothStatePin, INPUT);

  stopMotor();  // 初始化時馬達保持靜止
}

void loop() {
  // 讀取藍牙連線狀態 (HIGH 代表已連線，LOW 代表斷開)
  int bluetoothConnected = digitalRead(bluetoothStatePin);

  if (bluetoothConnected == HIGH && !isExtended) {
    // 藍牙已連線，且目前為收起狀態 → 執行展開動作
    extendShelf();
  } else if (bluetoothConnected == LOW && isExtended) {
    // 藍牙已斷開，且目前為展開狀態 → 執行收起動作
    retractShelf();
  }
}

// 展開抽屜：當未觸碰到「展開限位開關」且藍牙仍連線時，馬達持續正轉
// 若藍牙在途中斷開，停止並返回 loop() 處理後續動作
void extendShelf() {
  while (digitalRead(limitOpen) == HIGH) {
    if (digitalRead(bluetoothStatePin) == LOW) {
      stopMotor();
      return;
    }
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    delay(10);
  }
  stopMotor();
  isExtended = true;
}

// 收起抽屜：當未觸碰到「收起限位開關」且藍牙仍斷開時，馬達持續反轉
// 若藍牙在途中重新連線，停止並返回 loop() 處理後續動作
void retractShelf() {
  while (digitalRead(limitClose) == HIGH) {
    if (digitalRead(bluetoothStatePin) == HIGH) {
      stopMotor();
      return;
    }
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    delay(10);
  }
  stopMotor();
  isExtended = false;
}

// 馬達停止
void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}
```

---

## 五、 關鍵配置步驟：綁定電視藍牙 MAC

為了防止藍牙模組誤連到手機或鄰居的設備，必須透過 **AT 指令** 將 HC-05 鎖定電視的物理位址：

### 步驟 1 — 取得電視 MAC 位址

開啟電視藍牙，使用手機下載 **Bluetooth Serial Terminal** APP，掃描並記錄電視的 MAC 位址（例如：`94:E6:63:AB:CD:EF`）。

### 步驟 2 — 進入 AT 配置模式

按住 HC-05 上的小按鈕後通電。當 LED 變為**慢閃（約 2 秒閃一次）**，即進入配置模式。

### 步驟 3 — 發送綁定指令

透過串口調試工具（波特率 38400）依序發送：

```
AT+ROLE=1                      // 設定為主人 (Master) 模式
AT+CMODE=0                     // 設定為指定固定位址連線
AT+BIND=94E6,63,ABCDEF         // 填入電視 MAC（冒號換逗號，字母大寫）
```

> **格式說明**：MAC `94:E6:63:AB:CD:EF` → `AT+BIND=94E6,63,ABCDEF`

### 步驟 4 — 重啟系統

斷電後重新通電，模組即會專一監聽該台電視的藍牙訊號。

---

## 常見問題 (FAQ)

| 問題 | 可能原因 | 解決方式 |
|---|---|---|
| 推桿不動 | 電源不足 / L298N 未通 12V | 確認 12V 電源已接至 L298N 的 VCC 與 GND |
| 推桿持續運動不停 | 限位開關接線錯誤 | 確認開關使用常閉接法，並啟用 `INPUT_PULLUP` |
| 藍牙無法綁定電視 | AT 指令格式錯誤 | 確認 MAC 格式正確，且串口波特率為 38400 |
| 每次重啟後狀態重置 | `isExtended` 未持久化 | 可加入 `EEPROM` 讀寫保存最後狀態 |

---

## 授權 (License)

本專案以 [MIT License](LICENSE) 開源，歡迎自由使用、修改與散布。
