#include <SoftwareSerial.h>

int bluetoothTx = 2;
int bluetoothRx = 3;
const int ledPin = 13;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  //Setup usb serial connection to computer
  Serial.begin(9600);
  Serial.println("ciao mondo");
  //Setup Bluetooth serial connection to android
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  //Read from bluetooth and write to usb serial
  if(bluetooth.available())
  {
    byte toSend = (byte)bluetooth.read();
    switch (toSend) {
      case 1:
        digitalWrite(ledPin, HIGH);
        break;
      case 2:
        digitalWrite(ledPin, LOW);
        break;
       default:
        break;
    }
    Serial.print(toSend);
  }

  //Read from usb serial to bluetooth
  if(Serial.available())
  {
    char toSend = (char)Serial.read();
    bluetooth.print(toSend);
  }
}
