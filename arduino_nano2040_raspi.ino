// Pin definition
const int IN1_A = 2;
const int IN2_A = 4;
const int IN1_B = 3;
const int IN2_B = 5;

void setup() {
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "CW") {
      rotateMotorCW();
    } else if (command == "CCW") {
      rotateMotorCCW();
    } else if (command == "STOP") {
      stopMotor();
    } else {
      // Unknown command, do nothing
    }
  }
}

void rotateMotorCW() {
  digitalWrite(IN1_A, HIGH);
  digitalWrite(IN2_A, LOW);
  digitalWrite(IN1_B, HIGH);
  digitalWrite(IN2_B, LOW);
}

void rotateMotorCCW() {
  digitalWrite(IN1_A, LOW);
  digitalWrite(IN2_A, HIGH);
  digitalWrite(IN1_B, LOW);
  digitalWrite(IN2_B, HIGH);
}

void stopMotor() {
  digitalWrite(IN1_A, LOW);
  digitalWrite(IN2_A, LOW);
  digitalWrite(IN1_B, LOW);
  digitalWrite(IN2_B, LOW);
}
