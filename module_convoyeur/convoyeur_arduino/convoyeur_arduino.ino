/***********************************************
    projet robocup 2024
    convoyeur
    mjc fablab atelier codage 2023 2024
    https://passionelectronique.fr/tutoriel-l298n/
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
    https://github.com/sandeepmistry/arduino-CAN/tree/master
************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <SPI.h>        // pour la bibliothèque CAN
#include <CAN.h>
#include "variables.h"  // fichier variables

//======================
// sensor IR infra rouge
//======================
bool sensorIR() {
  bool sensorStatus = digitalRead(IRSensor);  // read IRsensor
  if (debug) {
    //Serial.print("sensor statut : ");
    //Serial.println(sensorStatus);
  }
  return sensorStatus;
}

//======
// setup
//======
void setup() {
  Serial.begin(SERIAL_BAUD);
  Serial.println();
  Serial.println("Demarrage du convoyeur avec le sensor ir");

  // Configuration des pins de l'Arduino en "sortie" pour le shield L298N - gestion du moteur
  pinMode(borneENB, OUTPUT);
  pinMode(borneIN3, OUTPUT);
  pinMode(borneIN4, OUTPUT);

  // sensor ir
  pinMode(IRSensor, INPUT);  // IR Sensor pin INPUT
  pinMode(LED, OUTPUT);      // LED Pin Output

  // start the CAN bus at 125 kbps
  if (!CAN.begin(125E3)) {
    Serial.println("Starting CAN failed!");
    while (1)
      ;
  }

  // register the receive callback - interruption des l'arrivee d'un message sur le bus can
  CAN.onReceive(onReceive);
}


//=========================================
// Fonction configurerSensDeRotationPontB()
// Definit le sens de rotation du moteur
//=========================================
void configurerSensDeRotationPontB(bool sensDeRotation) {
  if (sensDeRotation == MARCHE_AVANT) {
    // L298N en "marche avant", Selon sa table de verite
    digitalWrite(borneIN3, HIGH);  // IN3 niveau haut
    digitalWrite(borneIN4, LOW);   // IN4 niveau bas
  }
  if (sensDeRotation == MARCHE_ARRIERE) {
    // L298N en "marche avant", Selon sa table de verite
    digitalWrite(borneIN3, LOW);   // IN3 niveau bas
    digitalWrite(borneIN4, HIGH);  // IN4 niveau haut
  }
}

//=========================================================================
// Fonction changeVitesseMoteurPontB()
// Change la vitesse de rotation du moteur (valeur comprise entre 0 et 255)
//=========================================================================
void changeVitesseMoteurPontB(int nouvelleVitesse) {
  // signal PWM rapport cyclique "nouvelleVitesse"
  analogWrite(borneENB, nouvelleVitesse);
}

//==========================
//  CAN reception suite irq
//==========================
void onReceive(int packetSize) {
  while (CAN.available()) {
    caractere = (char)CAN.read();
  }
}

//======
// loop
//======
void loop() {
  /*
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending packet ... ");
  CAN.beginPacket(0x12);
  CAN.write('h');
  CAN.write('e');
  CAN.write('l');
  CAN.write('l');
  CAN.write('o');
  CAN.endPacket();
  Serial.println("done");
*/
  if (marche) {  // demarrage progessif - une seule fois
    //sens de rotation du moteur en "marche avant"
    configurerSensDeRotationPontB(MARCHE_AVANT);
    // depart progresif du moteur, vitesse maxi 255
    for (vitesse = vitesseMinimale; vitesse < vitesseMaximale; vitesse++) {
      changeVitesseMoteurPontB(vitesse);  // vitesse moteur avec signal PWM
      delay(delaiChangementVitesse);
    }
    marche = 0;  // pour avoir un seul demarrage progessif
  }

  // Check if the pin high or not IRsensor - objet present
  if ((sensorIR() == 0) and (presentAbsent == 0)) {
    digitalWrite(LED, HIGH);  // LED High
    presentAbsent = 1;        // objet present
    CAN.beginPacket(0x12);
    CAN.write('P');           // envoi objet present P
    CAN.endPacket();
    if (debug) {
      Serial.println("Sending packet objet present");
    }
  } else if ((sensorIR() == 1) and (presentAbsent == 1)) {  // objet absent
    digitalWrite(LED, LOW);  // LED LOW
    presentAbsent = 0;       // objet absent
    CAN.beginPacket(0x12);
    CAN.write('A');          // envoi objet absent A
    CAN.endPacket();
    if (debug) {
      Serial.println("Sending packet objet absent");
    }
  }

  if (caractere == 'S') {         // reception cde S du master
    changeVitesseMoteurPontB(0);  // arret moteur - vitesse a 0
    caractere = '0';
  }
  if (caractere == 'D') {         // reception cde D du master
    marche = 1;                   //  pour valider un nouveau demarrage des que l'objet n'est plus present
    caractere = '0';
  }


#if AUTONOME
  if (marche) {  // demarrage progessif une seule fois
    //sens de rotation du moteur en "marche avant"
    configurerSensDeRotationPontB(MARCHE_AVANT);
    // depart progresif du moteur, vitesse maxi 255
    for (vitesse = vitesseMinimale; vitesse < vitesseMaximale; vitesse++) {
      changeVitesseMoteurPontB(vitesse);  // vitesse moteur avec signal PWM
      delay(delaiChangementVitesse);
    }
    marche = 0;  // pour avoir un seul demarrage progessif
  }
  // Check if the pin high or not IRsensor
  if (sensorIR() == 1) {      // objet absent
    digitalWrite(LED, LOW);   // LED LOW
    if (objetPresent == 1) {  //  pour valider un nouveau demarrage des que l'objet n'est plus present
      marche = 1;
    }
    objetPresent = 0;  // pas d'objet 0
    if (debug) {
      Serial.println("objet absent");
    }
  }
  if (sensorIR() == 0) {  // objet present
    //else turn on the onboard LED
    digitalWrite(LED, HIGH);  // LED High
    // arret moteur
    changeVitesseMoteurPontB(0);
    objetPresent = 1;  // objet present 1
    if (debug) {
      Serial.println("objet present");
    }
  }
#endif

#if TEST
  //avant
  //sens de rotation du moteur en "marche avant"
  configurerSensDeRotationPontB(MARCHE_AVANT);
  // depart progresif du moteur, vitesse maxi 255
  for (vitesse = vitesseMinimale; vitesse < vitesseMaximale; vitesse++) {
    changeVitesseMoteurPontB(vitesse);  // vitesse moteur avec signal PWM
    delay(delaiChangementVitesse);
  }
  delay(10000);
  // deceleration progressive
  for (vitesse = vitesseMaximale; vitesse > vitesseMinimale; vitesse--) {
    changeVitesseMoteurPontB(vitesse);  // vitesse moteur avec signal PWM
    delay(delaiChangementVitesse);
  }
  // arret moteur
  changeVitesseMoteurPontB(0);
  delay(1000);
  //arriere
  //sens de rotation du moteur en "marche arriere"
  configurerSensDeRotationPontB(MARCHE_ARRIERE);
  //depart progresif du moteur, vitesse maxi 255
  for (vitesse = vitesseMinimale; vitesse < vitesseMaximale; vitesse++) {
    changeVitesseMoteurPontB(vitesse);  // vitesse moteur avec signal PWM
    delay(delaiChangementVitesse);
  }
  delay(10000);
  // deceleration progressive
  for (vitesse = vitesseMaximale; vitesse > vitesseMinimale; vitesse--) {
    changeVitesseMoteurPontB(vitesse);  // vitesse moteur avec signal PWM
    delay(delaiChangementVitesse);
  }
  // arret moteur
  changeVitesseMoteurPontB(0);
  delay(1000);
#endif
}
