#include <AFMotor.h>

AF_DCMotor left_motor(4, MOTOR12_64KHZ);
AF_DCMotor right_motor(2, MOTOR12_64KHZ);


boolean first=true;


//TCRT5000 Sensors
int right=A2;
int mid=A3;
int left=A4;

int seuil=200;




//Ultrasonic Sensor
long duration;         //duration of ultrasonic pulse
int distanceCm;        //distance in cm
int TRIG=A1;
int ECHO=A0;


char color( int cap){
  if (analogRead(cap)>seuil){
    return 'b';
  }else{
    return 'w';
  }
}
void tourner(char d,int vitesse){
  left_motor.setSpeed(vitesse*1.1);
  right_motor.setSpeed(vitesse);
  if (d=='r'){
    left_motor.run(FORWARD);
    right_motor.run(BACKWARD);
  }else{
    left_motor.run(BACKWARD);
    right_motor.run(FORWARD);
  }
}

void avancer(int vitesse){
    left_motor.setSpeed(vitesse*1.1);
    right_motor.setSpeed(vitesse);
    left_motor.run(FORWARD);
    right_motor.run(FORWARD);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode(TRIG, OUTPUT);    //Analog pin A1 connected to TRIG
  pinMode(ECHO, INPUT);     //Analog pin A0 connected to ECHO
}

void ultra(){
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);    //give a pulse of 10us on TRIG
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);     //check time elasped in receiving back the pulse on ECHO
  distanceCm = duration * 0.034 / 2; //convert to distance in cm
}

void partie1(){
  if(color(right)=='b'){
    tourner('r',70);
  }else if (color(mid)=='b'){
    avancer(70);
  }else if (color(left)=='b'){
    tourner('l',70);
  }else{
    tourner('l',70);
  }
}

void partie2(){
  if (color(left)=='b'){
    tourner('l',70);
  }else if (color(mid)=='b'){
    avancer(70);
  }else if(color(right)=='b'){
    tourner('r',70);
  }else{
    tourner('r',70); 
   }
  }

void partie3(){
  if (color(left)=='b'){
    tourner('l',70);
  }else if (color(mid)=='b'){
    avancer(70);
  }else if(color(right)=='b'){
    tourner('r',70);
  }else{
    if (first){
      while(color(right)=='w' && color(mid)=='w' && color(left)=='w')
      {
        tourner('r',70);
      }
      first=false;
    }else{
     while(true){
      avancer(0);
    }
   }
  }
}


void printDistance(){
  ultra();
  Serial.println("Distance= "+(String)distanceCm);
}

void loop() {
  ultra();
  if (distanceCm>15){
    avancer(70);
  }
  else{
    avancer(0);
    delay(500);
    tourner('r',70);
    delay(500);
  }
}
