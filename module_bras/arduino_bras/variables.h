//=========
// Controls
//=========
#define SERIAL_BAUD 9600  // vitesse moniteur serie
#define SerialMonitor 1

//========================================================
// Differentes fonctions du programme
//========================================================
#define TEST 0   // if 1 true,  0 false
#define debug 1  // for use Display log message if True

//==========================================
// Affectation des broches de l'arduino uno
// Association du CS du CAN MCP2515
//==========================================
#define mcp2515CSPin 10  // cs du circuit mcp2515

//========================
// for non-bloking delays
//========================
unsigned long nextTime;  // For non-blocking delays

//================
// bus can mcp2515
//================
const int SPI_CS_PIN = 10;  // CS du shield mcp2515

//==========
// Variables
//==========
char caractere = '0';    // caractere
int id = 0x0;            // valeur hexa de l'identification id sur le can bus
bool flag_bras = 1;      // flag bras  1 disponible, 0 occupe

//=======
// Servos
//=======
#define SERVOMIN 100  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 500  // This is the 'maximum' pulse length count (out of 4096)
int velocidad = 350;  // Velocidad du mouvement

// mini, neutre et maxi de tous les servos
#define MINIWAIST0 100    // position minimum du servo 0  waist - taille
#define NEUTREWAIST0 320  // position neutre du servo  0
#define MAXIWAIST0 540    // position maximum du servo 0

#define MINISHOULDER1 160    // position minimum du servo 1  shoulder - epaule
#define NEUTRESHOULDER1 340  // position neutre du servo  1
#define MAXISHOULDER1 500    // position maximum du servo 1
/*
#define MINIELBOW2 160    // position minimum du servo 2  elbow - coude
#define NEUTREELBOW2 310  // position neutre du servo  2
#define MAXIELBOW2 470    // position maximum du servo 2
*/
#define MINIWRISTROLL3 120    // position minimum du servo 3  wrist roll - tour de poignet
#define NEUTREWRISTROLL3 300  // position neutre du servo  3
#define MAXIWRISTROLL3 480    // position maximum du servo 3

#define MINIWRISTPITCH4 150    // position minimum du servo 4  wrist pitch - pas du poignet
#define NEUTREWRISTPITCH4 420  // position neutre du servo  4
#define MAXIWRISTPITCH4 650    // position maximum du servo 4

#define MINIGRIPPER5 320    // position minimum du servo 5  gripper - pince
#define NEUTREGRIPPER5 420  // position neutre du servo  5
#define MAXIGRIPPER5 480    // position maximum du servo 5
