// 左旋回歩行動作

#define SV_FREQ 50  // サーボ信号周波数
#define MIN_SV_PULSE 0.6  // 最小パルス幅　0°
#define MAX_SV_PULSE 2.4  // 最大パルス幅 180°

uint8_t i;
// 端子設定
uint8_t svPin[12];
// 動作関連
int16_t tempAngles[12] = 
{90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90};
int16_t offset[] = {0,12,-4,-4, 0, 0, 0, 0, 4,-8, 4,0};
int16_t ltrnAction[][13] = {
{90,100,100, 90,110, 90, 70,110, 90,100,100, 90, 8},
  {90, 90, 90, 80, 90, 90, 90, 80, 80,100,100, 90, 8}, //左重心
  {90, 90, 90, 80, 70, 90, 90, 70, 90, 90, 90, 90, 4},
  {90, 90, 90, 80, 70, 90, 90, 70, 90, 80, 80, 90, 4}, //右足前
  {90, 80, 80, 90, 70,110, 90, 70, 90, 80, 80, 90, 8},
  {90, 80, 80, 90, 90, 90, 90, 90, 90, 90, 90, 90, 8}, //中重心
  {90, 90, 90, 90,110, 90, 90,110, 90, 90, 90, 90, 4},
  {90,100,100, 90,110, 90, 90,110, 90, 90, 90, 90, 4}  //左足前
};
//uint8_t divide = 10;
uint8_t divCounter;
uint8_t keyFrame;
uint8_t nextKeyFrame;

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
  //i = 0;
  for(i = 0; i < 12; i++) {
    ledcSetup(i, SV_FREQ, 16);
    ledcAttachPin(svPin[i], i);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // フレーム処理
  divCounter++;
  if(divCounter >= ltrnAction[nextKeyFrame][12]) {
    divCounter = 0;
    keyFrame = nextKeyFrame;
    nextKeyFrame++;
    if(nextKeyFrame > 7) nextKeyFrame = 0;
  }
  // サーボ角度計算
  for(int i = 0; i < 12; i++) {
    tempAngles[i] = ltrnAction[keyFrame][i] +
              int8_t((ltrnAction[nextKeyFrame][i] - ltrnAction[keyFrame][i])
               * divCounter / ltrnAction[nextKeyFrame][12]);
  }
  // サーボ信号出力
  for(i = 0; i < 12; i++) {
    ledcWrite(i, get_pulse_width(tempAngles[i] + offset[i]));
  }
  delay(30);
}

// パルス幅計算
int get_pulse_width(int angle) {
  float pulseMs = MIN_SV_PULSE + 
    (MAX_SV_PULSE - MIN_SV_PULSE) * angle / 180;
  return (int)(65536 * (pulseMs * SV_FREQ /1000.0));
}
