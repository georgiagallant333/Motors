/* Moves all motors forward. Includes move functions for all four motors.
*/

byte cmd[4]; //array to send to motor controllers
//making hex commands into english to make it easier to understand
#define QIK_MOTOR_M0_FORWARD             0x08
#define QIK_MOTOR_M0_FORWARD_8_BIT       0x09
#define QIK_MOTOR_M0_REVERSE             0x0A
#define QIK_MOTOR_M0_REVERSE_8_BIT       0x0B
#define QIK_MOTOR_M1_FORWARD             0x0C
#define QIK_MOTOR_M1_FORWARD_8_BIT       0x0D
#define QIK_MOTOR_M1_REVERSE             0x0E
#define QIK_MOTOR_M1_REVERSE_8_BIT       0x0F

#define QIK_2S12V10_MOTOR_M0_BRAKE       0x86
#define QIK_2S12V10_MOTOR_M1_BRAKE       0x87


//to get errors so they clear
byte errorMotor1[3] = {0xAA, 0x0A, 0x02}; //0xAA autodetects baud rate, device number in hex, idk?
byte errorMotor2[3] = {0xAA, 0x0B, 0x02};


void setup() {
  Serial1.begin(9600);
  //writing to motorcontrollers to clear error
  Serial1.write(errorMotor1, 3);
  Serial1.write(errorMotor2, 3);
  //setting first byte to set them to autodetect baud rate
  cmd[0] = 0xAA;
}

void loop() {
  //setting speed
//  setBLSpeed(100); //M1
//  setFLSpeed(100); //M2
//  setFRSpeed(100); //M3
//  setBRSpeed(100); //M4
}
///////////////////////////////////////////MOVING//////////////////////////////////////

////////////////////////////////M0//////////////////////////
void setBLSpeed(int speed)
{
  cmd[1] = 0x0B; //setting second byte which is the device number in hex
  boolean reverse = 0;
  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1; // preserve the direction
  }

  if (speed > 255)
    speed = 255;

  if (speed > 127)
  {
    // 8-bit mode: actual speed is (speed + 128)
    cmd[2] = reverse ? QIK_MOTOR_M0_REVERSE_8_BIT : QIK_MOTOR_M0_FORWARD_8_BIT;
    cmd[3] = speed - 128;
  }
  else
  {
    cmd[2] = reverse ? QIK_MOTOR_M0_REVERSE : QIK_MOTOR_M0_FORWARD;
    cmd[3] = speed;
  }

  Serial1.write(cmd, 4); //sending all bytes (0xAA, device number, command, speed)
}


////////////////////////////////M1//////////////////////////
void setFLSpeed(int speed)
{
  cmd[1] = 0x0B;
  boolean reverse = 0;

  if (speed > 255)
    speed = 255;

  if (speed > 127)
  {
    // 8-bit mode: actual speed is (speed + 128)
    cmd[2] = reverse ? QIK_MOTOR_M1_REVERSE_8_BIT : QIK_MOTOR_M1_FORWARD_8_BIT;
    cmd[3] = speed - 128;
  }
  else
  {
    cmd[2] = reverse ? QIK_MOTOR_M1_REVERSE : QIK_MOTOR_M1_FORWARD;
    cmd[3] = speed;
  }

  Serial1.write(cmd, 4);
}

////////////////////////////////M2//////////////////////////
void setFRSpeed(int speed)
{
  cmd[1] = 0x0A;
  boolean reverse = 0;
  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1; // preserve the direction
  }

  if (speed > 255)
    speed = 255;

  if (speed > 127)
  {
    // 8-bit mode: actual speed is (speed + 128)
    cmd[2] = reverse ? QIK_MOTOR_M0_REVERSE_8_BIT : QIK_MOTOR_M0_FORWARD_8_BIT;
    cmd[3] = speed - 128;
  }
  else
  {
    cmd[2] = reverse ? QIK_MOTOR_M0_REVERSE : QIK_MOTOR_M0_FORWARD;
    cmd[3] = speed;
  }

  Serial1.write(cmd, 4);
}

////////////////////////////////M3//////////////////////////
void setBRSpeed(int speed)
{
  cmd[1] = 0x0A;
  boolean reverse = 0;

  if (speed > 255)
    speed = 255;

  if (speed > 127)
  {
    // 8-bit mode: actual speed is (speed + 128)
    cmd[2] = reverse ? QIK_MOTOR_M1_REVERSE_8_BIT : QIK_MOTOR_M1_FORWARD_8_BIT;
    cmd[3] = speed - 128;
  }
  else
  {
    cmd[2] = reverse ? QIK_MOTOR_M1_REVERSE : QIK_MOTOR_M1_FORWARD;
    cmd[3] = speed;
  }

  Serial1.write(cmd, 4);
}

///////////////////////////////////////BREAKING///////////////////////////////////////
void setBLBrake(unsigned char brake)
{
  cmd[1] = 0x0B; //setting second byte which is the device number in hex
  if (brake > 127)
    brake = 127;
  
  cmd[2] = QIK_2S12V10_MOTOR_M0_BRAKE;
  cmd[3] = brake;
  Serial1.write(cmd, 4);
}

void setFLBrake(unsigned char brake)
{
  cmd[1] = 0x0B; //setting second byte which is the device number in hex
  if (brake > 127)
    brake = 127;
  
  cmd[2] = QIK_2S12V10_MOTOR_M1_BRAKE;
  cmd[3] = brake;
  Serial1.write(cmd, 4);
}

void setFRBrake(unsigned char brake)
{
  cmd[1] = 0x0A; //setting second byte which is the device number in hex
  if (brake > 127)
    brake = 127;
  
  cmd[2] = QIK_2S12V10_MOTOR_M0_BRAKE;
  cmd[3] = brake;
  Serial1.write(cmd, 4);
}

void setBRBrake(unsigned char brake)
{
  cmd[1] = 0x0A; //setting second byte which is the device number in hex
  if (brake > 127)
    brake = 127;
  
  cmd[2] = QIK_2S12V10_MOTOR_M1_BRAKE;
  cmd[3] = brake;
  Serial1.write(cmd, 4);
}
