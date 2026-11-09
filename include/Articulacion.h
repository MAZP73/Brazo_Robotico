#pragma once
#include <Arduino.h>
#include <ESP32Servo.h>

// Una articulación del brazo: un servo con sus límites y su movimiento suave.
class Articulacion {
public:
  Articulacion(const char* nombre, uint8_t pin, int anguloMin, int anguloMax, int anguloInicio);

  void iniciar();
  void fijarObjetivo(int angulo);   // a dónde debe ir (se respeta el mínimo y el máximo)
  void volverAlInicio();
  bool avanzarUnPaso();             // se acerca 1 grado al objetivo; false si ya había llegado

  const char* getNombre() const   { return nombre; }
  int getAngulo() const           { return objetivo; }
  int getMinimo() const           { return anguloMin; }
  int getMaximo() const           { return anguloMax; }

private:
  const char* nombre;
  uint8_t pin;
  int anguloMin;
  int anguloMax;
  int anguloInicio;
  int actual;
  int objetivo;
  Servo servo;
};
