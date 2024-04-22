#include <espwifiarduino.h>

EspWifiArduino espwifi;

void setup() {
  Serial.begin(9600);
  espwifi.begin();
  espwifi.connect_wifi("TEST","12345678");
  espwifi.select_room("demo_arduino");
}

void loop() {
  Serial.println(espwifi.get_int(buf_0));
  espwifi.tick();
  espwifi.send_int(buf_0, 999);//recive only by others
  delay(1000);
}
