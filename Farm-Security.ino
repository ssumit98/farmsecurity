// TCS230 or TCS3200 pins wiring to Arduino
#define S0 2
#define S1 3
#define S2 6
#define S3 7
#define sensorOut 8






#define S4 30
#define S5 31
#define S6 32
#define S7 33
#define sensorOut2 34


#include <Servo.h>             //Servo library
 
Servo servo_test;        //initialize a servo object for the connected servo  
Servo servo_test2;                
int angle = 0;    


#include <Wire.h>
#include "Adafruit_TCS34725.h"




#define TCS34725_R_Coef 0.136
#define TCS34725_G_Coef 1.000
#define TCS34725_B_Coef -0.444
#define TCS34725_GA 1.0
#define TCS34725_DF 310.0
#define TCS34725_CT_Coef 3810.0
#define TCS34725_CT_Offset 1391.0
#define relay A0



// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int redFrequency2 = 0;

class tcs34725 {
private:
  struct tcs_agc {
    tcs34725Gain_t ag;
    tcs34725IntegrationTime_t at;
    uint16_t mincnt;
    uint16_t maxcnt;
  };
  static const tcs_agc agc_lst[];
  uint16_t agc_cur;

  void setGainTime(void);
  Adafruit_TCS34725 tcs;

public:
  tcs34725(void);

  boolean begin(void);
  void getData(void);

  boolean isAvailable, isSaturated;
  uint16_t againx, atime, atime_ms;
  uint16_t r, g, b, c;
  uint16_t ir;
  uint16_t r_comp, g_comp, b_comp, c_comp;
  uint16_t saturation, saturation75;
  float cratio, cpl, ct, lux, maxlux;
};
const tcs34725::tcs_agc tcs34725::agc_lst[] = {
  { TCS34725_GAIN_60X, TCS34725_INTEGRATIONTIME_700MS,     0, 20000 },
  { TCS34725_GAIN_60X, TCS34725_INTEGRATIONTIME_154MS,  4990, 63000 },
  { TCS34725_GAIN_16X, TCS34725_INTEGRATIONTIME_154MS, 16790, 63000 },
  { TCS34725_GAIN_4X,  TCS34725_INTEGRATIONTIME_154MS, 15740, 63000 },
  { TCS34725_GAIN_1X,  TCS34725_INTEGRATIONTIME_154MS, 15740, 0 }
};
tcs34725::tcs34725() : agc_cur(0), isAvailable(0), isSaturated(0) {
}

// initialize the sensor
boolean tcs34725::begin(void) {
  tcs = Adafruit_TCS34725(agc_lst[agc_cur].at, agc_lst[agc_cur].ag);
  if ((isAvailable = tcs.begin()))
    setGainTime();
  return(isAvailable);
}

// Set the gain and integration time
void tcs34725::setGainTime(void) {
  tcs.setGain(agc_lst[agc_cur].ag);
  tcs.setIntegrationTime(agc_lst[agc_cur].at);
  atime = int(agc_lst[agc_cur].at);
  atime_ms = ((256 - atime) * 2.4);
  switch(agc_lst[agc_cur].ag) {
  case TCS34725_GAIN_1X:
    againx = 1;
    break;
  case TCS34725_GAIN_4X:
    againx = 4;
    break;
  case TCS34725_GAIN_16X:
    againx = 16;
    break;
  case TCS34725_GAIN_60X:
    againx = 60;
    break;
  }
}

// Retrieve data from the sensor and do the calculations
void tcs34725::getData(void) {
  // read the sensor and autorange if necessary
  tcs.getRawData(&r, &g, &b, &c);
  while(1) {
    if (agc_lst[agc_cur].maxcnt && c > agc_lst[agc_cur].maxcnt)
      agc_cur++;
    else if (agc_lst[agc_cur].mincnt && c < agc_lst[agc_cur].mincnt)
      agc_cur--;
    else break;

    setGainTime();
    delay((256 - atime) * 2.4 * 2); // shock absorber
    tcs.getRawData(&r, &g, &b, &c);
    break;
  }

  // DN40 calculations
  ir = (r + g + b > c) ? (r + g + b - c) / 2 : 0;
  r_comp = r - ir;
  g_comp = g - ir;
  b_comp = b - ir;
  c_comp = c - ir;
  cratio = float(ir) / float(c);

  saturation = ((256 - atime) > 63) ? 65535 : 1024 * (256 - atime);
  saturation75 = (atime_ms < 150) ? (saturation - saturation / 4) : saturation;
  isSaturated = (atime_ms < 150 && c > saturation75) ? 1 : 0;
  cpl = (atime_ms * againx) / (TCS34725_GA * TCS34725_DF);
  maxlux = 65535 / (cpl * 3);

  lux = (TCS34725_R_Coef * float(r_comp) + TCS34725_G_Coef * float(g_comp) + TCS34725_B_Coef * float(b_comp)) / cpl;
  ct = TCS34725_CT_Coef * float(b_comp) / float(r_comp) + TCS34725_CT_Offset;
}

tcs34725 rgb_sensor;

void setup() {



  {



{ 
  for(angle = 0; angle < 180; angle += 1)    // command to move from 0 degrees to 180 degrees 
  {                                  
    servo_test.write(angle); 
    servo_test2.write(angle); //command to rotate the servo to the specified angle
    delay(10);                       
  } 
 
 
  
  for(angle = 360; angle>=1; angle-=5)     // command to move from 180 degrees to 0 degrees 
  {                                
    servo_test.write(angle); 
    servo_test2.write(angle);
    //command to rotate the servo to the specified angle
    delay(5);                       
  } 

    
}

  }
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);


  
    pinMode(S4, OUTPUT);
  pinMode(S5, OUTPUT);
  pinMode(S6, OUTPUT);
  pinMode(S7, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
   pinMode(sensorOut2, INPUT);

   
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);


  digitalWrite(S4,HIGH);
  digitalWrite(S5,LOW);






   
  rgb_sensor.begin();
  pinMode(50, OUTPUT);
pinMode(51, OUTPUT);
  digitalWrite(50, OUTPUT); // @gremlins Bright light, bright light!
digitalWrite(51, OUTPUT);
  
   // Begins serial communication 
  Serial.begin(9600);
}
void loop() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);


  digitalWrite(S6,LOW);
  digitalWrite(S7,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);

  redFrequency2 = pulseIn(sensorOut2, LOW);
   // Printing the RED (R) value
   Serial.print("  ");
  Serial.print("R = ");
  Serial.print(redFrequency);
  Serial.print("  ");
  Serial.print("R2 = ");
  Serial.print(redFrequency2);
 
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

   digitalWrite(S6,HIGH);
  digitalWrite(S7,HIGH);
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);

    greenFrequency = pulseIn(sensorOut2, LOW);
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(greenFrequency);
  ;
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);


  digitalWrite(S6,LOW);
  digitalWrite(S7,HIGH);
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);


  blueFrequency = pulseIn(sensorOut2, LOW);
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.println(blueFrequency);










  rgb_sensor.getData();
  

  Serial.print(F("Compensated R 0:"));
  Serial.print(rgb_sensor.r_comp);
 // Serial.print(F(" G:"));
 // Serial.print(rgb_sensor.g_comp);
 // Serial.print(F(" B:"));
  //Serial.print(rgb_sensor.b_comp);
 // Serial.print(F(" C:"));
 // Serial.println(rgb_sensor.c_comp);

 // Serial.print(F("Lux:"));
 // Serial.print(rgb_sensor.lux);
 // Serial.print(F(" CT:"));
//  Serial.print(rgb_sensor.ct);
//  Serial.println(F("K"));

 // Serial.println();

//if(rgb_sensor.r_comp <= 1000)
//{
//  digitalWrite(50,HIGH);
//  digitalWrite(51,HIGH);
//}
//else 
//{  digitalWrite(50,LOW);
//digitalWrite(51,LOW);
//}


{

if(redFrequency <= 60)
{
  digitalWrite(50,HIGH);
  digitalWrite(51,HIGH);
  delay (1000);
}
else 
{  digitalWrite(50,LOW);
digitalWrite(51,LOW);
}


if(redFrequency2 <= 300)
{
  digitalWrite(50,HIGH);
  digitalWrite(51,HIGH);
  delay (1000);
}
else 
{  digitalWrite(50,LOW);
digitalWrite(51,LOW);
}


}

 
}
