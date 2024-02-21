/***************************************************************
    projet robocup 2024
    master de tous les modules
    mjc fablab atelier codage 2023 2024
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
    https://github.com/sandeepmistry/arduino-CAN/tree/master
***************************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <CAN.h>  // pour la bibliothèque CAN
#include <SPI.h>
#include "variables.h"  // fichier variables

//======
// setup
//======
void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("Demarrage du master");

  // start the CAN bus at 125 kbps
  if (!CAN.begin(125E3)) {
    Serial.println("Starting CAN failed!");
    while (1)
      ;
  }

  // register the receive callback - interruption des l'arrivee d'un message sur le bus can
  CAN.onReceive(onReceive);
}

//==================================
//  CAN reception suite interruption
//==================================
void onReceive(int packetSize) {
  while (CAN.available()) {
    caractere = (char)CAN.read();  // lecture du bus can dans la variable caractere
    id = CAN.packetId();           // id du message can  dans la variable id
  }
}

//======
// loop
//======
void loop() {
    
// reception du portique id 0x16 - couleur du cube
  if ((caractere == 'R' or caractere == 'G' or caractere == 'B' or caractere == 'Y')  and (id == 0x16 or id == 0x19)) {
    if (debug) {
      Serial.print("caractere recu : couleur cube ");
      if (caractere == 'R') Serial.print("red : ");
      if (caractere == 'G') Serial.print("green : ");
      if (caractere == 'B') Serial.print("blue : ");
      if (caractere == 'Y') Serial.print("yellow : ");
      Serial.print(caractere);
      Serial.print("   id  ");
      Serial.println(id, HEX);
    }
    caractere = '0';        // effacement du caratere apres lecture
    id = 0x0;               // effacement de la variable id apres lecture
    CAN.beginPacket(0x17);  // id 0x17 pour envoyer la couleur a l'affichage
    CAN.write(caractere);         // cube de couleur rouge 
    CAN.endPacket();        // envoi sur le bus can
  }
  
  // reception du convoyeur id 0x12 - objet present P
  if (caractere == 'P' and id == 0x12) {
    if (debug) {
      Serial.print("caractere recu : objet present : ");
      Serial.print(caractere);
      Serial.print("   id  ");
      Serial.println(id, HEX);
    }
    caractere = '0';        // effacement du caratere apres lecture
    id = 0x0;               // effacement de la variable id apres lecture
    CAN.beginPacket(0x11);  // id 0x11 pour envoyer le stop pour le moteur du convoyeur
    CAN.write('S');         // objet present sur le convoyeur commande stop S
    CAN.endPacket();        // envoi sur le bus can

    CAN.beginPacket(0x18);  // id 0x18 demande au bras si il est dispo
    CAN.write('D');         // caractere de disponibilite
    CAN.endPacket();        // envoi sur le bus can
    
  }

  // reception du convoyeur id 0x12 - objet absent A
  if (caractere == 'A' and id == 0x12) {
    if (debug) {
      Serial.print("caractere recu : objet absent  : ");
      Serial.print(caractere);
      Serial.print("   id  ");
      Serial.println(id, HEX);
    }
    caractere = '0';        // effacement du caratere apres lecture
    id = 0x0;               // effacement de la variable id apres lecture
    CAN.beginPacket(0x11);  // id 0x11 pour envoyer le demarrage du moteur du convoyeur
    CAN.write('D');         // objet absent sur le convoyeur commande demarrage D
    CAN.endPacket();        // envoi sur le bus can
  }

}