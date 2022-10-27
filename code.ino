#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  
int relay_sprinkler = 11;
int relay_pump = 12;
int water_pin=A3;
int soil_pin = A0;
int ldr_pin = A1;
void setup() {
  pinMode(relay_sprinkler,OUTPUT);
  pinMode(relay_pump,OUTPUT);
  pinMode(water_pin,INPUT);
  pinMode(soil_pin,INPUT);
  pinMode(ldr_pin,INPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int ldr_data=analogRead(ldr_pin);
  if (ldr_data>200){
    //it is day
    int soil_data = analogRead(soil_pin);
    if (soil_data<400){
      digitalWrite(relay_sprinkler,HIGH);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Soil needs water"); 
    }else{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Soil moisture ok");
      digitalWrite(relay_sprinkler,LOW);
    }
    int water_data = analogRead(water_pin);
    if (water_data<250){
      lcd.setCursor(0,1);
      lcd.print("Water level low");
      digitalWrite(relay_pump, HIGH);
    }else{
      lcd.setCursor(0,1);
      lcd.print("Water level ok");
      digitalWrite(relay_pump, LOW);
    }
  }
  delay(3000);
}
