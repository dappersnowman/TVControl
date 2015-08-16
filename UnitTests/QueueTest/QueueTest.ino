//Try to max out the ARRAYSIZE based on your available storage space.
#define ARRAYSIZE 1000
#define EVENTSIZE 1 //Only a 1-dimensional array for this test

float DataQueue[ARRAYSIZE][EVENTSIZE];
int readPoint = 0;
int writePoint = 0;
float stagingArray[EVENTSIZE]; //global variable to pull values in and out of functions, memory efficient!
int x;

void pushToQueue(void) {
  for (int i=0; i<EVENTSIZE; i++) {
    DataQueue[writePoint][i] = stagingArray[i];
  }
  
  writePoint += 1;
  if (writePoint >= ARRAYSIZE) {
    writePoint = 0;
  }
}

void pullFromQueue(void) {
  for (int i=0; i<EVENTSIZE; i++) {
    stagingArray[i] = DataQueue[readPoint][i];
  }
  readPoint += 1;
  if (readPoint >= ARRAYSIZE) {
    readPoint = 0;
  }
}

void readFromQueue(void) {
  for (int i=0; i<EVENTSIZE; i++) {
    stagingArray[i] = DataQueue[readPoint][i];
  }
}

int countQueue(void) {
  x = (writePoint - readPoint);
  if (x < 0) {
    x = ((ARRAYSIZE - readPoint) + writePoint);
  }
  return x;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Queue is prepared.");
}

void loop() {
  Serial.println("Enter '1' to add values to queue");
  Serial.println("Enter '2' to count number of values in queue");
  Serial.println("Enter '3' to read one value from queue");
  Serial.println("Enter '4' to pull one value from queue");
  Serial.println("Enter '5' to pull all values from queue");

  while (Serial.available() == 0) {
    delay(10);
  }

  switch(Serial.parseInt()) {
    case 1: //Adding values to queue
      Serial.println("Enter value:");
      while (Serial.available() == 0) {
        delay(10);
      }

      stagingArray[0] = (float) Serial.parseInt();
      pushToQueue();
      break;
    case 2: //Counting values in queue
      Serial.print("There are ");
      Serial.print(countQueue());
      Serial.println(" items in the queue.");
      break;
    case 3: //Read one value
      if (writePoint != readPoint) {
        Serial.print("Pulling value: ");
        readFromQueue();
        Serial.println(stagingArray[0]);
      }
      else {
        Serial.println("No more items left in the queue");
      }
      break;
    case 4: //Pull one value
      if (writePoint != readPoint) {
        Serial.print("Pulling value: ");
        pullFromQueue();
        Serial.println(stagingArray[0]);
      }
      else {
        Serial.println("No more items left in the queue");
      }
      break;
    case 5: //Pull all values
      if (writePoint == readPoint) {
        Serial.println("No more items left in the queue");
      }
      else {
        while (writePoint != readPoint) {
          Serial.print("Pulling value: ");
          pullFromQueue();
          Serial.println(stagingArray[0]);
        }
      }
      break;
    default:
      Serial.println("Bad input :(");
  }
}
