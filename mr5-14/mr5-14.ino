// 音階出力

// 端子設定
uint8_t audPin = 17;

void setup() {
  // put your setup code here, to run once:
  // サウンド出力
  ledcSetup(12, 500, 8);
  ledcAttachPin(audPin, 12);
  //ledcWriteNote(12, NOTE_C, 4);
}

void loop() {
  // put your main code here, to run repeatedly:
  ledcWriteNote(12,NOTE_C,4);
  delay(500);
  ledcWriteNote(12,NOTE_D,4);
  delay(500);
  ledcWriteNote(12,NOTE_E,4);
  delay(500);
  ledcWriteNote(12,NOTE_F,4);
  delay(500);
  ledcWriteNote(12,NOTE_G,4);
  delay(500);
  ledcWriteNote(12,NOTE_A,4);
  delay(500);
  ledcWriteNote(12,NOTE_B,4);
  delay(500);
  ledcWriteNote(12,NOTE_C,5);
  delay(500);
  ledcDetachPin(audPin);
}
