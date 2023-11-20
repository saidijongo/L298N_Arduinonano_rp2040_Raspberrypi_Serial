// Pin definition
const int IN1 = 11;
const int IN2 = 12;
const int relay = 54;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(relay, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "CW") {
      relayPump();
      rotateMotorCW();
      Serial.println("CW");
    } else if (command == "CCW") {
      rotateMotorCCW();
      Serial.println("CCW");

    } else if (command == "STOP") {
      stopMotor();
    } else {
      // Unknown command, do nothing
    }
  }
}

void rotateMotorCW() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void rotateMotorCCW() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}
void relayPump() {
  digitalWrite(relay, HIGH);
}


void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(relay,LOW);

}
