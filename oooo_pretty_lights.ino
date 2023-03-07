#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 24


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  pixels.begin();
  for (int j=0; j<=25; j++){
    for (int i=0;i<=24; i++){
    pixels.setPixelColor(i, pixels.Color(j,0,0));
    pixels.show();
    }
      delay(1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int k=0; k<=25; k++){
     for (int i=0;i<=24; i++){
    pixels.setPixelColor(i, pixels.Color(k+25,k,0));
    pixels.show();
     }
       delay(1);
  }
  for (int l=0; l<=25; l++){
       for (int i=0;i<=24; i++){
    pixels.setPixelColor(i, pixels.Color(50-(l*2),25+l,0));
    pixels.show();
     }
       delay(1);
  }
  for (int m=0; m<=25; m++){
       for (int i=0;i<=24; i++){
    pixels.setPixelColor(i, pixels.Color(0,50,m));
    pixels.show();
     }
       delay(1);
  }
  for (int n=0; n<=25; n++){
       for (int i=0;i<=24; i++){
    pixels.setPixelColor(i, pixels.Color(0,50-(n*2),25+n));
    pixels.show();
     }
       delay(1);
  }
   for (int o=0; o<=25; o++){
       for (int i=0;i<=24; i++){
    pixels.setPixelColor(i, pixels.Color(o,0,50-(o*2)));
    pixels.show();
     }
       delay(1);
  }
}
