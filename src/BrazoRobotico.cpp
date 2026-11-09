#include "BrazoRobotico.h"

// Configuración de cada articulación: nombre, pin, ángulo mínimo, máximo e inicial.
// Se evitan los pines de arranque del ESP32 (0, 2, 5, 12, 15).
// Ajusta los límites si el brazo choca con algo.
BrazoRobotico::BrazoRobotico()
  : articulaciones{
      Articulacion("Base",   13, 0,   180, 90),
      Articulacion("Hombro", 14, 15,  160, 90),
      Articulacion("Codo",   27, 25,  160, 90),
      Articulacion("Pinza",  26, 0,   110, 110),  // 0° = abierta, 110° = cerrada; arranca cerrada
    },
    ultimoPaso(0), turno(0) {}

void BrazoRobotico::iniciar() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  // Se encienden de a uno para evitar un pico de corriente que reinicie la ESP32
  for (Articulacion& a : articulaciones) {
    a.iniciar();
    delay(400);
  }
  Serial.println("Brazo listo");
}

void BrazoRobotico::mover(uint8_t indice, int angulo) {
  if (indice < NUM_ARTICULACIONES) articulaciones[indice].fijarObjetivo(angulo);
}

void BrazoRobotico::posicionInicial() {
  for (Articulacion& a : articulaciones) a.volverAlInicio();
}

void BrazoRobotico::actualizar() {
  if (millis() - ultimoPaso < MS_POR_GRADO) return;
  ultimoPaso = millis();
  // Solo un servo da un paso por vez (por turnos): así nunca arrancan varios
  // a la vez y el pico de corriente no reinicia la ESP32.
  for (uint8_t i = 0; i < NUM_ARTICULACIONES; i++) {
    uint8_t indice = turno;
    turno = (turno + 1) % NUM_ARTICULACIONES;
    if (articulaciones[indice].avanzarUnPaso()) return;
  }
}
