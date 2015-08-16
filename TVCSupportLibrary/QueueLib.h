//Creates a two-dimensional queue.
//For size, functions and global variables were used instead of classes

#define ARRAYSIZE 1000
#define EVENTSIZE 12

float DataQueue[ARRAYSIZE][EVENTSIZE];
int readPoint = 0;
int writePoint = 0;
float stagingArray[EVENTSIZE]; //global variables to pull values in and out of. Memory efficient!
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
