#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd(0);

int sensorPin = A0;

int lowLed = 5;
int medLed = 6;
int highLed = 7;

int leftMotor = 8;
int middleMotor = 4;
int rightMotor = 10;

int enablePin1 = 9;
int enablePin2 = 3;

float voltage, temperatureC, temperatureF;
String status, lcdDisplayStatus;

void setup()
{
  for (int pinNum = 3; pinNum <=11; pinNum++){
      pinMode(pinNum, OUTPUT);
  } 
  
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop()
{
  // Setting the value of motorspeed
  analogWrite(enablePin1, 1023);
  analogWrite(enablePin2, 1023);
  
  int tempValue = analogRead(sensorPin);
  
  //CONVERTING TO VOLTAGE
  voltage = tempValue * 5.0;
  voltage/=1024.0;
  
  //CONVERTING TO CELSIUS
  temperatureC = (voltage-0.5)*100;
  
  //CONVERTING TO FAHRENHEIT
  temperatureF = (temperatureC*9.0/5.0)+32.0;
  
  //Temperature Conditions for LED
  temperatureConditions();
  
  //Displaying in Serial Monitor
  Serial.print("STATUS: ");
  Serial.println(status); 
  
  Serial.print("TEMPERATURE: ");
  Serial.print(temperatureC); 
  Serial.print(" C or ");
  Serial.print(temperatureF); 
  Serial.println(" F");
  
  Serial.print("------------------------------");
  Serial.println("");
  
  //Displaying in LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TEMP: ");
  lcd.print(temperatureC);
  lcd.print(" C");
  
  lcd.setCursor(0,1);
  lcd.print("STAT: ");
  lcd.print(status);
  delay(500);
}

void temperatureConditions(){
  if (temperatureC < 1){
    digitalWrite(lowLed, LOW);
    digitalWrite(medLed, LOW);
    digitalWrite(highLed, LOW);
    digitalWrite(leftMotor, LOW);
    digitalWrite(middleMotor, LOW);
    digitalWrite(rightMotor, LOW);
    status = "OFF";
  }
  
  else if (temperatureC > 1 && temperatureC <=49){
    digitalWrite(lowLed, HIGH);
    digitalWrite(medLed, LOW);
    digitalWrite(highLed, LOW);
    digitalWrite(leftMotor, HIGH);
    digitalWrite(middleMotor, LOW);
    digitalWrite(rightMotor, LOW);
    status = "LOW";
  }
  
  else if (temperatureC >= 49 && temperatureC <=99){
    digitalWrite(lowLed, LOW);
    digitalWrite(medLed, HIGH);
    digitalWrite(highLed, LOW);
    digitalWrite(leftMotor, HIGH);
    digitalWrite(middleMotor, HIGH);
    digitalWrite(rightMotor, LOW);
    status = "MEDIUM";
  }
  
  else if (temperatureC >= 99){
    digitalWrite(lowLed, LOW);
    digitalWrite(medLed, LOW);
    digitalWrite(highLed, HIGH);
    digitalWrite(leftMotor, HIGH);
    digitalWrite(middleMotor, HIGH);
    digitalWrite(rightMotor, HIGH);
    status = "HIGH";
  }
}
