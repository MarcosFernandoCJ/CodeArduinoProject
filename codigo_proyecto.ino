#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

// Configuración de pines para el LM35 y buzzer
const int LM35 = A0;        // Pin donde está conectado el LM35
const int buzzerPin = 13;   // Pin donde está conectado el buzzer

// Configuración de pines para el DS18B20
#define ONE_WIRE_BUS 9      // Pin donde está conectado el DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Configuración de pines para la pantalla LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(22, 24, 26, 28, 30, 32);

void setup() {
  // Inicialización de pines
  pinMode(buzzerPin, OUTPUT);  // Configura el buzzer como salida
  Serial.begin(9600);          // Inicia la comunicación serie

  // Inicialización de los sensores
  sensors.begin();

  // Inicialización de la pantalla LCD
  lcd.begin(16, 2);  // Configura la pantalla LCD de 16x2
  lcd.print("DS18B20 Temp:");
}

void loop() {
  // --- LM35 Sensor ---
  // Lee el valor analógico del LM35
  int sensorValue = analogRead(LM35);

  // Calcula la temperatura del LM35
  int temperaturaLM35 = int((float(sensorValue) * 5 / (1024.0)) / 0.01);

  // Muestra la temperatura del LM35 en el monitor serie
  Serial.print("Temperatura LM35: ");
  Serial.print(temperaturaLM35);
  Serial.println(" °C");

  // Si la temperatura del LM35 es mayor o igual a 30 grados
  if (temperaturaLM35 >= 30) {
    digitalWrite(buzzerPin, HIGH); // Enciende el buzzer
    delay(1000);                  // Mantén el buzzer encendido por 1 segundo
    digitalWrite(buzzerPin, LOW); // Apaga el buzzer
  }

  // --- DS18B20 Sensor ---
  // Solicitar datos del sensor DS18B20
  sensors.requestTemperatures();

  // Leer la temperatura del DS18B20
  float temperaturaDS18B20 = sensors.getTempCByIndex(0); // Lee el primer sensor conectado

  // Mostrar la temperatura del DS18B20 en la pantalla LCD
  lcd.setCursor(0, 1);              // Coloca el cursor en la segunda línea
  lcd.print("                ");    // Limpia la línea para evitar residuos
  lcd.setCursor(0, 1);              // Regresa al inicio de la segunda línea
  lcd.print(temperaturaDS18B20);    // Muestra la temperatura
  lcd.print((char)223);             // Símbolo de grado
  lcd.print("C"); 
                    // Muestra "C" para Celsius
  Serial.print("Temperatura DS18B20: ");
  Serial.print(temperaturaDS18B20);
  Serial.println(" °C");
  // Retrasos
  delay(500); // Espera 5 segundos antes de realizar otra lectura
}
