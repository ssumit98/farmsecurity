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









#include <SoftwareSerial.h>
SoftwareSerial mySerial(9,10);
char msg;
char call;


// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int redFrequency2 = 0;



void setup() {

  

 mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  Serial.println("GSM SIM900A BEGIN");
  Serial.println("Enter character for control option:");
  Serial.println("h : to disconnect a call");
  Serial.println("i : to receive a call");
  Serial.println("s : to send message");
  Serial.println("c : to make a call");  
  Serial.println("e : to redial");
  Serial.println();
  delay(100);

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

}
void loop(){ 
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
 
  
 
 



{

if(redFrequency >= 2)
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+917768058802\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println(" height 1 intrusion detected");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  mySerial.println("ATD+917768058802;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  Serial.println("Calling  "); // print response over serial port
  delay(1000);
  digitalWrite(50,HIGH);
  digitalWrite(51,HIGH);
  delay (10000);
}
else 
{  digitalWrite(50,LOW);
digitalWrite(51,LOW);
}


if(redFrequency2 >= 100)
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+917768058802\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("intrusion detected");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  mySerial.println("ATD+917768058802;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  Serial.println("Calling  "); // print response over serial port
  digitalWrite(50,HIGH);
  digitalWrite(51,HIGH);

  delay (10000);
}
else 
{  digitalWrite(50,LOW);
digitalWrite(51,LOW);
}


}

 
}
