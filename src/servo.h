#ifndef _RACER_SERVO_H
#define _RACER_SERVO_H

#include <bnp.h>
#include <Servo.h>

Servo servo;

void servo_init() {
    servo.attach(PIN_UART6_RX);
}

void servo_move(int targetPos) {
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

    delay(15); 
  }

  servo.write(targetPos);
}




#endif