// ir sensor 
const int sensor_left = 6;
const int sensor_middle_left = 5;
const int sensor_middle = 4;
const int sensor_middle_right = 3;
const int sensor_right = 2;

// ir motor L-R
const int motor_EN_A = 9; //motor power A
const int motor_EN_B = 10; //motor power B
const int motor_IN4 = 8;
const int motor_IN3 = 11;
const int motor_IN2 = 12;
const int motor_IN1 = 13;

// ir absove
const int BLACK = LOW;
const int WHITE = HIGH;

//speed ctrl
const int SPEED_Fast = 180;
const int SPEED_Direct = 140;
const int SPEED_Curve = 120;
const int SPEED_Slow = 90;
const int SPEED_Reverse = 80;

void setup() {
  // Input Sensors (5 sensors on prototype)
  pinMode(sensor_left, INPUT);
  pinMode(sensor_middle_left, INPUT);
  pinMode(sensor_middle, INPUT);
  pinMode(sensor_middle_right, INPUT);
  pinMode(sensor_right, INPUT);

  // Output Motor (L298)
  // Right on A 1 2
  // Left  on B 3 4
  pinMode(motor_EN_A, OUTPUT);
  pinMode(motor_EN_B, OUTPUT);
  pinMode(motor_IN1, OUTPUT);
  pinMode(motor_IN2, OUTPUT);
  pinMode(motor_IN3, OUTPUT);
  pinMode(motor_IN4, OUTPUT);

  left_dir(0);
  right_dir(0);
  motor_power(SPEED_Direct, SPEED_Direct);
}


/*===============================================================================================================================================================================*/


void loop() {
  int left = digitalRead(sensor_left);
  int middle_left = digitalRead(sensor_middle_left);
  int middle = digitalRead(sensor_middle);
  int middle_right = digitalRead(sensor_middle_right);
  int right = digitalRead(sensor_right);

  if (middle == BLACK && middle_left == BLACK && middle_right == BLACK && left == BLACK && right == BLACK) {
    stop_dir(1);
    back_dir(1);
    
    motor_power(SPEED_Direct, SPEED_Direct);
  }
  else if (middle == WHITE && middle_left == WHITE && middle_right == WHITE && left == WHITE && right == WHITE) {
    left_dir(1);
    right_dir(1);
    motor_power(SPEED_Direct, SPEED_Direct);
  }
  else if (left == BLACK) {
    // left_dir(0);
    // right_dir(1);
    motor_power(0, SPEED_Curve);
    delay(100);
  }
  else if (right == BLACK) {
    // left_dir(1);
    // right_dir(0);
    motor_power(SPEED_Curve, 0);
    delay(100);
  }
  else if ((left == BLACK || middle_left == BLACK) && middle_right == WHITE && middle == WHITE) {
    // left_dir(0);
    // right_dir(1);
    motor_power(0, SPEED_Curve);
    delay(50);
  }
  else if (middle_left == WHITE && middle == WHITE && (middle_right == BLACK || right == BLACK)) {
    // left_dir(1);
    // right_dir(0);
    motor_power(SPEED_Curve, 0);
    delay(50);
  }
  else if ((left == BLACK || middle_left == BLACK ) && middle == BLACK) {
    // left_dir(0);
    // right_dir(1);
    motor_power(0, SPEED_Curve);
    delay(50);
  }
  else if ((right == BLACK || middle_right == BLACK ) && middle == BLACK) {
    // left_dir(1);
    // right_dir(0);
    motor_power(SPEED_Curve, 0);
    delay(50);
  }
  else {
    left_dir(0);
    right_dir(0);
    motor_power(SPEED_Reverse, SPEED_Reverse);
  }
}



/*===============================================================================================================================================================================*/



void left_dir(int forward)
{    
    digitalWrite(motor_IN1, HIGH);
    digitalWrite(motor_IN2, LOW);
    digitalWrite(motor_IN3, LOW);
    digitalWrite(motor_IN4, LOW);

}

void right_dir(int forward)
{
    
    digitalWrite(motor_IN1, LOW);
    digitalWrite(motor_IN2, LOW);
    digitalWrite(motor_IN3, HIGH);
    digitalWrite(motor_IN4, LOW);
}

void forward_dir(int forward)
{
    digitalWrite(motor_IN1, HIGH);
    digitalWrite(motor_IN2, LOW);
    digitalWrite(motor_IN3, HIGH);
    digitalWrite(motor_IN4, LOW);
}

void back_dir(int forward)
{
    digitalWrite(motor_IN1, LOW);
    digitalWrite(motor_IN2, HIGH);
    digitalWrite(motor_IN3, LOW);
    digitalWrite(motor_IN4, HIGH);
}

void stop_dir(int forward)
{
    digitalWrite(motor_IN1, LOW);
    digitalWrite(motor_IN2, LOW);
    digitalWrite(motor_IN3, LOW);
    digitalWrite(motor_IN4, LOW);
    delay(2000);
}


void motor_power(int left, int right)
{
  if (left == 0)
    digitalWrite(motor_EN_B, LOW);
  else
    analogWrite(motor_EN_B, left);

  if (right == 0)
    digitalWrite(motor_EN_A, LOW);
  else
    analogWrite(motor_EN_A, right);
}

