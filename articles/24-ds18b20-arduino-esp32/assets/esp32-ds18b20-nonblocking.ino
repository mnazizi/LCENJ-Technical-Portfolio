#include <OneWire.h>
#include <DallasTemperature.h>

constexpr uint8_t ONE_WIRE_BUS = 4;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
uint32_t conversionStarted = 0;
bool converting = false;

void setup() {
  Serial.begin(115200);
  sensors.begin();
  sensors.setResolution(12);
  sensors.setWaitForConversion(false);
}

void loop() {
  if (!converting) {
    sensors.requestTemperatures();
    conversionStarted = millis();
    converting = true;
  }
  if (converting && millis() - conversionStarted >= 750) {
    const float temperature = sensors.getTempCByIndex(0);
    Serial.printf("Temperature: %.2f C\n", temperature);
    converting = false;
  }
}
