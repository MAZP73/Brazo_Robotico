#include "Articulacion.h"

// Rango de pulso típico del servo MG90S (microsegundos)
static const int PULSO_MIN = 500;
static const int PULSO_MAX = 2400;

Articulacion::Articulacion(const char* nombre, uint8_t pin, int anguloMin, int anguloMax, int anguloInicio)
  : nombre(nombre), pin(pin), anguloMin(anguloMin), anguloMax(anguloMax),
    anguloInicio(anguloInicio), actual(anguloInicio), objetivo(anguloInicio) {}

void Articulacion::iniciar() {
  servo.setPeriodHertz(50);
  servo.attach(pin, PULSO_MIN, PULSO_MAX);
  servo.write(actual);
}

void Articulacion::fijarObjetivo(int angulo) {
  objetivo = constrain(angulo, anguloMin, anguloMax);
}

void Articulacion::volverAlInicio() {
  objetivo = anguloInicio;
}

bool Articulacion::avanzarUnPaso() {
  if (actual == objetivo) return false;
  actual += (objetivo > actual) ? 1 : -1;
  servo.write(actual);
  return true;
}
