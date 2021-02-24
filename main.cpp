#include "mbed.h"
#include "ESPAT.h"

/*
Example program using the ESPAT library.
Made for BULME Bertl 2017 (LPC11U68)
Opens an Access Point called ESP with the password 12345678
# Features:
 - Led D10 turns on when ready (wifi connected + server listening)
 - Navigate to the device's ip in your browser and use the buttons to control Led D11
(C)2019 Elias Nestl
*/

// ESPAT esp(P1_0, P0_20, 115200); // Library initialisieren

ESPAT esp(D8, D2, 115200);


//DigitalOut Led0 (P1_18); // D10
//DigitalOut Led1 (P2_16); // D11
DigitalOut Led0 (LED1); // D10
DigitalOut Led1 (LED2); // D11

string htmlPage = "<html>"
"<head><title>Led toggler</title></head>"
"<body>"
"<button onclick=\"fetch('./ledOn')\">Led ON</button>"
"<button onclick=\"fetch('./ledOff')\">Led OFF</button>"
"</body></html>"; // Website code

void handleRequest(int linkId, string path) { // Bei HTTP Request
    if (path == "/") { // Bei direkter IP
        esp.httpReply(linkId, "200 OK", htmlPage); // Website senden
    } else if (path == "/ledOn") { // Bei Pfad ledOn/ledOff, Led ein bzw ausschalten
        Led1 = 0;
        esp.httpReply(linkId, "200 OK", "success");
    } else if (path == "/ledOff") {
        Led1 = 1;
        esp.httpReply(linkId, "200 OK", "success");
    } else { // Bei unbekannter Seite 404 antworten
        esp.httpReply(linkId, "404 Not Found", "404 Not found!");
    }
}

int main() {
    Led0 = Led1 = 1; // Leds aus
    esp.resetEsp(); // ESP Reset
    esp.initWifiAP("ESP", "12345678"); // ESP Access Point Initialiseren
    Led0 = 0; // LED ein um zu zeigen, dass Bertl aktiv ist
    esp.initServer(handleRequest); // Request Handler initialisieren
}