// testshapes demo for RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x64 RGB LED matrix.

// WILL NOT FIT on ARDUINO UNO -- requires a Mega, M0 or M4 board

#include <RGBmatrixPanel.h>
#include <Adafruit_Keypad.h>

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

//#define CLK  8   // USE THIS ON ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

// define your specific keypad here via PID
#define KEYPAD_PID1824
// define your pins here
// can ignore ones that don't apply
#define R1    17
#define R2    18
#define R3    19
#define R4    20
#define C1    14
#define C2    15
#define C3    16
#define C4    47
// leave this import after the above configuration
#include "keypad_config.h"

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
char PriorCharacter = '\0';
char *Answer;
String Guess = "-----";

uint8_t cursorX = 0;
uint8_t cursorY = 15;
bool Win = false;


long AnswerIndex;

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

char *Wordles[] = {
"ANGEL","ALIEN","BEAST","BLOOD","BROOM","CANDY","CREEP","CLOWN","VELMA","SHREK","SLASH",
"CARVE","CLOAK","CROWN","DEMON","DEATH","DREAD","DEVIL","DRESS","EERIE","ELVES","EVILS",
"FANGS","FOGGY","FAIRY","FLASH","FEARS","GENIE","GHOST","GHOUL","GRAVE","HAUNT","TIGER",
"HOWLS","KINGS","MISTY","MUMMY","MAGIC","MASKS","NIGHT","NINJA","OGRES","PARTY","PRANK",
"QUEEN","ROBOT","CLOAK","CAPES","ROBES","SCARE","SCARY","SHOCK","SHOOK","SKULL","STUNT",
"SPOOK","SWEET","TOGAS","TRICK","TREAT","TUTUS","TIARA","TOMBS","TROLL","WANDS","SMURF", 
"WEIRD","WITCH","SATAN","KNIFE","CRYPT","HOWLS","SPELL","COVEN","TAROT","CROSS","BONES",
"WICCA","ALONE","ANTIC","CRAWL","GROSS","LUNAR","MANIC","MOANS","QUEST","WAILS","WARTS",
"VIXEN","ZORRO","HOCUS","POCUS","GOLEM","SHARK","ZELDA","MIMIC","DALEK","HYDRA","JABBA",
"SPOCK","JOKER","ARIEL","BELLE","CHIEF","DUMBO","ELVIS","FRODO","GNOME","GOOFY","GYPSY",
"JUDGE","LURCH","MOUSE","NURSE","PANDA","PILOT","VADER","RAMBO"
};

void setup() {

  randomSeed(analogRead(0));
  AnswerIndex = random(sizeof(Wordles)/sizeof(char*));
  Answer = Wordles[AnswerIndex];


  Serial.begin(9600);

  Serial.println(Answer);
  customKeypad.begin();

  matrix.begin();
  matrix.setRotation(1);
  // fill the screen with 'black'
  matrix.fillScreen(matrix.Color333(0, 0, 0));

  matrix.setCursor(1, 0);
  uint8_t w0 = 0;
  char *str = "HALLO";
  for (w0=0; w0<5; w0++) {
    matrix.setTextColor(matrix.Color333(7,0,0));
    matrix.print(str[w0]);
  }

  //matrix.drawLine(0, 14, matrix.width()-1, 14, matrix.Color333(5, 5, 5));
  // draw a pixel in solid white
  // matrix.drawPixel(0, 0, matrix.Color333(7, 7, 7));
  //delay(500);
  //matrix.drawPixel(0, 1, matrix.Color333(7, 7, 7));
  //delay(500);

  matrix.setCursor(1, 8);
  uint8_t w1 = 0;
  char *str1 = "WORDLE";
  for (w1=0; w1<5; w1++) {
    matrix.setTextColor(matrix.Color333(7,0,0));
    matrix.print(str1[w1]);
  }

  for (int i=0; i<5; i++){
    for (int j=0; j<6; j++){
      matrix.drawRect(i*6, j*8+15, 7,9,matrix.Color333(1,1,1));
    }
  }

  matrix.drawRect(cursorX, cursorY, 7,9,matrix.Color333(15,0,15));
  


}

void processWin(){
  if(Guess == Answer){
    Win = true;
  }
  if(Win == true){
    matrix.fillRect(1, 0, 31, 7,matrix.Color333(0,0,0));
    if(cursorY == 23){
      matrix.setCursor(1, 0);
      uint8_t w0 = 0;
      char *str = "WOW!";
      for (w0=0; w0<5; w0++) {
       matrix.setTextColor(matrix.Color333(7,0,0));
       matrix.print(str[w0]);
      }
    }
    if(cursorY == 31){
      matrix.setCursor(1, 0);
      uint8_t w0 = 0;
      char *str = "BANG!";
      for (w0=0; w0<5; w0++) {
       matrix.setTextColor(matrix.Color333(7,0,0));
       matrix.print(str[w0]);
      }
    }
    if(cursorY == 39){
      matrix.setCursor(1, 0);
      uint8_t w0 = 0;
      char *str = "NICE!";
      for (w0=0; w0<5; w0++) {
       matrix.setTextColor(matrix.Color333(7,0,0));
       matrix.print(str[w0]);
      }
    } 
    if(cursorY == 47){
      matrix.setCursor(1, 0);
      uint8_t w0 = 0;
      char *str = "GOOD!";
      for (w0=0; w0<5; w0++) {
       matrix.setTextColor(matrix.Color333(7,0,0));
       matrix.print(str[w0]);
      }
    }

    if(cursorY == 55){
      matrix.setCursor(1, 0);
      uint8_t w0 = 0;
      char *str = "OKAY!";
      for (w0=0; w0<5; w0++) {
       matrix.setTextColor(matrix.Color333(7,0,0));
       matrix.print(str[w0]);
      }
    }

    if(cursorY == 63){
      matrix.setCursor(1, 0);
      uint8_t w0 = 0;
      char *str = "WHEW!";
      for (w0=0; w0<5; w0++) {
       matrix.setTextColor(matrix.Color333(7,0,0));
       matrix.print(str[w0]);
      }
    }    
  }else{
    if(cursorY == 63){
      matrix.fillRect(1, 0, 31, 7,matrix.Color333(0,0,0));
      matrix.setCursor(1, 0);
      uint8_t w0 = 0;
      for (w0=0; w0<5; w0++) {
       matrix.setTextColor(matrix.Color333(7,0,0));
       matrix.print(Answer[w0]);
      }
    }

  }
}

void processGuess(){
  
  char clue[6]= {'-','-','-','-','-','\0'};
  //a set of flags indicating if that letter in the answer is used as clue
  bool answerFlags[5] = {false, false, false,false,false};

  //first pass, look for exact matches
  for (int i=0; i<5; i++){
    if(Guess[i]== Answer[i]){
      clue[i] = 'G';
      answerFlags[i] = true;
      matrix.setCursor(6*i+1, cursorY+1);
      matrix.setTextColor(matrix.Color333(0,7,0));
      matrix.print(Guess[i]);
    }
  }

  //second pass, look there but elsewhere
  for (int i=0; i<5; i++){
    if(clue[i]=='-'){
      for(int j=0; j<5; j++){
        if(Guess[i] == Answer[j] && !answerFlags[j]){
          //a match at another position and has not been used as clue
          clue[i]='Y';
          answerFlags[j]=true;
          matrix.setCursor(6*i+1, cursorY+1);
          matrix.setTextColor(matrix.Color333(7,7,0));
          matrix.print(Guess[i]);
          break; //end this j-loop because we don't want multiple clues from the same letter
        }
      }
    }
  }
}

void advancecursor(){
  matrix.drawRect(cursorX, cursorY, 7,9,matrix.Color333(1,1,1));
  if(cursorX<24){
   cursorX = cursorX + 6;
  }else {
    processGuess();
    cursorX = 0;
    cursorY = cursorY+8;
    processWin();
  }

  if(cursorY<63){
    if (Win == false){
     matrix.drawRect(cursorX, cursorY, 7,9,matrix.Color333(15,0,15));
    }
  }

  

}

void retreatcursor(){
  matrix.drawRect(cursorX, cursorY, 7,9,matrix.Color333(1,1,1));
  Guess.setCharAt(cursorX/6,"\0");
  matrix.fillRect(cursorX+1, cursorY+1, 5,7,matrix.Color333(0,0,0));
  if(cursorX>0){
   cursorX = cursorX - 6;
   Guess.setCharAt(cursorX/6,"\0");
   matrix.fillRect(cursorX+1, cursorY+1, 5,7,matrix.Color333(0,0,0));
   //PriorCharacter = Guess[cursorX/6];
  }//else {
 //   cursorX = 24;
  //  cursorY = cursorY-8;
 // }

  //if(cursorY<15){
 //   cursorY = 55;
  //}
  if(cursorY<63){
    if (Win == false){
     matrix.drawRect(cursorX, cursorY, 7,9,matrix.Color333(15,0,15));
    }
  }
}


void printCharacter(char Character){
  matrix.fillRect(cursorX+1, cursorY+1, 5,7,matrix.Color333(0,0,0));
  matrix.setCursor(cursorX+1, cursorY+1);
  matrix.setTextColor(matrix.Color333(5,5,5));
  matrix.print(Character);
  PriorCharacter = Character; 
}

void evaluateKeypress(char CurrentCharacter){
  if(CurrentCharacter == '#'){
    Guess.setCharAt(cursorX/6,PriorCharacter);
    advancecursor();

  }else if(CurrentCharacter == '*'){
    retreatcursor();

  }else if(CurrentCharacter == '2'){
    if (PriorCharacter!='A' && PriorCharacter!='B'){
     CurrentCharacter = 'A';
    }else if (PriorCharacter == 'A'){
     CurrentCharacter = 'B';
    }else if (PriorCharacter == 'B'){
     CurrentCharacter = 'C';
    }
    printCharacter(CurrentCharacter);

  }else if(CurrentCharacter == '3'){
    if (PriorCharacter!='D' && PriorCharacter!='E'){
     CurrentCharacter = 'D';
    }else if (PriorCharacter == 'D'){
     CurrentCharacter = 'E';
    }else if (PriorCharacter == 'E'){
     CurrentCharacter = 'F';
    }    
    printCharacter(CurrentCharacter);
    
  }else if(CurrentCharacter == '4'){
    if (PriorCharacter!='G' && PriorCharacter!='H'){
     CurrentCharacter = 'G';
    }else if (PriorCharacter == 'G'){
     CurrentCharacter = 'H';
    }else if (PriorCharacter == 'H'){
     CurrentCharacter = 'I';
    }    
    printCharacter(CurrentCharacter);
       
  }else if(CurrentCharacter == '5'){
    if (PriorCharacter!='J' && PriorCharacter!='K'){
     CurrentCharacter = 'J';
    }else if (PriorCharacter == 'J'){
     CurrentCharacter = 'K';
    }else if (PriorCharacter == 'K'){
     CurrentCharacter = 'L';
    }    
    printCharacter(CurrentCharacter);
       
  }else if(CurrentCharacter == '6'){
    if (PriorCharacter!='M' && PriorCharacter!='N'){
     CurrentCharacter = 'M';
    }else if (PriorCharacter == 'M'){
     CurrentCharacter = 'N';
    }else if (PriorCharacter == 'N'){
     CurrentCharacter = 'O';
    }    
    printCharacter(CurrentCharacter);
       
  }else if(CurrentCharacter == '7'){
    if (PriorCharacter!='P' && PriorCharacter!='Q' && PriorCharacter!='R'){
     CurrentCharacter = 'P';
    }else if (PriorCharacter == 'P'){
     CurrentCharacter = 'Q';
    }else if (PriorCharacter == 'Q'){
     CurrentCharacter = 'R';
    }else if (PriorCharacter == 'R'){
     CurrentCharacter = 'S';
    }
    printCharacter(CurrentCharacter);
       
  }else if(CurrentCharacter == '8'){
    if (PriorCharacter!='T' && PriorCharacter!='U'){
     CurrentCharacter = 'T';
    }else if (PriorCharacter == 'T'){
     CurrentCharacter = 'U';
    }else if (PriorCharacter == 'U'){
     CurrentCharacter = 'V';
    }    
    printCharacter(CurrentCharacter);
       
  }else if(CurrentCharacter == '9'){
    if (PriorCharacter!='W' && PriorCharacter!='X' && PriorCharacter!='Y'){
     CurrentCharacter = 'W';
    }else if (PriorCharacter == 'W'){
     CurrentCharacter = 'X';
    }else if (PriorCharacter == 'X'){
     CurrentCharacter = 'Y';
    }else if (PriorCharacter == 'Y'){
     CurrentCharacter = 'Z';
    }
    printCharacter(CurrentCharacter);
       
  }
   
}

void loop() {
  // Do nothing -- image doesn't change



// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.
  delay(10);

  customKeypad.tick();
  while(customKeypad.available()){
    keypadEvent e = customKeypad.read();
    //Serial.print((char)e.bit.KEY);
    if(e.bit.EVENT == KEY_JUST_PRESSED){ 
      //Serial.println(" pressed");
      evaluateKeypress((char)e.bit.KEY);
      Serial.println(Answer);
      Serial.println(PriorCharacter);
      Serial.println(Guess);
    }else if(e.bit.EVENT == KEY_JUST_RELEASED) Serial.println(" released");
  }
  




}
