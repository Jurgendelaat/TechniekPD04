//LCD:

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//integers:
  int code[] = {3, 2, 1};
  int ingevoerdeCode[3];
  int codeLength = 3;
  int pos = 0;

  int buttonPin1 = 10;
  int buttonPin2 = 11;
  int buttonPin3 = 12;
  int ledPin = 5;
  int buzzer = 3;

  //PROGRAMMA 
void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  

  //Serial monitor:
  Serial.begin(9600);
  Serial.println("Hallo");
  delay(2000);
  Serial.println("Voer pincode in");

  //LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Enter pincode!");
 }


void loop() {
 
  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);
  int buttonState3 = digitalRead(buttonPin3);

    
  if (pos <= codeLength) {
    if (buttonState1 == LOW) {
      ingevoerdeCode[pos] = 1;
      Serial.println("1");
      Serial.println(ingevoerdeCode[pos]);
      lcd.setCursor(pos, 2);
      lcd.print(ingevoerdeCode[pos]);
      delay(200);
      pos++;  
      while (digitalRead(buttonPin1) == LOW) {};
      }

     else if (buttonState2 == LOW) {
      ingevoerdeCode[pos] = 2;
      Serial.println("2");
      Serial.println(ingevoerdeCode[pos]);
      lcd.setCursor(pos, 2);
      lcd.print(ingevoerdeCode[pos]);
      delay(200);
      pos++;    
      while (digitalRead(buttonPin2) == LOW) {};
       }     

     else if (buttonState3 == LOW) {
      ingevoerdeCode[pos] = 3;
      Serial.println("3");
      Serial.println(ingevoerdeCode[pos]);
      lcd.setCursor(pos, 2);
      lcd.print(ingevoerdeCode[pos]);
      delay(200);
      pos++;    
      while (digitalRead(buttonPin3) == LOW) {};
      }
  }

  //GOEDE CODE:
  if (pos >= codeLength && ingevoerdeCode[0] == code[0] && ingevoerdeCode[1] == code[1] && ingevoerdeCode[2] == code[2]) {
      digitalWrite(ledPin, LOW);
      Serial.println("Goede code, toegang verleent");
      lcd.begin(16, 1);
      lcd.clear();
      lcd.print("Correct pincode");
      tone(buzzer, 100);
      delay(3000);
      noTone(buzzer);
      digitalWrite(ledPin, HIGH);

      //RESET
      pos = 0;
      memset(ingevoerdeCode, 0, sizeof(ingevoerdeCode));
      lcd.begin(16, 2);
      lcd.clear();
      lcd.print("Enter pincode!");        
      }

   //VERKEERDE CODE:                         
   if (pos >= codeLength && ingevoerdeCode != code) {
      Serial.println("Verkeerde code, zelfdestructie wordt gestart");
      lcd.clear();
      lcd.print("Wrong pincode");
      delay(1000);
      lcd.clear();
      lcd.print("Selfdestruction");
      lcd.setCursor(1,2);
      lcd.print("started");
      int i = 1;

      //BUZZER EN LED KNIPPER ALS VERKEERDE PIN IS INGEVULD
      for (i = 1; i < 10; i++) { 
      Serial.println(i);
      tone(buzzer, 2000);
      digitalWrite(ledPin, LOW);
      delay(500);
      noTone(buzzer);
      digitalWrite(ledPin, HIGH);
      delay(500);      
      } 

      //RESET
      i = 0;
      pos = 0;
      memset(ingevoerdeCode, 0, sizeof(ingevoerdeCode));  
      lcd.begin(16, 2);
      lcd.clear();
      lcd.print("Enter pincode!");
      }  
  
}       
           
    
