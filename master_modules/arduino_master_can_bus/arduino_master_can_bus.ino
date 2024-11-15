/************************************************************************
    projet robocup 2024
    master de tous les modules
    mjc fablab atelier codage 2023 2024
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
    https://github.com/sandeepmistry/arduino-CAN/tree/master
    https://github.com/gewisser/GyverOLEDMenu
    https://lastminuteengineers.com/mcp2515-can-module-arduino-tutorial/
*************************************************************************/

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
  // pour l'ecran de la carte master
  oled.init();           // initialisation
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

//============================================
//  CAN reception caractere suite interruption
//============================================
void onReceive(int packetSize) {
  while (CAN.available()) {
    caractere = (char)CAN.read();  // lecture du bus can dans la variable caractere
    id = CAN.packetId();           // id du message can  dans la variable id
  }
}

//========================
//  affichage du code recu
//========================
void affichage_ecran(bool sens, char caractere, int id, int y) {
  oled.setCursor(0, y);  // position
  if (sens) {
    oled.print("receive : ");
  } else {
    oled.print("transmi : ");
  }
  oled.print(caractere);
  oled.setCursor(70, y);  // position
  oled.print(id, HEX);
  oled.update();
}

//==================================
//  affichage clear ligne de l'ecran
//==================================
void clearLigne(int y) {
  oled.setCursor(0, y);           // position
  oled.print("               ");  // effacement de la ligne
  oled.update();
}

//======
// loop
//======
void loop() {
  // id 11 : moteur du convoyeur  (Demarrage Stop)
  // id 12 : IR du convoyeur  (Absent Present)
  // id 13 : master
  // id 14 : distributeur de cube  (Liberer)
  // id 15 : IR du portique de detection de la couleur
  // id 16 : detection de la couleur du cube avec le portique n°1 (Red Green Blue Yellow Non_reconnu)
  // id 17 : panneau d'affichage  (Red Green Blue Yellow Non_reconnu Extinction)
  // id 18 : bras articule  (Red Green Blue Yellow)
  // id 19 : detection de la couleur du cube avec le portique n°2  (Red Green Blue Yellow Non_reconnu)

  // si reponse Oui du bras, alors mise a jour du flag
  if (id == 0x18 and caractere == 'O') {
    flag_bras = 1;  // flag mis à 1 suite à la dispo du bras
    if (debug) {
      Serial.print("reponse Disponible du bras : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }
  }

  if (flag_bras == 0) {  // attente de la disponibilite du bras
    // effacement des lignes de l'ecran du master
    //clearLigne(2);
    //clearLigne(4);
    //clearLigne(6);
    id = 0x18;
    caractere = 'D';
    CAN.beginPacket(id);
    CAN.write(caractere);
    CAN.endPacket();                       // envoi sur le bus can de la demande de disponibilte du bras (reponse dans la routine onReceive)
    affichage_ecran(0, caractere, id, 2);  // affichage du code transmis (0) sur la ligne n
    if (debug) {
      Serial.print("demande de disponibilite du bras : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

  } else if (flag_bras == 1) {  // bras dispo
    // effacement des lignes de l'ecran du master
    //clearLigne(2);
    //clearLigne(4);
    //clearLigne(6);
    if (debug) {
      //Serial.print("flag_bras : ");
      //Serial.println(flag_bras);
    }

    if (flag_extinction != 1) {
      id = 0x17;
      caractere = 'E';
      CAN.beginPacket(id);
      CAN.write(caractere);
      CAN.endPacket();                       // envoi sur le bus can de l'extinction de l'affichage
      flag_extinction = 1;                   // pour envoi une seul fois l'extinction de l'afficheur
      affichage_ecran(0, caractere, id, 2);  // affichage du code transmis (0) sur la ligne n
      if (debug) {
        Serial.print("commande effacement de l'affciheur E : ");
        Serial.print(caractere);
        Serial.print("   id : ");
        Serial.println(id, HEX);
      }
    }

    if (flag_demarrage != 1) {
      id = 0x11;
      caractere = 'D';
      CAN.beginPacket(id);
      CAN.write(caractere);
      CAN.endPacket();                       // envoi sur le bus can du demarrage du convoyeur
      flag_demarrage = 1;                    // pour envoi une seul fois le démarrage du convoyeur
      affichage_ecran(0, caractere, id, 4);  // affichage du code transmis (0) sur la ligne n
      if (debug) {
        Serial.print("commande demarrage du convoyeur D : ");
        Serial.print(caractere);
        Serial.print("   id : ");
        Serial.println(id, HEX);
      }
    }

    if (flag_lache != 1) {
      id = 0x14;
      caractere = 'L';
      CAN.beginPacket(id);
      CAN.write(caractere);
      CAN.endPacket();                       // envoi sur le bus can du lache d'un cube
      flag_lache = 1;                        // pour lache un seul cube
      affichage_ecran(0, caractere, id, 6);  // affichage du code transmis (0) sur la ligne n
      if (debug) {
        Serial.print("commande lache d'un cube L : ");
        Serial.print(caractere);
        Serial.print("   id : ");
        Serial.println(id, HEX);
      }
    }

    // reception du portique id 0x16 - couleur du cube
    if ((caractere == 'R' or caractere == 'G' or caractere == 'B' or caractere == 'Y') and (id == 0x16)) {  // le portique a deux detecteurs id 16 et id 19
      couleur = caractere; //sauvegarde du caractere couleur dans la variable couleur
      Serial.print("couleur : ");
      Serial.println(couleur);
      flag_couleur = 1;
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
      affichage_ecran(1, caractere, id, 2);  // affichage du code recu (1) sur la ligne n
      id = 0x17;
      CAN.beginPacket(id);
      CAN.write(caractere);
      CAN.endPacket();                       // envoi sur le bus can de la couleur a l'afficheur
      affichage_ecran(0, caractere, id, 4);  // affichage du code transmis (0) sur la ligne n
      //clearLigne(6);
      if (debug) {
        Serial.print("envoi de la couleur a l'afficheur : ");
        Serial.print(caractere);
        Serial.print("   id : ");
        Serial.println(id, HEX);
      }
      caractere = '0';  // effacement du caratere apres lecture
      id = 0x0;         // effacement de la variable id apres lecture
    }

    // reception du convoyeur id 0x12 - objet present P
    if (caractere == 'P' and id == 0x12) {
      flag_objet_present = 1;
      if (debug) {
        Serial.print("caractere recu : objet present : ");
        Serial.print(caractere);
        Serial.print("   id : ");
        Serial.println(id, HEX);
      }
      affichage_ecran(1, caractere, id, 2);  // affichage du code recu (1) sur la ligne n
      if (couleur == 'R' or couleur == 'G' or couleur == 'B' or couleur == 'Y') {
        id = 0x11;
        caractere = 'S';
        CAN.beginPacket(id);
        CAN.write(caractere);
        CAN.endPacket();                       // envoi sur le bus can  objet present sur le convoyeur commande stop S
        affichage_ecran(0, caractere, id, 4);  // affichage du code transmis (0) sur la ligne n
        if (debug) {
          Serial.print("objet present sur le convoyeur envoi commande stop S : ");
          Serial.print(caractere);
          Serial.print("   id : ");
          Serial.println(id, HEX);
        }

        id = 0x18;
        CAN.beginPacket(id);
        CAN.write(couleur);
        CAN.endPacket();                     // envoi au bras, la couleur sur le bus can
        affichage_ecran(0, couleur, id, 4);  // affichage du code transmis (0) sur la ligne n
        //clearLigne(6);
        if (debug) {
          Serial.print("envoi de la couleur au bras : ");
          Serial.print(couleur);
          Serial.print("   id : ");
          Serial.println(id, HEX);
        }

        caractere = '0';  // effacement du caratere apres lecture
        id = 0x0;         // effacement de la variable id apres lecture
        couleur = '0';    // effacement de la sauvegarde de la couleur
      }
    }

    // reception du convoyeur id 0x12 - objet absent A
    if (caractere == 'A' and id == 0x12 and flag_couleur == 1 and flag_objet_present == 1 and flag_objet_absent != 1) {  // caractere recu  absent sur le convoyeur
      flag_objet_absent = 1;
      if (debug) {
        Serial.print("caractere recu : objet absent  : ");
        Serial.print(caractere);
        Serial.print("   id : ");
        Serial.println(id, HEX);
      }
      affichage_ecran(1, caractere, id, 2);  // affichage du code recu (1) sur la ligne n
      //clearLigne(4);
      //clearLigne(6);

      caractere = '0';  // effacement du caratere apres lecture
      id = 0x0;         // effacement de la variable id apres lecture
      flag_bras = 0;
      flag_extinction = 0;
      flag_demarrage = 0;
      flag_lache = 0;
      flag_couleur = 0;        // flag couleur du cube
      flag_objet_present = 0;  // sur le convoyeur
      flag_objet_absent = 0;   // sur le convoyeur
    }
  }
}
