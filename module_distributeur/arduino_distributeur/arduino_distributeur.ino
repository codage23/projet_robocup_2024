/***************************************************************
    projet robocup 2024
    module distributeur
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
#include <Servo.h>

//==============
// objet servo01
//==============
Servo servo01; //Distrib

//======
// setup
//======
void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("Demarrage du distributeur");

  servo01.attach(DISTRIB);
  servo1PPos = PP_DISTRIB;  //  initial position
  servo01.write(servo1PPos);


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

void libererCube() {
  delay(1000);
  // tour max de 180 a 0º
  for (int i = max; i > min; i--) {
    servo01.write(i);
    Serial.print("Angle:180  ");
    Serial.println(i);
  }
}

  //======
  // loop
  //======
  void loop() {
    // reception commande L du master id 0x14 - liberer un cube
    if (caractere == 'L' and id == 0x14) {

      libererCube();

      if (debug) {
        Serial.print("caractere recu : liberer un cube :  ");
        Serial.print(caractere);
        Serial.print("   id  ");
        Serial.println(id, HEX);
      }
      caractere = '0';        // effacement du caratere apres lecture
      id = 0x0;               // effacement de la variable id apres lecture
    }
libererCube();

  }
