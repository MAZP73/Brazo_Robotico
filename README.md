# Brazo Robótico ESP32

Brazo robótico de 4 servos MG90S controlado desde el celular con una ESP32.

## Uso

1. Prender la ESP32 con los servos conectados.
2. En el celular, conectarse a la red Wi-Fi **BrazoRobotico** (clave `brazo1234`).
3. Abrir **http://192.168.4.1** en el navegador.

## Conexiones

| Servo  | Pin ESP32 | Rango                     | Al prender |
|--------|-----------|---------------------------|------------|
| Base   | D13       | 0–180°                    | 90°        |
| Hombro | D14       | 15–160°                   | 90°        |
| Codo   | D27       | 25–160°                   | 90°        |
| Pinza  | D26       | 0° abierta – 110° cerrada | cerrada    |

Cada servo:

- **Naranja/amarillo (señal)** → su pin
- **Rojo (+)** → 5V de una fuente externa (2–3 A o más)
- **Café/negro (−)** → GND de la fuente

**Importante:** el GND de la fuente debe ir unido al GND de la ESP32. Sin eso los servos se mueven solos.

## Compilar y subir

Proyecto [PlatformIO](https://platformio.org/):

```
pio run -t upload
```

Si la subida falla con "No serial data received", desconectar los servos de la ESP32 y volver a intentar.

## Estructura

- `Articulacion` — un servo con sus límites y movimiento suave.
- `BrazoRobotico` — agrupa las 4 articulaciones y las mueve por turnos.
- `ServidorControl` — red Wi-Fi y servidor web.
- `PaginaControl` — página de control para el celular.
