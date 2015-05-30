//Creates a two-dimensional queue.
//For size, functions and global variables were used instead of classes

float DataQueue[100000][12];
int readPoint = 0;
int writePoint = 0;

void pushToQueue(float * event) {
  DataQueue[writePoint] = event;
  writePoint += 1;
  if (writePoint >= 100000) {
    writePoint = 0;
  }
}

float* pullFromQueue(void) {
  float stagingArray[12];
  stagingArray = DataQueue[readPoint];
  readPoint += 1;
  if (readPoint >= 100000) {
    readPoint = 0;
  }
  return stagingArray;
}

float* readFromQueue(void) {
  float stagingArray[12];
  stagingArray = DataQueue[readPoint];
  return stagingArray;
}

int countQueue(void) {
  return (writePoint - readPoint);
}
