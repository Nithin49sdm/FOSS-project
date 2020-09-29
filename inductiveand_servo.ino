#include <Servo.h>
#include <SoftwareSerial.h>
 #define trigger  3
#define echo     4
 int sen=8;
int time_;
float distance, dist_limit = 20.00;//cms
String pilih;

int buzz = 13;

Servo myservo;  
       int pos = 0;       
int x;
void setup() {

Serial.begin(9600); // Setting the baud rate of GSM Module

Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)

//RecieveMessage();

delay(100);
 pinMode(buzz, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(buzz, LOW);     //set the buzzer in off mode (initial condition)


   myservo.attach(9);
pinMode(sen,INPUT);
Serial.begin(9600);
}

void loop() {
  int c=ultrasound();
 if (c==1)
 {
 digitalWrite(buzz,HIGH);

if (Serial.available()>0)
SendMessage();
 }
else
{
digitalWrite(buzz,LOW);
}

  
x=digitalRead(sen);
Serial.println(x);
if(x==HIGH)
serv();
delay(500);
}
void serv(){
for(pos = 0; pos <60; pos += 1)  // goes from 0 degrees to 180 degrees
 {                                  // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
 }
 delay(1250);
 for(pos =60; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees
 {
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
 }
// delay(2500);
}

void SendMessage()

{

Serial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode

delay(1000); // Delay of 1000 milli seconds or 1 second

Serial.println("AT+CMGS=\"+7996783508\"\r"); // Replace x with mobile number

delay(1000);

Serial.println("the dustbin was completely fill");// The SMS text you want to send

Serial.println(pilih);

delay(100);

Serial.println((char)26);// ASCII code of CTRL+Z

delay(1000);

}


int ultrasound(void)
{
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  time_ = pulseIn(echo,HIGH);
  distance = time_*0.01725;
  Serial.println(distance);
  if (distance <= dist_limit)
    return 1;
  else
    return 0;
}
