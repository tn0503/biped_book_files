#define SV_FREQ 50 
#define MIN_SV_PULSE 0.6 
#define MAX_SV_PULSE 2.4

uint8_t sv0 = 32;

void setup() {
// put your setup code here, to run once: 
  ledcSetup(0, SV_FREQ, 16); 
  ledcAttachPin(sv0, 0);
}

void loop() {
// put your main code here, to run repeatedly:
  ledcWrite(0, get_pulse_width(70));
  delay(500);
  ledcWrite(0, get_pulse_width(110)); 
  delay(500); 
}

int get_pulse_width(int angle) { 
  float pulseMs = MIN_SV_PULSE + (MAX_SV_PULSE - MIN_SV_PULSE) * angle / 180; 
  return (int)(65536 * (pulseMs * SV_FREQ /1000.0));
}
