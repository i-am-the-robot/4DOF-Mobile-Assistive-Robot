#include <Servo.h>

const int gp = D6; 
const int wp = D7;   
const int ep = D3;   
const int bp = D4; 

const int inA = D0; 
const int inB = D1; 
const int inC = D2; 
const int inD = D5; 
const int bledP = D8;
String comm = "DISCONNECTED";

Servo wrist, gripper, elbow, base;
int bangle, eangle, wangle ,gangle, Activator, eangleR;



bool rotateBaseLeft = false;
bool rotateBaseRight = false;
bool rotateLift = false;
bool rotateLower = false;
bool rotatePull = false;
bool rotatePush = false;
bool rotateGripO = false;
bool rotateGripC = false;

void initialize(){
  wrist.attach(wp , 500, 2400);
  base.attach(bp, 500, 2400);
  gripper.attach(gp, 500, 2400);
  elbow.attach(ep, 500, 2400);
  gripper.write(70);
  delay(200);
  elbow.write(45);
  delay(200);
  wrist.write(110);
  delay(200);
  base.write(178);
  delay(200);
  digitalWrite(bledP, HIGH);
  delay(100);
  digitalWrite(bledP, LOW);
  delay(200);
  

  eangle = 45;
  wangle = 110;
  bangle = 178;
  gangle = 70;
  Activator = 0;
}

void setup(){
  Serial.begin(9600);
  pinMode(inA, OUTPUT);
  pinMode(inB, OUTPUT);
  pinMode(inC, OUTPUT);
  pinMode(inD, OUTPUT);
  pinMode(bledP, OUTPUT);
  initialize();
}

void turnLeft() {
  digitalWrite(inA, LOW); 
  digitalWrite(inB, HIGH);
  digitalWrite(inC, LOW); 
  digitalWrite(inD, HIGH);
}

void turnRight() { 
  digitalWrite(inA, HIGH);
  digitalWrite(inB, LOW);
  digitalWrite(inC, HIGH);
  digitalWrite(inD, LOW);
}

void moveBackward() {
  digitalWrite(inA, LOW);
  digitalWrite(inB, HIGH);
  digitalWrite(inC, HIGH);
  digitalWrite(inD, LOW);
}

void moveForward() {
  digitalWrite(inA, HIGH);
  digitalWrite(inB, LOW);
  digitalWrite(inC, LOW);
  digitalWrite(inD, HIGH);
}

void stopCar() {
  digitalWrite(inA, LOW);
  digitalWrite(inB, LOW);
  digitalWrite(inD, LOW);
  digitalWrite(inC, LOW);
}


void home(){
  gripper.write(70);
  delay(200);
  elbow.write(45);
  delay(200);
  wrist.write(110);
  delay(200);
  base.write(178);
  delay(200);
  eangle = 45;
  wangle = 110;
  bangle = 178;
  eangleR =eangle;
}


void start(){
  Activator = 1;
  gripper.write(70);
  delay(200);
  elbow.write(45);
  delay(200);
  wrist.write(110);
  delay(200);
  base.write(178);
  delay(200);
  eangle = 45;
  wangle = 110;
  bangle = 178;
  eangleR =eangle;
}

void loop(){
  if(comm == "DISCONNECTED" || comm == "DISCONNECTED+DISC:SUCCESS" || comm == "OK" || comm == "+DISC:LINK_LOSS" ){
    digitalWrite(bledP, HIGH);
    delay(100);
    digitalWrite(bledP, LOW);
    delay(100);
  }

  else{
    digitalWrite(bledP, HIGH);
    delay(100);
  }


  if (rotatePush && Activator == 1) {
    eangleR += 1;
    if (eangleR > 165) eangleR = 165;
    elbow.write(eangleR);
    delay(15);
  }

  if (rotatePull && Activator == 1) {
    eangleR -= 1;
    if (eangleR < 45) eangleR = 45;
    elbow.write(eangleR);
    delay(15);
  }

  if (rotateBaseLeft && Activator == 1) {
    bangle += 1;
    if (bangle > 180) bangle = 180;
    base.write(bangle);
    delay(15);
  }
  
  if (rotateBaseRight && Activator == 1) {
    bangle -= 1;
    if (bangle < 0) bangle = 0;
    base.write(bangle);
    delay(15);
  }
  
  if (rotateLift && Activator == 1) {
    eangle -= 1;
    wangle += 1;
    if (eangle < 45) eangle = 45;
    if (wangle > 135) wangle = 135;
    elbow.write(eangle);
    wrist.write(wangle);
    delay(15);
    eangleR =eangle;
  }
  
  if (rotateLower && Activator == 1) {
    eangle += 1;
    wangle -= 1;
    if (eangle > 165) eangle = 165;
    if (wangle < 5) wangle = 5;
    elbow.write(eangle);
    wrist.write(wangle);
    delay(15);
    eangleR =eangle;
  }

   if (rotateGripO && Activator == 1) {
    gangle += 1;
    if (gangle > 70) gangle = 70;
    gripper.write(gangle);
    delay(15);
  }
  
  if (rotateGripC && Activator == 1) {
    gangle -= 1;
    if (gangle < 30) gangle = 30;
    gripper.write(gangle);
    delay(15);
  }


  if (Serial.available()){
    comm = "";
    while (Serial.available()){
      char data = Serial.read();
      comm += data;
      delay(10);
      digitalWrite(bledP, HIGH);
      delay(10);
    }
    comm.trim();
    comm.toUpperCase();

  
    if (comm == "BL") {
      rotateBaseLeft = true;
    }
    else if (comm == "BR") {
      rotateBaseRight = true;
    }
    else if (comm == "HL") {
      rotateLift = true;
    }
    else if (comm == "LL") {
      rotateLower = true;
      
    }

    else if (comm == "PUSH") {
      rotatePush = true;
      
    }
    else if (comm == "PULL") {
      rotatePull = true;
      
    }

    else if (comm == "PK") {
      rotateGripC = true;
      
    }
    else if (comm == "PL") {
      rotateGripO = true;
      
    }
    
    
  
    else if (comm == "BLS") {
      rotateBaseLeft = false;
    }
    else if (comm == "BRS") {
      rotateBaseRight = false;
    }
    else if (comm == "HLS") {
      rotateLift = false;
    }
    else if (comm == "LLS") {
      rotateLower = false;
    }
    else if (comm == "PUSHS") {
      rotatePush = false;
      
    }
    else if (comm == "PULLS") {
      rotatePull = false;
      
    }
    else if (comm == "PKS") {
      rotateGripC = false;
      
    }
    else if (comm == "PLS") {
      rotateGripO = false;
      
    }
    
    else if (comm == "H" && Activator == 1){
      //autoPick();
      //home();  
    }
    
    else if (comm == "ST"){
      start();
    }
    else if (comm == "FWD" && Activator == 1){
      moveForward();
    }
    else if (comm == "BWD" && Activator == 1){
      moveBackward();
    }
    else if (comm == "LFT" && Activator == 1){
      turnLeft();
    }
    else if (comm == "RGT" && Activator == 1){
      turnRight();
    }
    else if (comm == "STP" && Activator == 1){
      stopCar();
      
    }

    else if (comm == "FDS" && Activator == 1){
      moveForward();
      delay(50);
      stopCar();
      delay(10);
      comm = "STP";
    }
    else if (comm == "BDS" && Activator == 1){
      moveBackward();
      delay(50);
      stopCar();
      delay(10);
      comm = "STP";
    }
    else if (comm == "LTS" && Activator == 1){
      turnLeft();
      delay(50);
      stopCar();
      delay(10);
      comm = "STP";
    }
    else if (comm == "RTS" && Activator == 1){
      turnRight();
      delay(50);
      stopCar();
      delay(10);
      comm = "STP";
    }
  Serial.println(comm);
  Serial.print("bangle = ");
  Serial.println(bangle);
  Serial.print("eangle = ");
  Serial.println (eangle);
  Serial.print("wangle = ");
  Serial.println(wangle);
  Serial.print("gangle = ");
  Serial.println(gangle);
  Serial.print("EangleR = ");
  Serial.println(eangleR);
  }


  
}