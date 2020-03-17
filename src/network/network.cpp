#include "network.h"

void scanWifi_func() {
    WiFi.mode(WIFI_STA);
    clear();
    drawString(0, 20, "Scan start...");
    display();

    uint8_t n = WiFi.scanNetworks();
    
    drawString(0, 30, "Scan done");
    display();
    delay(500);
    clear();
    if (n == 0) {
        clear();
        drawString(0, 0, "no network found");
        display();
        while(1);
    } else {
        drawString(0, 0, (String)n);
        drawString(14, 0, "networks found");
        display();
        delay(500);
        for (int i = 0; i < n; ++i) {
            if(i == n - 1 || i == 18) {
                tmp[i] = {"BACK", "wifi_page", BACK};
                tmpLen = i+1;
                break;
            }
            tmp[i] = { (String)(i + 1)+":"+(String)(WiFi.SSID(i))+" ("+(String)(WiFi.RSSI(i))+")" , (String)(WiFi.SSID(i)), WIFI_CONNECTION };
            delay(10);
        }
    }
}

long getWifiSignal_func() {
    return WiFi.RSSI();
}

bool connectWifi_func(String SSID, String password) {
    clear();
    drawString(0, 0, "disconnecting current wifi...");
    display();

    WiFi.disconnect(true);
    delay(1000);

    drawString(0, SECOND_ROW, "setting up wifi connection...");
    display();

    WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(true);
    WiFi.begin(SSID.c_str(), password.c_str());
    delay(100);

    String connect = "connecting";

    byte count = 0;
	while(WiFi.status() != WL_CONNECTED && count < 10) {
        connect += ".";
        drawString(0, THIRD_ROW, connect);
        display();
		count ++;
		delay(500);
	}

	if(WiFi.status() == WL_CONNECTED) {
        drawString(0, FOURTH_ROW, "connected!");
        display();
        delay(1000);
        clear();
        return true;
	} else {
        drawString(0, FOURTH_ROW, "fail to connect!");
        display();
        delay(1000);
        clear();
        return false;
	}
}

void disconnectWifi_func() {
    clear();
    drawString(0, 0, "disconnecting...");
    display();

    WiFi.disconnect(true);
    delay(1000);

    drawString(0, SECOND_ROW, "done!");
    display();
    delay(1000);

    
}

String ipAddressToString(const IPAddress& address){
    return String() + address[0] + "." + address[1] + "." + address[2] + "." + address[3];
}

String macToStr(const uint8_t* mac) {
    String result;
    for (int i = 0; i < 6; ++i) {
        result += String(mac[i], 16);
        if (i < 5)
            result += ':';
    }
return result;
}

void currentWifiInfo_func() {
    if(!getWifiSignal_func()) {
        tmp[0] = { "You're not connected to", "", 0 };
        tmp[1] = { "any wifi...", "", 0 };
        tmp[2] = { "", "", 0 };
        tmp[3] = { "BACK", "wifi_page", BACK };
        tmpLen = 4;
    } else {
        IPAddress local_ipaddress = WiFi.localIP();

        String clientMac = "";
        unsigned char mac[6];
        WiFi.macAddress(mac);
        clientMac += macToStr(mac);

        tmp[0] = { "CURRENT WIFI INFO", "", 0 };
        tmp[1] = { "mac: "+clientMac, "", 0 };
        tmp[2] = { "ipaddress: "+ipAddressToString(local_ipaddress), "", 0 };
        tmp[3] = { "BACK", "wifi_page", BACK };
        tmpLen = 4;
    }
    
}

