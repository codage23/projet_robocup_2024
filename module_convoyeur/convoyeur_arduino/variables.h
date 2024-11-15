//=========
// Controls
//=========
#define SERIAL_BAUD 9600  // vitesse moniteur serie
#define SerialMonitor   1

//========================================================
// Differentes fonctions du programme
//========================================================
#define TEST 0       // if 1 true
#define AUTONOME 0   // if 1 convoyeur autonome
#define CANBUS 1     // if 1 CAN bus
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
#define mcp2515CSPin  10  // cs chip select du circuit mcp2515
char  caractere = '0';    // lecture can
int  id = 0x0;            // valeur hexa de l'identification id sur le can bus

//========================
// for non-bloking delays
//========================
unsigned long nextTime;  // For non-blocking delays

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

int vitesse;                         // vitesse de rotation du moteur, de (0) a (255) <= signal PWM
bool presentAbsent = 0;             // constante  objet 1 present, 0 absent 

//================
// bus can mcp2515
//================
const int SPI_CS_PIN = 10;  // CS du shield mcp2515


//==========
// Variables
//==========
bool marche = 1;              // 1 demarrage du moteur
bool objetPresent = 0;        // pas d'objet 0

