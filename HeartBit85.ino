
#include <Adafruit_NeoPixel.h>
#include "RoboAnim.h"
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN PB0
#define BTN_PIN PB1
#define NUMPIXELS 24

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
int currentAnim = 0;


void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  pinMode(BTN_PIN,INPUT_PULLUP);
  pixels.begin();
  RoboAnim::init(&pixels);
  RoboAnim::stripClear();
}


void loop() {
  if(digitalRead(BTN_PIN)==LOW){
    playAnimation(currentAnim);
    delay(100);
  }
  delay(10);
}


void playAnimation(int x){
  switch(x){
    case 0:
      RoboAnim::anim0();
      break;
    case 1:
      RoboAnim::anim1();
      break;
    case 2:
      RoboAnim::anim2();
      break;
    case 3:
      RoboAnim::anim3();  
      break;
    case 4:
      RoboAnim::anim4();
      break;
    case 5:
      RoboAnim::anim5();
      break;
    case 6:
      RoboAnim::anim6();
      break;
    case 7:
      RoboAnim::anim7();
      break;
    default:
      currentAnim = -1;
      break;    
  }
  RoboAnim::stripClear();
  currentAnim++;
}
