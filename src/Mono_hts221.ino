// Basic demo for reading Humidity and Temperature from HTS221, tested on an
// Arduino MKR ZERO
#include <Wire.h>
#include <Adafruit_HTS221.h>
#include <Adafruit_Sensor.h>

// Chip select signals for the two HTS-221
#define HTS_CS_OBS 6

// SCK/MOSI/MISO pins (from the Arduino MKR ZERO pinout)
#define HTS_SCK   9
#define HTS_MISO 10
#define HTS_MOSI  8

Adafruit_HTS221 hts;

// Iteration number: will be used as a sort of time stamp from beginning of acquisition
unsigned long int numIteration = 0L;

void setup(void) {
  
  Serial.begin(9600);
  
  while (!Serial) delay(10); // Pause until serial console opens

  // Try to initialize!
  if (!hts.begin_SPI(HTS_CS_OBS, HTS_SCK, HTS_MISO, HTS_MOSI)) {
    Serial.println("Failed to find base HTS221 chip");
    while (1) { delay(10); }
  }

  hts.setDataRate(hts221_rate_t::HTS221_RATE_12_5_HZ);

  delay(1000);

  // Print header (useful when processing data)
  Serial.println("");
  Serial.println("Iteration, Temp, RelH");

}

void loop() {

  numIteration++;
    
  // Gather data from the sensor
  float rTemp;
  float rRelH;
  sensors_event_t tTemp;
  sensors_event_t tHumidity;
  hts.getEvent(&tHumidity, &tTemp);
  rRelH = tHumidity.relative_humidity;
  rTemp = tTemp.temperature;
  
  // Write data
  Serial.print(numIteration); Serial.print(", ");
  Serial.print(rTemp); Serial.print(", ");
  Serial.println(rRelH);
  
  // Wait some time
  delay(1000);
  
}
