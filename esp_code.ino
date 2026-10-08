/*
 * ============================================================
 *          8-DOF QUADRUPED ROBOT
 * ============================================================
 *
 * Controller : ESP32
 * Servo Driver: PCA9685 16-Channel PWM
 * Servos      : 8 x SG90S
 *
 * I2C:
 * SDA -> GPIO 21
 * SCL -> GPIO 22
 *
 * PCA9685 Address:
 * 0x40
 *
 * Servo Mapping:
 *
 * CH0 -> Front Left Hip
 * CH1 -> Front Left Knee
 *
 * CH2 -> Front Right Hip
 * CH3 -> Front Right Knee
 *
 * CH4 -> Rear Left Hip
 * CH5 -> Rear Left Knee
 *
 * CH6 -> Rear Right Hip
 * CH7 -> Rear Right Knee
 *
 * ============================================================
 */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// ------------------------------------------------------------
// PCA9685
// ------------------------------------------------------------

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// PCA9685 PWM frequency for servos
#define SERVO_FREQ 50

// ------------------------------------------------------------
// Servo Channels
// ------------------------------------------------------------

// Front Left
#define FL_HIP   0
#define FL_KNEE  1

// Front Right
#define FR_HIP   2
#define FR_KNEE  3

// Rear Left
#define RL_HIP   4
#define RL_KNEE  5

// Rear Right
#define RR_HIP   6
#define RR_KNEE  7


// ------------------------------------------------------------
// Servo Calibration
// ------------------------------------------------------------

// Typical SG90 servo pulse range.
// These values may need adjustment for your particular servos.

#define SERVO_MIN  110
#define SERVO_MAX  500


// ------------------------------------------------------------
// Convert angle to PCA9685 pulse
// ------------------------------------------------------------

int angleToPulse(int angle)
{
  angle = constrain(angle, 0, 180);

  return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
}


// ------------------------------------------------------------
// Move one servo
// ------------------------------------------------------------

void setServo(int channel, int angle)
{
  angle = constrain(angle, 0, 180);

  int pulse = angleToPulse(angle);

  pwm.setPWM(channel, 0, pulse);
}


// ------------------------------------------------------------
// Move servo smoothly
// ------------------------------------------------------------

void smoothServo(int channel, int startAngle, int endAngle, int delayTime)
{
  if (startAngle < endAngle)
  {
    for (int angle = startAngle; angle <= endAngle; angle++)
    {
      setServo(channel, angle);
      delay(delayTime);
    }
  }
  else
  {
    for (int angle = startAngle; angle >= endAngle; angle--)
    {
      setServo(channel, angle);
      delay(delayTime);
    }
  }
}


// ------------------------------------------------------------
// Set all servos
// ------------------------------------------------------------

void setAllServos(int angle)
{
  for (int channel = 0; channel < 8; channel++)
  {
    setServo(channel, angle);
  }
}


// ------------------------------------------------------------
// Servo Test
// ------------------------------------------------------------

void servoTest()
{
  Serial.println("Starting servo test...");

  for (int channel = 0; channel < 8; channel++)
  {
    Serial.print("Testing Servo Channel: ");
    Serial.println(channel);

    setServo(channel, 90);
    delay(500);

    setServo(channel, 0);
    delay(500);

    setServo(channel, 180);
    delay(500);

    setServo(channel, 90);
    delay(500);
  }

  Serial.println("Servo test completed.");
}


// ============================================================
//              QUADRUPED POSITIONS
// ============================================================

/*
 * IMPORTANT:
 *
 * These angles are starting values only.
 *
 * Depending on how your servos are physically mounted,
 * some joints may need their angles reversed.
 *
 * Tune these values after assembling the robot.
 */


// ------------------------------------------------------------
// Standing Position
// ------------------------------------------------------------

void stand()
{
  Serial.println("Robot -> STANDING");

  // Front Left
  setServo(FL_HIP, 90);
  setServo(FL_KNEE, 90);

  // Front Right
  setServo(FR_HIP, 90);
  setServo(FR_KNEE, 90);

  // Rear Left
  setServo(RL_HIP, 90);
  setServo(RL_KNEE, 90);

  // Rear Right
  setServo(RR_HIP, 90);
  setServo(RR_KNEE, 90);

  delay(1000);
}


// ------------------------------------------------------------
// Sit Position
// ------------------------------------------------------------

void sit()
{
  Serial.println("Robot -> SITTING");

  // Front legs
  setServo(FL_HIP, 90);
  setServo(FL_KNEE, 140);

  setServo(FR_HIP, 90);
  setServo(FR_KNEE, 140);

  // Rear legs
  setServo(RL_HIP, 90);
  setServo(RL_KNEE, 40);

  setServo(RR_HIP, 90);
  setServo(RR_KNEE, 40);

  delay(1000);
}


// ------------------------------------------------------------
// Neutral Position
// ------------------------------------------------------------

void neutral()
{
  Serial.println("Robot -> NEUTRAL");

  setServo(FL_HIP, 90);
  setServo(FL_KNEE, 90);

  setServo(FR_HIP, 90);
  setServo(FR_KNEE, 90);

  setServo(RL_HIP, 90);
  setServo(RL_KNEE, 90);

  setServo(RR_HIP, 90);
  setServo(RR_KNEE, 90);
}


// ============================================================
//              BASIC LEG MOVEMENTS
// ============================================================

// ------------------------------------------------------------
// Lift Front Left Leg
// ------------------------------------------------------------

void liftFrontLeft()
{
  Serial.println("Lifting Front Left Leg");

  setServo(FL_HIP, 70);
  setServo(FL_KNEE, 130);

  delay(500);
}


// ------------------------------------------------------------
// Lift Front Right Leg
// ------------------------------------------------------------

void liftFrontRight()
{
  Serial.println("Lifting Front Right Leg");

  setServo(FR_HIP, 110);
  setServo(FR_KNEE, 130);

  delay(500);
}


// ------------------------------------------------------------
// Lift Rear Left Leg
// ------------------------------------------------------------

void liftRearLeft()
{
  Serial.println("Lifting Rear Left Leg");

  setServo(RL_HIP, 70);
  setServo(RL_KNEE, 50);

  delay(500);
}


// ------------------------------------------------------------
// Lift Rear Right Leg
// ------------------------------------------------------------

void liftRearRight()
{
  Serial.println("Lifting Rear Right Leg");

  setServo(RR_HIP, 110);
  setServo(RR_KNEE, 50);

  delay(500);
}


// ============================================================
//              SIMPLE WALKING SEQUENCE
// ============================================================

void walkForward()
{
  Serial.println("Robot -> WALK FORWARD");

  /*
   * Basic diagonal gait:
   *
   * Pair 1:
   * Front Left + Rear Right
   *
   * Pair 2:
   * Front Right + Rear Left
   *
   * This is a starting gait and will require
   * mechanical tuning.
   */

  // ----------------------------------------------------------
  // STEP 1
  // Lift diagonal pair
  // ----------------------------------------------------------

  setServo(FL_HIP, 70);
  setServo(FL_KNEE, 130);

  setServo(RR_HIP, 110);
  setServo(RR_KNEE, 50);

  delay(300);


  // ----------------------------------------------------------
  // Move lifted legs forward
  // ----------------------------------------------------------

  setServo(FL_HIP, 110);
  setServo(RR_HIP, 70);

  delay(300);


  // ----------------------------------------------------------
  // Put legs down
  // ----------------------------------------------------------

  setServo(FL_KNEE, 90);
  setServo(RR_KNEE, 90);

  delay(300);


  // ----------------------------------------------------------
  // STEP 2
  // Other diagonal pair
  // ----------------------------------------------------------

  setServo(FR_HIP, 110);
  setServo(FR_KNEE, 130);

  setServo(RL_HIP, 70);
  setServo(RL_KNEE, 50);

  delay(300);


  // Move legs forward

  setServo(FR_HIP, 70);
  setServo(RL_HIP, 110);

  delay(300);


  // Put legs down

  setServo(FR_KNEE, 90);
  setServo(RL_KNEE, 90);

  delay(300);
}


// ============================================================
//              SERIAL COMMAND SYSTEM
// ============================================================

void serialCommands()
{
  if (Serial.available())
  {
    char command = Serial.read();

    switch (command)
    {
      case 's':
        stand();
        break;

      case 'x':
        sit();
        break;

      case 'n':
        neutral();
        break;

      case 't':
        servoTest();
        break;

      case 'w':
        walkForward();
        break;

      case '1':
        liftFrontLeft();
        break;

      case '2':
        liftFrontRight();
        break;

      case '3':
        liftRearLeft();
        break;

      case '4':
        liftRearRight();
        break;

      default:
        Serial.println("Unknown command.");
        break;
    }
  }
}


// ============================================================
//                     SETUP
// ============================================================

void setup()
{
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("====================================");
  Serial.println("   8-DOF QUADRUPED ROBOT");
  Serial.println("====================================");

  // Initialize I2C
  Wire.begin(21, 22);

  Serial.println("Initializing PCA9685...");

  // Initialize PCA9685
  pwm.begin();

  // Set servo PWM frequency
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);

  delay(500);

  Serial.println("PCA9685 initialized.");
  Serial.println("I2C Address: 0x40");
  Serial.println("Servo Frequency: 50 Hz");

  // Move robot to neutral position
  neutral();

  delay(1000);

  Serial.println();
  Serial.println("Commands:");
  Serial.println("-----------------------------");
  Serial.println("s = Stand");
  Serial.println("x = Sit");
  Serial.println("n = Neutral");
  Serial.println("t = Servo Test");
  Serial.println("w = Walk Forward");
  Serial.println("1 = Lift Front Left");
  Serial.println("2 = Lift Front Right");
  Serial.println("3 = Lift Rear Left");
  Serial.println("4 = Lift Rear Right");
  Serial.println("-----------------------------");
}


// ============================================================
//                      LOOP
// ============================================================

void loop()
{
  serialCommands();
}
