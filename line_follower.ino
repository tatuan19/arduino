/*Mert Arduino and Raspberry Pi - Line Following Robot*/
#include <SoftwareSerial.h>

//Define Pins

int ENA = 6; //Enable Pin of the Right Motor (must be PWM)
//int IN1 = 2; //Control Pin
//int IN2 = 3;

int ENB = 11; //Enable Pin of the Left Motor (must be PWM)
//int IN3 = 4;
//int IN4 = 5;

#define inA1 5 //Định nghĩa chân in1 của động cơ A  //right
#define inA2 4//Định nghĩa chân in2 của động cơ A
#define inB1 2 //Định nghĩa chân in1 của động cơ B  // left
#define inB2 3 //Định nghĩa chân in2 của động cơ B


//Speed of the Motors
#define ENASpeed 120 
#define ENBSpeed 120

int Sensor1 = 0;
int Sensor2 = 0;
int Sensor3 = 0;

SoftwareSerial BT(12, 13); 

char t;

void setup() {
  Serial.begin(9600);
  
  pinMode(ENA, OUTPUT);
//  pinMode(IN1, OUTPUT);
//  pinMode(IN2, OUTPUT);
//
  pinMode(ENB, OUTPUT);
//  pinMode(IN3, OUTPUT);
//  pinMode(IN4, OUTPUT);

   pinMode(inA1, OUTPUT);//Set chân in1 của dc A là output
  pinMode(inA2, OUTPUT);//Set chân in2 của dc A là output
  pinMode(inB1, OUTPUT);//Set chân in1 của dc B là output
  pinMode(inB2, OUTPUT);//Set chân in2 của dc B là output
  
  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Sensor3, INPUT);

  // set the data rate for the SoftwareSerial port
  BT.begin(9600);
  // Send test message to other device
  BT.println("Hello from Arduino");
  Serial.begin(9600);
}

void loop(){

  //Use analogWrite to run motor at adjusted speed
  analogWrite(ENA, ENASpeed);
  analogWrite(ENB, ENBSpeed);

  //Read the Sensor if HIGH (BLACK Line) or LOW (WHITE Line)
  Sensor1 = digitalRead(8);
  Sensor2 = digitalRead(9);
  Sensor3 = digitalRead(10);

  int check;
  if((check = BT.available())>0) {
    t = BT.read();
    Serial.println(t);
    Serial.println(check);
    bluetoothControl(inB1, inB2, inA1, inA2, t);
  } else {
//    Serial.println("Chay o day ------------------------------");
//    darkLineFollower();
  }
}

// --------------------------------------------------------------------------------------
void bluetoothControl(byte inR1, byte inR2, byte inL1, byte inL2, char sig) {
    if(sig == 'F'){            // Forward
      dithang();// tiến thẳng
    }
    else if(sig == 'B'){      // Back
      lui();// lùi
    }
    else if(sig== 'L'){      // Left
      quaytrai();// rẽ trái
    }
 
    else if(sig == 'R'){      // Right
      quayphai();// rẽ phải
    }
    else if(sig == 'S'){      //STOP (all motors stop)
      dung();// stop
    }
    delay(5);
}

void darkLineFollower() {
  //0 sang 
  //1 toi -> đèn tắt -> gặp đen
  Serial.print("p1:");
  Serial.println(Sensor1);
  Serial.print("p2:");
  Serial.println(Sensor3);
  Serial.print("p3:");
  Serial.println(Sensor3);

  //Set conditions for FORWARD, LEFT and RIGHT
  int right = 0, left = 0, deviation = 0;
  right = analogRead(Sensor1)+analogRead(Sensor2);  //bao nhiêu cái bên phải trong màu đen
  left = analogRead(Sensor3)+analogRead(Sensor2);   //bao nhiêu cái bên trái trong màu đen
  
  if (right == 0 && left == 0) {lui();} //Trượt ra khỏi Line thì lùi lại
  else {deviation = right - left;}

  if (deviation > 0){
    Serial.println("Lệch trái");
    quaytrai();//Lệch trái, thỳ quay trái
  }
  else if (deviation < 0){
  Serial.println("Lệch phải");
  quayphai();}//lệch phải thì quay phải
  else if (deviation == 0){
  dithang();}//Không lệch đi thẳng
}

void dithang(){
           digitalWrite(inA1,HIGH);
           digitalWrite(inA2,LOW);
           digitalWrite(inB1,HIGH);
           digitalWrite(inB2,LOW);
   
}
void lui(){
           digitalWrite(inA1,LOW);
           digitalWrite(inA2,HIGH);
           digitalWrite(inB1,LOW);
           digitalWrite(inB2,HIGH);
}
void quaytrai(){
           digitalWrite(inA1,HIGH);
           digitalWrite(inA2,LOW);
           digitalWrite(inB1,LOW);
           digitalWrite(inB2,LOW);
}
void quayphai(){
           digitalWrite(inA1,LOW);
           digitalWrite(inA2,LOW);
           digitalWrite(inB1,HIGH);
           digitalWrite(inB2,LOW);
}
void dung() {
           digitalWrite(inA1,LOW);
           digitalWrite(inA2,LOW);
           digitalWrite(inB1,LOW);
           digitalWrite(inB2,LOW);
}
