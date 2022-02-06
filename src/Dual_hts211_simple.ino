// Basic demo for reading Humidity and Temperature from HTS221, tested on an
// Arduino MKR ZERO
#include <Wire.h>
#include <Adafruit_HTS221.h>
#include <Adafruit_Sensor.h>

// Chip select signals for the two HTS-221
#define HTS_CS_OBS 6
#define HTS_CS_REF 7

// SCK/MOSI/MISO pins (from the Arduino MKR ZERO pinout)
#define HTS_SCK   9
#define HTS_MISO 10
#define HTS_MOSI  8

Adafruit_HTS221 hts_6;
Adafruit_HTS221 hts_7;

// Iteration number: will be used as a sort of time stamp from beginning of acquisition
unsigned long int numIteration = 0L;

void setup(void) {
  
  Serial.begin(9600);
  
  while (!Serial) delay(10); // Pause until serial console opens

  // Try to initialize!
  if (!hts_6.begin_SPI(HTS_CS_OBS, HTS_SCK, HTS_MISO, HTS_MOSI)) {
    Serial.println("Failed to find base HTS221 chip");
    while (1) { delay(10); }
  }
  if (!hts_7.begin_SPI(HTS_CS_REF, HTS_SCK, HTS_MISO, HTS_MOSI)) {
    Serial.println("Failed to find base HTS221 chip");
    while (1) { delay(10); }
  }

  hts_6.setDataRate(hts221_rate_t::HTS221_RATE_12_5_HZ);
  hts_7.setDataRate(hts221_rate_t::HTS221_RATE_12_5_HZ);

  delay(1000);

  // Print header (useful when processing data)
  Serial.println("");
  Serial.println("Iteration, Temp.6, RelH.6, Temp.7, RefH.7");

}

void loop() {

  numIteration++;
    
  // Gather data from the sensor
  float rTemp6;
  float rRelH6;
  float rTemp7;
  float rRelH7;
  sensors_event_t tTemp6;
  sensors_event_t tHumidity6;
  sensors_event_t tTemp7;
  sensors_event_t tHumidity7;
  hts_6.getEvent(&tHumidity6, &tTemp6);
  hts_7.getEvent(&tHumidity7, &tTemp7);
  rRelH6 = tHumidity6.relative_humidity;
  rTemp6 = tTemp6.temperature;
  rRelH7 = tHumidity7.relative_humidity;
  rTemp7 = tTemp7.temperature;
  
  // Write data
  Serial.print(numIteration); Serial.print(", ");
  delay(50);
  Serial.print(rTemp6); Serial.print(", ");
  delay(50);
  Serial.print(rRelH6); Serial.print(", ");
  delay(50);
  Serial.print(rTemp7); Serial.print(", ");
  delay(50);
  Serial.println(rRelH7);
  
  // Wait some time
  delay(800);
  
}
