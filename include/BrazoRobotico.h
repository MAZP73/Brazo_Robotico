#pragma once
#include <Arduino.h>
#include "Articulacion.h"

// El brazo completo: agrupa sus 4 articulaciones y las mueve suavemente.
class BrazoRobotico {
public:
  static const uint8_t NUM_ARTICULACIONES = 4;

  BrazoRobotico();

  void iniciar();
  void mover(uint8_t indice, int angulo);
  void posicionInicial();
  void actualizar();   // llamar en cada loop()

  const Articulacion& getArticulacion(uint8_t indice) const { return articulaciones[indice]; }

private:
  static const unsigned long MS_POR_GRADO = 20;   // velocidad: 1 grado cada 20 ms

  Articulacion articulaciones[NUM_ARTICULACIONES];
  unsigned long ultimoPaso;
  uint8_t turno;   // articulación a la que le toca moverse (se mueven de a una)
};
