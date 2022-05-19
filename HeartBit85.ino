
//#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN PB0
#define NUMPIXELS 24
#define DELAYVAL 15
#define BTN_PIN PB1
#define MAX_ANIM_LOOPS 3

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//int animationLoops;
int r,g,b;
int animationLoops = 0;
int middlePixel=NUMPIXELS/2;

int currentAnim = 0;

void animation(int x);


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos, float brightness) {
  if(WheelPos < 85) {
   return pixels.Color((WheelPos * 3)*brightness, (255 - WheelPos * 3)*brightness, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return pixels.Color((255 - WheelPos * 3)*brightness, 0, (WheelPos * 3)*brightness);
  } else {
   WheelPos -= 170;
   return pixels.Color(0, (WheelPos * 3)*brightness, (255 - WheelPos * 3)*brightness);
  }
}

void clear() {
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();  
}

void playNextAnimation() {
    animation(currentAnim);
    currentAnim++;  
}

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  pinMode(BTN_PIN,INPUT_PULLUP);
  pixels.begin();
  clear();
}


void loop() {
  if(digitalRead(BTN_PIN)==LOW){
    playNextAnimation();
  }


  delay(10);
}


void animation(int x){

  switch(x){
    case 0:
      animationLoops = 0;
      r = 255;
      g = random(50,150);
      b = random(0,150);  
    
      while(animationLoops<MAX_ANIM_LOOPS){
        for(int i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(r, g, b));
          pixels.show();
          delay(DELAYVAL);
        }
        for(int i=NUMPIXELS; i>-1; i--) { // For each pixel...
          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
          pixels.show();
          delay(DELAYVAL);
        }  
        delay(1500);
        
        animationLoops++;
      }
      break;
      
    case 1:
      animationLoops = 0;
      r = 30;
      g = 0;
      b = 10;

    
      while(animationLoops<MAX_ANIM_LOOPS){

        
        for(int i=0; i<=NUMPIXELS/2; i++) {
          pixels.setPixelColor(middlePixel+i, pixels.Color(r, g, b));
          pixels.setPixelColor(middlePixel-i, pixels.Color(r, g, b));
          pixels.show();
          delay(DELAYVAL*2);
        }
        
        for(int i=0; i<=NUMPIXELS/2; i++) {
          pixels.setPixelColor(middlePixel+i, pixels.Color(0,0,0));
          pixels.setPixelColor(middlePixel-i, pixels.Color(0,0,0));
          pixels.show();
          delay(DELAYVAL);
        }  
        delay(1500);
        
        animationLoops++;
      }
    
      break;


    case 2:
      animationLoops = 0;
      r = 30;
      g = 0;
      b = 10;
      
    
      while(animationLoops<MAX_ANIM_LOOPS){

        
        for(int i=0; i<=NUMPIXELS/2; i++) {
          pixels.setPixelColor(middlePixel+i-2, pixels.Color(0,0,0));
          pixels.setPixelColor(middlePixel+i-1, pixels.Color(r/2, g/2, b/2));
          pixels.setPixelColor(middlePixel+i, pixels.Color(r, g, b));
          pixels.setPixelColor(middlePixel-i+2, pixels.Color(0,0,0));
          pixels.setPixelColor(middlePixel-i+1, pixels.Color(r/2, g/2, b/2));
          pixels.setPixelColor(middlePixel-i, pixels.Color(r, g, b));
          pixels.show();
          delay(DELAYVAL*2);
        }
        
        for(int i=0; i<=NUMPIXELS/2; i++) {
          pixels.setPixelColor(i-2, pixels.Color(0,0,0));
          pixels.setPixelColor(i-1, pixels.Color(r/2, g/2, b/2));
          pixels.setPixelColor(i, pixels.Color(r, g, b));
          pixels.setPixelColor(NUMPIXELS-1-i+2, pixels.Color(0,0,0));
          pixels.setPixelColor(NUMPIXELS-1-i+1, pixels.Color(r/2, g/2, b/2));
          pixels.setPixelColor(NUMPIXELS-1-i, pixels.Color(r, g, b));
          pixels.show();
          delay(DELAYVAL*2);
        }

        for(int i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(0,0,0));
        }
        pixels.show();
        
        delay(500);
        
        animationLoops++;
      }
    
      break;

    case 3:
      animationLoops = 0;

      while(animationLoops<MAX_ANIM_LOOPS){
        uint16_t i, j;
       

        for(i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, Wheel((i*13) & 255, 0.3));
          pixels.show();
          delay(DELAYVAL);
        }

        delay(100);

        for(i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(0,0,0));
          pixels.show();
          delay(DELAYVAL);
        }
        delay(1000);
               
        animationLoops++;
      }
      
               
      break;


    case 4:
      animationLoops = 0;

      uint16_t i, j;

      j = 1;
      while(animationLoops<MAX_ANIM_LOOPS*8){
        
       

        for(i=0; i<NUMPIXELS; i++) {
          if(i%2 == 0) {
            pixels.setPixelColor(i, Wheel((i*j)+30 & 255, 0.5));
          }
          else {
            pixels.setPixelColor(i, Wheel(((i-1)*j)+30 & 255, 0.2));
//            pixels.setPixelColor(i, pixels.Color(0,0,0));
          }
        }
        pixels.show();

        delay(100);

        for(i=0; i<NUMPIXELS; i++) {
          if(i%2 == 0) {
            pixels.setPixelColor(i, Wheel(((i-1)*j)+30 & 255, 0.2));
//            pixels.setPixelColor(i, pixels.Color(0,0,0));
          }
          else {
            pixels.setPixelColor(i, Wheel((i*j)+30 & 255, 0.5));
          }
        }
        pixels.show();

        delay(100);
               
        animationLoops++;
        j++;
      }


      clear();
      
               
      break;            
    case 5:
      currentAnim = 0;
      playNextAnimation();
      break;
    
  }



}
