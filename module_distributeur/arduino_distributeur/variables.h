//=========
// Controls
//=========
#define SERIAL_BAUD 9600  // vitesse moniteur serie
#define SerialMonitor   1

//========================================================
// Differentes fonctions du programme
//========================================================
#define TEST 0       // if 1 true,  0 false
#define debug 1      // for use Display log message if True

//==========================================
// Affectation des broches de l'arduino uno
// Association du CS du CAN MCP2515
//==========================================
#define mcp2515CSPin  10  // cs du circuit mcp2515

//========================
// for non-bloking delays
//========================
unsigned long nextTime;   // For non-blocking delays

//================
// bus can mcp2515
//================
const int SPI_CS_PIN = 10;  // CS du shield mcp2515

//==========
// Variables
//==========
char  caractere = '0';     // lecture can
int  id = 0x0;             // valeur hexa de l'identification id sur le can bus

//==========================================
// Affectation des broches de l'arduino uno
//==========================================
#define DISTRIB 5  // liaison entre la carte arduino et le servo moteur

// value should usually be 750 to 2200 (environ 1500 = stop)
// modification vitesse arriere 1500 - 150  / avant 1500 + 150
#define POSITIONSTOP 1500      // position stop  environ 1500
#define POSITIONAVANT 1500+150     // marche avant  maxi 750
#define POSITIONRETOUR 1500-150    // marche arriere  maxi 2200

//========
// Millis
//========
// 1        = 1ms
// 1000     = 1s
// 1550000  = 30min
// 3600000  = 1h
unsigned long currentTime = 0;
unsigned long previousTime = 0;
unsigned long interval;
unsigned long interval_avant_milli     = 1000;  // en millisecondes
unsigned long interval_arriere_milli   = 1000;  // en millisecondes

/*
//===========================
// initial position
//===========================
#define PP_DISTRIB 90
//==================
// current position
//==================
int servo1Pos;
//==================
// previous position
//==================
int servo1PPos;
int min = 0, max = 180;
*/
