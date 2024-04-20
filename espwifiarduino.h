#ifndef ESPWIFIARDUINO_H
#define ESPWIFIARDUINO_H

#include "Arduino.h"
#include <SoftwareSerial.h>

#define RX_PIN 12
#define TX_PIN 11

struct key
{
    int val_i;
    float val_f;
    char val_s[9];
};

class EspWifiArduino {
    public:
        EspWifiArduino();
        bool begin();
        void tick();
        int get_int(int id);
        float get_float(int id);
        char* get_string(int id);
        void send_int(int id, int out);
        void send_float(int id, float out);
        void send_string(int id, char* out);
        void send_string(int id, const char out[]);
        void send_string(int id, String out);
        void connect_wifi(const char ssid[], const char pass[]);
        void select_room(const char room[]);
        void set_led(int brightness);
    private:
        SoftwareSerial esp_serial = SoftwareSerial(RX_PIN, TX_PIN);
        char read_buff[65] = "";
        int read_pos = 0;
        int write_pos = 0;
        key values[8];
        char* readline();
        void parse_values(char* inp);
};

#endif