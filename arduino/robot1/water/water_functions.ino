void waterServos(int dirtyAngle, int cleanAngle) {
  clean.write(cleanAngle);
  dirty.write(dirtyAngle);
}

void getCleanWater() {
  waterServos(90,0);
}

void getMixedWater() {
  waterServos(0,90);
  delay(100);
  waterServos(90,0);
  delay(100);
}

void flushDirtyWater() {
  dirty.write(90);
  delay(5000);
  dirty.write(0);
}

