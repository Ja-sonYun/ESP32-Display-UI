#ifndef NETWORK_H
#define NETWORK_H

#include "WiFi.h"
#include "arduino.h"
#include "menu.h"


void scanWifi_func();
bool connectWifi_func(String SSID, String password);
long getWifiSignal_func();
void currentWifiInfo_func();
void disconnectWifi_func();

#endif
