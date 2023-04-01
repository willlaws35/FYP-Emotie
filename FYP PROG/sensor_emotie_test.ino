#include <Servo.h>
#include <Stepper.h>
#include <Adafruit_NeoPixel.h>
#include <DFRobot_DF1201S.h>
#include <SoftwareSerial.h>

#define PIN 6
#define PINMIN 6
#define NUMPIXELS 24
#define NUMPIXELSMIN 24

int delayval = 50;
const int stepsPerRevolution = 200;
int pos = 0; 

int echoPinR = 53;
int trigPinR = 52;
int echoPin = 51;
int trigPin = 50;
int echoPinL = 49;    
int trigPinL = 48;

float lowest = 0;

//reye = 10, leye = 9
Servo REYE, LEYE;
Stepper myStepper = Stepper(stepsPerRevolution, 2,3,4,5);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelsMIN = Adafruit_NeoPixel(NUMPIXELSMIN, PINMIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial DF1201SSerial(12, 13);  //RX  TX
DFRobot_DF1201S DF1201S;

float duration_usR, distance_cmR, duration_us, distance_cm,
duration_usL, distance_cmL;

void setup() {

  Serial.begin(115200);
  DF1201SSerial.begin(115200);
  pixels.begin();
  pixelsMIN.begin();

  REYE.attach(10);
  LEYE.attach(9);
  myStepper.setSpeed(10);

    while(!DF1201S.begin(DF1201SSerial)){
    Serial.println("Init failed, please check the wire connection!");
    delay(1000);
  }
  /*Set volume to 20*/
  DF1201S.setVol(/*VOL = */20);
  Serial.print("VOL:");
  /*Get volume*/
  Serial.println(DF1201S.getVol());
  DF1201S.switchFunction(DF1201S.MUSIC);

  
  pinMode(trigPinR, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinR, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(echoPinL, INPUT);

  for(int i=0;i<NUMPIXELSMIN;i++)
  {
    pixelsMIN.setPixelColor(i, pixelsMIN.Color(0,8,3)); 
    delay(125);
    pixelsMIN.show(); 
  }
  delay(500);
  
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(8,0,0)); 
    delay(125);
    pixels.show(); 
  }
  delay(500);
  
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(0,8,0)); 
    delay(125);
    pixels.show(); 
  }
  delay(500);
  
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(0,0,8)); 
    delay(125);
    pixels.show(); 
  }
  delay(500);
  
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(8,8,8)); 
    delay(125);
    pixels.show(); 
  }
  delay(500);
  REYE.write(180);
  LEYE.write(0);
  delay(1000);
  REYE.write(0);
  delay(750);
  LEYE.write(180);
  delay(750);
  REYE.write(180);
  delay(750);
  LEYE.write(0);
  }

void loop() {
  
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  duration_usR = pulseIn(echoPinR, HIGH);
  distance_cmR = 0.017 * duration_usR;
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration_us = pulseIn(echoPin, HIGH);
  distance_cm = 0.017 * duration_us;
   
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  duration_usL = pulseIn(echoPinL, HIGH);
  distance_cmL = 0.017 * duration_usL;

  Serial.print("distance RIGHT: ");
  Serial.print(distance_cmR);
  Serial.print(" cm ");
  Serial.print("distance MID: ");
  Serial.print(distance_cm);
  Serial.print(" cm ");
  Serial.print("distance LEFT: ");
  Serial.print(distance_cmL);
  Serial.print(" cm ");
  delay(500);

 
  if(distance_cm<distance_cmR){
    if (distance_cm<distance_cmL){
      Serial.print("MID LOW");
      lowest = 2;
    }
  }
  if(distance_cmR<distance_cm){
    if(distance_cmR<distance_cmL){
      Serial.print("RIGHT LOW");
      lowest = 1;
    }
  }
  if(distance_cmL<distance_cm){
    if(distance_cmL<distance_cmR){
      Serial.print("LEFT LOW");
      lowest = 3;
    }
  }
  
  Serial.println(lowest);
  if (lowest==1){
    if (distance_cmR < 75){
       for(int i=0;i<NUMPIXELS;i++)
       {
         pixels.setPixelColor(i, pixels.Color(0,8,0)); 
         delay(20);
         pixels.show(); 
      }
        myStepper.step(-23);
        delay(150);
          Serial.println("Start playing");
  /*Start playing*/
  DF1201S.start();
  delay(2000);
  Serial.println("Pause");
  /*Pause*/
  DF1201S.pause();
        myStepper.step(24);
        delay(150);
        //right sensor turn left
    }
       for(int i=0;i<NUMPIXELS;i++)
     {
       pixels.setPixelColor(i, pixels.Color(8,8,8)); 
       delay(20);
       pixels.show(); 
     }
  }
  if (lowest==2){
    if (distance_cm<100){
    delay(300);
     for(int i=0;i<NUMPIXELS;i++)
     {
       pixels.setPixelColor(i, pixels.Color(0,0,8)); 
       delay(20);
       pixels.show(); 
     }
              Serial.println("Start playing");
  /*Start playing*/
  DF1201S.start();
  delay(2000);
  Serial.println("Pause");
  /*Pause*/
  DF1201S.pause();
  //both up and down symmetry
  for (pos = 0; pos <= 180; pos += 1) {
    // in steps of 1 degree
    LEYE.write(pos);              
    delay(3);                     
    REYE.write(180-pos);
    delay(3);
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    LEYE.write(pos);              
    delay(3);                     
    REYE.write(180-pos);
    delay(3);
  }
      //centre motor
    }
       for(int i=0;i<NUMPIXELS;i++)
     {
       pixels.setPixelColor(i, pixels.Color(8,8,8)); 
       delay(20);
       pixels.show(); 
     }
     lowest = 0;
  }
  if (lowest==3){
    if (distance_cmL < 40){
       for(int i=0;i<NUMPIXELS;i++)
     {
       pixels.setPixelColor(i, pixels.Color(8,0,0)); 
       delay(20);
       pixels.show(); 
     }
      myStepper.step(27);
      delay(150);
        Serial.println("Start playing");
  /*Start playing*/
  DF1201S.start();
  delay(2000);
  Serial.println("Pause");
  /*Pause*/
  DF1201S.pause();
      myStepper.step(-24);
      delay(150);
      //left sensor turn right
    }
       for(int i=0;i<NUMPIXELS;i++)
     {
       pixels.setPixelColor(i, pixels.Color(8,8,8)); 
       delay(20);
       pixels.show(); 
     }
     lowest = 0;
  }

}
