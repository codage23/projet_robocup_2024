/***************************************************************
    projet robocup 2024
    module distributeur
    mjc fablab atelier codage 2023 2024
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
    https://github.com/sandeepmistry/arduino-CAN/tree/master
    https://forum.arduino.cc/t/partage-boutons-poussoirs/361656
    https://github.com/BretStateham/28BYJ-48/blob/master/Arduino/Code/S07_AccelStepperDemo/S07_AccelStepperDemo.ino
    https://hackaday.io/project/183279-accelstepper-the-missing-manual/details
    https://megma.ma/moteur-pas-a-pas-5v-28byj-48-driver-uln2003-arduino/?srsltid=AfmBOoroTC77IhqYj8DPUh0I-ErdgYl3wGY-NUotNZNl8FS28KVLwKX4
    https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/
    https://www.makerguides.com/28byj-48-stepper-motor-arduino-tutorial/

  Basic Usage
  You can create multiple AccelStepper objects, giving a unique name to each motor. AccelStepper can manage any number of motors, as long as you repetitively call their "run" functions.
  Defining & Configuring Motors
  AccelStepper mystepper(1, pinStep, pinDirection);
  A stepper motor controlled by a dedicated driver board.

  AccelStepper mystepper(2, pinA, pinB);
  A bipolar stepper motor controlled by an H-Bridge circuit.

  AccelStepper mystepper(4, pinA1, pinA2, pinB1, pinB2);
  A unipolar stepper motor, controlled by 4 transistors.

  mystepper.setMaxSpeed(stepsPerSecond);
  Sets the maximum speed. The default is very slow, so this must be configured. When controlled by setting position, the stepper will accelerate to move at this maximum speed, and decelerate as it reaches the destination.

  mystepper.setAcceleration(stepsPerSecondSquared);
  Sets the acceleration to be used, in steps per second per second.

  Position Based Control
  mystepper.moveTo(targetPosition);
  Move the motor to a new absolute position. This returns immediately. Actual movement is caused by the run() function.

  mystepper.move(distance);
  Move the motor (either positive or negative) relative to its current position. This returns immediately. Actual movement is caused by the run() function.

  mystepper.currentPosition();
  Read the motor's current absolution position.

  mystepper.distanceToGo();
  Read the distance the motor is from its destination position. This can be used to check if the motor has reached its final position.

  mystepper.run();
  Update the motor. This must be called repetitively to make the motor move.

  mystepper.runToPosition();
  Update the motor, and wait for it to reach its destination. This function does not return until the motor is stopped, so it is only useful if no other motors are moving.

  Speed Based Control
  mystepper.setSpeed(stepsPerSecond);
  Set the speed, in steps per second. This function returns immediately. Actual motion is caused by called runSpeed().

  mystepper.runSpeed();
  Update the motor. This must be called repetitively to make the motor move.



***************************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <CAN.h>  // pour la bibliothèque CAN
#include <SPI.h>
#include <AccelStepper.h>  // the AccelStepper Library
#include "variables.h"     // fichier variables

#include "simpleBouton.h"
simpleBouton boutonTest(5);

//====================
// Creates an instance
//====================
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper myStepper(MotorInterfaceType, 9, 7, 8, 6);

int position = 0;

//======
// setup
//======
void setup() {
  Serial.begin(SERIAL_BAUD);
  while (!Serial)
    ;

  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  // Définit le nombre maximum de pas par seconde:
  // If ican do 20 rpm with 2048 step/revolution. Max speed should be 1 revolution each 3 sec.
  // So 2048/3 step in one sec = 682.XXX
  myStepper.setMaxSpeed(maxSpeed);
  myStepper.setAcceleration(acceleration);
  // Réglez la vitesse du moteur en pas par seconde:
  // Run the motor backwards at -625 steps/second until the motor reaches -2048 steps (1 revolution):
  myStepper.setSpeed(speed);
  // 1 revolution
  myStepper.moveTo(2038);

  // zero du poussoir grace au switch
  while (!boutonTest) {
    myStepper.setSpeed(-speed);  // vitesse et sens de rotation du stepper
    // Faire avancer le moteur avec une vitesse constante définie par setSpeed ​​():
    myStepper.runSpeed();
    //Serial.println(myStepper.currentPosition());
  }

  myStepper.setCurrentPosition(0);  // position 0 du stepper
  myStepper.stop();                 //arret du stepper
  Serial.println("Detection appui bouton");
  position = 0;  // raz du flag du poussoir stepper

  Serial.println("Demarrage du distributeur stepper");

  //  start the CAN bus at 125 kbps
  if (!CAN.begin(125E3)) {
    Serial.println("Starting CAN failed!");
    while (1)
      ;
  } else {
    if (debug) {
      Serial.println("Starting CAN OK");
    }
  }

  // register the receive callback - interruption des l'arrivee d'un message sur le bus can
  CAN.onReceive(onReceive);

  // pour test du dialogue
  //caractere = 'L';
   //id = 0x14;
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
  // depart du poussoir
  if (position == 0) {
    //Serial.println(myStepper.currentPosition());
    myStepper.moveTo(3000);  // position du stepper pous pousser le cube
    myStepper.run();
  }
  if (myStepper.currentPosition() == 2999 and position == 0) {
    position = 1;
  }

  // retour du poussoir
  if (position == 1) {
    //Serial.println(myStepper.currentPosition());
    myStepper.moveTo(0);  // position 0 du stepper
    myStepper.run();
  }
  if (myStepper.currentPosition() == 1 and position == 1 or boutonTest) {
    position = 2;
  }
   // pour test du dialogue
  caractere = 'L';
  id = 0x14;
}

//======
// loop
//======
void loop() {

  // pour test du dialogue
  //caractere = 'L';
  //id = 0x14;

  // pour tester la fonction
  //libererCube();

  if (debug) {
    Serial.println(" ");
    Serial.print("position : ");
    Serial.println(position);
  }

  // reception commande L du master id 0x14 - liberer un cube
  if (caractere == 'L' and id == 0x14 or position == 1) {

    libererCube();  //  fonction liberer le cube

    if (debug) {
      Serial.print("caractere recu : liberer un cube :  ");
      Serial.print(caractere);
      Serial.print("   id  ");
      Serial.println(id, HEX);
    }
  }

  if (position == 2) {
    caractere = '0';  // effacement du caratere apres lecture
    id = 0x0;         // effacement de la variable id apres lecture
    position = 0;     // remise a zero de la position du poussoir
  }
}
