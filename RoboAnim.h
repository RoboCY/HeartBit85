#include <Adafruit_NeoPixel.h>

#define LED_PIN PB0
#define NUMPIXELS 24
#define BRIGHTNESS 0.5 // 0-1

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
        pixels.setPixelColor(pixel, pixels.Color(r*brightness*BRIGHTNESS, g*brightness*BRIGHTNESS, b*brightness*BRIGHTNESS));
    }


    void pixelTurnOff(int pixel) {
        pixels.setPixelColor(pixel, pixels.Color(0,0,0));
    }


    void stripClear() {
        for(int i=0; i<numPixels; i++) {
            pixelTurnOff(i);
        }
        pixels.show();  
    }


    void stripFadeOut() {
        for(int j=0; j<8; j++) {
            for(int i=0; i<numPixels; i++) {
                pixelPaint(i, 1-((float)j/(float)10));
            }
            pixels.show();
            delay(20);
        }        
    }


    uint32_t wheel(byte wheelPos, float brightness) {
        if(wheelPos < 85) {
            return pixels.Color((wheelPos * 3)*brightness*BRIGHTNESS, (255 - wheelPos * 3)*brightness*BRIGHTNESS, 0);
        } 
        else if(wheelPos < 170) {
            wheelPos -= 85;
            return pixels.Color((255 - wheelPos * 3)*brightness*BRIGHTNESS, 0, (wheelPos * 3)*brightness*BRIGHTNESS);
        }
        else {
            wheelPos -= 170;
            return pixels.Color(0, (wheelPos * 3)*brightness*BRIGHTNESS, (255 - wheelPos * 3)*brightness*BRIGHTNESS);
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




    void anim1() {
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




    void anim2() {
        generateRandomColor();
        int randPixel = 0;
        int animationLoops = 0;
        while(animationLoops<2){
            int affectedPixels[numPixels];
            for(int i=0; i<numPixels; i++) {
                bool duplicate = false;
                do {
                    randPixel = random(0,numPixels);
                    bool found = false;
                    for (int x = 0; x < numPixels; x++) {
                        if (randPixel == affectedPixels[x]) {
                            found = true;
                            break;
                        }
                    }
                    duplicate = found;
                }
                while(duplicate);
                if(animationLoops == 0) pixelPaint(randPixel, 1);
                else pixelTurnOff(randPixel);
                pixels.show();
                affectedPixels[i] = randPixel;
                delay(60);
            }
            delay(1000);
            memset(affectedPixels, 99, sizeof(affectedPixels));
            animationLoops++;
        }
    }




    void anim3() {
        generateRandomColor();
        int animationLoops = 0;
        while(animationLoops<6){
            // fade in evens
            for(int j=1; j<numPixels; j++) {
                for(int i=0; i<numPixels; i++) {
                    if(i%2 == 0) {
                        pixelPaint(i, ((float)j/(float)numPixels));
                    }
                    else {
                        pixelPaint(i, 1-((float)j/(float)numPixels));
                    }
                }
                pixels.show();
                delay(2);
            }
            // fade out evens
            for(int j=1; j<numPixels; j++) {
                for(int i=0; i<numPixels; i++) {
                    if(i%2 == 0) {
                        pixelPaint(i, 1-((float)j/(float)numPixels));
                    }
                    else {
                        pixelPaint(i, ((float)j/(float)numPixels));
                    }
                }
                pixels.show();
                delay(2);
            }
            animationLoops++;
        }
        stripFadeOut();
    }




    void anim4() {
        generateRandomColor();
        for(int i=0; i<numPixels; i++) {
            if(i%2 == 0) {
                pixelPaint(i, 1);
                pixels.show();
                delay(80);
            }
        }
        for(int i=numPixels; i>0; i--) {
            if(i%2 == 1) {
                pixelPaint(i, 1);
                pixels.show();
                delay(80);
            }
        }
        delay(200);
        int animationLoops = 0;
        while(animationLoops<3){
            for(int j=0; j<10; j++) {
                for(int i=0; i<numPixels; i++) {
                    pixelPaint(i, 1-((float)j/(float)10));
                }
                pixels.show();
                delay(10);
            }            
            delay(100);
            for(int j=0; j<10; j++) {
                for(int i=0; i<numPixels; i++) {
                    pixelPaint(i, (float)j/(float)10);
                }
                pixels.show();
                delay(10);
            }     
            delay(100);
            animationLoops++;
        }
        delay(200);
        stripFadeOut();
    }




    void anim5() {
        generateRandomColor();
        int trips = 1;
        while(trips<numPixels+1){
            for(int i=0; i<numPixels; i++) {
                pixelPaint(i, 1);
                pixelTurnOff(i-trips);
                pixels.show();
                // delay(60-(trips*4));
                // delay((numPixels-trips)*0.6);
                // delay(80 * (1/((float)trips/2))));
                delay((numPixels-trips)*(1/((float)trips/4)));
            }
            trips++;
            for(int i=numPixels; i>-1; i--) {
                pixelPaint(i, 1);
                pixelTurnOff(i+trips);
                pixels.show();
                // delay(60-(trips*4));
                // delay(80 * (1/((float)trips/2))));
                // delay((numPixels-trips)*0.6);
                delay((numPixels-trips)*(1/((float)trips/4)));
            }
            trips++;
        }
        delay(1000);
        stripFadeOut();     
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
        stripFadeOut();
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




    void anim8() {
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




    void anim9() {
        int animationLoops = 0;
        while(animationLoops<3){
            for(int i=0; i<numPixels; i++) {
                pixels.setPixelColor(i, wheel((i*13) & 255, 0.8));
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
}