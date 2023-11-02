//========================================================
// Controls supression of the MonPrintf function to serial
//========================================================
#define SERIAL_BAUD 115200   // vitesse moniteur serie
#define SerialMonitor   1
#define debug 1  // true for use Display log message if True

//========================================================
// Differentes fonctions du programme
//========================================================
#define TEST 0       // if 1 true,  0 false
#define I2C  1        // if 1 true,  0 false

//==========================================
// Affectation des broches de l'arduino uno
//==========================================
// Câblage:


//==================================================
// Definition de l'adresse logique de l'esclave I2C
//==================================================
#define I2C_SLAVE_CONVOYEUR  12

//==========
// Sensor IR
//==========
int IRSensor = 12; // connect IR sensor module to Arduino pin D12

int LED = 13;      // connect LED to Arduino pin 13

//==========
// Variables
//==========
//==================
// stepper
//==================

// nema 17 sur X
const int enPin = 8;    // enable driver X
const int stepXPin = 2; // X.STEP  envoyer une impulsion effectue une step.
const int dirXPin = 5;  // X.DIR  permet d'indiquer la direction de rotation du moteur

int stepPin = stepXPin;
int dirPin = dirXPin;

int stepsPerRev = 200;        // nombre de pas  200 pour un moteur NEMA17 en full step , 2048 pour un 28BYJ-48
int pulseWidthMicros  = 1500; // microsecondes - 2400 lent, 500 rapide - 2400 to 500, donc 24x100 to 5x100

unsigned long motorSpeed = 2 ;   // 1 rapide , 2 moyen et 4 lent 
//int motorStep = 20;            // 200 donc 20x10
bool motorInverse = 1;           // sens
bool stopStart = 1;              // 0 stop et 1 start

//=====
// I2C
//=====
String dataIn = "";
int dataI2C = 0;
bool requestI2C = 0;

const unsigned int MAX_MESSAGE_LENGTH = 32;
static char message[MAX_MESSAGE_LENGTH]; // longueur maxi du message I2C
