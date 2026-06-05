#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include <WiFi.h>

class accessPoint {
    public:
        accessPoint(String name, String password);

        void activateAP();
        void deactiveAP();
        void send(String message);
    private:
        String SSID;
        String securityKey;

        IPAddress localIP;
        IPAddress gateway;
        IPAddress subnet;

        WiFiServer server;
        WiFiClient client;
};

#endif