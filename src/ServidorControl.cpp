#include "ServidorControl.h"
#include <WiFi.h>
#include "PaginaControl.h"

static const char* WIFI_NOMBRE = "BrazoRobotico";
static const char* WIFI_CLAVE  = "brazo1234";   // mínimo 8 caracteres

ServidorControl::ServidorControl(BrazoRobotico* brazo) : brazo(brazo), server(80) {}

void ServidorControl::iniciar() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFI_NOMBRE, WIFI_CLAVE);
  Serial.print("Red Wi-Fi: "); Serial.println(WIFI_NOMBRE);
  Serial.print("Abre en el celular: http://"); Serial.println(WiFi.softAPIP());

  server.on("/",       [this]() { enviarPagina(); });
  server.on("/mover",  [this]() { moverUna(); });
  server.on("/todos",  [this]() { moverTodas(); });
  server.on("/inicio", [this]() { irAlInicio(); });
  server.on("/estado", [this]() { enviarEstado(); });
  server.begin();
}

void ServidorControl::atender() {
  server.handleClient();
}

void ServidorControl::enviarPagina() {
  server.send_P(200, "text/html", PAGINA_CONTROL);
}

void ServidorControl::moverUna() {
  if (!server.hasArg("servo") || !server.hasArg("angulo")) {
    server.send(400, "text/plain", "Faltan parametros");
    return;
  }
  brazo->mover(server.arg("servo").toInt(), server.arg("angulo").toInt());
  server.send(200, "text/plain", "OK");
}

void ServidorControl::moverTodas() {
  if (!server.hasArg("a")) {
    server.send(400, "text/plain", "Falta parametro a");
    return;
  }
  String angulos = server.arg("a");
  int inicio = 0;
  for (uint8_t i = 0; i < BrazoRobotico::NUM_ARTICULACIONES && inicio < (int)angulos.length(); i++) {
    int coma = angulos.indexOf(',', inicio);
    if (coma < 0) coma = angulos.length();
    brazo->mover(i, angulos.substring(inicio, coma).toInt());
    inicio = coma + 1;
  }
  server.send(200, "text/plain", "OK");
}

void ServidorControl::irAlInicio() {
  brazo->posicionInicial();
  server.send(200, "text/plain", "OK");
}

void ServidorControl::enviarEstado() {
  String json = "[";
  for (uint8_t i = 0; i < BrazoRobotico::NUM_ARTICULACIONES; i++) {
    const Articulacion& a = brazo->getArticulacion(i);
    if (i) json += ",";
    json += "{\"nombre\":\"" + String(a.getNombre()) + "\",\"angulo\":" + a.getAngulo() +
            ",\"min\":" + a.getMinimo() + ",\"max\":" + a.getMaximo() + "}";
  }
  json += "]";
  server.send(200, "application/json", json);
}
