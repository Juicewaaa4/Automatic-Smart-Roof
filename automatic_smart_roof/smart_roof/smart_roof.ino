/*
 * =====================================================
 * AUTOMATIC SMART ROOF - 360° Servo Version
 * =====================================================
 * 
 * Rain detected = Servo spins to CLOSE roof, then STOPS
 * No rain       = Servo spins REVERSE to OPEN roof, then STOPS
 * 
 * Components:
 * - Arduino Uno
 * - Rain Sensor Module (AO → A0)
 * - 360° Continuous Rotation Servo Motor (Signal → Pin 9)
 * - LEDs (Green=Pin2, Red=Pin3)
 * =====================================================
 */

#include <Servo.h>

// ==================== PINS ====================
const int RAIN_SENSOR_PIN = A0;
const int SERVO_PIN = 9;
const int LED_GREEN = 2;
const int LED_RED = 3;

// ==================== SETTINGS ====================
const int RAIN_THRESHOLD = 500;    // Below 500 = WET

// 360° Servo: 90=STOP, 0=one direction, 180=other direction
const int SERVO_STOP = 90;
const int SERVO_FORWARD = 115;     // Medium-slow open
const int SERVO_REVERSE = 65;      // Medium-slow close
const int MOVE_TIME = 6000;        // 6 seconds for 7 inches

const int READ_DELAY = 500;

// ==================== VARIABLES ====================
Servo roofServo;
bool isRoofOpen = true;

// ==================== SETUP ====================
void setup() {
  Serial.begin(9600);
  Serial.println("================================");
  Serial.println("  AUTOMATIC SMART ROOF");
  Serial.println("  360 Servo Version");
  Serial.println("================================");
  
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  // Attach servo and STOP it immediately
  roofServo.attach(SERVO_PIN);
  roofServo.write(SERVO_STOP);
  delay(500);
  
  // Start with roof OPEN
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
  isRoofOpen = true;
  
  // Wait for sensor to stabilize
  delay(1000);
  
  Serial.println("System Ready! Roof is OPEN");
  Serial.println("--------------------------------");
}

// ==================== MAIN LOOP ====================
void loop() {
  int rainValue = analogRead(RAIN_SENSOR_PIN);
  
  // Print status
  Serial.print("Rain: ");
  Serial.print(rainValue);
  if (rainValue < RAIN_THRESHOLD) {
    Serial.print(" (WET)");
  } else {
    Serial.print(" (DRY)");
  }
  Serial.print(" | Roof: ");
  Serial.println(isRoofOpen ? "OPEN" : "CLOSED");
  
  // === RAIN DETECTED = CLOSE ROOF ===
  if (rainValue < RAIN_THRESHOLD && isRoofOpen) {
    Serial.println(">>> RAIN! Closing roof...");
    
    // LEDs
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
    
    // Spin servo REVERSE to close
    roofServo.write(SERVO_REVERSE);
    delay(MOVE_TIME);
    roofServo.write(SERVO_STOP);  // STOP!
    
    isRoofOpen = false;
    Serial.println("*** Roof CLOSED ***");
    Serial.println("--------------------------------");
  }
  
  // === NO RAIN = OPEN ROOF ===
  if (rainValue >= RAIN_THRESHOLD && !isRoofOpen) {
    Serial.println(">>> DRY! Opening roof...");
    
    // LEDs
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    
    // Spin servo FORWARD to open (opposite direction!)
    roofServo.write(SERVO_FORWARD);
    delay(MOVE_TIME);
    roofServo.write(SERVO_STOP);  // STOP!
    
    isRoofOpen = true;
    Serial.println("*** Roof OPEN ***");
    Serial.println("--------------------------------");
  }
  
  delay(READ_DELAY);
}
