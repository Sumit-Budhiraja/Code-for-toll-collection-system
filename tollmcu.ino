
#define SS_PIN D4
#define RST_PIN D3
#define IR_PIN D0
#define IR2_PIN D2
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo servo;

int lcdColumns = 16;
int lcdRows = 2;
int val=0;
int val2=0;
int cardbalance = 500;
int a=0;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(IR_PIN, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("IOT TOLL PLAZA !");
  lcd.setCursor(0,1);
  lcd.print("EVERYTHING IS OK");
  
  servo.attach(15); //D8

  servo.write(0);

delay(2000);
}
void loop() 
{
  val = digitalRead(IR_PIN);
  val2 = digitalRead(IR2_PIN);

  Serial.println("***");
 Serial.println(val2);
 Serial.println("***");
 delay(1000);
 if(val==HIGH)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome to toll.");
    lcd.setCursor(0, 1);
    lcd.print("Show your Card.");
    a=1;
    delay(1000);
  }
  else
  {
//      lcd.setCursor(0, 0);
//    lcd.print("IOT TOLL PLAZA");
//    lcd.setCursor(0,1);
//    lcd.print("EVERYTHING IS OK");
//     
  }
  
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
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  
  if (content.substring(1) == "FA E9 D4 83") //change UID of the card that you want to give access
  {
    //Serial.println(" Access Granted ");
    //Serial.println(" Welcome Mr. Sumit Budhiraja");
    //delay(1000);
    //Serial.println(" Have FUN ");
    //Serial.println();
    if(cardbalance>0 && a==1){ 
      a=2;
     lcd.clear();
    cardbalance=cardbalance-50;
    lcd.setCursor(0, 0);
    lcd.print("BALANCE ");
    lcd.setCursor(8,0);
    lcd.print(cardbalance);
  //delay(1000);
  // clears the display to print new message
  //lcd.clear();
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print(" SAFE JOURNEY ");
  delay(1000);
  //lcd.clear(); 
    statuss = 1;
    servo.write(180);
    
    delay(5000);
     servo.write(0);
//    if(val2==1)
//    {
//      servo.write(0);
//      lcd.clear();
//      lcd.setCursor(0, 0);
//      lcd.print("Thanks for visit");
//      lcd.setCursor(0, 1);
//      lcd.print("System Ready..");
//    }
delay(1000);
    }
    else if(cardbalance<=0&&a==1)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ALERT! BALANCE:0");
      lcd.setCursor(0,1);
      lcd.print("Please Recharge");
    }
  }
 
  
  else   {
    //Serial.println(" Access Denied ");

    lcd.clear();
    lcd.setCursor(0, 0);
  // print message
  lcd.print("NOT A VALID CARD");
  //delay(1000);
  // clears the display to print new message
  //lcd.clear();
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print("SECUIRITY ALERT");
  delay(3000);
  lcd.clear(); 
    statuss = 1;
    //delay(3000);
    lcd.setCursor(0, 0);
  // print message
  lcd.print("IOT TOLL PLAZA");
  //delay(500);
  lcd.setCursor(0,1);
  lcd.print("Show your card");
  
  }
} 
