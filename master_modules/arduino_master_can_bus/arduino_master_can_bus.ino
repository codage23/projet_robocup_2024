/***********************************************
    projet robocup 2024
    master de tous les modules
    mjc fablab atelier codage 2023 2024
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
    https://github.com/sandeepmistry/arduino-CAN/tree/master
************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <CAN.h>        // pour la bibliothèque CAN 
#include <SPI.h>        
#include "variables.h"  // fichier variables

char  caractere = '0';

//======
// setup
//======
void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Demarrage du master");

  // start the CAN bus at 125 kbps
  if (!CAN.begin(125E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  // register the receive callback - interruption des l'arrivee d'un message sur le bus can
  CAN.onReceive(onReceive);
}

//==================================
//  CAN reception suite interruption
//==================================
void onReceive(int packetSize) {
  while (CAN.available()) {
    caractere = (char)CAN.read();
  }
}

//======
// loop
//======
void loop() {

  if (caractere == 'P') {   // reception du convoyeur - objet present P
    Serial.print("caractere reçu   ");
    Serial.println(caractere);
    caractere = '0';
    CAN.beginPacket(0x11);  // adresse 11 pour envoyer le stop  sur le convoyeur
    CAN.write('S');         // objet present sur le convoyeur commande stop S
    CAN.endPacket();
  }
  if (caractere == 'A') {   // reception info du convoyeur - objet absent
    Serial.print("caractere reçu   ");
    Serial.println(caractere);
    caractere = '0';
    CAN.beginPacket(0x11);  // adresse 11 pour envoyer le depart du convoyeur
    CAN.write('D');         // objet absent sur le convoyeur commande demarrage D
    CAN.endPacket();
  }
}
