
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


void setColorAndBrightness(int pixel, int r, int g, int b, float brightness) {
  pixels.setPixelColor(pixel, pixels.Color(r*brightness, g*brightness, b*brightness));
}


void pixelTurnOff(int pixel) {
  pixels.setPixelColor(pixel, pixels.Color(0,0,0));
}


void stripClear() {
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  // setColorAndBrightness(currentAnim, 255,0,0, 0.1); // TEMP
  pixels.show();  
}


void playNextAnimation() {
    playAnimation(currentAnim);
    stripClear();
}


void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  pinMode(BTN_PIN,INPUT_PULLUP);
  pixels.begin();
  stripClear();
}


void loop() {
  if(digitalRead(BTN_PIN)==LOW){
    playNextAnimation();
    delay(200);
  }

  delay(10);
}



void playAnimation(int x){
  uint16_t i, j;
  animationLoops = 0;
  r = 255;
  g = random(0,100);
  b = random(0,150);  

  switch(x){

    case 0:
    
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
    
      while(animationLoops<MAX_ANIM_LOOPS){
        
        for(i=0; i<=NUMPIXELS/2; i++) {
          setColorAndBrightness(middlePixel+i, r, g, b, 1);
          setColorAndBrightness(middlePixel-i, r, g, b, 1);
          pixels.show();
          delay(DELAYVAL*2);
        }
        
        for(i=0; i<=NUMPIXELS/2; i++) {
          pixelTurnOff(middlePixel+i);
          pixelTurnOff(middlePixel-i);
          pixels.show();
          delay(DELAYVAL);
        }

        delay(1500);
        
        animationLoops++;
      }
    
      break;


    case 2:
    
      while(animationLoops<MAX_ANIM_LOOPS){

        
        for(i=0; i<=NUMPIXELS/2; i++) {
          // animate right half (up->down)
          pixelTurnOff(middlePixel+i-3);
          setColorAndBrightness(middlePixel+i-2, r, g, b, 0.2);
          setColorAndBrightness(middlePixel+i-1, r, g, b, 0.5);
          setColorAndBrightness(middlePixel+i, r, g, b, 1);
          // animate left half (up->down)
          pixelTurnOff(middlePixel-i+3);
          setColorAndBrightness(middlePixel-i+2, r, g, b, 0.2);
          setColorAndBrightness(middlePixel-i+1, r, g, b, 0.5);
          setColorAndBrightness(middlePixel-i, r, g, b, 1);
          pixels.show();
          delay(DELAYVAL*2);
        }
        
        for(i=0; i<=NUMPIXELS/2; i++) {
          // animate right half (down->up)
          pixelTurnOff(i-3);
          setColorAndBrightness(i-2, r, g, b, 0.2);
          setColorAndBrightness(i-1, r, g, b, 0.5);
          setColorAndBrightness(i, r, g, b, 1);
          // animate left half (down->up)
          pixelTurnOff(NUMPIXELS-i+3);
          setColorAndBrightness(NUMPIXELS-i+2, r, g, b, 0.2);
          setColorAndBrightness(NUMPIXELS-i+1, r, g, b, 0.5);
          setColorAndBrightness(NUMPIXELS-i, r, g, b, 1);
          pixels.show();
          delay(DELAYVAL*2);
        }

        stripClear();
        delay(1000);
        animationLoops++;
      }
    
      break;

    case 3:


      while(animationLoops<MAX_ANIM_LOOPS){
     

        for(i=0; i<NUMPIXELS; i++) {
          pixels.setPixelColor(i, Wheel((i*13) & 255, 0.8));
          pixels.show();
          delay(DELAYVAL);
        }

        delay(100);

        for(i=0; i<NUMPIXELS; i++) {
          pixelTurnOff(i);
          pixels.show();
          delay(DELAYVAL);
        }
        delay(1000);
               
        animationLoops++;
      }
      
               
      break;


    case 4:


      j = 1;
      while(animationLoops<MAX_ANIM_LOOPS*8){
        
       

        for(i=0; i<NUMPIXELS; i++) {
          if(i%2 == 0) {
            pixels.setPixelColor(i, Wheel((i*j)+30 & 255, 0.8));
          }
          else {
            pixels.setPixelColor(i, Wheel(((i-1)*j)+30 & 255, 0.3));
          }
        }
        pixels.show();

        delay(100);

        for(i=0; i<NUMPIXELS; i++) {
          if(i%2 == 0) {
            pixels.setPixelColor(i, Wheel(((i-1)*j)+30 & 255, 0.2));
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

      
      
               
      break;    
      
              
    case 5:
      
      // heart beat

      while(animationLoops<MAX_ANIM_LOOPS){
        
        // fade in
        for(j=1; j<NUMPIXELS; j++) {
          for(i=0; i<NUMPIXELS; i++) {
            setColorAndBrightness(i, r, g, b, ((float)j/(float)NUMPIXELS));
          }
          pixels.show();
          delay(2);
        }

        // fade out
        for(j=NUMPIXELS; j>0; j--) {
          for(i=0; i<NUMPIXELS; i++) {
            setColorAndBrightness(i, r, g, b, ((float)j/(float)NUMPIXELS));
          }
          pixels.show();
          delay(2);
        }

        // fade in
        for(j=1; j<NUMPIXELS; j++) {
          for(i=0; i<NUMPIXELS; i++) {
            setColorAndBrightness(i, r, g, b, ((float)j/(float)NUMPIXELS));
          }
          pixels.show();
          delay(2);
        }

        // fade out
        for(j=NUMPIXELS; j>0; j--) {
          for(i=0; i<NUMPIXELS; i++) {
            setColorAndBrightness(i, r, g, b, ((float)j/(float)NUMPIXELS));
          }
          pixels.show();
          delay(15);
        }        

        stripClear();
        delay(500);

        animationLoops++;
      }
      break;
    


    case 6:


      // for(int x=0; x<NUMPIXELS; x++) {
      //   setColorAndBrightness(x, 255,0,0, 1);
      //   // pixels.setPixelColor(x, pixels.Color(r, g, b));
      //   pixels.show();
      //   delay(DELAYVAL);
      // }

      for(int j=0; j<=NUMPIXELS/2; j++) {

        for(int i=0; i<=NUMPIXELS/2; i++) {
          // animate left half (up->down)
          setColorAndBrightness(middlePixel-i, r, g, b, 1);
          if((NUMPIXELS/2)-i > j) pixelTurnOff(middlePixel-i+1);
          pixels.show();
          delay(DELAYVAL);
        }
        // delay(DELAYVAL);

        for(int i=0; i<=NUMPIXELS/2; i++) {
          // animate right half (up->down)
          setColorAndBrightness(middlePixel+i, r, g, b, 1);
          if(i < (NUMPIXELS/2)-j) pixelTurnOff(middlePixel+i-1);
          pixels.show();
          delay(DELAYVAL);
        }
        // delay(DELAYVAL);

      }

      delay(1000);
    
      break;

    case 7:

      int p=0;
      int currentPixel;

      
      for(i=0; i<(NUMPIXELS*3)+1; i++) {
        currentPixel = i%NUMPIXELS;

        p = currentPixel-5 >= 0 ? currentPixel-5 : (currentPixel-5)+NUMPIXELS;
        pixelTurnOff(p);

        p = currentPixel-4 >= 0 ? currentPixel-4 : (currentPixel-4)+NUMPIXELS;
        setColorAndBrightness(p, r, g, b, 0.1);

        p = currentPixel-3 >= 0 ? currentPixel-3 : (currentPixel-3)+NUMPIXELS;
        setColorAndBrightness(p, r, g, b, 0.2);

        p = currentPixel-2 >= 0 ? currentPixel-2 : (currentPixel-2)+NUMPIXELS;
        setColorAndBrightness(p, r, g, b, 0.4);

        p = currentPixel-1 >= 0 ? currentPixel-1 : (currentPixel-1)+NUMPIXELS;
        setColorAndBrightness(p, r, g, b, 0.6);

        setColorAndBrightness(currentPixel, r, g, b, 1);

        pixels.show();
        delay(40);
      }
      


    
      break;





    case 8:


      currentAnim = 0;
      playAnimation(0);
      break;    
  }

  currentAnim++;


}
