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
//Servo servo01; //Distrib
Servo monServo;  // on crée l'objet monServo

//======
// setup
//======
void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("Demarrage du distributeur");

  //servo01.attach(DISTRIB);
  //servo1PPos = PP_DISTRIB;  //  initial position
  //servo01.write(servo1PPos);
  monServo.attach(5); // on définit le Pin utilisé par le servomoteur
  int position = 0;
             monServo.write(position);  // le bras du servomoteur prend la position de la variable position
  delay(3000);  // on attend 15 millisecondes

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
  //delay(1000);
  //for (int i = 100; i > 1; i--) {
  // int i = 500 ;  // 50 tourne droite et 500 tourne gauche tourne gauche liberer cube
  //servo01.write(i);
  // Serial.print("Angle:180  ");
  //Serial.println(i);
  // }
  delay(0);



  for (int position = 0; position <= 180; position ++) { // on crée une variable position qui prend des valeurs entre 0 à 180 degrés
    monServo.write(position);  // le bras du servomoteur prend la position de la variable position
    delay(5);  // on attend 15 millisecondes
  }

  for (int position = 180; position >= 0; position --) { // cette fois la variable position passe de 180 à 0°
    monServo.write(position);  // le bras du servomoteur prend la position de la variable position
    delay(5);  // le bras du servomoteur prend la position de la variable position
  }


}

//======
// loop
//======
void loop() {
  // reception commande L du master id 0x14 - liberer un cube
  if (caractere == 'L' and id == 0x14) {

    libererCube(); //  fonction liberer le cube

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
