// --------------------------------------
// i2c_scanner
//
//

#include <SoftWire.h>

SoftWire SWire(PB6, PB7, SOFT_FAST); // use one of SOFT_STANDARD, SOFT_FAST or SOFT_HSPEED


void setup() {
  Serial.begin(115200);
  while(!Serial); delay(1000);
  SWire.begin();
  Serial.println("\nSoftware I2C.. Scanner");
}

uint32_t counter;

void loop() {
  byte error, address;
  int nDevices;

  Serial.print(counter++);
  Serial.println(": Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.

    SWire.beginTransmission(address);
    error = SWire.endTransmission();
    
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) 
        Serial.print("0");
      Serial.println(address, HEX);

      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) 
        Serial.print("0");
      Serial.println(address, HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found");
  else
    Serial.println("done");

  delay(5000);           // wait 5 seconds for next scan
}