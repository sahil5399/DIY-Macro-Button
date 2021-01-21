/*Typical pin layout used:
   -----------------------------------
               rfid      Arduino
               Reader/PCD   Pro Micro
   Signal      Pin          Pin
   -----------------------------------
   RST/Reset   RST          RST
   SPI SS      SDA(SS)      10
   SPI MOSI    MOSI         16
   SPI MISO    MISO         14
   SPI SCK     SCK          15

*/


#include <SPI.h>
#include <MFRC522.h>
#include <Keyboard.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
#define valid_card="C9 5C 19 BD";
MFRC522 rfid(SS_PIN, RST_PIN);  // Create rfid instance

String content = "";
int macro_num;

void press1(uint8_t k){
  Keyboard.press(k);
  delay(100);
  Keyboard.releaseAll();
}
void press2(uint8_t k,uint8_t k2){
  Keyboard.press(k);
  Keyboard.press(k2);
  Keyboard.releaseAll();
}
void press3(uint8_t k,uint8_t k2,uint8_t k3){
  Keyboard.press(k);
  Keyboard.press(k2);
  Keyboard.press(k3);
  Keyboard.releaseAll();
}

void macro_password(){
  //Serial.println("Print the Password");
  Keyboard.print("<Your Password Here>"); //Enter your Password Here
  delay(150);
  press1(KEY_RETURN);
  delay(100);
  rfid.PICC_HaltA();
}

void setup() {
  Serial.begin(115600);   // Initialize serial communications with the PC
  Keyboard.begin();
  pinMode(A1,INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();   // Init rfid
  delay(4);       
}
void loop() {
  int sensorVal1 = digitalRead(2);
  int sensorVal2 = digitalRead(3);
  int sensorVal3 = digitalRead(4);
  int sensorVal4 = digitalRead(5);
  int sensorVal5 = digitalRead(6);
  int sensorVal6 = digitalRead(A1);
  if (sensorVal1 == 0) {
    Serial.println("B1 press");
    delay(250);
  }
  if (sensorVal2 == 0) {
    Serial.println("B2 press");
    delay(250);
  }
  if (sensorVal3 == 0) {
    Serial.println("B4 press");
    delay(250);
  }
  if (sensorVal4 == 0) {
    Serial.println("B3 press");
    delay(250);
  }
  if (sensorVal5 == 0) {
    Serial.println("B6 press");
  }
  if (sensorVal6 == 0) {
    Serial.println("B5 press");
    delay(250);
  } 
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial()) {
    return;
  }
  else {
    
    for (byte i = 0; i < rfid.uid.size; i++)
    {
      content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(rfid.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    if (content.substring(1) == valid_card) //change here the UID of the card/cards that you want to give access
    {
      //Serial.println("\nAuthorized access");
      macro_password();
    }
    content = "";
  }

  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
