#pragma once
#include <WebServer.h>
#include "BrazoRobotico.h"

// Crea la red Wi-Fi del brazo y atiende las órdenes que llegan desde el celular.
class ServidorControl {
public:
  explicit ServidorControl(BrazoRobotico* brazo);

  void iniciar();
  void atender();   // llamar en cada loop()

private:
  // Una función por cada dirección de la página
  void enviarPagina();    // /
  void moverUna();        // /mover?servo=0&angulo=90
  void moverTodas();      // /todos?a=90,90,90,45
  void irAlInicio();      // /inicio
  void enviarEstado();    // /estado

  BrazoRobotico* brazo;
  WebServer server;
};
