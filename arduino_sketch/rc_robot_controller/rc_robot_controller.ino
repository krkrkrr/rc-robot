#define AIN1 21
#define AIN2 19
#define BIN1 4
#define BIN2 18

void setup_() {
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    Serial.begin(115200);
}

void forward() {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    Serial.write("-- forward --");
}

void coast() {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    Serial.write("-- coast --");
}

void loop() {
    forward();
    delay(1000);
    coast();
    delay(3000);
}