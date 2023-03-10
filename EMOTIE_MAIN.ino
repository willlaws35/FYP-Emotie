//  ___       ___
// /   \     /   \
//|     |---|     |
// \___/     \___/
//
 //  L     R


//9 = blue = REYE
//10 = green = LEYE
//47 = green = LBROW1
//46 = blue = RBROW2
//45 = green = LBROW2
//44 = blue = RBROW1

#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <Servo.h>
#include <Stepper.h>
#include <ezButton.h>
#include <Adafruit_GFX.h>
#include <SoftwareSerial.h>
#include <DFRobot_DF1201S.h> 
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 24
#define NUMPIXELSMIN 24
#define LOGO_HEIGHT   64
#define LOGO_WIDTH    128
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C


Sd2Card card;
SdVolume volume;
SdFile root;

int pos = 0;
int delayval = 50;
int calibrated = 0;

int echoPin = 37;
int trigPin = 36;
int echoPinL = 39;    
int trigPinL = 38;
int echoPinR = 35;
int trigPinR = 34;


const int chipSelect = 53;
const int stepsPerRevolution = 200;

const unsigned char boswin_test [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xc0, 0x0f, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x4f, 0xdf, 0xef, 0xcb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x67, 0x13, 0x23, 0x9b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x53, 0x53, 0x2b, 0x2b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x48, 0x5f, 0xe8, 0x4b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x80, 0x07, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xf0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0x6f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0x6f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0x6f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1b, 0x60, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfb, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x03, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7c, 0xff, 0x9e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7c, 0xff, 0x9e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7c, 0xff, 0x9e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7c, 0xff, 0x9e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x44, 0xff, 0x9e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x44, 0xff, 0x9e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x44, 0xff, 0x9e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x44, 0xf3, 0x9e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x44, 0xf3, 0x9e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x44, 0xf3, 0x9e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xf3, 0x9e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xf8, 0x3e, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x80, 0x7f, 0xff, 0x8f, 0xff, 0xff, 0xe7, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x8e, 0x3f, 0xff, 0x8f, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x8e, 0x3f, 0xff, 0x8f, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x8e, 0x3e, 0x0f, 0x80, 0xfe, 0x0f, 0x80, 0x7c, 0x1f, 0xe0, 0x3c, 0x07, 0xff, 0xff, 
  0xff, 0xff, 0x80, 0x7c, 0xe7, 0x86, 0x3c, 0xe7, 0xe7, 0xff, 0x1f, 0xc7, 0xf8, 0xe3, 0xff, 0xff, 
  0xff, 0xff, 0x81, 0xf8, 0xe3, 0x8e, 0x38, 0xe3, 0xe7, 0xff, 0x1f, 0x8f, 0xf8, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x89, 0xf8, 0xe3, 0x8e, 0x38, 0xe3, 0xe7, 0xff, 0x1f, 0x8f, 0xfc, 0x1f, 0xff, 0xff, 
  0xff, 0xff, 0x88, 0xf8, 0xe3, 0x8e, 0x38, 0xe3, 0xe7, 0xff, 0x1f, 0x8f, 0xff, 0x07, 0xff, 0xff, 
  0xff, 0xff, 0x8c, 0x78, 0xe3, 0x8e, 0x38, 0xe3, 0xe7, 0xff, 0x1f, 0x8f, 0xff, 0xc7, 0xff, 0xff, 
  0xff, 0xff, 0x8c, 0x78, 0xe3, 0x8e, 0x38, 0xe3, 0xe7, 0xff, 0x1f, 0x8f, 0xff, 0xe3, 0xff, 0xff, 
  0xff, 0xff, 0x8e, 0x3c, 0xe7, 0x86, 0x3c, 0xe7, 0xe6, 0x3f, 0x1f, 0xc7, 0xf9, 0xe3, 0xff, 0xff, 
  0xff, 0xff, 0x8e, 0x3e, 0x0f, 0x80, 0xfe, 0x0f, 0xf0, 0x7c, 0x07, 0xe0, 0x3c, 0x07, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 1040)
const int epd_bitmap_allArray_LEN = 1;
const unsigned char* epd_bitmap_allArray[1] = {
  boswin_test
};

float lowest = 0, duration_usR, distance_cmR, duration_us, 
      distance_cm, duration_usL, distance_cmL;

File myFile;
DFRobot_DF1201S DF1201S;
SoftwareSerial BLE(14,15); // TX RX
SoftwareSerial DF1201SSerial(12, 13);
ezButton toggleSwitch(18), LOWPOW(7);
Stepper myStepper = Stepper(stepsPerRevolution, 2,3,4,5);
Servo REYE, LEYE, RBROW1, RBROW2, LBROW1, LBROW2, calibrate;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelsMIN = Adafruit_NeoPixel(NUMPIXELSMIN, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void testdrawbitmap(void) {
  Serial.println("testing1");
  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
   boswin_test, LOGO_WIDTH, LOGO_HEIGHT, 1);
   Serial.println("testing2");
  display.display();
  delay(1000);
}

void setup() {

  Serial.begin(115200);
  DF1201SSerial.begin(115200);
  BLE.begin(9600);
  pixels.begin();
  pixelsMIN.begin();
  
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  display.invertDisplay(true);
  delay(1000);
  testdrawbitmap();

  for (int i=0; i<=12; i++){
    pixels.setPixelColor(12-i, pixels.Color(00,0,50));
    pixels.setPixelColor(12+i, pixels.Color(0,0,50));
    delay(125);
    pixels.show();
  }
  delay(7500);
  pixels.setPixelColor(0, pixels.Color(0,0,0)); 
  delay(125);
  pixels.show();
  for (int i=12;i>=0;i--){
    pixels.setPixelColor(12-i, pixels.Color(0,0,0));
    pixels.setPixelColor(i+12, pixels.Color(0,0,0));
    delay(125);
    pixels.show();
  }
  while (!Serial) {
  }


  Serial.print("\nInitializing SD card...");
  BLE.print("Initializing");
  delay(50);
  BLE.print("SD card...");
  
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    BLE.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    BLE.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    BLE.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    BLE.println("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
    BLE.println("Wiring is correct");
    delay(50);
    BLE.println("and a card");
    delay(50);
    BLE.println("is present.");
    delay(50);
    
  }

  // print the type of card
  Serial.println();
  BLE.println();
  Serial.print("Card type:         ");
  BLE.print("Card type:         ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      BLE.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      BLE.print("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      BLE.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
      BLE.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    BLE.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (1);
  }

  Serial.print("Clusters:          ");
  BLE.print("Clusters:          ");
  Serial.println(volume.clusterCount());
  BLE.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  ");
  BLE.print("Blocks x Cluster:  ");
  Serial.println(volume.blocksPerCluster());
  BLE.println(volume.blocksPerCluster());

  Serial.print("Total Blocks:      ");
  BLE.print("Total Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  BLE.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();
  BLE.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  BLE.print("Volume type is:    FAT");
  Serial.println(volume.fatType(), DEC);
  BLE.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  Serial.print("Volume size (Kb):  ");
  BLE.print("Volume size (Kb):  ");
  Serial.println(volumesize);
  BLE.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  BLE.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  BLE.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  BLE.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);
  BLE.println((float)volumesize / 1024.0);


//file making test
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
    BLE.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
    BLE.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
    BLE.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
      BLE.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
    BLE.println("error opening test.txt");
  }

  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  BLE.println("\nFiles found on the card (name, date and size in bytes): ");

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);

  delay(5000);
  toggleSwitch.setDebounceTime(50);

  REYE.attach(10);
  LEYE.attach(9);
  RBROW1.attach(44);
  LBROW1.attach(47);
  RBROW2.attach(46);
  LBROW2.attach(45);
  calibrate.attach(8);
  myStepper.setSpeed(10);

    while(!DF1201S.begin(DF1201SSerial)){
    Serial.println("Init failed, please check the wire connection!");
    BLE.println("Init failed, please check the wire connection!");
    delay(1000);
  }
  /*Set volume to 20*/
  DF1201S.setVol(/*VOL = */20);
  Serial.print("VOL:");
  BLE.println("VOL:");
  /*Get volume*/
  Serial.println(DF1201S.getVol());
  BLE.println(DF1201S.getVol());
  DF1201S.switchFunction(DF1201S.MUSIC);

  
  pinMode(trigPinR, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinR, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(echoPinL, INPUT);
  //servo format
  REYE.write(180);
  LEYE.write(0);
  delay(500);
  RBROW1.write(180);
  LBROW1.write(0);
  delay(500);
  RBROW2.write(0);
  LBROW2.write(180);
  delay(500);
  
 
 // red pixel loop
  pixels.begin();
  pixels.setPixelColor(12, pixels.Color(50,0,0)); 
  delay(125);
  pixels.show();
  for (int i=0;i<=12;i++){
    pixels.setPixelColor(12-i, pixels.Color(50,0,0));
    pixels.setPixelColor(12+i, pixels.Color(50,0,0));
    delay(125);
    pixels.show();
  }
  delay(250);  
  pixels.setPixelColor(0, pixels.Color(0,0,0)); 
  delay(125);
  pixels.show();
  for (int i=12;i>=0;i--){
    pixels.setPixelColor(12-i, pixels.Color(0,0,0));
    pixels.setPixelColor(i+12, pixels.Color(0,0,0));
    delay(125);
    pixels.show();
  }
  delay(250); 
  
  //green pixel loop
  Serial.begin(9600);
  pixels.begin();
  pixels.setPixelColor(12, pixels.Color(0,50,0)); 
  delay(125);
  pixels.show();
  for (int i=0;i<=12;i++){
    pixels.setPixelColor(12-i, pixels.Color(0,50,0));
    pixels.setPixelColor(12+i, pixels.Color(0,50,0));
    delay(125);
    pixels.show();
  }
  delay(250);  
  pixels.setPixelColor(0, pixels.Color(0,0,0)); 
  delay(125);
  pixels.show();
  for (int i=12;i>=0;i--){
    pixels.setPixelColor(12-i, pixels.Color(0,0,0));
    pixels.setPixelColor(i+12, pixels.Color(0,0,0));
    delay(125);
    pixels.show();
  }
  delay(250);
  
  //blue pixel loop
  Serial.begin(9600);
  pixels.begin();
  pixels.setPixelColor(12, pixels.Color(0,0,50)); 
  delay(125);
  pixels.show();
  for (int i=0;i<=12;i++){
    pixels.setPixelColor(12-i, pixels.Color(0,0,50));
    pixels.setPixelColor(12+i, pixels.Color(0,0,50));
    delay(125);
    pixels.show();
  }
  delay(250);  
  pixels.setPixelColor(0, pixels.Color(0,0,0)); 
  delay(125);
  pixels.show();
  for (int i=12;i>=0;i--){
    pixels.setPixelColor(12-i, pixels.Color(0,0,0));
    pixels.setPixelColor(i+12, pixels.Color(0,0,0));
    delay(125);
    pixels.show();
  }
  delay(250);

  //white pixel loop
  Serial.begin(9600);
  pixels.begin();
  pixels.setPixelColor(12, pixels.Color(32,32,32)); 
  delay(125);
  pixels.show();
  for (int i=0;i<=12;i++){
    pixels.setPixelColor(12-i, pixels.Color(32,32,32));
    pixels.setPixelColor(12+i, pixels.Color(32,32,32));
    delay(125);
    pixels.show();
  }
  delay(250);  
  
  //run calibration
  while (calibrated == 0){
     for(int i=0;i<NUMPIXELSMIN;i++)
  {
    pixelsMIN.setPixelColor(i, pixelsMIN.Color(8,8,8)); 
    delay(20);
    pixelsMIN.show(); 
  }
  delay(250);
  pixelsMIN.setPixelColor(13, pixelsMIN.Color(8,0,0));
  pixelsMIN.setPixelColor(12, pixelsMIN.Color(8,0,0));
  pixelsMIN.setPixelColor(11, pixelsMIN.Color(8,0,0));
  pixelsMIN.show();
  calibrate.write(0);
  delay(250);
     for(int i=0;i<NUMPIXELSMIN;i++)
  {
    pixelsMIN.setPixelColor(i, pixelsMIN.Color(8,8,8)); 
    delay(20);
    pixelsMIN.show(); 
  }
  delay(250);
 pixelsMIN.setPixelColor(13, pixelsMIN.Color(8,0,0));
  pixelsMIN.setPixelColor(12, pixelsMIN.Color(8,0,0));
  pixelsMIN.setPixelColor(11, pixelsMIN.Color(8,0,0));
  pixelsMIN.show();
  calibrate.write(0);
  delay(250);

  toggleSwitch.loop(); // MUST call the loop() function first

  if (toggleSwitch.isPressed())
    Serial.println("switch:OFF->ON");
    BLE.println("switch:OFF->ON");
    
  if (toggleSwitch.isReleased())
    Serial.println("switch:ON->OFF");
    BLE.println("switch:ON->OFF");

  int state = toggleSwitch.getState();
  if (state == HIGH){
    Serial.println("switch:OFF");
    BLE.println("switch:OFF");
         for(int i=0;i<NUMPIXELSMIN;i++)
  {
    pixelsMIN.setPixelColor(i, pixelsMIN.Color(8,0,0)); 
    delay(20);
    pixelsMIN.show(); 
  }
  }
  else if (state == LOW){
    Serial.println("switch:ON");
    BLE.println("switch:ON");
    calibrated = 1;
  }
    delay(500);
  calibrate.write(90);
  delay(1000);
  }
   Serial.write("successfully calibrated");
   BLE.write("successfully");
   delay(50);
   BLE.write("calibrated");
   delay(50);
   BLE.println("");
    for(int i=0;i<NUMPIXELSMIN;i++)
  {
    pixelsMIN.setPixelColor(i, pixelsMIN.Color(0,32,5)); 
    delay(125);
    pixelsMIN.show(); 
  }
  delay(500);
  }

void loop() {
   //servo format
  REYE.write(180);
  LEYE.write(0);
  delay(500);
  RBROW1.write(180);
  LBROW1.write(0);
  delay(500);
  RBROW2.write(0);
  LBROW2.write(180);
  delay(500);
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

  Serial.print("RIGHT: ");
  Serial.print(distance_cmR);
  Serial.print(" cm ");
  BLE.print("RIGHT: ");
  delay(50);
  BLE.print(distance_cmR);
  delay(50);
  BLE.println("cm");
  delay(50);
  
  Serial.print("MID: ");
  Serial.print(distance_cm);
  Serial.print(" cm ");
  BLE.print("MID: ");
  delay(50);
  BLE.print(distance_cm);
  delay(50);
  BLE.println(" cm ");
  delay(50);
  
  Serial.print("LEFT: ");
  Serial.print(distance_cmL);
  Serial.print(" cm ");
  BLE.print("LEFT: ");
  delay(50);
  BLE.print(distance_cmL);
  delay(50);
  BLE.println(" cm ");
  delay(50);

 
  if(distance_cm<distance_cmR){
    if (distance_cm<distance_cmL){
      Serial.print("MID LOW");
      BLE.print("MID LOW");
      lowest = 2;
    }
  }
  if(distance_cmR<distance_cm){
    if(distance_cmR<distance_cmL){
      Serial.print("RIGHT LOW");
      BLE.print("RIGHT LOW");
      lowest = 1;
    }
  }
  if(distance_cmL<distance_cm){
    if(distance_cmL<distance_cmR){
      Serial.print("LEFT LOW");
      BLE.print("LEFT LOW");
      lowest = 3;
    }
  }
  
  Serial.println(lowest);
  if (lowest==1){
    if (distance_cmR < 75){
       for(int i=0;i<NUMPIXELS;i++)
       {
         pixels.setPixelColor(i, pixels.Color(0,32,0)); 
         delay(20);
         pixels.show(); 
      }
        myStepper.step(-25);
        delay(250);
          Serial.println("Start playing");
          BLE.println("Start playing");
  /*Start playing*/
  DF1201S.start();
  delay(2000);
  Serial.println("Previous");
  BLE.println("Previous");
  /*Play the previous song*/
  DF1201S.last();
   Serial.println("Pause");
   BLE.print("Pause");
  /*Pause*/
  DF1201S.pause();
        myStepper.step(20);
        delay(150);
        //right sensor turn left
          //both up and down symmetry
  for (pos = 0; pos <= 180; pos += 1) {
    // in steps of 1 degree
    LBROW1.write(pos);              
    delay(3);                     
    RBROW1.write(180-pos);
    delay(3);
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    LBROW1.write(pos);              
    delay(3);                     
    RBROW1.write(180-pos);
    delay(3);
  }
    }
       for(int i=0;i<NUMPIXELS;i++)
     {
       pixels.setPixelColor(i, pixels.Color(32,32,32)); 
       delay(20);
       pixels.show(); 
     }
     lowest=0;
  }
  if (lowest==2){
    if (distance_cm<100){
    delay(300);
     for(int i=0;i<NUMPIXELS;i++)
     {
       pixels.setPixelColor(i, pixels.Color(0,0,32)); 
       delay(20);
       pixels.show(); 
     }
              Serial.println("Start playing");
              BLE.print("Start playing");
  /*Start playing*/
  DF1201S.start();
  delay(2000);
  Serial.println("Previous");
  BLE.print("Previous");
  /*Play the previous song*/
  DF1201S.last();
   Serial.println("Pause");
   BLE.println("Pause");
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
       pixels.setPixelColor(i, pixels.Color(32,32,32)); 
       delay(20);
       pixels.show(); 
     }
     lowest = 0;
  }
  if (lowest==3){
    if (distance_cmL < 40){
       for(int i=0;i<NUMPIXELS;i++)
     {
       pixels.setPixelColor(i, pixels.Color(32,0,0)); 
       delay(20);
       pixels.show(); 
     }
      myStepper.step(27);
      delay(150);
        Serial.println("Start playing");
        BLE.println("Start playing");
  /*Start playing*/
  DF1201S.start();
  delay(2000);
  Serial.println("Previous");
  BLE.print("Previous");
  /*Play the previous song*/
  DF1201S.last();
   Serial.println("Pause");
   BLE.println("Pause");
  /*Pause*/
  DF1201S.pause();
      myStepper.step(-24);
      delay(150);
      //left sensor turn right
      //both up and down symmetry
  for (pos = 0; pos <= 180; pos += 1) {
    // in steps of 1 degree
    RBROW2.write(pos);              
    delay(3);                     
    LBROW2.write(180-pos);
    delay(3);
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    RBROW2.write(pos);              
    delay(3);                     
    LBROW2.write(180-pos);
    delay(3);
  }
    }
       for(int i=0;i<NUMPIXELS;i++)
     {
       pixels.setPixelColor(i, pixels.Color(32,32,32)); 
       delay(20);
       pixels.show(); 
     }
     lowest = 0;
  }  
   //servo format
  REYE.write(180);
  LEYE.write(0);
  delay(500);
  RBROW1.write(180);
  LBROW1.write(0);
  delay(500);
  RBROW2.write(0);
  LBROW2.write(180);
  delay(500);
}
