// サウンド出力

// 端子設定
uint8_t audPin = 17;

void setup() {
  // put your setup code here, to run once:
  // サウンド出力
  ledcSetup(12, 500, 8);
  ledcAttachPin(audPin, 12);
  ledcWriteNote(12, NOTE_C, 4);
}

void loop() {
  // put your main code here, to run repeatedly:
}
