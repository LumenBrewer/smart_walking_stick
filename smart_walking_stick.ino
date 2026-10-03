#define trigPin 9
#define echoPin 8
#define buzzer 5
#define motorIN 6

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(motorIN, OUTPUT);
  Serial.begin(9600);
}

// --- Stronger vibration functions ---
void vibrateMedium() {
  analogWrite(motorIN, 200);
}

void vibrateStrong() {
  analogWrite(motorIN, 255);   // kick-start
  delay(25);
  analogWrite(motorIN, 230);   // sustain strong vibration
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= 20 && distance > 0) {
    // TOO CLOSE
    analogWrite(buzzer, 200);  // stronger sound
    vibrateStrong();           // stronger vibration
  }
  else if (distance > 20 && distance <= 30) {
    // CLOSE
    analogWrite(buzzer, 120);  // medium sound
    vibrateMedium();           // stronger medium vibration
  }
  else {
    // SAFE → OFF
    analogWrite(buzzer, 0);
    analogWrite(motorIN, 0);
  }

  delay(100);
}
