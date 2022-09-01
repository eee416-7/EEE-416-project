#include <NewPing.h>
#include <Adafruit_MLX90614.h>

#define BUZZER_PIN 5
#define CUT_OFF_TEMPERATURE 42  //This is temperature in degreeC
#define DISTANCE_TO_CHECK 10    //This is in cm
#define tempPin1 6 // logic that tells us whether 
#define tempPin2 7 // logic 
NewPing ultrasonicSensor(2,3,400);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


void setup() 
{
  lcd.begin(16, 2);  
  lcd.clear();  
  Serial.begin(9600);
  analogWrite(BUZZER_PIN, 0);
  pinMode(tempPin1, OUTPUT);
  pinMode(tempPin2, OUTPUT);
  mlx.begin();
}

void tempReadTone() 
{ 
  for (int i = 0; i < 5; i++)
  {
    analogWrite(BUZZER_PIN,100);
    delay(100);
    analogWrite(BUZZER_PIN,0);
    delay(100);  
  }      
}

void tempHighTone() 
{ 
  for (int i = 0; i < 10; i++)
  {
    analogWrite(BUZZER_PIN,100);
    delay(100);
    analogWrite(BUZZER_PIN,0);
    delay(100);  
  }      
}

void tempOkTone() 
{ 
  analogWrite(BUZZER_PIN, 100);
  delay(2000);
  analogWrite(BUZZER_PIN, 0);
}

void loop() 
{
  String displayString;
  lcd.setCursor(0, 0);
  lcd.print("Check Temp");
  
  int distance = ultrasonicSensor.ping_cm();
  Serial.println("Distance of object from sonar:");
  Serial.println(distance);
  if (distance > 6 && distance < DISTANCE_TO_CHECK)
  {
    tempReadTone();
    delay(2000);
    float sum = 0;
    float temperature = 0;
    int i = 0;
    for(i=0;i<=100;i++){
      temperature = mlx.readObjectTempC();
      sum = sum + temperature;
      Serial.println(temperature);
    }
    temperature = sum / i;
    Serial.println("The average temperature is:");
    Serial.println(temperature);
    //temperature = mlx.readObjectTempC();
    //Serial.println(temperature);
    distance = ultrasonicSensor.ping_cm();
    if (distance > 6 && distance < DISTANCE_TO_CHECK && temperature <= CUT_OFF_TEMPERATURE)
    {
      tempOkTone();
      delay(2000);
      digitalWrite(tempPin1, HIGH);
      digitalWrite(tempPin2, LOW);
    }
    else if (distance > 6 && distance < DISTANCE_TO_CHECK && temperature > CUT_OFF_TEMPERATURE){
      tempHighTone();
      delay(2000);
      digitalWrite(tempPin1, LOW);
      digitalWrite(tempPin2, HIGH);
    }
    else
    {
      delay(2000);
    }

  }
  else{
      delay(2000);
      digitalWrite(tempPin1, HIGH);
      digitalWrite(tempPin2, HIGH);
    
  }
  delay(5000);

}