#include "errors.h"
#include <utility/wifi_drv.h>

void enableErrors() {
    WiFiDrv::pinMode(25, OUTPUT); //R
    WiFiDrv::pinMode(26, OUTPUT); //G
    WiFiDrv::pinMode(27, OUTPUT); //B
    WiFiDrv::analogWrite(26, 255);
    WiFiDrv::analogWrite(25, 0);
    WiFiDrv::analogWrite(27, 0);
}

void showError() {
    WiFiDrv::analogWrite(25, 255);
    WiFiDrv::analogWrite(26, 0);
    WiFiDrv::analogWrite(27, 0);
}

void hideError() {
    WiFiDrv::analogWrite(25, 0);
    WiFiDrv::analogWrite(26, 255);
    WiFiDrv::analogWrite(27, 0);
}