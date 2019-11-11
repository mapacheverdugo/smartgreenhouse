#include <DHT.h>
#include <Ubidots.h>

#define PIN_LED              13
#define PIN_BOMBA            8
#define PIN_HUMEDAD_SUELO    14
#define PIN_DHT11            6
#define SEGUNDOS_DELAY       5

#define TOKEN                  "BBFF-aTe3nWlq6lK9VB3KHjDwt42Gf8KpB2" // Token de Ubidots
#define DEVICE_LABEL           "smartgreenhouse"                     // Etiqueta del device de Ubidots
#define TEMPERATURA_LABEL      "5d9ea7b9642ab61905a225c3" 
#define HUMEDAD_RELATIVA_LABEL "5d9ea7e1642ab6191a30c897"
#define HUMEDAD_SUELO_LABEL    "5da37906642ab611af07d699"
#define LED_LABEL              "5d9ea7e1642ab6191a30c897"
#define BOMBA_LABEL            "5da37906642ab611af07d699"

// Configuración del Wi-Fi
#define WIFI_SSID "Amanda" // SSID de la conexión Wi-Fi
#define WIFI_PASS "28152713" // Contraseña de la conexión Wi-Fi

// Se inicializa el sensor DHT11
DHT dht(PIN_DHT11, DHT11);

// Se declaran las variables donde se guardaran los valores
float valorHumedadSuelo;
float valorHumedadRelativa;
float valorTemperatura;
float valorLed;
float valorBomba;

// Se inicializa el cliente de Ubidots
Ubidots ubidots(TOKEN);

void setup() {
  // Se configuran los pines digitales como pines de salida
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BOMBA, OUTPUT);
  
  // Comenzamos el sensor DHT
  dht.begin();
  
  Serial.begin(115200);

  // Se configura el cliente de Ubidots
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  ubidots.setDebug(true);  
}

void loop() {
  valorHumedadSuelo = analogRead(PIN_HUMEDAD_SUELO);
  
  // Leemos la temperatura en grados Fahrenheit
  valorHumedadRelativa = dht.readHumidity();
  valorTemperatura = dht.readTemperature();
  
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
  ubidots.add(HUMEDAD_RELATIVA_LABEL, valorHumedadRelativa);
  ubidots.add(HUMEDAD_SUELO_LABEL, valorHumedadSuelo);
  
  bool valoresEnviados = false;
  valoresEnviados = ubidots.send();
  if (valoresEnviados) {
    Serial.println("Los valores se enviaron correctamente");
  }
  
  delay(SEGUNDOS_DELAY * 1000);
}
