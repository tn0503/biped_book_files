#define SV_FREQ 50  // サーボ信号周波数
#define MIN_SV_PULSE 0.6  // 最小パルス幅　0°
#define MAX_SV_PULSE 2.4  // 最大パルス幅 180°

uint8_t i;
// 端子設定
uint8_t svPin[12];
// サーボ関連
int16_t offset[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  // サーボ用端子設定
  svPin[0] = 32;
  svPin[1] = 33;
  svPin[2] = 25;
  svPin[3] = 26;
  svPin[4] = 27;
  svPin[5] = 14;
  svPin[6] = 12;
  svPin[7] = 13;
  svPin[8] = 15;
  svPin[9] = 2;
  svPin[10] = 4;
  svPin[11] = 16;
  // サーボ信号出力設定
  i = 0;
  ledcSetup(i, SV_FREQ, 16);
  ledcAttachPin(svPin[i], i);
}

void loop() {
  // put your main code here, to run repeatedly:
  // サーボ信号出力
  ledcWrite(i, get_pulse_width(90 + offset[i]));
}

// パルス幅計算
int get_pulse_width(int angle) {
  float pulseMs = MIN_SV_PULSE + 
    (MAX_SV_PULSE - MIN_SV_PULSE) * angle / 180;
  return (int)(65536 * (pulseMs * SV_FREQ /1000.0));
}
