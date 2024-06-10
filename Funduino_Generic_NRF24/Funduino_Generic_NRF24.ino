#include <SPI.h>
#include "printf.h"
#include "RF24.h"

#define CE_PIN 9
#define CSN_PIN 10

#define BUTTON_UP 2
#define BUTTON_RIGHT 3
#define BUTTON_DOWN  4
#define BUTTON_LEFT 5
#define BUTTON_E 6
#define BUTTON_F  7
#define BUTTON_K 8
#define PIN_ANALOG_X 0
#define PIN_ANALOG_Y  1

#define DELAY 100

RF24 radio(CE_PIN, CSN_PIN);// instantiate an object for the nRF24L01 transceiver

const byte address[6] = "00001";

void setup() {

 Serial.begin(9600);

 radio.begin();
 radio.openWritingPipe(address);
 radio.setPALevel(RF24_PA_MIN);
 radio.stopListening();

 pinMode(BUTTON_UP, INPUT_PULLUP);
 pinMode(BUTTON_RIGHT, INPUT_PULLUP);
 pinMode(BUTTON_DOWN, INPUT_PULLUP);
 pinMode(BUTTON_LEFT, INPUT_PULLUP);
 pinMode(BUTTON_E, INPUT_PULLUP);
 pinMode(BUTTON_F, INPUT_PULLUP);
 pinMode(BUTTON_K, INPUT_PULLUP);

}



void loop() {

  const char text1[] = "X:";
  const char text2[] = "Y:";
  const char text3[] = "UP:";
  const char text4[] = "DOWN:";
  const char text5[] = ",";

  String message;
  //message.concat(text1);
  message.concat(analogRead(PIN_ANALOG_X));
  message.concat(text5);
  //message.concat(text2);
  //message.concat(analogRead(PIN_ANALOG_Y));
  //message.concat(text5);
  //Serial.println(message);

  //message.concat(text3);
  message.concat(digitalRead(BUTTON_UP));
  message.concat(text5);
  //message.concat(text4);
  message.concat(digitalRead(BUTTON_DOWN));
  message.concat(text5);
  


  Serial.println(message);

  char sendBuffer[32];

  message.toCharArray(sendBuffer, 32);
  radio.write(&sendBuffer, sizeof(sendBuffer));
  delay(DELAY);

}