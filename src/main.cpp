// Brazo robótico con ESP32 + 4 servos MG90S
// Control desde el celular: red Wi-Fi "BrazoRobotico", página http://192.168.4.1

#include <Arduino.h>
#include "BrazoRobotico.h"
#include "ServidorControl.h"

BrazoRobotico brazo;
ServidorControl servidor(&brazo);

void setup() {
  Serial.begin(115200);
  brazo.iniciar();
  servidor.iniciar();
}

void loop() {
  servidor.atender();
  brazo.actualizar();
}
