#include "Ubidots.h"

#define PIN_LED              13
#define PIN_BOMBA            8
#define PIN_HUMEDAD_SUELO    A0
#define PIN_HUMEDAD_AMBIENTE 5
#define PIN_TEMPERATURA      6
#define SEGUNDOS_DELAY       5

#define TOKEN                  "BBFF-aTe3nWlq6lK9VB3KHjDwt42Gf8KpB2" // Token de Ubidots
#define DEVICE_LABEL           "smartgreenhouse"                     // Etiqueta del device de Ubidots
#define TEMPERATURA_LABEL      "5d9ea7b9642ab61905a225c3" 
#define HUMEDAD_AMBIENTE_LABEL "5d9ea7e1642ab6191a30c897"
#define HUMEDAD_SUELO_LABEL    "5da37906642ab611af07d699"
#define LED_LABEL              "5d9ea7e1642ab6191a30c897"
#define BOMBA_LABEL            "5da37906642ab611af07d699"

#define WIFI_SSID "Amanda" // SSID de la conexión Wi-Fi
#define WIFI_PASS "28152713" // Contraseña de la conexión Wi-Fi

Ubidots ubidots(TOKEN);

float valorHumedadSuelo;
float valorHumedadAmbiente;
float valorTemperatura;
float valorLed;
float valorBomba;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BOMBA, OUTPUT);
  
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  ubidots.setDebug(true);  
}

void loop() {
  valorHumedadSuelo = analogRead(PIN_HUMEDAD_SUELO);
  valorHumedadAmbiente = analogRead(PIN_HUMEDAD_SUELO);
  valorTemperatura = analogRead(PIN_TEMPERATURA);
  valorLed = ubidots.get(DEVICE_LABEL, LED_LABEL);
  valorBomba = ubidots.get(DEVICE_LABEL, BOMBA_LABEL);


  if (valorLed != ERROR_VALUE) {
    Serial.print("Valor LED:");
    Serial.println(valorLed);
    // digitalWrite(PIN_LED, valorLed);
  }

  if (valorBomba != ERROR_VALUE) {
    Serial.print("Valor Bomba:");
    Serial.println(valorBomba);
    // digitalWrite(PIN_BOMBA, valorBomba);
  }

  /*
  if (Valor_Temperatura>100)Valor_Temperatura=0;
  
  Valor_Temperatura = Valor_Temperatura + 4 ;
  
  if (Valor_HumedadRelativa>100)Valor_HumedadRelativa=0;
  
  Valor_HumedadRelativa = Valor_HumedadRelativa + 3 ;
  
  if (Valor_HumedadSuelo>100)Valor_HumedadSuelo=0;
  
  Valor_HumedadSuelo= Valor_HumedadSuelo + 2 ;
  */
    
  ubidots.add(TEMPERATURA_LABEL, valorTemperatura);
  ubidots.add(HUMEDAD_AMBIENTE_LABEL, valorHumedadAmbiente);
  ubidots.add(HUMEDAD_SUELO_LABEL, valorHumedadSuelo);
  
  bool valoresEnviados = false;
  valoresEnviados = ubidots.send();
  if (valoresEnviados) {
    Serial.println("Los valores se enviaron correctamente");
  }
  
  delay(SEGUNDOS_DELAY * 1000);
}
