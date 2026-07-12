#include "servo.h"
#include "log.h"

Servo racer::servo::servo;

bnp::DigitalOutput racer::servo::power(PIN_S4, HIGH, false);

void racer::servo::init() {
    power.begin();
    servo.attach(PIN_UART6_RX);
}

void racer::servo::move(int targetPos) {
  int startPos = servo.read();

  int distance = abs(targetPos - startPos);

  if (distance == 0) return;

  const unsigned long msParDegre = 40;

  unsigned long duration = distance * msParDegre;

  float currentPos;
  unsigned long tStart = millis();
  unsigned long tDelta = 0;

  while (tDelta < duration) {
    tDelta = millis() - tStart;

    float tFrac = (float)tDelta / (float)duration;
    if (tFrac > 1.0) tFrac = 1.0;

    float smoothProgression = (1.0 - cos(tFrac * PI)) / 2.0;

    currentPos = startPos + (targetPos - startPos) * smoothProgression;

    servo.write((int)currentPos);

    bnp::sleep(15);
  }

  servo.write(targetPos);
}