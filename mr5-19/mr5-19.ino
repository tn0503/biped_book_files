#define SV_FREQ 50  // サーボ信号周波数
#define MIN_SV_PULSE 0.6  // 最小パルス幅　0°
#define MAX_SV_PULSE 2.4  // 最大パルス幅 180°

#define STOP  0
#define FWRD  1
#define BWRD  2
#define LTRN  3
#define RTRN  4
#define LEFT  5
#define RGHT  6

// 端子設定
uint8_t svPin[12];
uint8_t audPin = 17;
uint8_t interruptPin = 5;
uint8_t ledPin = 18;

uint8_t i;

// 動作関連
int16_t tempAngles[12] = {90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90};
int16_t offset[] = { 20, 12, -8, -4, 0, 0, 0, 0, 4,-12, 4, 0};

int16_t fwrd[8][14] = {
//LHR LHP LAP LAR LSP LSR RSR RSP RAR RAP RHP RHR time snd
  /*{90,100,100, 90, 90, 90, 90, 90, 90,100,100, 90, 8, 0},
  {90, 90, 90, 80, 80, 90, 90, 80, 80,100,100, 90, 8, 0},
  {90, 90, 90, 80, 70, 90, 90, 70, 90, 90, 90, 90, 4, 1},
  {90, 90, 90, 80, 80, 90, 90, 80, 90, 80, 80, 90, 4, 1},
  {90, 80, 80, 90, 90, 90, 90, 90, 90, 80, 80, 90, 8, 0},
  {90, 80, 80,100,100, 90, 90,100,100, 90, 90, 90, 8, 0},
  {90, 90, 90, 90,110, 90, 90,110,100, 90, 90, 90, 4, 2},
  {90,100,100, 90,100, 90, 90,100,100, 90, 90, 90, 4, 2}*/
  {90,105,105, 90, 90, 90, 90, 90, 90,105,105, 90, 8, 0},
  {90, 90, 90, 80, 80, 90, 90, 80, 80,105,105, 90, 8, 0},
  {90, 90, 90, 80, 70, 90, 90, 70, 90, 90, 90, 90, 4, 1},
  {90, 90, 90, 80, 80, 90, 90, 80, 90, 75, 75, 90, 4, 1},
  {90, 75, 75, 90, 90, 90, 90, 90, 90, 75, 75, 90, 8, 0},
  {90, 75, 75,100,100, 90, 90,100,100, 90, 90, 90, 8, 0},
  {90, 90, 90, 90,110, 90, 90,110,100, 90, 90, 90, 4, 2},
  {90,105,105, 90,100, 90, 90,100,100, 90, 90, 90, 4, 2}
};
int16_t bwrd[][14] = {
  {90,100,100-4, 90,110, 90, 70,110, 90,100+4,100, 90, 8, 0},
  {90,100,100-4, 90,110, 90, 90,110,100, 90+4, 90, 90, 8, 0},
  {90, 90, 90-4, 90,110, 90, 90,110,100, 90+4, 90, 90, 4, 1},
  {90, 80, 80-4,100, 90, 90, 90, 90,100, 90+4, 90, 90, 4, 1},
  {90, 80, 80-4, 90, 70,110, 90, 70, 90, 80+4, 80, 90, 8, 0},
  {90, 90, 90-4, 80, 70, 90, 90, 70, 90, 80+4, 80, 90, 8, 0},
  {90, 90, 90-4, 80, 70, 90, 90, 70, 90, 90+4, 90, 90, 4, 2},
  {90, 90, 90-4, 80, 90, 90, 90, 90, 80,100+4,100, 90, 4, 2} 
};
int16_t ltrn[][14] = {
  {90,100,100, 90,110, 90, 70,110, 90,100,100, 90, 8, 0},
  {90, 90, 90, 80, 90, 90, 90, 80, 80,100,100, 90, 8, 0},
  {90, 90, 90, 80, 70, 90, 90, 70, 90, 90, 90, 90, 4, 0},
  {90, 90, 90, 80, 70, 90, 90, 70, 90, 80, 80, 90, 4, 1},
  {90, 80, 80, 90, 70,110, 90, 70, 90, 80, 80, 90, 8, 1},
  {90, 80, 80, 90, 90, 90, 90, 90, 90, 90, 90, 90, 8, 0},
  {90, 90, 90, 90,110, 90, 90,110, 90, 90, 90, 90, 4, 2},
  {90,100,100, 90,110, 90, 90,110, 90, 90, 90, 90, 4, 2} 
};
int16_t rtrn[][14] = {
  {90,100,100, 90,110, 90, 70,110, 90,100,100, 90, 8, 0},
  {90, 90, 90, 90, 90, 90, 90, 80, 90,100,100, 90, 8, 0},
  {90, 90, 90, 90, 70, 90, 90, 70, 90, 90, 90, 90, 4, 1},
  {90, 90, 90, 90, 70, 90, 90, 70, 90, 80, 80, 90, 4, 1},
  {90, 80, 80, 90, 70,110, 90, 70, 90, 80, 80, 90, 8, 0},
  {90, 80, 80, 90, 90, 90, 90, 90,100, 90, 90, 90, 8, 0},
  {90, 90, 90, 90,110, 90, 90,110,100, 90, 90, 90, 4, 2},
  {90,100,100, 90,110, 90, 90,110,100, 90, 90, 90, 4, 2} 
};
int16_t left[][14] = {
  { 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 8, 0},
  { 90, 90, 90,100, 90, 90, 90, 90,100, 90, 90, 90, 8, 0},
  {100, 90, 90,100, 90, 90, 90, 90,100, 90, 90, 90, 8, 1},
  { 90, 90, 90, 80, 90, 90, 90, 90, 80, 90, 90, 80, 8, 1},
  { 90, 90, 90, 80, 90, 90, 90, 90, 80, 90, 90, 90, 8, 0},
  { 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 8, 0}
};
int16_t rght[][14] = {
  { 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 8, 0},
  { 90, 90, 90, 80, 90, 90, 90, 90, 80, 90, 90, 90, 8, 0},
  { 90, 90, 90, 80, 90, 90, 90, 90, 80, 90, 90, 80, 8, 1},
  {100, 90, 90,100, 90, 90, 90, 90,100, 90, 90, 90, 8, 1},
  { 90, 90, 90,100, 90, 90, 90, 90,100, 90, 90, 90, 8, 0},
  { 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 8, 0}
};
int16_t action[8][14];
uint8_t maxRows;
uint8_t divCounter;
uint8_t keyFrame;
uint8_t nextKeyFrame;
uint8_t actionMode;
uint8_t svFlag = 0; //30msecの割り込みを知らせる

// タイマー
hw_timer_t * timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;

// 音声関連
boolean beep = false; //リモコンからのbeep音を鳴らす
uint16_t bpCounter = 0; //beep音用カウンター

// リモコン関連
boolean  rmReceived = 0;  //信号受信完了した
uint8_t  digit;           //受信データの桁
uint8_t  rmState = 0;     //信号受信状況
uint8_t  dataCode;        //データコード(8bit)
uint8_t  invDataCode;     //反転データコード(8bit)
uint16_t customCode;      //カスタムコード(16bit)
uint32_t rmCode;          //コード全体(32bit)
volatile uint32_t prevMicros = 0; //時間計測用

// タイマー割り込み
void IRAM_ATTR onTimer(){
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
  svFlag = 1;
  bpCounter++;
}

void rmUpdate() //信号が変化した
{
  uint32_t width; //パルスの幅を計測
  if(rmState != 0){
    width = micros() - prevMicros;  //時間間隔を計算
    if(width > 10000)rmState = 0; //長すぎ
    prevMicros = micros();  //次の計算用
  }
  switch(rmState){
    case 0: //信号未達
    prevMicros = micros();  //現在時刻(microseconds)を記憶
    rmState = 1;  //最初のLOW->HIGH信号を検出した
    digit = 0;
    return;
    case 1: //最初のHIGH状態
      if((width > 9500) || (width < 8500)){ //リーダーコード(9ms)ではない
        rmState = 0;
      }else{
        rmState = 2;  //HIGH->LOWで9ms検出
      }
      break;
    case 2: //9ms検出した
      if((width > 5000) || (width < 4000)){ //リーダーコード(4.5ms)ではない
        rmState = 0;
      }else{
        rmState = 3;  //LOW->HIGHで4.5ms検出
      }
      break;
    case 3: //4.5ms検出した
      if((width > 700) || (width < 400)){
        rmState = 0;
      }else{
        rmState = 4;  //HIGH->LOWで0.56ms検出した
      }
      break;
    case 4: //0.56ms検出した
      if((width > 1800) || (width < 400)){  //LOW期間(2.25-0.56)msより長い or (1.125-0.56)msより短い
        rmState = 0;
      }else{
        if(width > 1000){ //LOW期間長い -> 1
          bitSet(rmCode, (digit));
        }else{             //LOW期間短い -> 0
          bitClear(rmCode, (digit));
        }
        digit++;  //次のbit
        if(digit > 31){ //完了
          rmReceived = 1;
          return;
        }
        rmState = 3;  //次のHIGH->LOWを待つ
      }
      break;
    }
}

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
  for(i=0; i<12; i++) {
    ledcSetup(i, SV_FREQ, 16);
    ledcAttachPin(svPin[i], i);
  }
  
  // 音声出力設定
  ledcSetup(12, 500, 8);

  // 動作モード初期化
  actionMode = STOP;

  // LED用端子設定
  pinMode(ledPin, OUTPUT);

  // リモコン用端子設定
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), rmUpdate, CHANGE);

  // タイマー割り込みセット
  timerSemaphore = xSemaphoreCreateBinary();
  timer = timerBegin(1, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 30000, true);
  timerAlarmEnable(timer);
}

void loop() {
  // put your main code here, to run repeatedly:
  // リモコン受信関連
  if(rmReceived){ //リモコン受信した
    detachInterrupt(digitalPinToInterrupt(interruptPin));
    rmReceived = 0;   //初期化
    rmState = 0;      //初期化
    //図とは左右が逆であることに注意
    customCode = rmCode;    //下16bitがcustomCode
    dataCode = rmCode >> 16;  //下16bitを捨てたあとの下8bitがdataCode
    invDataCode = rmCode >> 24; //下24bitを捨てたあとの下8bitがinvDataCode
    if((dataCode + invDataCode) == 0xff){   //反転確認
      //Serial.println(dataCode);
      switch(dataCode){
        case 248:
          digitalWrite(ledPin, HIGH);
          break;
        case 120:
          digitalWrite(ledPin, LOW);
          break;
        case 88:  //サウンド出力
          beep = true;
          bpCounter = 0;
          ledcAttachPin(audPin, 12);
          memcpy(action, load, sizeof(load));
          maxRows = sizeof(load) / sizeof(*load) - 1;
          break;
        case 160:
          actionMode = FWRD;
          memcpy(action, fwrd, sizeof(fwrd));
          maxRows = sizeof(fwrd) / sizeof(*fwrd) - 1;
          break;
        case 0:
          actionMode = BWRD;
          memcpy(action, bwrd, sizeof(bwrd));
          maxRows = sizeof(bwrd) / sizeof(*bwrd) - 1;
          break;
        case 177:
          actionMode = LTRN;
          memcpy(action, ltrn, sizeof(ltrn));
          maxRows = sizeof(ltrn) / sizeof(*ltrn) - 1;
          break;
        case 33:
          actionMode = RTRN;
          memcpy(action, rtrn, sizeof(rtrn));
          maxRows = sizeof(rtrn) / sizeof(*rtrn) - 1;
          break;
        case 16:
          actionMode = LEFT;
          memcpy(action, left, sizeof(left));
          maxRows = sizeof(left) / sizeof(*left) - 1;
          break;
        case 128:
          actionMode = RGHT;
          memcpy(action, rght, sizeof(rght));
          maxRows = sizeof(rght) / sizeof(*rght) - 1;
          break;
        case 32:
          actionMode = STOP;
          for(int i=0; i<12; i++) {
            tempAngles[i] = 90;
          }
          break;
        default:
        break;
      }
      divCounter = 0;
        keyFrame = 0;
        nextKeyFrame = 1;
    }
    attachInterrupt(digitalPinToInterrupt(interruptPin), rmUpdate, CHANGE);
  }
  // リモコン受信関連ここまで
  
  // 動作・サウンド出力
  if(svFlag) {  // 30ミリ秒ごと
    svFlag = 0;
    if(actionMode != STOP){ // STOPモード以外
      // フレーム処理
      divCounter++;
    if(divCounter >= action[nextKeyFrame][12]) {
        divCounter = 0;
        keyFrame = nextKeyFrame;
        nextKeyFrame++;
      if(nextKeyFrame > maxRows) nextKeyFrame = 0;
      if(action[nextKeyFrame][12] == 127)actionMode=STOP;
        // サウンド出力
        if(!beep){
          if(action[keyFrame][13] == 1){
        ledcAttachPin(audPin, 12);
            ledcWriteNote(12,NOTE_C,4);
      }else if(action[keyFrame][13] == 2){
            ledcAttachPin(audPin, 12);
            ledcWriteNote(12,NOTE_G,4);
      }else if(action[keyFrame][13] == 0){
            ledcDetachPin(audPin);
      }
        }
      }
      // サーボ角度計算
      for(int i=0; i<12; i++) {
        tempAngles[i] = action[keyFrame][i] +
             int8_t((action[nextKeyFrame][i] - action[keyFrame][i])
                * divCounter / action[nextKeyFrame][12]);
      }
    }
    // サーボ信号出力
    for(i = 0; i < 12; i++) {
      ledcWrite(i, get_pulse_width(tempAngles[i] + offset[i]));
  }
    //delay(30);
    // サウンド出力
    if(beep) {
      if(bpCounter == 0)ledcWriteNote(12,NOTE_C,4);
    else if(bpCounter == 10)ledcWriteNote(12,NOTE_D,4);
      else if(bpCounter == 20)ledcWriteNote(12,NOTE_E,4);
      else if(bpCounter == 30){
      ledcDetachPin(audPin);
        beep = false;
      }
    }
  }
  // 動作・サウンド出力ここまで
}

// パルス幅計算
int get_pulse_width(int angle) {
  float pulseMs = MIN_SV_PULSE + 
    (MAX_SV_PULSE - MIN_SV_PULSE) * angle / 180;
  return (int)(65536 * (pulseMs * SV_FREQ /1000.0));
}
