/***********************************************************************************************************************
    projet robocup 2024
    module bras articule
    mjc fablab atelier codage 2023 2024
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
    https://github.com/sandeepmistry/arduino-CAN/tree/master
    Le bus de données CAN (Controller Area Network)
    est un bus système série très répandu dans beaucoup d'industries, notamment l'automobile.
    Il met en application une approche connue sous le nom de multiplexage,
    et qui consiste à raccorder à un même câble (un bus) un grand nombre de calculateurs qui communiqueront donc à tour de rôle.
    Cette technique élimine le besoin de câbler des lignes dédiées pour chaque information à faire transiter.
    https://community.element14.com/products/arduino/arduino-projects/b/blog/posts/6-axis-robotic-arm-with-servo-motors
***********************************************************************************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <CAN.h>                      // bibliothèque CAN
#include <SPI.h>                      // bibliotheque SPI communications
#include <Wire.h>                     // Library for I2C communications
#include <Adafruit_PWMServoDriver.h>  // PCA9685 Library
#include "variables.h"                // fichier variables

// Implementation of an object of module PCA9685
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver();

//=======================
// fonction repos du bras
//=======================
// Servo Motors position for Robot Arm home position
void home(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 0
  pca9685.setPWM(0, 0, posServo0);
  delay(velocidad);

  // Servo Motor 1
  pca9685.setPWM(1, 0, posServo1);
  delay(velocidad);

  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);
  delay(velocidad);

  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);
  delay(velocidad);

  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);
  delay(velocidad);

  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);
  delay(velocidad);
}

//================================
// fonction position ready du bras
//================================
// Position of the Servo Motors for the first movement of the Robot Arm
void ready(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 0
  pca9685.setPWM(0, 0, posServo0);
  delay(velocidad);

  // Servo Motor 1
  pca9685.setPWM(1, 0, posServo1);
  delay(velocidad);

  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);
  delay(velocidad);

  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);
  delay(velocidad);

  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);
  delay(velocidad);

  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);
  delay(velocidad);
}

//=======================================================
// fonction position ready du bras pour attrapper le cube
//=======================================================
// Position of the Servo Motors to prepare to pick up the cube
void get_ready(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 0
  pca9685.setPWM(0, 0, posServo0);
  delay(velocidad);

  // Servo Motor 1
  pca9685.setPWM(1, 0, posServo1);
  delay(velocidad);

  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);
  delay(velocidad);

  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);
  delay(velocidad);

  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);
  delay(velocidad);

  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);
  delay(velocidad);
}

//===================================
// fonction prepare attrapper le cube
//===================================
// Position of the Servo Motors to prepare for download the cube
void prepare_download_object(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 0
  pca9685.setPWM(0, 0, posServo0);
  delay(velocidad);

  // Servo Motor 1
  pca9685.setPWM(1, 0, posServo1);
  delay(velocidad);

  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);
  delay(velocidad);

  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);
  delay(velocidad);

  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);
  delay(velocidad);

  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);
  delay(velocidad);
}

//=================================================
// fonction position du bras pour attrapper le cube
//=================================================
// Position of the Servo Motors to pick up the cube
void pick_up_object(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 0
  pca9685.setPWM(0, 0, posServo0);
  delay(velocidad);

  // Servo Motor 1
  pca9685.setPWM(1, 0, posServo1);
  delay(velocidad);

  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);
  delay(velocidad);

  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);
  delay(velocidad);

  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);
  delay(velocidad);

  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);
  delay(velocidad);

}

//============================
// fonction attrapper le cube
//============================
// Position of the Servo Motors to download the objet
void download_object(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {

  // Servo Motor 0
  pca9685.setPWM(0, 0, posServo1);
  delay(velocidad);

  // Servo Motor 1
  pca9685.setPWM(1, 0, posServo1);
  delay(velocidad);

  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);
  delay(velocidad);

  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);
  delay(velocidad);

  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);
  delay(velocidad);

  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);
  delay(velocidad);
}

//================================
// fonction deplacement cube rouge
//================================
void deplacementCaseRed(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 0
  pca9685.setPWM(0, 0, posServo0);
  delay(velocidad);

  // Servo Motor 1
  pca9685.setPWM(1, 0, posServo1);
  delay(velocidad);

  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);
  delay(velocidad);

  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);
  delay(velocidad);

  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);
  delay(velocidad);

  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);
  delay(velocidad);
}

//================================
// fonction deplacement cube vert
//================================
void deplacementCaseGreen(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 0
  pca9685.setPWM(0, 0, posServo0);
  delay(velocidad);

  // Servo Motor 1
  pca9685.setPWM(1, 0, posServo1);
  delay(velocidad);

  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);
  delay(velocidad);

  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);
  delay(velocidad);

  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);
  delay(velocidad);

  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);
  delay(velocidad);
}

//================================
// fonction deplacement cube bleu
//================================
void deplacementCaseBlue(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 0
  pca9685.setPWM(0, 0, posServo0);
  delay(velocidad);

  // Servo Motor 1
  pca9685.setPWM(1, 0, posServo1);
  delay(velocidad);

  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);
  delay(velocidad);

  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);
  delay(velocidad);

  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);
  delay(velocidad);

  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);
  delay(velocidad);
}

//================================
// fonction deplacement cube jaune
//================================
void deplacementCaseYellow(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 0
  pca9685.setPWM(0, 0, posServo0);
  delay(velocidad);

  // Servo Motor 1
  pca9685.setPWM(1, 0, posServo1);
  delay(velocidad);

  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);
  delay(velocidad);

  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);
  delay(velocidad);

  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);
  delay(velocidad);

  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);
  delay(velocidad);
}

//==========================
// fonction relacher du cube
//==========================
void exit_download_object(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {

  // Servo Motor 0
  pca9685.setPWM(0, 0, posServo0);
  delay(velocidad);

  // Servo Motor 1
  pca9685.setPWM(1, 0, posServo1);
  delay(velocidad);

  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);
  delay(velocidad);

  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);
  delay(velocidad);

  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);
  delay(velocidad);

  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);
  delay(velocidad);
}

//======
// setup
//======
void setup() {
  // moniteur serie
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("Demarrage du distributeur");

  // demarrage pwm servo moteur
  pca9685.begin();
  pca9685.setPWMFreq(50);  // Analog servos run at 50 Hz ou 20ms

  // start the CAN bus at 125 kbps
  if (!CAN.begin(125E3)) {
    Serial.println("Starting CAN failed!");
    while (1)
      ;
  }

  // register the receive callback - interruption des l'arrivee d'un message sur le bus can
  CAN.onReceive(onReceive);

  // Servo Motors position for Robot Arm home position
  // servo 0 , servo 1, servo 2, servo 3, servo 4, servo 5
  home(NEUTREWAIST0, NEUTRESHOULDER1, NEUTREELBOW2, NEUTREWRISTROLL3, NEUTREWRISTPITCH4, NEUTREGRIPPER5);
  delay(50);

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
  
  //caractere = 'R';
  //id = 0x18;
  
  // reception de la couleur du master id 0x18 - couleur du cube
  if ((caractere == 'R' or caractere == 'G' or caractere == 'B' or caractere == 'Y') and id == 0x18) {
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


    // Position of the Servo Motors for the first movement of the Robot Arm
    ready(320, NEUTRESHOULDER1, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, NEUTREGRIPPER5);
    delay(50);
    // Position of the Servo Motors to prepare to pick up the cube
    get_ready(320, 350, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, 320);
    delay(50);

    // Position of the Servo Motors to prepare for download the cube
    prepare_download_object(320, 280, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, 320);
    delay(50);

    // Position of the Servo Motors to pick up the cube
    pick_up_object(320, 280, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, 400);
    delay(50);

    // Position of the Servo Motors to download the objet
    download_object(320, 280, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, 400);
    delay(50);

    if ( caractere == 'R') {
      // Position of the Servo Motors deplacement
      deplacementCaseRed(540, 280, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, 400);
      delay(50);

      // Position of the Servo Motors to exit the objet
      exit_download_object(540, 230, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, 320);
      delay(50);

      // Position of the Servo Motors to prepare
      deplacementCaseRed(540, 350, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, NEUTREGRIPPER5);
      delay(50);

    } else if (caractere == 'G') {
      // Position of the Servo Motors deplacement
      deplacementCaseRed(500, 280, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, 400);
      delay(50);

      // Position of the Servo Motors to exit the objet
      exit_download_object(500, 230, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, 320);
      delay(50);

      // Position of the Servo Motors to prepare
      deplacementCaseRed(500, 350, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, NEUTREGRIPPER5);
      delay(50);

    } else if (caractere == 'B') {
      // Position of the Servo Motors deplacement
      deplacementCaseRed(450, 280, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, 400);
      delay(50);

      // Position of the Servo Motors to exit the objet
      exit_download_object(450, 230, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, 320);
      delay(50);

      // Position of the Servo Motors to prepare
      deplacementCaseRed(450, 350, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, NEUTREGRIPPER5);
      delay(50);

    } else if (caractere == 'Y') {
      // Position of the Servo Motors deplacement
      deplacementCaseRed(400, 280, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, 400);
      delay(50);

      // Position of the Servo Motors to exit the objet
      exit_download_object(400, 230, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, 320);
      delay(50);

      // Position of the Servo Motors to prepare
      deplacementCaseRed(400, 350, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, NEUTREGRIPPER5);
      delay(50);

    }

    // Position of the Servo Motors for the first movement of the Robot Arm
    ready(320, NEUTRESHOULDER1, NEUTREELBOW2, 100, NEUTREWRISTPITCH4, NEUTREGRIPPER5);
    delay(50);

    caractere = '0';  // effacement du caratere apres lecture
    id = 0x0;         // effacement de la variable id apres lecture
  }
}
