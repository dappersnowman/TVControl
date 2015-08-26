String s;

void setup() {
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() == 0) {
    delay(10);
  }

  s = String(Serial.readString());//constructor for Arduino specific String class

  if (s == "ping") {
    Serial.println("pong");
  }
  else if (s == "whoami") {
    Serial.println("Kevin Flynn"); //If you don't get this reference, you're terrible
  }
  else if (s == "knock knock") {
    Serial.println("Who's there?");
  }
  else {
    Serial.println("Bad input :(");
  }
}
