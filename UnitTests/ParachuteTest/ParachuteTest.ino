#define EJECTIONCHARGEPIN 5

void deploy() {
  digitalWrite(EJECTIONCHARGEPIN, HIGH);
}

void setup() {
  pinMode(EJECTIONCHARGEPIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Ready to test deployment");
  Serial.println("Enter '1' to deploy immediately");
  Serial.println("Enter '2' to deploy after five seconds");

  while(Serial.available() == 0) {
    delay(10);
  }
  
  switch(Serial.parseInt()) {
    case 1:
      deploy();
      Serial.println("Parachute deployed");
      delay(2000);
      digitalWrite(EJECTIONCHARGEPIN, LOW);
      break;
    case 2:
      Serial.println("Preparing to deploy parachute");
      delay(5000);
      deploy();
      Serial.println("Parachute deployed");
      delay(2000);
      digitalWrite(EJECTIONCHARGEPIN, LOW);
      break;
    default:
      Serial.println("Bad input :(");
  }
}
