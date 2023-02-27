//---------------------------------------------------
// 1. Librerias
//---------------------------------------------------

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//----------------------------------------------------
// 2. Pines
//----------------------------------------------------

#define xPin     A1   
#define yPin     A0   
#define kPin      9   
//SDA            A4
//SCL            A5

//----------------------------------------------------
// 3. Variables y Comandos
//----------------------------------------------------

int tCount1;
bool refresh;//display clearDisplay On/Off
//leerJoystick
int joyRead;
int joyPos; 
int lastJoyPos;
long lastDebounceTime = 0; 
long debounceDelay = 70;                 //user define
//Control Joystick
bool PQCP;
bool editMode;
//sistema de menus
int mNivel1;  
int mNivel2;  
//editmode
byte n[19];
int lastN;
int displayX;
//int displayY;
bool exiT;
//----------------------------------------------------
// 4. Objetos
//----------------------------------------------------
#define ANCHO_PANTALLA 128 // ancho pantalla OLED
#define ALTO_PANTALLA 64 // alto pantalla OLED

// Objeto de la clase Adafruit_SSD1306
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);


//====================================================
// SETUP
//====================================================
void setup() {
  
//----------------------------------------------------
// S1. Pines
//----------------------------------------------------

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(kPin, INPUT_PULLUP);
  
//----------------------------------------------------
// S2. Objetos
//----------------------------------------------------

  Serial.begin(9600);
  delay(100);
  
  // Iniciar pantalla OLED en la dirección 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
#ifdef __DEBUG__
    Serial.println("No se encuentra la pantalla OLED");
#endif
    while (true);
  }

  // Limpiar buffer
  display.clearDisplay();

  // Tamaño del texto
  display.setTextSize(2);
  // Color del texto
  display.setTextColor(SSD1306_WHITE);
  // Posición del texto
  display.setCursor(10, 32);
  // Escribir texto
  display.println("SKULLGEAR");

  // Enviar a pantalla
  display.display();
  delay(2000); 
  display.clearDisplay();
  display.display();
}

//====================================================
// LOOP
//====================================================
void loop() {
  controlJoystick();
  menu();
/*  if (millis()%50==0){
    tCount1++;}
  if (tCount1>1000){tCount1=0;}*/
}

//====================================================
// Menu
//====================================================

void menu(){
  switch (mNivel1){
    case 0:
      menu0();//pantalla de inicio
    break;
    case 1:
        if(mNivel2==1){menu11();
        }else if (mNivel2==2){menu12();
        }else{menu1();}
    break;
    case 2:
        if(mNivel2==1){menu21();
        }else if (mNivel2==2){menu22();
        }else{menu2();}
    break;
    case 3:
        if(mNivel2==1){menu31();
        }else if (mNivel2==2){menu32();
        }else if (mNivel2==3){menu33();
        }else if (mNivel2==4){menu34();
        }else if (mNivel2==5){menu35();
        }else{menu3();}
    break;
    case 4:
        if(mNivel2==1){menu41();
        }else if (mNivel2==2){menu42();
        }else if (mNivel2==3){menu43();
        }else if (mNivel2==4){menu44();
        }else if (mNivel2==5){menu55();
        }else{menu4();}
    break;
    case 5:
        if(mNivel2==1){menu51();
        }else if (mNivel2==2){menu52();
        }else{menu5();}
    break;
    case 6:
        if(mNivel2==1){menu61();
        }else if (mNivel2==2){menu62();
        }else if (mNivel2==3){menu63();
        }else{menu6();}
    break;
    case 7:
        if(mNivel2==1){menu71();
        }else if (mNivel2==2){menu72();
        }else if (mNivel2==3){menu73();
        }else{menu7();}
    break;
    case 8:
      menu8(); //
    break;
  }//switch
}

//----------------------------------------------------
// Pantalla de inicio
//----------------------------------------------------
void menu0(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("SubGHZ");
  display.println("RF-2.4");
  display.println("Bluetooth");
  display.println("WiFi");
  display.println("InfraRed");
  display.println("RFID-NFC");
  display.println("Ethernet");
  display.println("badUSB");
  display.display();
}
//----------------------------------------------------
// Menu 1 Modulo SubGHZ
//----------------------------------------------------
void menu1(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("-> SubGHZ");
  display.println("RF-2.4");
  display.println("Bluetooth");
  display.println("WiFi");
  display.println("InfraRed");
  display.println("RFID-NFC");
  display.println("Ethernet");
  display.println("badUSB");
  display.display();
  display.setCursor(0,1);
//++++++++++++++++++++
  while(editMode){
    controlJoystick();
    display.setCursor(displayX,1);
    if(n[displayX]!=lastN){
      display.print(n[displayX]);
      lastN=n[displayX];
    }
  }
}
//-------------------------------------------------1.1
void menu11(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/SubGHZ/");
  display.print("");
  display.print("-> Sniffer Mode");
  display.print("Transmiter Mode");
  display.display();
}
//-------------------------------------------------1.2
void menu12(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/SubGHZ/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("-> Transmiter Mode");
  display.display();
}

//----------------------------------------------------
// Menu 2 Modulo NRLF24L01
//----------------------------------------------------
void menu2(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("SubGHZ");
  display.println("-> RF-2.4");
  display.println("Bluetooth");
  display.println("WiFi");
  display.println("InfraRed");
  display.println("RFID-NFC");
  display.println("Ethernet");
  display.println("badUSB");
  display.display();
}
//-------------------------------------------------2.1
void menu21(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/RF-2.4/");
  display.print("");
  display.print("-> Sniffer Mode");
  display.print("Transmiter Mode");
  display.display();
}
//-------------------------------------------------2.2
void menu22(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/RF-2.4/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("-> Transmiter Mode");
  display.display();
}

//----------------------------------------------------
// Menu 3 Bluetooth
//----------------------------------------------------
void menu3(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("SubGHZ");
  display.println("RF-2.4");
  display.println("-> Bluetooth");
  display.println("WiFi");
  display.println("InfraRed");
  display.println("RFID-NFC");
  display.println("Ethernet");
  display.println("badUSB");
  display.display();;

//-------------------------------------------------3.1
void menu31()
{
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/Bluetooth/");
  display.print("");
  display.print("-> Sniffer Mode");
  display.print("Transmiter Mode");
  display.print("Scan Mode");
  display.print("Pair Mode");
  display.print("DoS Mode");
  display.display();
}
//-------------------------------------------------3.2
void menu32(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/Bluetooth/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("-> Transmiter Mode");
  display.print("Scan Mode");
  display.print("Pair Mode");
  display.print("DoS Mode");
  display.display();
}
//-------------------------------------------------3.3
void menu33(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/Bluetooth/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("Transmiter Mode");
  display.print("-> Scan Mode");
  display.print("Pair Mode");
  display.print("DoS Mode");
  display.display();
}

//-------------------------------------------------3.4
void menu34(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/Bluetooth/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("Transmiter Mode");
  display.print("Scan Mode");
  display.print("-> Pair Mode");
  display.print("DoS Mode");
  display.display();
}

//-------------------------------------------------3.5
void menu35(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/Bluetooth/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("Transmiter Mode");
  display.print("Scan Mode");
  display.print("Pair Mode");
  display.print("-> DoS Mode");
  display.display();
}

//----------------------------------------------------
// Menu 4 WiFi
//----------------------------------------------------
void menu4(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("SubGHZ");
  display.println("RF-2.4");
  display.println("Bluetooth");
  display.println("-> WiFi");
  display.println("InfraRed");
  display.println("RFID-NFC");
  display.println("Ethernet");
  display.println("badUSB");
  display.display();;

//-------------------------------------------------4.1
void menu41(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/WiFi/");
  display.print("");
  display.print("-> Sniffer Mode");
  display.print("Transmiter Mode");
  display.print("Scan Mode");
  display.print("Pair Mode");
  display.print("DoS Mode");
  display.display();
}
//-------------------------------------------------4.2
void menu42(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/Wifi/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("-> Transmiter Mode");
  display.print("Scan Mode");
  display.print("Pair Mode");
  display.print("DoS Mode");
  display.display();
}
//-------------------------------------------------4.3
void menu43(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/WiFi/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("Transmiter Mode");
  display.print("-> Scan Mode");
  display.print("Pair Mode");
  display.print("DoS Mode");
  display.display();
}

//-------------------------------------------------4.4
void menu44(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/Wifi/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("Transmiter Mode");
  display.print("Scan Mode");
  display.print("-> Pair Mode");
  display.print("DoS Mode");
  display.display();
}

//-------------------------------------------------4.5
void menu45(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/WiFi/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("Transmiter Mode");
  display.print("Scan Mode");
  display.print("Pair Mode");
  display.print("-> DoS Mode");
  display.display();
}

//----------------------------------------------------
// Menu 5 Modulo InfraRed
//----------------------------------------------------
void menu5(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("SubGHZ");
  display.println("RF-2.4");
  display.println("Bluetooth");
  display.println("WiFi");
  display.println("-> InfraRed");
  display.println("RFID-NFC");
  display.println("Ethernet");
  display.println("badUSB");
  display.display();
}
//-------------------------------------------------5.1
void menu51(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/InfraRed/");
  display.print("");
  display.print("-> Sniffer Mode");
  display.print("Transmiter Mode");
  display.display();
}
//-------------------------------------------------5.2
void menu52(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/InfraRed/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("-> Transmiter Mode");
  display.display();
}

//----------------------------------------------------
// Menu 6 Modulo RFID-NFC
//----------------------------------------------------
void menu6(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("SubGHZ");
  display.println("RF-2.4");
  display.println("Bluetooth");
  display.println("WiFi");
  display.println("InfraRed");
  display.println("-> RFID-NFC");
  display.println("Ethernet");
  display.println("badUSB");
  display.display();
}
//-------------------------------------------------6.1
void menu61(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/RFID-NFC/");
  display.print("");
  display.print("-> Sniffer Mode");
  display.print("Transmiter Mode");
  display.print("Burn Mode");
  display.display();
}
//-------------------------------------------------6.2
void menu62(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/RFID-NFC/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("-> Transmiter Mode");
  display.print("Burn Mode");
  display.display();
}
//-------------------------------------------------6.3
void menu63(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/RFID-NFC/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("Transmiter Mode");
  display.print("-> Burn Mode");
  display.display();
}

//----------------------------------------------------
// Menu 7 Modulo Ethernet
//----------------------------------------------------
void menu7(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("SubGHZ");
  display.println("RF-2.4");
  display.println("Bluetooth");
  display.println("WiFi");
  display.println("InfraRed");
  display.println("RFID-NFC");
  display.println("-> Ethernet");
  display.println("badUSB");
  display.display();
}
//-------------------------------------------------7.1
void menu71(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/Ethernet/");
  display.print("");
  display.print("-> Sniffer Mode");
  display.print("Transmiter Mode");
  display.print("Poisoning");
  display.display();
}
//-------------------------------------------------7.2
void menu72(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/Ethernet/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("-> Transmiter Mode");
  display.print("Poisoning");
  display.display();
}
//-------------------------------------------------7.3
void menu73(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/Ethernet/");
  display.print("");
  display.print("Sniffer Mode");
  display.print("Transmiter Mode");
  display.print("-> Poisoning");
  display.display();
}

//----------------------------------------------------
// Menu 8 badUSB
//----------------------------------------------------
void menu8(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("SubGHZ");
  display.println("RF-2.4");
  display.println("Bluetooth");
  display.println("WiFi");
  display.println("InfraRed");
  display.println("RFID-NFC");
  display.println("-> Ethernet");
  display.println("badUSB");
  display.display();
}
//-------------------------------------------------8.1
void menu81(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/badUSB/");
  display.print("");
  display.print("-> Select Payload");
  display.print("Run Payload");
  display.display();
}
//-------------------------------------------------8.2
void menu82(){
  if (refresh){display.clearDisplay();refresh=0;}
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("/badUSB/");
  display.print("");
  display.print("Select Payload");
  display.print("-> Run Payload");
  display.display();
}

switch (mNivel2){
    case 0:
      return;
    case 1:
      menu81();
    break;
    case 2:
      menu82();
    break;
    default:
    break;
  }//switch
}

//====================================================
// Control Joystic
//====================================================
void controlJoystick(){
  leeJoystick();
  if(PQCP) {
    PQCP=0;
    if (joyPos==5){editMode=!editMode;}
    switch (editMode){
       case 1: 
          if (joyPos==4&&n[displayX]<9){n[displayX]++;   //arriba
              refresh=0;}
          if (joyPos==3&&n[displayX]>0){n[displayX]--;   //abajo
              refresh=0;} 
          if (joyPos==1&&displayX<19){displayX++;        //derecha
            refresh=0;}
          if (joyPos==2&&displayX>0){displayX--;         //izq
           refresh=0;}
        break;
        case 0:
          if (mNivel1<3&&joyPos==3){mNivel1++;    //abajo
            refresh=1;
            mNivel2=0;}
          if (mNivel1>0&&joyPos==4){mNivel1--;    //arriba
            mNivel2=0;
            refresh=1;}
          if (mNivel2<3&&joyPos==1){mNivel2++;   //derecha
            refresh=1;}
          if (mNivel2>0&&joyPos==2){mNivel2--;    //izq
           refresh=1;}
        }//!edit
  }//PQCP
}
int leeJoystick(){
  int x = analogRead(xPin);
  int y = analogRead(yPin);
  int k = digitalRead(kPin);
    if(x>900){joyRead=1;        //x+
    }else if(x<100){joyRead=2;  //x-
    }else if(y>900){joyRead=3;  //y+
    }else if(y<100){joyRead=4;  //y-
    }else if(!k){joyRead=5;
    }else{joyRead=0;}

  if (joyRead != lastJoyPos){lastDebounceTime = millis();}
  if(((millis() - lastDebounceTime) > debounceDelay)&&(joyRead!=joyPos)){
    joyPos=joyRead;
    if(!PQCP){PQCP=1;}
    }
  if(((millis() - lastDebounceTime) > (5*debounceDelay))&&(joyPos==3||joyPos==4)){
    joyPos=joyRead;                     //repeat time only for UP/DOWN
    if(!PQCP){PQCP=1;}
    }
  lastJoyPos=joyRead;
}
