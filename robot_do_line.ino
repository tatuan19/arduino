#define in1 2
#define in2 3
#define in3 4
#define in4 5
#define enA 6
#define enB 11


 int M1_Speed = 120; // speed of motor 1
 int M2_Speed = 100; // speed of motor 2
 int LeftRotationSpeed = 150;  // Left Rotation Speed
 int RightRotationSpeed = 150; // Right Rotation Speed


 void setup() {

  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

    pinMode(enA,OUTPUT);
    pinMode(enB,OUTPUT);

      pinMode(A2, INPUT); // initialize Left sensor as an input
      pinMode(A1, INPUT); // initialize Mid sensor as an input
      pinMode(A0, INPUT); // initialize Right sensor as an input

}

void loop() {

  int LEFT_SENSOR = digitalRead(A0);
  int MID_SENSOR = digitalRead(A1);
  int RIGHT_SENSOR = digitalRead(A2);
  int RIGHT_SIDE = RIGHT_SENSOR + MID_SENSOR;
  int LEFT_SIDE = LEFT_SENSOR + MID_SENSOR;

if(RIGHT_SIDE == LEFT_SIDE) {
    if(RIGHT_SIDE == 2) {
      Stop();
    } else {
      forward(); //FORWARD
    }
}

  else if(LEFT_SIDE > RIGHT_SIDE) {
    left(); //Move Right
 }

  else if(RIGHT_SIDE > LEFT_SIDE) {
    right(); //Move Left
  }
}



void forward()
{
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            digitalWrite(in3, HIGH);
            digitalWrite(in4, LOW);

                analogWrite(enA, M1_Speed);
                analogWrite(enB, M2_Speed);
}

void backward()
{
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);

                analogWrite(enA, M1_Speed);
                analogWrite(enB, M2_Speed);
}

void right()
{
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);

                analogWrite(enA, LeftRotationSpeed);
                analogWrite(enB, RightRotationSpeed);
}

void left()
{
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, HIGH);
            digitalWrite(in4, LOW);

                analogWrite(enA, LeftRotationSpeed);
                analogWrite(enB, RightRotationSpeed);
}

void Stop()
{
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            digitalWrite(in3, LOW);
            digitalWrite(in4, LOW);
}
