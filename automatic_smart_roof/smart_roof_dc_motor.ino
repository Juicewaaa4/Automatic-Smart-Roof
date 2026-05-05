/*
 * =====================================================
 * AUTOMATIC SMART ROOF - DC MOTOR VERSION
 * =====================================================
 * 
 * Use this code if you're using a DC Motor with L298N
 * instead of a Servo Motor.
 * 
 * Components:
 * - Arduino Uno/Nano
 * - Rain Sensor Module
 * - LDR with 10K resistor
 * - DC Motor (Geared motor recommended)
 * - L298N Motor Driver Module
 * - Limit Switches (2x) - Optional but recommended
 * - LEDs (Red, Green, Yellow)
 * 
 * =====================================================
 */

// ==================== PIN DEFINITIONS ====================
// Sensor Pins
const int RAIN_SENSOR_PIN = A0;
const int LDR_PIN = A1;

// L298N Motor Driver Pins
const int MOTOR_ENA = 5;     // Enable A (PWM for speed control)
const int MOTOR_IN1 = 6;     // Input 1
const int MOTOR_IN2 = 7;     // Input 2

// Limit Switch Pins (Optional - for knowing roof position)
const int LIMIT_OPEN = 10;    // Limit switch when roof is fully open
const int LIMIT_CLOSED = 11;  // Limit switch when roof is fully closed

// LED Pins
const int LED_GREEN = 2;
const int LED_RED = 3;
const int LED_YELLOW = 4;

// ==================== SETTINGS ====================
const int RAIN_THRESHOLD = 500;
const int LIGHT_THRESHOLD = 300;
const int MOTOR_SPEED = 200;       // PWM value (0-255)
const int MOTOR_RUN_TIME = 3000;   // Time to run motor if no limit switches (ms)

// ==================== GLOBAL VARIABLES ====================
bool isRoofOpen = true;
bool useLimitSwitches = true;      // Set to false if not using limit switches

// ==================== SETUP ====================
void setup() {
  Serial.begin(9600);
  Serial.println("================================");
  Serial.println(" SMART ROOF - DC MOTOR VERSION");
  Serial.println("================================");
  
  // Motor pins
  pinMode(MOTOR_ENA, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  
  // Limit switches with internal pull-up
  pinMode(LIMIT_OPEN, INPUT_PULLUP);
  pinMode(LIMIT_CLOSED, INPUT_PULLUP);
  
  // LED pins
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  
  // Stop motor initially
  stopMotor();
  
  // Initial state
  digitalWrite(LED_GREEN, HIGH);
  
  Serial.println("System Ready!");
}

// ==================== MAIN LOOP ====================
void loop() {
  int rainValue = analogRead(RAIN_SENSOR_PIN);
  int lightValue = analogRead(LDR_PIN);
  
  // Print sensor data
  Serial.print("Rain: ");
  Serial.print(rainValue);
  Serial.print(" | Light: ");
  Serial.print(lightValue);
  Serial.print(" | Roof: ");
  Serial.println(isRoofOpen ? "OPEN" : "CLOSED");
  
  // Control logic
  if (rainValue < RAIN_THRESHOLD || lightValue < LIGHT_THRESHOLD) {
    if (isRoofOpen) {
      Serial.println(">>> Closing roof...");
      closeRoof();
    }
  } else {
    if (!isRoofOpen) {
      Serial.println(">>> Opening roof...");
      openRoof();
    }
  }
  
  delay(500);
}

// ==================== MOTOR CONTROL FUNCTIONS ====================

void openRoof() {
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  
  // Rotate motor in one direction
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, MOTOR_SPEED);
  
  if (useLimitSwitches) {
    // Wait until limit switch is triggered
    while (digitalRead(LIMIT_OPEN) == HIGH) {
      delay(10);
    }
  } else {
    // Run for fixed time
    delay(MOTOR_RUN_TIME);
  }
  
  stopMotor();
  isRoofOpen = true;
  
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, HIGH);
  Serial.println("*** Roof OPEN ***");
}

void closeRoof() {
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  
  // Rotate motor in opposite direction
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, HIGH);
  analogWrite(MOTOR_ENA, MOTOR_SPEED);
  
  if (useLimitSwitches) {
    // Wait until limit switch is triggered
    while (digitalRead(LIMIT_CLOSED) == HIGH) {
      delay(10);
    }
  } else {
    // Run for fixed time
    delay(MOTOR_RUN_TIME);
  }
  
  stopMotor();
  isRoofOpen = false;
  
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, HIGH);
  Serial.println("*** Roof CLOSED ***");
}

void stopMotor() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_ENA, 0);
}

/*
 * =====================================================
 * L298N WIRING:
 * =====================================================
 * 
 * L298N Module      →    Arduino
 * ------------           -------
 * ENA              →    D5 (PWM)
 * IN1              →    D6
 * IN2              →    D7
 * OUT1, OUT2       →    DC Motor
 * 12V              →    External 12V Power
 * GND              →    Arduino GND + External GND
 * 5V               →    Can power Arduino (remove jumper first!)
 * 
 * =====================================================
 */
