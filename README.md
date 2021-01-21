# DIY-Macro-Button
A DIY 6 Button USB macro Keyboard made on atmega 32u4 development board with an NFC Reader to unlock the PC using NFC card
## Parts Required
- Arduino Pro Micro Atmega 32u4 based Development Board
- MFRC 522 NFC reader with NFC Card
- Push Button x6
- Wires 
## Circuit Diagram

[Circuit Diagram](CircuitDiagram.png?raw=true)

## Connection Matrix
|Arduino Pro Micro | MFRC 522 |
|---|---|
|9|RST|
|10|SDA|
|16|MOSI|
|14|MISO|
|15|SCK|
|VCC|VCC|
|GND|GND|

To Attach the Buttons Connect one end to the ground of the Arduino and the other end to the different pins on the arduino which are 2,3,4,5,6,A1

## Code 
Arduino Pro Micro Code: [Project Code](code.ino)

You need to install the [MFRC522 Library](https://github.com/miguelbalboa/rfid) by [Miguelbalboa]("https://github.com/miguelbalboa/")
## Code Modification
Modidyfing your code in the macro_password Function
```
void macro_password(){
  Keyboard.print("<Your Password Here"); //Enter your Password Here
  delay(150);
  press1(KEY_RETURN); // Press Enter
  delay(100);
  rfid.PICC_HaltA();
}
```
Modifying the commands on the button Press
After Wiring the Buttons, Give your macro commands inside the if statement before the delay command
For the key reference please refer to the [Keyboard.h ](https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h)  
```
if (sensorVal1 == 0) {
    //Enter your macro here
    delay(250);
  }
  if (sensorVal2 == 0) {
    //Enter your macro here
    delay(250);
  }
  if (sensorVal3 == 0) {
    //Enter your macro here
    delay(250);
  }
  if (sensorVal4 == 0) {
    //Enter your macro here
    delay(250);
  }
  if (sensorVal5 == 0) {
    //Enter your macro here
  }
  if (sensorVal6 == 0) {
    //Enter your macro here
    delay(250);
  } 
```

Functions for multiple button press
There are 3 funtions which can simulate the button press

`press1(<key>)` Simulates single button press. For example, pressing funtion key f1, pressing enter key

`press2(<key1> <key2>)` Simululates 2 button press. For example, pressing alt and f4 together

`press3(<key1> <key2> <key3> ` Simulates 3 button press. For example, pressing ctrl alt t together

`Keyboard.print("<STRING>");` Simu;ates typing of the defined string 

Examples:
- Simulating ctrl alt t `press3(KEY_LEFT_CTRL KEY_LEFT_ALT 't');`
- Simulating Hello World `Keyboard.print("Hello World");`
- Simulating alt f4 ` press2(KEY_LEFT_ALT,KEY_F4);`
- Simulating Enter key `press1(KEY_RETURN); `

Changing the value of the valid_card variable

`#define valid_card="C9 5C 19 BD";` Change the value with the UID of the NFC card which you want to use to open your laptop. 

The uid can be found by uploading the DumpInfo sketch from the MFRC522 example skectch

## Working and Usage
After the wiring is done and the code is modified and uploaded, you will be able to use the nfc card to open your computer just by placing the nfc card on the receiver. 

Please note: If you place the card when the system is unloced, the arduino will type the password on the screen. On pressing the buttons, the assigned keystroke combination will be performed.
