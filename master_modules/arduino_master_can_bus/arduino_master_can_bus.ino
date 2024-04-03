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
  if ((caractere == 'R' or caractere == 'G' or caractere == 'B' or caractere == 'Y') and (id == 0x16)) {  // le portique a deux detecteurs id 16 et id 19
    if (debug) {
      Serial.print("caractere recu : couleur cube ");
      if (caractere == 'R') Serial.print("red : ");
      if (caractere == 'G') Serial.print("green : ");
      if (caractere == 'B') Serial.print("blue : ");
      if (caractere == 'Y') Serial.print("yellow : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    id = 0x17;
    CAN.beginPacket(id);   // id 0x17 pour envoyer la couleur a l'affichage
    CAN.write(caractere);  // cube de la couleur
    CAN.endPacket();       // envoi sur le bus can
    if (debug) {
      Serial.print("envoi de la couleur a l'afficheur : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    id = 0x18;
    CAN.beginPacket(id);   // id 0x18 pour envoyer la couleur au bras
    CAN.write(caractere);  // cube de la couleur
    CAN.endPacket();       // envoi sur le bus can
    if (debug) {
      Serial.print("envoi de la couleur au bras : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    id = 0x14;
    caractere = 'L';
    CAN.beginPacket(id);   // id 0x14 pour demander au distributeur de lache un cube
    CAN.write(caractere);  // caractere L
    CAN.endPacket();       // envoi sur le bus can
    if (debug) {
      Serial.print("demande de lache d'un cube : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    caractere = '0';  // effacement du caratere apres lecture
    id = 0x0;         // effacement de la variable id apres lecture
  }

  /*
  // reception du portique id 0x16 - couleur du cube
  if ((caractere == 'R' or caractere == 'G' or caractere == 'B' or caractere == 'Y')  and (id == 0x19)) { // le portique a deux detecteurs id 16 et id 19
    if (debug) {
      Serial.print("caractere recu : couleur cube ");
      if (caractere == 'R') Serial.print("red : ");
      if (caractere == 'G') Serial.print("green : ");
      if (caractere == 'B') Serial.print("blue : ");
      if (caractere == 'Y') Serial.print("yellow : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }
    id = 0x17;
    CAN.beginPacket(id);    // id 0x17 pour envoyer la couleur a l'affichage
    CAN.write(caractere);   // cube de la couleur 
    CAN.endPacket();        // envoi sur le bus can
    if (debug) {
      Serial.print("envoi de la couleur a l'afficheur : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }
    id = 0x18;
    CAN.beginPacket(id);    // id 0x18 pour envoyer la couleur au bras
    CAN.write(caractere);   // cube de la couleur
    CAN.endPacket();        // envoi sur le bus can
    if (debug) {
      Serial.print("envoi de la couleur au bras : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }
    caractere = '0';        // effacement du caratere apres lecture
    id = 0x0;               // effacement de la variable id apres lecture
  }
  */

  // reception du convoyeur id 0x12 - objet present P
  if (caractere == 'P' and id == 0x12) {
    if (debug) {
      Serial.print("caractere recu : objet present : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    id = 0x11;
    caractere = 'S';      // objet present sur le convoyeur commande stop S
    CAN.beginPacket(id);  // id 0x11 pour envoyer le stop pour le moteur du convoyeur
    CAN.write(caractere);
    CAN.endPacket();      // envoi sur le bus can

    if (debug) {
      Serial.print("objet present sur le convoyeur envoi commande stop S : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    /*
    id = 0X18;
    CAN.beginPacket(id);    // id 0x18 demande au bras si le bras est dispo
    CAN.write('D');         // caractere de disponibilite
    CAN.endPacket();        // envoi sur le bus can
    */
    caractere = '0';  // effacement du caratere apres lecture
    id = 0x0;         // effacement de la variable id apres lecture
  }


  // reception du convoyeur id 0x12 - objet absent A
  if (caractere == 'A' and id == 0x12) {
    if (debug) {
      Serial.print("caractere recu : objet absent  : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    id = 0x11;
    caractere = 'D';      // objet absent sur le convoyeur commande demarrage D
    CAN.beginPacket(id);  // id 0x11 pour envoyer le demarrage du moteur du convoyeur
    CAN.write(caractere);
    CAN.endPacket();      // envoi sur le bus can

    if (debug) {
      Serial.print("objet absent sur le convoyeur envoi commande demarrage D : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    id = 0x17;
    caractere = 'E';        // effacement du tableau
    CAN.beginPacket(id);    // id 0x17 pour envoyer la couleur pour l'affichage
    CAN.write(caractere);
    CAN.endPacket();        // envoi sur le bus can

    if (debug) {
      Serial.print("effacement du tableau envoi commande effacement E : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    caractere = '0';  // effacement du caratere apres lecture
    id = 0x0;         // effacement de la variable id apres lecture
  }
}
