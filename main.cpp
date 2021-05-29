#include "mbed.h"
#include "ESPAT.h"

//commento di Federico Copes
//Commento di Jakub Bocian
//commento di Nicolas D'Agostini

//Commento 2 di Jakub Bocian
//commento 2 di Federico Copes

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

DigitalOut Led3 (D4); // D4
DigitalOut Led4 (D5); // D5
DigitalOut Led2 (D7); // D7

string htmlPage = "<html>"
"<head><title> LED Control </title></head>"
"<body style=\"background-color:rgb(124,143,137);\">"
"<h1 style=\"background-color:rgb(213,146,55);\"><center> Controllo Led </center></h1>"
"<center><button onclick=\"fetch('./ledOn')\" style=\"background-color:#98D12E; width:400px; height:150px;\"><font size=\"6\"> Led Verde ON </font></button>"
"<button onclick=\"fetch('./ledOff')\" style=\"background-color:#98D12E; width:400px; height:150px;\"><font size=\"6\"> Led Verde OFF </font></button></center>"
"<br>"
"<br>"
"<center><button onclick=\"fetch('./ledbluOn')\" style=\"background-color:#20B5DF; width:400px; height:150px;\"><font size=\"6\"> Led Blu ON </font></button>"
"<button onclick=\"fetch('./ledbluOff')\" style=\"background-color:#20B5DF; width:400px; height:150px;\"><font size=\"6\"> Led Blu OFF </font></button></center>"
"<br>"
"<br>"
"<center><button onclick=\"fetch('./ledbiancoOn')\" style=\"background-color:white; width:400px; height:150px;\"><font size=\"6\"> Led Bianco ON </font></button>"
"<button onclick=\"fetch('./ledbiancoOff')\" style=\"background-color:white; width:400px; height:150px;\"><font size=\"6\"> Led Bianco OFF </font></button></center>"
"<br>"
"<br>"
"<center><button onclick=\"fetch('./ledrossoOn')\" style=\"background-color:#C43C3C; width:400px; height:150px;\"><font size=\"6\"> Led Rosso ON </font></button>"
"<button onclick=\"fetch('./ledrossoOff')\" style=\"background-color:#C43C3C; width:400px; height:150px;\"><font size=\"6\"> Led Rosso OFF </font></button></center>"
"<br>"
"<footer><center> Federico Copes </center></footer>"
"</body></html>"; // Website code

void handleRequest(int linkId, string path) { // richiesta HTTP
    if (path == "/") { // Bei direkter IP
        esp.httpReply(linkId, "200 OK", htmlPage); // Carica sito Web
    
    //LED scheda NUCLEO
    } else if (path == "/ledOn") { // Con il percorso ledOn/ledOff, accende o spegne il LED
        Led1 = 1;
        esp.httpReply(linkId, "200 OK", "success");
    } else if (path == "/ledOff") {
        Led1 = 0;
        esp.httpReply(linkId, "200 OK", "success");
        
    //LED breadboard
    }else if (path == "/ledbluOn") {
        Led2 = 1;
        esp.httpReply(linkId, "200 OK", "success");
    } else if (path == "/ledbluOff") {
        Led2 = 0;
        esp.httpReply(linkId, "200 OK", "success");
    }else if (path == "/ledbiancoOn") {
        Led3 = 1;
        esp.httpReply(linkId, "200 OK", "success");
    } else if (path == "/ledbiancoOff") {
        Led3 = 0;
        esp.httpReply(linkId, "200 OK", "success");
    }else if (path == "/ledrossoOn") {
        Led4 = 1;
        esp.httpReply(linkId, "200 OK", "success");
    } else if (path == "/ledrossoOff") {
        Led4 = 0;
        esp.httpReply(linkId, "200 OK", "success");
    } else { // Risponde 404 se la pagina è sconosciuta
        esp.httpReply(linkId, "404 Not Found", "404 Not found!");
    }
}

int main() {
    Led0 = Led1 = 1; // Leds aus
    esp.resetEsp(); // ESP Reset
    esp.initWifiAP("ESP", "12345678", "1", "3"); // Inizializza Access Point ESP
    Led0 = 0; // LED ein um zu zeigen, dass Bertl aktiv ist
    esp.initServer(handleRequest); // Request Handler initialisieren
}

