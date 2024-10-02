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
  if (id == 0x18 and carectere == 'O') {
    flag_bras = 1; // flag mis à 1 suite à la dispo du bras
  }
}

//============================
//  CAN transmission caractere
//============================
void transmission(int id, char caratere) {
  CAN.beginPacket(id);
  CAN.write(caractere);
  CAN.endPacket();      // envoi sur le bus can
}

//========================
//  affichage du code recu
//========================
void receive(char caractere, int id, int y) {
  oled.setCursor(0, y);  // position
  oled.print("receive : ");
  oled.print(caractere);
  oled.setCursor(70, y);  // position
  oled.print(id, HEX);
  oled.update();
}



//=======================
//  affichage clear ligne
//=======================
void clearLigne(int y) {
  oled.setCursor(0, y);  // position
  oled.print("               ");
  oled.update();
}

//======
// loop
//======
void loop() {
  // id 11 : moteur du convoyeur  D S
  // id 12 : convoyeur  A P
  // id 13 :
  // id 14 : distributeur de cube  L
  // id 15 :
  // id 16 : detection de la couleur du cube avec le portique n1  R G B Y
  // id 17 : panneau d'affichage  R G B Y  E
  // id 18 : bras articule  R G B Y
  // id 19 : detection de la couleur du cube avec le portique n2  R G B Y




  //==================================
  // attendre la dispo du bras id 0x18
  //==================================


  if (flag_bras == 1) {
    if (flag_extinction != 1) {
      transmission (17, 'E'); // extinction afficheur
      flag_extinction = 1; // pour envoi une seul fois l'extinction de l'afficheur
    }
    if (flag_demarrage != 1) {
      transmission (11, 'D'); // démarrage convoyeur
      flag_demarrage = 1; // pour envoi une seul fois le démarrage du convoyeur
    }
  } else if (flag_bras == 0) {
    transmission (18, 'D'); // demande bras dispo
   
  }
   delay( 1000);
   if (flag_bras == 1 and flag_lache != 1){
    transmission (14, 'L');//lache cube
    flag_lache = 1;//pour lache un cube a la fois
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

    receive(caractere, id, 2);  // affichage du code recu sur la ligne n


    transmission(17, caractere); // id 0x17 pour envoyer la couleur a l'affichage

    transmit(caractere, id, 4);  // affichage du code transmis sur la ligne n

    if (debug) {
      Serial.print("envoi de la couleur a l'afficheur : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    
   // id = 0x18;
   // transmission(id, caractere); // id 0x18 pour envoyer la couleur au bras

    //transmit(caractere, id, 5);  // affichage du code transmis sur la ligne n


   // id = 0x14;
  //  caractere = 'L';
  //  transmission(id, caractere);// id 0x14 pour demander au distributeur de lache un cube

  //  transmit(caractere, id, 6);  // affichage du code transmis sur la ligne n



    caractere = '0';  // effacement du caratere apres lecture
    id = 0x0;         // effacement de la variable id apres lecture
  }

  /*
    //================================================
    // reception du portique id 0x16 - couleur du cube
    //================================================
    if ((caractere == 'R' or caractere == 'G' or caractere == 'B' or caractere == 'Y')  and (id == 0x19)) { // le portique a deux detecteurs id 16 et id 19
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

    receive(caractere, id, 2);  // affichage du code recu sur la ligne n

    id = 0x17;
    CAN.beginPacket(id);    // id 0x17 pour envoyer la couleur a l'affichage
    CAN.write(caractere);   // cube de la couleur
    CAN.endPacket();        // envoi sur le bus can

    transmit(caractere, id, 4);  // affichage du code transmis sur la ligne n

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

    transmit(caractere, id, 5);  // affichage du code transmis sur la ligne n

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
    caractere = 'S';      // objet present sur le convoyeur commande stop S
    transmission(id, caractere);// id 0x11 pour envoyer le stop pour le moteur du convoyeur


    transmit(caractere, id, 4);  // affichage du code transmis sur la ligne n

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

      transmit(caractere, id, 5);  // affichage du code transmis sur la ligne n
    */
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

    receive(caractere, id, 2);  // affichage du code recu sur la ligne n

    id = 0x11;
    caractere = 'D';      // objet absent sur le convoyeur commande demarrage D
    transmission(id, caractere);// id 0x11 pour envoyer le demarrage du moteur du convoyeur
    //CAN.beginPacket(id);  // id 0x11 pour envoyer le demarrage du moteur du convoyeur
    //CAN.write(caractere);
    //CAN.endPacket();  // envoi sur le bus can

    transmit(caractere, id, 2);  // affichage du code transmis sur la ligne n

    if (debug) {
      Serial.print("objet absent sur le convoyeur envoi commande demarrage D : ");
      Serial.print(caractere);
      Serial.print("   id : ");
      Serial.println(id, HEX);
    }

    id = 0x17;
    caractere = 'E';      // effacement du tableau
    transmission(id, caractere);// id 0x17 pour effacer l'affichage
    //CAN.beginPacket(id);  // id 0x17 pour effacer l'affichage
    //CAN.write(caractere);
    //CAN.endPacket();  // envoi sur le bus can

    transmit(caractere, id, 4);  // affichage du code transmis sur la ligne n

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
