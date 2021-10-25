#define IN1 5
#define IN2 6

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, INPUT);
}

void Forward() {
  analogWrite(IN1, 126);
  analogWrite(IN2, 0);
}

void Stop() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
}

void loop() {
  if(digitalRead(A0) == LOW) {
    Forward();
    digitalWrite(LED_BUILTIN, HIGH);  
  } else {
    Stop();
    digitalWrite(LED_BUILTIN, LOW);  
  }
}
