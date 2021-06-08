#include <SoftwareSerial.h>
#define inA1 2 //Định nghĩa chân in1 của động cơ A  //right
#define inA2 3 //Định nghĩa chân in2 của động cơ A
#define inB1 5 //Định nghĩa chân in1 của động cơ B  // left
#define inB2 4 //Định nghĩa chân in2 của động cơ B
#define enA 6
#define enB 11


 int M1_Speed = 80; // speed of motor 1
 int M2_Speed = 70; // speed of motor 2
 int LeftRotationSpeed = 70;  // Left Rotation Speed
 int RightRotationSpeed = 70;
 int mode2=40;
 int mode3=20;
SoftwareSerial BT(12, 13); 

char t;

 void setup() {

  pinMode(inA1,OUTPUT);
  pinMode(inA2,OUTPUT);
  pinMode(inB1,OUTPUT);
  pinMode(inB2,OUTPUT);

    pinMode(enA,OUTPUT);
    pinMode(enB,OUTPUT);
    Serial.begin(9600);
}

void loop() {

  int check;
  if((check = BT.available())>0) {
    t = BT.read();
    Serial.println(t);
    Serial.println(check);
    bluetoothControl(inB1, inB2, inA1, inA2, t);
  } else {
    Serial.println("Chay o day ------------------------------");
  
}

Bluetooth controller
void bluetoothControl(byte inR1, byte inR2, byte inL1, byte inL2, char sig) {
    if(sig == 'F'){            // Forward
      forward();// tiến thẳng
    }
    else if(sig == 'B'){      // Back
      backward();// lùi
    }
    else if(sig== 'L'){      // Left
      left();// rẽ trái
    }
 
    else if(sig == 'R'){      // Right
      right();// rẽ phải
    }
    else if(sig == 'S'){      //STOP (all motors stop)
      Stop();// stop
    } else if(sig == 'X') {
      BlackLineFollower();
    }
    delay(5);
}

void BlackLineFollower() {
  int Sensor5 = digitalRead(A4);
  int Sensor4 = digitalRead(A3);
  int Sensor3 = digitalRead(A2);
  int Sensor2 = digitalRead(A1);
  int Sensor1 = digitalRead(A0);
  int RIGHT_SIDE = Sensor1+Sensor2;
  int LEFT_SIDE = Sensor4+Sensor5;
  if(RIGHT_SIDE > LEFT_SIDE) {
    left();
  } else if(RIGHT_SIDE < LEFT_SIDE) {
    right();
  } else {
    if(RIGHT_SIDE==2){
      Stop();
    } else{
      forward();
    }
  }
}

void forward()
{
            digitalWrite(inA1, HIGH);
            digitalWrite(inA2, LOW);
            digitalWrite(inB1, HIGH);
            digitalWrite(inB2, LOW);

                analogWrite(enA, M1_Speed);
                analogWrite(enB, M2_Speed);
}

void backward()
{
            digitalWrite(inA1, LOW);
            digitalWrite(inA2, HIGH);
            digitalWrite(inB1, LOW);
            digitalWrite(inB2, HIGH);

                analogWrite(enA, M1_Speed);
                analogWrite(enB, M1_Speed);
}

void left(){
           digitalWrite(inA1,HIGH);
           digitalWrite(inA2,LOW);
           digitalWrite(inB1,LOW);
           digitalWrite(inB2,LOW);
           analogWrite(enA, 0);
           analogWrite(enB, M1_Speed);
}
void right(){
           digitalWrite(inA1,LOW);
           digitalWrite(inA2,LOW);
           digitalWrite(inB1,HIGH);
           digitalWrite(inB2,LOW);
          analogWrite(enA, M1_Speed);
          analogWrite(enB, 0);
}

void Stop()
{
            digitalWrite(inA1, LOW);
            digitalWrite(inA2, LOW);
            digitalWrite(inB1, LOW);
            digitalWrite(inB2, LOW);
}


//-----------------------------------------------
