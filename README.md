以下為您將這套開源方案整理為一份結構完整、可直接複製保存的 Markdown 專案開發文檔。
------------------------------
## 🛠️ 專案文檔：基於藍牙監聽的隱藏式激光電視電動伸縮架 (DIY Open-Source Project)
本專案透過微控制器（Arduino / ESP32）主動監聽激光電視的藍牙（Bluetooth）連線狀態。當電視開機並發出藍牙訊號時，系統驅動電動推桿自動展開抽屜；電視關機藍牙斷開時，自動收回平齊電視櫃。
------------------------------
## 一、 系統架構圖 (System Architecture)

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
 │   │ 12V 直流電源   ├────────►│  L298N 驅動板 │                │
 │   └───────────────┘         └───────┬───────┘                    │
 │                                     │                            │
 └─────────────────────────────────────┼────────────────────────────┘
                                       ▼
                     ======================================
                     [限位開關A] ◄──  電動推桿  ──► [限位開關B]
                     ======================================

------------------------------
## 二、 硬體採購清單 (BOM)

| 序號 | 元件名稱 | 建議規格 | 功能說明 |
|---|---|---|---|
| 1 | 控制主板 | Arduino Nano 或 ESP32 | 系統邏輯控制核心。 |
| 2 | 藍牙模組 | HC-05 串口藍牙模組 | 設為主機模式，用以監聽電視藍牙狀態（若用 ESP32 則免）。 |
| 3 | 馬達驅動板 | L298N 驅動模組 | 放大電流以驅動 12V 直流馬達。 |
| 4 | 執行機構 | 12V 直流電動推桿（行程 300-400mm） | 負責抽屜的物理伸縮推拉。 |
| 5 | 安全定位 | 機械式常閉限位開關 (Limit Switch) × 2 | 到達最前端或最底端時物理斷電保護。 |
| 6 | 供電系統 | 12V 5A 直流電源適配器 | 為馬達和控制板供電。 |

------------------------------
## 三、 硬體接線定義 (Wiring Definition)

| 起始元件與引腳 | 目標元件與引腳 | 線路類型 | 備註說明 |
|---|---|---|---|
| HC-05 (STATE) | Arduino (D7) | 訊號線 | 監聽藍牙連線狀態（HIGH=已連，LOW=斷開）。 |
| Arduino (D5) | L298N (IN1) | PWM/數字訊號 | 控制推桿前進（展開）。 |
| Arduino (D6) | L298N (IN2) | PWM/數字訊號 | 控制推桿後退（收起）。 |
| 限位開關 A (OUT) | Arduino (D2) | 訊號線 | 展開極限位置感應（使用內建上拉電阻）。 |
| 限位開關 B (OUT) | Arduino (D3) | 訊號線 | 收起極限位置感應（使用內建上拉電阻）。 |
| L298N (OUT1/OUT2) | 電動推桿 (正/負極) | 動力線 | 驅動馬達運作。 |

------------------------------
## 四、 核心控制原始碼 (Arduino C++)

/**
 * 激光電視藍牙聯動伸縮架控制程式
 * 適用平台：Arduino Nano / UNO
 * 驅動晶片：L298N
 */
// 定義 L298N 馬達驅動引腳const int motorPin1 = 5;  // 控制推桿前進const int motorPin2 = 6;  // 控制推桿後退
// 定義限位開關引腳const int limitOpen = 2;   // 展開到位的極限開關const int limitClose = 3;  // 收起到位的極限開關
// 定義藍牙狀態引腳 (HC-05 的 STATE 引腳)const int bluetoothStatePin = 7; 
bool isExtended = false; // 紀錄目前推桿是否已展開
void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(limitOpen, INPUT_PULLUP);  // 啟用內建上拉電阻
  pinMode(limitClose, INPUT_PULLUP);
  pinMode(bluetoothStatePin, INPUT);
  
  stopMotor(); // 初始化時馬達保持靜止
}
void loop() {
  // 讀取藍牙連線狀態 (HIGH 代表已連線，LOW 代表斷開)
  int bluetoothConnected = digitalRead(bluetoothStatePin);

  if (bluetoothConnected == HIGH && !isExtended) {
    // 藍牙已連線，且目前為收起狀態 -> 執行展開動作
    extendShelf();
  } 
  else if (bluetoothConnected == LOW && isExtended) {
    // 藍牙已斷開，且目前為展開狀態 -> 執行收起動作
    retractShelf();
  }
}
// ─── 驅動函數：執行展開 ───void extendShelf() {
  // 當未觸碰到「展開限位開關」時，馬達持續正轉
  while (digitalRead(limitOpen) == HIGH) {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  }
  stopMotor();
  isExtended = true; // 更新狀態為已展開
}
// ─── 驅動函數：執行收起 ───void retractShelf() {
  // 當未觸碰到「收起限位開關」時，馬達持續反轉
  while (digitalRead(limitClose) == HIGH) {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
  }
  stopMotor();
  isExtended = false; // 更新狀態為已收起
}
// ─── 驅動函數：馬達停止 ───void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}

------------------------------
## 五、 關鍵配置步驟：綁定電視藍牙 MAC
為了防止藍牙模組誤連到手機或鄰居的設備，必須透過 AT 指令 將 HC-05 鎖定電視的物理位址：

   1. 獲取電視 MAC：開啟電視藍牙，使用手機下載 Bluetooth Serial Terminal APP，掃描並記錄電視的 MAC 位址（例如：94:E6:63:AB:CD:EF）。
   2. 進入 AT 模式：按住 HC-05 上的小按鈕通電，當 LED 變為慢閃（2秒閃一次），即進入配置模式。
   3. 發送綁定指令：透過串口調試工具發送以下指令：
   * AT+ROLE=1（設定為主人模式）
      * AT+CMODE=0（設定為指定固定位址連線）
      * AT+BIND=94E6,63,ABCDEF（注意：電視 MAC 的冒號要換成逗號，十六進制字母大寫）
   4. 重啟系統：斷電重新通電，模組即會專一監聽該電視。

------------------------------
如果您在焊接電路或調試 AT 指令 時遇到任何問題，隨時告訴我：

* 您手邊是否有串口偵錯工具（如 TTL 轉 USB 模組）？
* 是否需要幫您調整為 ESP32 的免外接藍牙原生程式碼？

我可以為您補充相應的技術細節！

