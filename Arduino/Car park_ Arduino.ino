#include <SPI.h>
#include <Servo.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9

Servo myservo;

String tagUID = "29 B9 ED 23";

String arr[] = {"39 6D BD 2B","9C 85 D2 37","03 25 1F 05","29 76 6D 3C"};

SoftwareSerial espSerial(2, 3);

MFRC522 mfrc522(SS_PIN, RST_PIN);  

const int rs = 6, en = 7, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal_I2C lcd(0x27,16,2);

char str[128];

const int park1 = A0;     
const int park2 = A1;    
const int park3 = A2;    
const int park4 = A3;

// Auxiliar variables to store the current INPUT state
int parks1 = 0;
int parks2 = 0;
int parks3 = 0;
int parks4 = 0;

byte readCard[4];

boolean DetectCard = false;

int reply[4];

void setup() {
  // put your setup code here, to run once:
  pinMode(park1, INPUT);
  pinMode(park2, INPUT);
  pinMode(park3, INPUT);
  pinMode(park4, INPUT);

  SPI.begin(); 
  mfrc522.PCD_Init();   // Initiate MFRC522

  lcd.init();
  lcd.clear();         
  lcd.backlight();

  lcd.begin(16, 2);
  lcd.print("hello, world!");

  delay(500);
  lcd.clear();

  myservo.attach(A4);
  myservo.write(0);
  
  Serial.begin(9600);
  espSerial.begin(115200);
  delay(2000);
}

void IRsensor(){
  if(digitalRead(park1)== HIGH){
      parks1 = 1;
    }
    else{
      parks1 = 0;
    }
  
    //........................................
    if(digitalRead(park2)== HIGH){
      parks2 = 1;
    }
    else{
      parks2 = 0;
    }
  
    //........................................
    if(digitalRead(park3)== HIGH){
      parks3 = 1;
    }
    else{
      parks3 = 0;
    }
  
    //........................................
    if(digitalRead(park4)== HIGH){
      parks4 = 1;
    }
    else{
      parks4 = 0;
    }

    reply[0] = parks1;
    reply[1] = parks2;
    reply[2] = parks3;
    reply[3] = parks4;
    
    sprintf(str, "%u,%u,%u,%u", reply[0],reply[1],reply[2],reply[3]);
}

// To print on the LCD ...................
void LCD(){

  if (parks1 ==0 and parks2 == 0 and parks3 == 0 and parks4 == 0){
    lcd.clear();
    lcd.print("CAR PARK IS FULL");
  }
  else{
  lcd.clear();
  if(parks1 ==1){
    lcd.print("PARK 1 is free");
    }
  else{
    lcd.clear();
    }
    
  delay(1000);
  lcd.clear();

  if(parks2 ==1){
    lcd.print("PARK 2 is free");
    }
  else{
    lcd.clear();
    }
    
  delay(1000);
  lcd.clear();

  if(parks3 ==1){
    lcd.print("PARK 3 is free");
    }
  else{
    lcd.clear();
    }
    
  delay(1000);
  lcd.clear();

  if(parks4 ==1){
    lcd.print("PARK 4 is free");
    }
  else{
    lcd.clear();
    }
    
  delay(1000);
  lcd.clear();

    delay(1000);
    lcd.clear();
    }
  }


void gate(){
   if (DetectCard == true){
    myservo.write(90);
    delay(3000);
    myservo.write(0);
    DetectCard = false;
    }
   else{
    myservo.write(0);
    }
    
    DetectCard = false;
  }

void getID() {  

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  for (int idx = 0; idx < sizeof(arr) / sizeof(arr[0]); idx++) {
      if (content.substring(1) == arr[idx]) //change here the UID of the card/cards that you want to give access
      {
        Serial.println("Authorized access");
        Serial.println();
        DetectCard = true;
        delay(500);
      }
     
     else   {
        Serial.println(" Access denied");
        delay(500);
      }
  }
}

void loop() {
  
  // put your main code here, to run repeatedly:
  IRsensor();
  LCD();
  getID();
  gate();
  
  espSerial.println(str);
  Serial.print(str);
  delay(500);
}
