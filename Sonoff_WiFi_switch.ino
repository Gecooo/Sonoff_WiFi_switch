#include "sets.h"             //Содержится в пакете

File fsUploadFile;
TickerScheduler ts(10);
DNSServer dnsServer;
ESP8266WebServer HTTP(80);
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer HTTPWAN;

Ticker motion;
WiFiUDP udp;
WiFiClient wclient;
StringCommand sCmd;     // Обьект для работы с командами
PubSubClient client(wclient);

#define DS18B20PIN 14
//OneWire oneWire(DS18B20PIN);
//OneWire ow();
//DallasTemperature DS18B20(&oneWire);
DHT dht;

RCSwitch mySwitch = RCSwitch();
IRrecv *irReceiver;
decode_results results;
IRsend *irSender;

WS2812FX ws2812fx = WS2812FX();

static InputDebounce buttonTestA;
//static InputDebounce buttonTestB ;

void setup() {
  Serial.begin(115200);
  TickerScheduler(1);
  start_init();
}

void loop() {
  ts.update();
  HTTP.handleClient();
  yield();
  handleSSDP();
  dnsServer.processNextRequest();
  handleScenary();
  handleMQTT();
  ws2812fx.service();
  unsigned long now = millis();
  buttonTestA.process(now); // callbacks called in context of this function
  handleRfReceiv();
}
