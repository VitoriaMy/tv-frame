/**
 * 激光電視藍牙聯動伸縮架控制程式
 * Laser TV Bluetooth-Linked Motorized Shelf Controller
 *
 * 適用平台 (Platform): Arduino Nano / UNO
 * 驅動晶片 (Motor Driver): L298N
 *
 * 功能說明 (Description):
 *   透過監聽 HC-05 藍牙模組的 STATE 引腳，判斷激光電視是否開機。
 *   電視開機（藍牙連線）→ 驅動電動推桿展開抽屜。
 *   電視關機（藍牙斷開）→ 驅動電動推桿收起抽屜。
 *
 * 接線說明 (Wiring):
 *   HC-05 STATE  → Arduino D7
 *   Arduino D5   → L298N IN1  (推桿前進 / Extend)
 *   Arduino D6   → L298N IN2  (推桿後退 / Retract)
 *   限位開關 A   → Arduino D2  (展開極限 / Open Limit)
 *   限位開關 B   → Arduino D3  (收起極限 / Close Limit)
 *   L298N OUT1/OUT2 → 電動推桿正/負極
 */

// ── 引腳定義 (Pin Definitions) ──────────────────────────────────────────────

// L298N 馬達驅動引腳
const int motorPin1 = 5;  // 控制推桿前進 (Extend)
const int motorPin2 = 6;  // 控制推桿後退 (Retract)

// 限位開關引腳（使用內建上拉電阻，觸發時讀值為 LOW）
const int limitOpen  = 2;  // 展開到位的極限開關 (Open  limit switch)
const int limitClose = 3;  // 收起到位的極限開關 (Close limit switch)

// HC-05 STATE 引腳（HIGH = 已連線，LOW = 斷開）
const int bluetoothStatePin = 7;

// ── 狀態變數 (State Variable) ────────────────────────────────────────────────

bool isExtended = false;  // 目前推桿是否已展開

// ── 函數宣告 (Function Declarations) ────────────────────────────────────────

void extendShelf();
void retractShelf();
void stopMotor();

// ── 初始化 (Setup) ───────────────────────────────────────────────────────────

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(limitOpen,  INPUT_PULLUP);  // 啟用內建上拉電阻
  pinMode(limitClose, INPUT_PULLUP);  // 啟用內建上拉電阻
  pinMode(bluetoothStatePin, INPUT);

  stopMotor();  // 初始化時馬達保持靜止
}

// ── 主迴圈 (Main Loop) ───────────────────────────────────────────────────────

void loop() {
  // 讀取藍牙連線狀態 (HIGH = 已連線，LOW = 斷開)
  int bluetoothConnected = digitalRead(bluetoothStatePin);

  if (bluetoothConnected == HIGH && !isExtended) {
    // 藍牙已連線，且目前為收起狀態 → 展開抽屜
    extendShelf();
  } else if (bluetoothConnected == LOW && isExtended) {
    // 藍牙已斷開，且目前為展開狀態 → 收起抽屜
    retractShelf();
  }
}

// ── 驅動函數 (Motor Control Functions) ──────────────────────────────────────

/**
 * 展開抽屜
 * 當「展開限位開關」未被觸發，且藍牙仍保持連線時，馬達持續正轉。
 * 若藍牙在運動途中斷開，立即停止並返回主迴圈，由 loop() 觸發收起。
 */
void extendShelf() {
  while (digitalRead(limitOpen) == HIGH) {
    // 藍牙在展開途中斷開 → 停止並交由 loop() 決定下一步
    if (digitalRead(bluetoothStatePin) == LOW) {
      stopMotor();
      return;
    }
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    delay(10);  // 避免 CPU 空轉，減少訊號雜訊
  }
  stopMotor();
  isExtended = true;
}

/**
 * 收起抽屜
 * 當「收起限位開關」未被觸發，且藍牙仍保持斷開時，馬達持續反轉。
 * 若藍牙在運動途中重新連線，立即停止並返回主迴圈，由 loop() 觸發展開。
 */
void retractShelf() {
  while (digitalRead(limitClose) == HIGH) {
    // 藍牙在收起途中重新連線 → 停止並交由 loop() 決定下一步
    if (digitalRead(bluetoothStatePin) == HIGH) {
      stopMotor();
      return;
    }
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    delay(10);  // 避免 CPU 空轉，減少訊號雜訊
  }
  stopMotor();
  isExtended = false;
}

/**
 * 馬達停止
 * 同時拉低 IN1 / IN2，使 L298N 輸出懸空，推桿停止。
 */
void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}
