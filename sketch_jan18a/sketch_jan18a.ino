//////////// LCD Display/////////////////////////////////////////////////////////////////////////////////
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////Reading the Weight Scale///////////////////////////////////////////////////////////////////
#include "HX711.h"

#define calibration_factor 1930.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

HX711 scale;

float weight;

void weight_func ();
///////////////////////////////////////////////////////////////////////////////////////////////////////

/////////// Keypad////////////////////////////////////////////////////////////////////////////////////
#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char key;
String new_key;
long inputInt;

/////////////////////////////////////////////////////////////////////////////////////////////////////

String msg = "Remove the garments";
String msg1 = "from the scale";
String msg2 = "Garments ?";
int i = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("WELCOME TO ");
  lcd.setCursor(4, 1);
  lcd.print("METHLIYA");
  delay(2000);
  lcd.setCursor(3, 0);
  lcd.print(" Methliya  ");
  lcd.setCursor(3, 1);
  lcd.print("Innovation ");
  delay(2000);
  lcd.clear();
  while (i < msg.length()) {
    if (i == msg.length()) {
      i = 1;
      lcd.clear();
    }
    lcd.setCursor(1, 0);
    lcd.print(msg);
    lcd.scrollDisplayLeft();
    lcd.setCursor(i, 1);
    lcd.print(msg1);
    delay(600);
    i++;
  }
  lcd.clear();
  delay(1000);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  key = keypad.getKey();  //Variable to store pressed key


  while (key != " ") {
    Serial.println(key);
    int total=0;
    float avg_weight=0;
    weight = scale.get_units();
  
    for (int x = 0; x < 10; x++) {
      weight = scale.get_units();
      total = total + weight;
    }
    avg_weight = total / 10;
    key= keypad.getKey();

    lcd.setCursor(1, 0);
    lcd.print("WEIGHT= ");
    lcd.setCursor(5, 1);
    lcd.print(avg_weight);
    lcd.setCursor(15, 1);
    lcd.print("g");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
////////////////////////////////////////////Read the weight until a start button is pressed/////////////////////////////////////////////////////////////
//void read_weight() {
//  int total = 0;
//  int avg_weight = 0;
//  int i = 0;
//  key_press();
//  while (new_key != "*" || i < 10) {
//    weight_func ();
//    key_press();
//    Serial.print(weight);
//    weight = scale.get_units();
//    total = total + weight;
//    i++;
//    break;
//  }
//  avg_weight = total / 10;
//
//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////Weight Function/////////////////////////////////////////////////////////////////////////////////////////////
//void weight_func () {
//  int total;
//  int avg_weight;
//  weight = scale.get_units();
//  Serial.println("weight");
//  for (int x = 0; x < 10; x++) {
//    weight = scale.get_units();
//    total = total + weight;
//  }
//  avg_weight = total / 10;
//  return avg_weight;
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////key pressed reading///////////////////////////////////////////////////////////////////////////////////////
//void key_press() {
//  key = keypad.getKey();  //Variable to store pressed key
//  Serial.println("key pass");
//  if (key) {
//    Serial.println(key);
//
//    if (key >= '0' && key <= '9') {     // only act on numeric keys
//      new_key += key;               // append new character to input string
//    } else if (key == '#') {
//      if (new_key.length() > 0) {
//        inputInt = new_key.toInt(); // YOU GOT AN INTEGER NUMBER
//        new_key = "";               // clear input
//
//      }
//    } else if (key == '*') {
//      new_key = "";                 // clear input
//    }
//  }
//  return new_key;
//}
