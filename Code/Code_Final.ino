#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <dht.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//Temperature and Humidity Sensor
dht T_and_H;

//Soil Moisture Sensor 
int soil_sensorPin = A0; 
int soil_sensorValue;  
int soil_M_limit = 950; 
int solenoid = 6;



//Methane Sensor
int Meth_pin = A2;
float Meth_val ;


void setup()
{
  Serial.begin(9600);
  pinMode(solenoid, OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(4,HIGH);
  digitalWrite(13,LOW);

  
  //Display
  lcd.init();                   
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print(" Athugalpura");
  lcd.setCursor(1,1);
  lcd.print("    Devans");
  delay(2500);
  lcd.clear();

  
}


void loop()
{
  //Temperature 
  int val = T_and_H.read11(7);
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.setCursor(12,0);
  lcd.print(T_and_H.temperature);
  lcd.setCursor(14,0);
  lcd.print(" C");
  delay(1000);

  //Humidity
  lcd.setCursor(0,0);
  lcd.print("Humidity : ");
  lcd.setCursor(11,0);
  lcd.print(T_and_H.humidity);
  lcd.setCursor(13,0);
  lcd.print(" %   ");
  delay(1000);
  

  //Soil moisture sensor
  soil_sensorValue = analogRead(soil_sensorPin);
  delay(250);
  //lcd.setCursor(0,0);
  //lcd.print("Soil M :");
  //lcd.setCursor(7,0);
  //lcd.print(soil_sensorValue);
  Serial.println(soil_sensorValue);

  if (soil_sensorValue<soil_M_limit) {
    digitalWrite(solenoid, HIGH); 
    lcd.setCursor(0,1);
    lcd.print("Valve OFF");
    digitalWrite(4,HIGH);
  }
  else {
    digitalWrite(solenoid, LOW); 
    lcd.setCursor(0,1);
    lcd.print("Valve ON  ");
    digitalWrite(4,LOW);
  }

  //Methane Sensor
  Meth_val = analogRead(Meth_pin);
  //Serial.println(Meth_val);
  lcd.setCursor(0,0);
  lcd.print("Methane : ");
  lcd.setCursor(10,0);
  lcd.print(Meth_val);
  //lcd.setCursor(13,0);
  //lcd.print(" %   ");
  delay(1000);
  

 
}












