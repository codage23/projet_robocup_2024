/***************************************************************
    projet robocup 2024
    master de tous les modules
    mjc fablab atelier codage 2023 2024
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
    https://github.com/sandeepmistry/arduino-CAN/tree/master
    https://github.com/gewisser/GyverOLEDMenu
    https://lastminuteengineers.com/mcp2515-can-module-arduino-tutorial/
***************************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <CAN.h>  // pour la bibliothèque CAN
#include <SPI.h>
#include "variables.h"  // fichier variables

//Libraries for OLED Display
#include <GyverOLED.h>
//GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
//GyverOLED<SSH1106_128x64> oled;

//======
// setup
//======
void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  oled.init();  // initialisation
  oled.clear();          // raz ecran
  oled.setScale(1);      // taille
  oled.setCursor(0, 0);  // position
  oled.print("   Projet robocup");
  oled.update();  // affichage
  delay(500);

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

//============================
//  CAN transmission caractere
//============================
void transmission(int id, char caratere) {  // id et caractere
  CAN.beginPacket(id);
  CAN.write(caractere);
  CAN.endPacket();                          // envoi sur le bus can
}

//========================
//  affichage du code recu
//========================
void receive(char caractere, int id, int y) {
  oled.setCursor(0, y);         // position
  oled.print("receive : ");
  oled.print(caractere);
  oled.setCursor(70, y);        // position
  oled.print(id, HEX);
  oled.update();
}

//============================
//  affichage du code transmis
//============================
void transmit(char caractere, int id, int y) {
  oled.setCursor(0, y);         // position
  oled.print("transmit : ");
  oled.print(id, HEX);
  oled.setCursor(84, y);        // position
  oled.print(caractere);
  oled.update();
}

//=======================
//  affichage clear ligne
//=======================
void clearLigne(int y) {
  oled.setCursor(0, y);         // position
  oled.print("               ");
  oled.update();
}

//======
// loop
//======
void loop() {
  // id 11 : moteur du convoyeur  (Demarrage  Stop)
  // id 12 : Infra Rouge du convoyeur  (Absent  Present)
  // id 13 : master
  // id 14 : distributeur de cube  (Lache)
  // id 15 : Infra Rouge du portique de detection de la couleur  (Present  Absent)
  // id 16 : detection de la couleur du cube avec le portique n1  (Red  Green  Blue  Yellow  Non_reconnue)
  // id 17 : panneau d'affichage  (Red  Green  Blue  Yellow  Extinction)
  // id 18 : bras articule  (Red  Green  Blue  Yellow )
  // id 19 : detection de la couleur du cube avec le portique n2  (Red  Green  Blue  Yellow  Non_reconnue)

  //================================
  // attendre la dispo du bras idx18
  //================================
  while (caractere != 'O' and id != 0x18  and bras_dispo != 1) {
    transmission (18, 'D'); // demande si bras dispo
    bras_dispo = 0;
    delay (1000);
    
  }
  bras_dispo = 1;
  if (bras_dispo == 1) {
    transmission (17, 'E'); // extinction afficheur
    transmission (11, 'D'); // démarage convoyeur
  }
  

  //================================================
  // reception du portique id 0x16 - couleur du cube
  //================================================
  if ((caractere == 'R' or caractere == 'G' or caractere == 'B' or caractere == 'Y') and (id == 0x16)) {  // le portique a deux detecteurs id 16 et id 19

    clearLigne(2);
    clearLigne(4);
    clearLigne(5);
    clearLigne(6);

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

    receive(caractere, id, 2);   // affichage du code recu sur la ligne n

    id = 0x17;
    transmission(id, caractere); // id 0x17 pour envoyer la couleur a l'affichage
    transmit(caractere, id, 4);  // affichage du code transmis sur la ligne n

    if (debug) {
      Serial.print("envoi de la couleur a l'afficheur : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    id = 0x18;
    transmission(id, caractere); // id 0x18 pour envoyer la couleur au bras
    transmit(caractere, id, 5);  // affichage du code transmis sur la ligne n

    if (debug) {
      Serial.print("envoi de la couleur au bras : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    id = 0x14;
    caractere = 'L';
    transmission(id, caractere);// id 0x14 pour demander au distributeur de lache un cube
    transmit(caractere, id, 6);  // affichage du code transmis sur la ligne n

    if (debug) {
      Serial.print("demande de lache d'un cube : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    caractere = '0';  // effacement du caratere apres lecture
    id = 0x0;         // effacement de la variable id apres lecture
  }

  //=================================================
  // reception du convoyeur id 0x12 - objet present P
  //=================================================
  if (caractere == 'P' and id == 0x12) {

    clearLigne(2);
    clearLigne(4);
    clearLigne(5);
    clearLigne(6);

    if (debug) {
      Serial.print("caractere recu : objet present : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    receive(caractere, id, 2);  // affichage du code recu sur la ligne n

    id = 0x11;
    caractere = 'S';             // objet present sur le convoyeur commande stop S
    transmission(id, caractere); // id 0x11 pour envoyer le stop pour le moteur du convoyeur
    transmit(caractere, id, 4);  // affichage du code transmis sur la ligne n

    if (debug) {
      Serial.print("objet present sur le convoyeur envoi commande stop S : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    caractere = '0';  // effacement du caratere apres lecture
    id = 0x0;         // effacement de la variable id apres lecture
  }

  //=================================================
  // reception du convoyeur id 0x12 - objet absent A
  //=================================================
  if (caractere == 'A' and id == 0x12) {

    clearLigne(2);
    clearLigne(4);
    clearLigne(5);
    clearLigne(6);

    if (debug) {
      Serial.print("caractere recu : objet absent  : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    receive(caractere, id, 2);   // affichage du code recu sur la ligne n

    id = 0x11;
    caractere = 'D';             // objet absent sur le convoyeur commande demarrage D
    transmission(id, caractere); // id 0x11 pour envoyer le demarrage du moteur du convoyeur
    transmit(caractere, id, 2);  // affichage du code transmis sur la ligne n

    if (debug) {
      Serial.print("objet absent sur le convoyeur envoi commande demarrage D : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    id = 0x17;
    caractere = 'E';              // effacement du tableau
    transmission(id, caractere);  // id 0x17 pour effacer l'affichage
    transmit(caractere, id, 4);   // affichage du code transmis sur la ligne n

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
