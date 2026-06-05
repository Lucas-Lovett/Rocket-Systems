#include "accessPoint.h"

accessPoint::accessPoint(String name, String password) : server(23) {
    this->SSID = name;
    this->securityKey = password;
    
    localIP = IPAddress(192, 168, 1, 100);
    gateway = IPAddress(192, 168, 1, 1);
    subnet = IPAddress(255, 255, 255, 0);
}

void accessPoint::activateAP() {
    WiFi.softAPConfig(localIP, gateway, subnet);
    WiFi.softAP(SSID, securityKey);
    Serial.print("IP: "); Serial.println(WiFi.softAPIP());
    server.begin();
}

void accessPoint::deactiveAP() {
    WiFi.softAPdisconnect(true);
    server.end();
}

void accessPoint::send(String message) {
    if (!client || !client.connected()) {
        client = server.available();
    }
    if (client && client.connected()) {
        client.println(message);
    }
}