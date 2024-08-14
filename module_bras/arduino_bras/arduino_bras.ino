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
void home(int posServo0, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 0
  pca9685.setPWM(0, 0, posServo0);
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
// fonction position du bras
//==========================
// Position of the Servo Motors for the movement of the Robot Arm
void position(int posServo0, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 0
  if (posServo0 != 0) {
    pca9685.setPWM(0, 0, posServo0);
    delay(velocidad);
  }
  // Servo Motor 2
  if (posServo0 != 0) {
    pca9685.setPWM(2, 0, posServo2);
    delay(velocidad);
  }
  // Servo Motor 3
  if (posServo0 != 0) {
    pca9685.setPWM(3, 0, posServo3);
    delay(velocidad);
  }
  // Servo Motor 4
  if (posServo0 != 0) {
    pca9685.setPWM(4, 0, posServo4);
    delay(velocidad);
  }
  // Servo Motor 5
  if (posServo0 != 0) {
    pca9685.setPWM(5, 0, posServo5);
    delay(velocidad);
  }
}

//======
// setup
//======
void setup() {
  // moniteur serie
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("Demarrage du bras");

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
  home(NEUTREWAIST0, NEUTRESHOULDER1, NEUTREWRISTROLL3, NEUTREWRISTPITCH4, NEUTREGRIPPER5);
  delay(50);
}

//==================================
//  CAN reception suite interruption
//==================================
void onReceive(int packetSize) {
  while (CAN.available()) {
    caract = (char)CAN.read();  // lecture du bus can dans la variable caractere
    id = CAN.packetId();           // id du message can  dans la variable id
  }
}


//======
// loop
//======
void loop() {
  // pour tester la sequence
  //delay(2000);
  //caract = 'R';
  //id = 0x18;
  caractere = caract;

  // reception de la couleur du master id 0x18 - couleur du cube
  if ((caractere == 'R' or caractere == 'G' or caractere == 'B' or caractere == 'Y') and id == 0x18) {
    bras = 0; // bras occupe
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
    position(320, 340, 150, 420, 420);
    // Position of the Servo Motors to prepare to pick up the cube
    position(100, 340, 150, 420, 300);
    // Position of the Servo Motors to prepare for download the cube
    position(100, 250, 150, 420, 300);
    // Position of the Servo Motors to pick up the cube
    position(100, 250, 150, 420, 400);
    // Position of the Servo Motors to download the objet
    position(100, 340, 150, 420, 400);

    Serial.println(caractere);

    if (caractere == 'R') {
      // Position of the Servo Motors deplacement
      position(540, 340, 150, 450, 400);
      // rotation de la main
      velocidad = 80;
      position(540, 340, 150, 500, 400);
      position(540, 340, 150, 300, 400);
      position(540, 340, 150, 500, 400);
      position(540, 340, 150, 400, 400);
      velocidad = 350;
      velocidad = 350;// Position of the Servo Motors to exit the objet
      position(540, 230, 150, 400, 300);
      // Position of the Servo Motors to prepare
      position(540, 340, 150, 420, 300);

      caractere = '0';  // effacement du caratere apres lecture
      id = 0x0;         // effacement de la variable id apres lecture

    } else if (caractere == 'G') {
      // Position of the Servo Motors deplacement
      position(480, 340, 150, 450, 400);
      // rotation de la main
      velocidad = 80;
      position(480, 340, 150, 500, 400);
      position(480, 340, 150, 400, 400);
      position(480, 340, 150, 300, 400);
      position(480, 340, 150, 400, 400);
      velocidad = 350;
      // Position of the Servo Motors to exit the objet
      position(480, 230, 150, 400, 300);
      // Position of the Servo Motors to prepare
      position(480, 340, 150, 420, 300);

      caractere = '0';  // effacement du caratere apres lecture
      id = 0x0;         // effacement de la variable id apres lecture

    } else if (caractere == 'B') {
      // Position of the Servo Motors deplacement
      position(450, 340, 150, 400, 400);
      // rotation de la main
      velocidad = 80;
      position(420, 340, 150, 500, 400);
      position(420, 340, 150, 400, 400);
      position(420, 340, 150, 300, 400);
      position(420, 340, 150, 400, 400);
      velocidad = 350;
      // Position of the Servo Motors to exit the objet
      position(420, 230, 150, 400, 300);
      // Position of the Servo Motors to prepare
      position(420, 340, 150, 420, 300);

      caractere = '0';  // effacement du caratere apres lecture
      id = 0x0;         // effacement de la variable id apres lecture

    } else if (caractere == 'Y') {
      // Position of the Servo Motors deplacement
      position(360, 340, 150, 400, 400);
      // rotation de la main
      velocidad = 80;
      position(360, 340, 150, 500, 400);
      position(360, 340, 150, 400, 400);
      position(360, 340, 150, 300, 400);
      position(360, 340, 150, 400, 400);
      velocidad = 350;
      // Position of the Servo Motors to exit the objet
      position(360, 230, 150, 400, 300);
      // Position of the Servo Motors to prepare
      position(360, 340, 150, 420, 300);

      caractere = '0';  // effacement du caratere apres lecture
      id = 0x0;         // effacement de la variable id apres lecture

    }

    // Position of the Servo Motors for the first movement of the Robot Arm
    position(320, 340, 300, 420, 420);

  }
}
