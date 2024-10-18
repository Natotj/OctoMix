#include <LiquidCrystal.h>

//Definierung der Pins
#define LCD_RS 4
#define LCD_E 7
#define LCD_D4 8
#define LCD_D5 9
#define LCD_D6 10
#define LCD_D7 11
#define JSTICK_VRX 3
#define JSTICK_VRY 4
#define JSTICK_SW 2
#define DIODE 6
#define USONIC_TRIG 1
#define USONIC_ECHO 0
#define PUMPE 12 //high an; low aus
#define ABNEHMER 2 //Analog wird umgeplant auf 5

//Globale Variablen

#define Cocktailanzahl 12 //ist die Größe des Arays Namen
#define Zutatenanzahl 29 
#define Ventilzahl 20
#define t_pro_ml 5 //sekunden pro ml

int CursorX = 1;
int CursorY = 0;
int Save_CursorY = 0; //Speichert den Cursor
byte Wert_Abnehmer = 0;
byte Save_Wert_Abnehmer = 0;

byte ScreenEbene = 0; //siehe Main, 1=MixWarteScreen
byte Cocktail_mixen = 2; //0=nicht mixen, 1=mixen, 2=nichts ausgewählt

volatile bool JStick_Push = false;
bool firstRun = false;

String Namen[Cocktailanzahl +1] = {
                        "_Einstellungen_",
                        "0Cool Brezze", 
                        "0Cherry Bomb", 
                        "0Golden Ginger", 
                        "0St. Kitts", 
                        "0Pina Colada", 
                        "!Pina Colada",
                        "0Mexican on Ice",
                        "!Mexicore",
                        "!Tequila Tonic", 
                        "!Whisky Ginger", 
                        "!Jack Cola", 
                        "!Gin Tonic"
                       };

byte Zutatenkoordinate [Zutatenanzahl+1]={
                        -0, //zurück
                        1,  //Wasser        1
                        2,  //Oragen_Sf     2
                        3,  //Annanas_Sf    3
                        4,  //Kirsch_Sf     4
                        5,  //Grapefruit_Sf 5
                        6,  //Ginger Ale    6
                        7,  //Tonic Water   7
                        8,  //Bitter Lemon  8
                        0,  //Cola          9
                        9,  //Lion Energy   10
                        10, //Kirsch_Ne     11
                        11, //Cranberry_Ne  12
                        12, //Maracuja_Ne   13
                        13, //Sahne         14
                        0,  //Kokusmilch    15
                        14, //Limetten_Sf   16
                        0,  //Zitronen_Sf   17
                        15, //Grenadine_Si  18
                        0,  //Erdbeer_Si    19  
                        0,  //Haselnuss_Si  20
                        0,  //Kokos_Si      21  
                        16, //Vanille_Si    22
                        17, //BlueCuracao_Si23
                        18, //Tequila       24
                        0,  //Whisky        25 
                        0,  //Aperol        26
                        19, //Malibu        27
                        20, //Gin           28
                        0   //Pitu          29
                       };

String Zutatennamen [Zutatenanzahl+1] = {
                        "____return_____",
                        "Wasser",
                        "Orangen_Sf",
                        "Ananas_Sf",
                        "Kirsch_Sf",
                        "Grapefruit_Sf",
                        "Ginger Ale",
                        "Tonic Water",
                        "Bitter Lemon",
                        "Cola",
                        "Lion Energy",
                        "Kirsch_Ne",
                        "Cranberry_Ne",
                        "Maracuja_Ne",
                        "Sahne",
                        "Kokusmilch",
                        "Limetten_Sf",
                        "Zitronen_Sf",
                        "Grenadine_Si",
                        "Erdbeer_Si",
                        "Haselnuss_Si",
                        "Kokos_Si",
                        "Vanille_Si",
                        "Bl.Curacao_Si",
                        "Tequila",
                        "Whisky",
                        "Aperol",
                        "Malibu",
                        "Gin",
                        "Pitu"
                       };
                   

byte Rezept [Cocktailanzahl][11] = {
                        23,2,16,2,8,-4,0,0,0,0,0, //Cool Breeze
                        11,2,22,2,16,2,12,10,7,-16,4, //Cherry Bomb
                        2,4,5,3,3,4,6,-10,0,0,3, //Golden Ginger
                        18,2,16,2,3,9,6,-13,0,0,3, //St. Kitts
                        15,4,21,2,14,4,3,-10,0,0,3, //Vg. Pina Colada
                        15,4,21,2,14,4,27,5,3,-15,4, //Pina Colada
                        16,2,10,2,9,-4,0,0,0,0,0, //Mexican on Ice
                        24,3,3,4,6,-7,0,0,0,0,1, //Mexicore
                        24,4,7,-4,0,0,0,0,0,0,0, //Tequila Tonic
                        25,6,6,-6,0,0,0,0,0,0,0, //Whisky Ginger
                        25,8,9,-8,0,0,0,0,0,0,0, //Jack Cola
                        28,7,7,-7,0,0,0,0,0,0,0 //Gin Tonic
                       };

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
