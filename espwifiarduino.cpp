#include "espwifiarduino.h"

EspWifiArduino::EspWifiArduino(){}

bool EspWifiArduino::begin(){
    esp_serial.begin(4800);
}

void EspWifiArduino::parse_values(char* inp){
    int pack_id;
    int temp_i;
    float temp_f;
    char temp_c[9];
    if(strncmp(inp, "ARD_PACK:", sizeof("ARD_PACK:")-1) != 0)return;
    if(sscanf(inp, "ARD_PACK:%d:i:%d", &pack_id, &temp_i) == 2){
        values[pack_id].val_i = temp_i;
    }
    if(sscanf(inp, "ARD_PACK:%d:f:%f", &pack_id, &temp_f) == 2){
        values[pack_id].val_f = temp_f;
    }
    if(sscanf(inp, "ARD_PACK:%d:s:%s", &pack_id, temp_c) == 2){
        memcpy(values[pack_id].val_s, temp_c, sizeof(values[pack_id].val_s));
    }
}

void EspWifiArduino::tick(){
    esp_serial.listen();
    while (esp_serial.available() != 0){
        read_buff[write_pos] = esp_serial.read();
        write_pos++;
        if(write_pos >= sizeof(read_buff)){
            write_pos = 0;
        }
    }
    parse_values(readline());
}

char* EspWifiArduino::readline(){
    static char out[65];
    int out_pos = 0;
    int old_read_pos = read_pos;
    while(read_pos != write_pos){
        if(read_buff[read_pos] == '\n'){
            out[out_pos] = '\0';
            read_pos++;
            return out;
        }
        out[out_pos] = read_buff[read_pos];
        out_pos++;
        read_pos++;
        if(read_pos >= sizeof(read_buff)){
            read_pos = 0;
        }
    }
    read_pos = old_read_pos;
    out[0] = '\0';
    return out;
}

int EspWifiArduino::get_int(key_buf_id id){
    return values[id].val_i;
}
float EspWifiArduino::get_float(key_buf_id id){
    return values[id].val_f;
}
char* EspWifiArduino::get_string(key_buf_id id){
    return values[id].val_s;
}

void EspWifiArduino::send_int(key_buf_id id, int out){
    esp_serial.print("ARD_PACK:");
    esp_serial.print(id);
    esp_serial.print(":i:");
    esp_serial.print(out);
    esp_serial.print("\n");
}
void EspWifiArduino::send_float(key_buf_id id, float out){
    esp_serial.print("ARD_PACK:");
    esp_serial.print(id);
    esp_serial.print(":f:");
    esp_serial.print(out);
    esp_serial.print("\n");
}
void EspWifiArduino::send_string(key_buf_id id, char* out){
    esp_serial.print("ARD_PACK:");
    esp_serial.print(id);
    esp_serial.print(":s:");
    esp_serial.print(out);
    esp_serial.print("\n");
}
void EspWifiArduino::send_string(key_buf_id id, const char out[]){
    esp_serial.print("ARD_PACK:");
    esp_serial.print(id);
    esp_serial.print(":s:");
    esp_serial.print(out);
    esp_serial.print("\n");
}
void EspWifiArduino::send_string(key_buf_id id, String out){
    esp_serial.print("ARD_PACK:");
    esp_serial.print(id);
    esp_serial.print(":s:");
    esp_serial.print(out);
    esp_serial.print("\n");
}

void EspWifiArduino::connect_wifi(const char ssid[], const char pass[]){
    esp_serial.print("AT+SSIDPASS=");
    esp_serial.print(ssid);
    esp_serial.print(",");
    esp_serial.print(pass);
    esp_serial.print("\n");
}
void EspWifiArduino::select_room(const char room[]){
    esp_serial.print("AT+WSROOM=");
    esp_serial.print(room);
    esp_serial.print("\n");
}
void EspWifiArduino::set_led(int brightness){
    esp_serial.print("AT+LED=");
    esp_serial.print(brightness);
    esp_serial.print("\n");
}
