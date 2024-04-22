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

enum key_buf_id {
    buf_0 = 0,
    buf_1 = 1,
    buf_2 = 2,
    buf_3 = 3,
    buf_4 = 4,
    buf_5 = 5,
    buf_6 = 6,
    buf_7 = 7,
};

class EspWifiArduino {
    public:
        EspWifiArduino();
        bool begin();
        void tick();
        int get_int(key_buf_id id);
        float get_float(key_buf_id id);
        char* get_string(key_buf_id id);
        void send_int(key_buf_id id, int out);
        void send_float(key_buf_id id, float out);
        void send_string(key_buf_id id, char* out);
        void send_string(key_buf_id id, const char out[]);
        void send_string(key_buf_id id, String out);
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
