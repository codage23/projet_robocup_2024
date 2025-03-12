/***********************************************************************************************
    projet robocup 2024
    module afficheur
    mjc fablab atelier codage 2023 2024
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
    https://github.com/sandeepmistry/arduino-CAN/tree/master
    https://github.com/Jorgen-VikingGod/LEDMatrix
    https://electroniqueamateur.blogspot.com/2021/03/ecrire-des-nombres-sur-une-matrice-de.html
    https://electroniqueamateur.blogspot.com/2020/05/matrice-de-leds-rgb-16-x-16-ws2812b-et.html
    https://electroniqueamateur.blogspot.com/2021/02/esp8266-et-esp32-controle-dune-matrice.html
    https://www.instructables.com/16x16-RGB-LED-Panel-Arduino-Projects/

*************************************************************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <CAN.h>           // pour la bibliothèque CAN
#include <SPI.h>           // bus spi
#include "variables.h"     // fichier variables
#include <avr/pgmspace.h>  // pour utiliser la memoire flash et augmenter la memoire de travail
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini myDFPlayer;
//SoftwareSerial mySerial(8, 9); // RX, TX
SoftwareSerial softSerial(/*rx =*/8, /*tx =*/9);
#define FPSerial softSerial

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
// setup
//======
void setup() {

  if (debug) {
    Serial.begin(9600);
    while (!Serial)
      ;
    Serial.println("Demarrage de l'afficheur");
  }
  FPSerial.begin(9600);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(FPSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true) {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3 5

  // start the CAN bus at 125 kbps
  if (!CAN.begin(125E3)) {
    if (debug) {
      Serial.println("Starting CAN failed!");
    }
    while (1)
      ;
  } else {
    if (debug) {
      Serial.println("Starting CAN");
    }
  }

  // register the receive callback - interruption des l'arrivee d'un message sur le bus can
  CAN.onReceive(onReceive);
}

//======
// loop
//======
void loop() {

  //delay(3000);
  // pour test de bon fonctionnement
  //caractere = 'G';
  //id = 0x17;


  // reception de la couleur du master id 0x17 - couleur du cube
  if ((caractere == 'R' or caractere == 'G' or caractere == 'B' or caractere == 'Y') and id == 0x17) {
    if (caractere == 'R') {
      // affichage de la couleur rouge
      myDFPlayer.next();  //Play next mp3

    } else if (caractere == 'G') {
      // affichage de la couleur verte

    } else if (caractere == 'B') {
      // affichage de la couleur bleue

    } else if (caractere == 'Y') {
      // affichage de la couleur jaune

    }

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

    caractere = '0';  // effacement du caratere apres lecture
    id = 0x0;         // effacement de la variable id apres lecture
  }

  //delay(3000);
  // pour test de bon fonctionnement
  //caractere = 'E';
  //id = 0x17;

  // effacement afficheur id 0x17
  if ((caractere == 'E') and id == 0x17) {

  }
}
