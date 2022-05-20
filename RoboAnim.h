#include <Adafruit_NeoPixel.h>

#define LED_PIN PB0
#define BTN_PIN PB1
#define NUMPIXELS 24

namespace RoboAnim {

    /**********************/
    /******** INIT ********/
    /**********************/

    Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

    int numPixels = 0;
    int middlePixel = 0;
    int r,g,b;

    void init() {
        pixels.begin();
        numPixels = pixels.numPixels();
        middlePixel = numPixels/2;
    }


    /************************/
    /*** HELPER FUNCTIONS ***/
    /************************/

    void pixelPaint(int pixel, float brightness) {
        pixels.setPixelColor(pixel, pixels.Color(r*brightness, g*brightness, b*brightness));
    }


    void pixelTurnOff(int pixel) {
        pixels.setPixelColor(pixel, pixels.Color(0,0,0));
    }


    void stripClear() {
        for(int i=0; i<numPixels; i++) {
            pixels.setPixelColor(i, pixels.Color(0,0,0));
        }
        pixels.show();  
    }


    uint32_t Wheel(byte WheelPos, float brightness) {
        if(WheelPos < 85) {
            return pixels.Color((WheelPos * 3)*brightness, (255 - WheelPos * 3)*brightness, 0);
        } 
        else if(WheelPos < 170) {
            WheelPos -= 85;
            return pixels.Color((255 - WheelPos * 3)*brightness, 0, (WheelPos * 3)*brightness);
        }
        else {
            WheelPos -= 170;
            return pixels.Color(0, (WheelPos * 3)*brightness, (255 - WheelPos * 3)*brightness);
        }
    }


    void generateRandomColor() {
        r = 255;
        g = random(0,100);
        b = (r+g > 300) ? random(0,40) : random(0,100);
    }



    /***********************/
    /* ANIMATION FUNCTIONS */
    /***********************/


    void anim0() {
        generateRandomColor();
        int trips = 1;
        while(trips<numPixels+1){
            for(int i=0; i<numPixels; i++) {
                pixelPaint(i, 1);
                pixelTurnOff(i-trips);
                pixels.show();
                delay(numPixels-trips);
            }
            trips++;
            for(int i=numPixels; i>-1; i--) {
                pixelPaint(i, 1);
                pixelTurnOff(i+trips);
                pixels.show();
                delay(numPixels-trips);
            }  
            // delay(10);
            trips++;
        }
        delay(1000);    
    }




    void anim1() {
        generateRandomColor();
        int animationLoops = 0;
        while(animationLoops<3){
            for(int i=0; i<=middlePixel; i++) {
                pixelPaint(middlePixel+i, 1);
                pixelPaint(middlePixel-i, 1);
                pixels.show();
                delay(30);
            }
            for(int i=0; i<=middlePixel; i++) {
                pixelTurnOff(middlePixel+i);
                pixelTurnOff(middlePixel-i);
                pixels.show();
                delay(30);
            }
            delay(1000);
            animationLoops++;
        }    
    }




    void anim2() {
        generateRandomColor();
        int animationLoops = 0;
        while(animationLoops<3){
            for(int i=0; i<=numPixels/2; i++) {
                // animate right half (up->down)
                pixelTurnOff(middlePixel+i-3);
                pixelPaint(middlePixel+i-2, 0.2);
                pixelPaint(middlePixel+i-1, 0.5);
                pixelPaint(middlePixel+i, 1);
                // animate left half (up->down)
                pixelTurnOff(middlePixel-i+3);
                pixelPaint(middlePixel-i+2, 0.2);
                pixelPaint(middlePixel-i+1, 0.5);
                pixelPaint(middlePixel-i, 1);
                pixels.show();
                delay(30);
            }     
            for(int i=0; i<=numPixels/2; i++) {
                // animate right half (down->up)
                pixelTurnOff(i-3);
                pixelPaint(i-2, 0.2);
                pixelPaint(i-1, 0.5);
                pixelPaint(i, 1);
                // animate left half (down->up)
                pixelTurnOff(numPixels-i+3);
                pixelPaint(numPixels-i+2, 0.2);
                pixelPaint(numPixels-i+1, 0.5);
                pixelPaint(numPixels-i, 1);
                pixels.show();
                delay(30);
            }
            stripClear();
            delay(1000);
            animationLoops++;
        }
    }  




    void anim3() {
        int animationLoops = 0;
        while(animationLoops<3){
            for(int i=0; i<numPixels; i++) {
                pixels.setPixelColor(i, Wheel((i*13) & 255, 0.8));
                pixels.show();
                delay(15);
            }
            delay(300);
            for(int i=0; i<numPixels; i++) {
                pixelTurnOff(i);
                pixels.show();
                delay(15);
            }
            delay(1000);
            animationLoops++;
        }
    }




    void anim4() {
        int j = 1;
        int animationLoops = 0;
        while(animationLoops<18){
            for(int i=0; i<numPixels; i++) {
                if(i%2 == 0) {
                    pixels.setPixelColor(i, Wheel((i*j)+30 & 255, 0.8));
                }
                else {
                    pixels.setPixelColor(i, Wheel(((i-1)*j)+30 & 255, 0.3));
                }
            }
            pixels.show();
            delay(100);
            for(int i=0; i<numPixels; i++) {
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
    }




    void anim5() {
        generateRandomColor();
        int animationLoops = 0;
        while(animationLoops<3){
            // fade in
            for(int j=1; j<numPixels; j++) {
                for(int i=0; i<numPixels; i++) {
                    pixelPaint(i, ((float)j/(float)numPixels));
                }
                pixels.show();
                delay(2);
            }
            // fade out
            for(int j=numPixels; j>0; j--) {
                for(int i=0; i<numPixels; i++) {
                    pixelPaint(i, ((float)j/(float)numPixels));
                }
                pixels.show();
                delay(2);
            }
            // fade in
            for(int j=1; j<numPixels; j++) {
                for(int i=0; i<numPixels; i++) {
                    pixelPaint(i, ((float)j/(float)numPixels));
                }
                pixels.show();
                delay(2);
            }
            // fade out
            for(int j=numPixels; j>0; j--) {
                for(int i=0; i<numPixels; i++) {
                    pixelPaint(i, ((float)j/(float)numPixels));
                }
                pixels.show();
                delay(10);
            }
            stripClear();
            delay(500);
            animationLoops++;
        }
    }




    void anim6() {
        generateRandomColor();
        for(int j=0; j<=numPixels/2; j++) {
            for(int i=0; i<=numPixels/2; i++) {
                // animate left half (up->down)
                pixelPaint(middlePixel-i, 1);
                if((numPixels/2)-i > j) pixelTurnOff(middlePixel-i+1);
                pixels.show();
                delay(10);
            }
            for(int i=0; i<=numPixels/2; i++) {
                // animate right half (up->down)
                pixelPaint(middlePixel+i, 1);
                if(i < (numPixels/2)-j) pixelTurnOff(middlePixel+i-1);
                pixels.show();
                delay(10);
            }
        }
        delay(500);
    }




    void anim7() {
        generateRandomColor();
        int p=0;
        int currentPixel;
        for(int i=0; i<(numPixels*3)+1; i++) {
            currentPixel = i%numPixels;
            p = currentPixel-5 >= 0 ? currentPixel-5 : (currentPixel-5)+numPixels;
            pixelTurnOff(p);
            p = currentPixel-4 >= 0 ? currentPixel-4 : (currentPixel-4)+numPixels;
            pixelPaint(p, 0.1);
            p = currentPixel-3 >= 0 ? currentPixel-3 : (currentPixel-3)+numPixels;
            pixelPaint(p, 0.2);
            p = currentPixel-2 >= 0 ? currentPixel-2 : (currentPixel-2)+numPixels;
            pixelPaint(p, 0.4);
            p = currentPixel-1 >= 0 ? currentPixel-1 : (currentPixel-1)+numPixels;
            pixelPaint(p, 0.6);
            pixelPaint(currentPixel, 1);
            pixels.show();
            delay(40);
        }
    }


}