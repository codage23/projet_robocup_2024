//=========
// Controls
//=========
#define SERIAL_BAUD 9600  // vitesse moniteur serie
#define SerialMonitor   1

//========================================================
// Differentes fonctions du programme
//========================================================
#define TEST 0       // if 1 true,  0 false
#define I2C  0       // if 1 true,  0 false
#define AUTONOME 0   // if 1 convoyeur autonome, 0 commandes CAN bus
#define debug 1      // for use Display log message if True

//==========================================
// Affectation des broches de l'arduino uno
// Association des entrees du L298N
//==========================================
#define borneENB        9       // On associe la borne "ENB" du L298N a la pin D9 de l'arduino
#define borneIN3        8       // On associe la borne "IN3" du L298N a la pin D8 de l'arduino
#define borneIN4        7       // On associe la borne "IN4" du L298N a la pin D7 de l'arduino

//==========================================
// Affectation des broches de l'arduino uno
// Association du CS du CAN MCP2515
//==========================================
#define mcp2515CSPin  10  // cs du circuit mcp2515

//========================
// for non-bloking delays
//========================
unsigned long nextTime; // For non-blocking delays

//==========
// Sensor IR
//==========
#define IRSensor        6        // connect IR sensor module to Arduino pin D6
#define LED             4        // connect LED to Arduino pin D4

//*************************//
// Constantes du programme //
//*************************//
#define delaiChangementVitesse     12       // delai en millisecondes
#define vitesseMinimale            60       // Rapport cylique minimal du signal PWM, pour faire tourner le moteur au minimum de sa vitesse
#define vitesseMaximale            255      // Rapport cylique maximal du signal PWM, pour faire tourner le moteur au maximum de sa vitesse

const bool MARCHE_AVANT   = 1;            // constante  "marche avant"
const bool MARCHE_ARRIERE = 0;            // constante  "marche arrière"

int vitesse;         // vitesse de rotation du moteur, de (0) a (255) <= signal PWM
bool presentAbsent = 0;             // constante  objet 1 present, 0 absent 

//================
// bus can mcp2515
//================
const int SPI_CS_PIN = 10;  // CS du shield mcp2515

//==================================================
// Definition de l'adresse logique de l'esclave I2C
//==================================================
#define I2C_SLAVE_CONVOYEUR  12

//==========
// Variables
//==========

int motorSpeed = 6 ;   // 6 to 25
bool motorSens = 1;          // 1 marche avant, 0 marche arriere
bool marche = 1;              // 1 start
bool arret = 0;               // 1 stop
bool objetPresent = 0;        // pas d'objet 0

//=====
// I2C
//=====
String dataIn = "";
int dataI2C = 0;
bool requestI2C = 0;

const unsigned int MAX_MESSAGE_LENGTH = 32;
static char message[MAX_MESSAGE_LENGTH]; // longueur maxi du message I2C
