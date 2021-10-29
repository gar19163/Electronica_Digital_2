/*
   File:          Proyecto02.c
   Dispositivo:   Tiva C TM4123G
   Autor:         Alejandro García Aguirre - 19163
   Compilador:    Energia 1.8.11

   Programa:      Donkey Kong
   Hardware:
   Entrega:       22 de Octubre de 2021
*/
//*******************************************************************************************************************************************************************************
// Librerias
//********************************************************************************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include <SD.h>
#include <SPI.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "bitmaps.h"
#include "font.h"
#include "lcd_registers.h"

#define LCD_RST PD_0
#define LCD_CS PD_1
#define LCD_RS PD_2
#define LCD_WR PD_3
#define LCD_RD PE_1
int DPINS[] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
//***************************************************************************************************************************************
// Functions Prototypes
//***************************************************************************************************************************************
void LCD_Init(void);
void LCD_CMD(uint8_t cmd);
void LCD_DATA(uint8_t data);
void SetWindows(unsigned int x, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_Clear(unsigned int c);
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void LCD_Print(String text, int x, int y, int fontSize, int color, int background);
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[], int columns, int index, char flip, char offset);
bool Collision(int x, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
void mapeo(void);
void beep(int note, int duration);
void menu_principal(void);
void GAMEOVER(void);
void WIN(void);
void mapeo_SD(char doc[]) ;
int ascii2hex(int a);
//***************************************************************************************************************************************
// Declaración de variables
//***************************************************************************************************************************************
extern uint8_t marioBitmap[]; // cargar bitmap desde memoria flash
extern uint8_t menu[];
int estado = 0;
int pulsado_start = 1;
int buzzerPin = PF_1;
int pb3 = 1;
int pb4 = 1;
int song = 1;
int comu = 0;
int movb = 7;
int movb1 = 7;
String c;
int cuenta=0;
File myFile;
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define note_g 391
#define note_gs 415
#define note_a 440
//***************************************************************************************************************************************
// Declaración de estructuras
//***************************************************************************************************************************************
struct Sprite { // estructura para sprites
  int x; // posicion x
  int y; // posicion y
  int width; // ancho de bitmap
  int height; // altura de bitmap
  int columns; // columna sprite sheet
  int index; // indice sprite sheet
  int flip; // voltear imagen
  int offset; // desfase
} mario;

struct Sprite1 { // estructura para sprites
  int x; // posicion x
  int y; // posicion y
  int width; // ancho de bitmap
  int height; // altura de bitmap
  int columns; // columna sprite sheet
  int index; // indice sprite sheet
  int flip; // voltear imagen
  int offset; // desfase
} don;

struct Sprite2 { // estructura para sprites
  int x; // posicion x
  int y; // posicion y
  int width; // ancho de bitmap
  int height; // altura de bitmap
  int columns; // columna sprite sheet
  int index; // indice sprite sheet
  int flip; // voltear imagen
  int offset; // desfase
} bard;

struct Sprite3 { // estructura para sprites
  int x; // posicion x
  int y; // posicion y
  int width; // ancho de bitmap
  int height; // altura de bitmap
  int columns; // columna sprite sheet
  int index; // indice sprite sheet
  int flip; // voltear imagen
  int offset; // desfase
} bari;

struct Borrador { // estructura para rectangulos
  int x; // posicion x
  int y; // posicion y
  int width; // ancho de rectángulo
  int height; // altura de rectángulo
  int color; // color de relleno
} bor;

bool collisionover1 = false; // detección de colisión
bool collisionover2 = false; // detección de colisión
bool collisionwin = false; // detección de colisión
unsigned long previousMillis = 0;
const long interval = 42;
//***************************************************************************************************************************************
// Initialization
//***************************************************************************************************************************************
void setup() {
  SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
  Serial.begin(9600);
  Serial3.begin(9600);
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  Serial.println("Start");
  LCD_Init();
  LCD_Clear(0x00);
  SPI.setModule(0);
  pinMode(PUSH1, INPUT_PULLUP); // botones integrados con como entrada pull-up
  pinMode(PUSH2, INPUT_PULLUP);
  pinMode(PA_7, INPUT_PULLUP);
  pinMode(PF_4, INPUT_PULLUP);
  pinMode(PF_1, OUTPUT);
  Serial.println("Inicializando tarjeta SD...");

  if (!SD.begin(PA_3)) {
    Serial.println("initialización fallida!");  //mensaje si hay algun error
    return;
  }
  Serial.println("initialización correcta.");   //mensaje si todo esta bien

  myFile = SD.open("/");                        //se abre el directorio de la SD
  if (song == 1) {
    beep(NOTE_E7, 200);
    beep(NOTE_E7, 200);
    beep(0, 200);
    beep(NOTE_E7, 200);
    beep(0, 200);
    beep(NOTE_C7, 200);
    beep(NOTE_E7, 200);
    beep(0, 200);
    beep(0, 200);
    beep(0, 200);
    beep(NOTE_G7, 200);
    beep(0, 200);
    beep(0, 200);
    beep(NOTE_G6, 200);

    beep(NOTE_C7, 150);
    beep(0, 150);
    beep(0, 150);
    beep(NOTE_G6, 150);
    beep(0, 200);
    beep(0, 200);
    beep(NOTE_E6, 200);
    beep(0, 200);
    beep(0, 200);
    beep(NOTE_A6, 200);
    beep(0, 200);
    beep(NOTE_B6, 200);
    beep(0, 200);
    beep(NOTE_AS6, 200);
    beep(NOTE_A6, 200);
    beep(0, 200);
    song = 0;
  }
  menu_principal ();//Mostrar la pantalla principal
  beep(note_g, 400);
}
//***************************************************************************************************************************************
// Loop
//***************************************************************************************************************************************
void loop() {
  int pb1 = digitalRead(PUSH1);
  int pb2 = digitalRead(PUSH2);
  comunicacion();
  //--------------------------------------------------------------------------------------------------------
  //Inicio de casos
  //--------------------------------------------------------------------------------------------------------
  switch (estado) {
    //--------------------------------------------------------------------------------------------------------
    //Menu y start
    //--------------------------------------------------------------------------------------------------------
    case 0:
      delay(100);
      //--------------------------------------------------------------------------------------------------------
      //Structuras de los sprites
      //--------------------------------------------------------------------------------------------------------
      Serial.print(pb1);
      mario.x = 100;
      mario.y = 191;
      mario.width = 16;
      mario.height = 32;
      mario.columns = 8;
      mario.index = 0;
      mario.flip = 0;
      mario.offset = 0;

      bard.x = 152;
      bard.y = 54;
      bard.width = 16;
      bard.height = 11;
      bard.columns = 4;
      bard.index = 0;
      bard.flip = 0;
      bard.offset = 0;

      bari.x = 152;
      bari.y = 54;
      bari.width = 16;
      bari.height = 11;
      bari.columns = 4;
      bari.index = 0;
      bari.flip = 0;
      bari.offset = 0;

      don.x = 137;
      don.y = 30;
      don.width = 46;
      don.height = 36;
      don.columns = 2;
      don.index = 2;
      don.flip = 0;
      don.offset = 0;

      bor.x = 0;
      bor.y = 0;
      bor.width = 30;
      bor.height = 30;
      bor.color = 0X0000;
      //--------------------------------------------------------------------------------------------------------
      //Start
      //--------------------------------------------------------------------------------------------------------
      if (pulsado_start == 1 && estado == 0 && (pb1 == 0 | pb2 == 0 | pb3 == 0 | pb4 == 0)) { //Mapeo
        pulsado_start = 0;
        LCD_Clear(0x00);
        mapeo();
        estado = 1;//Se cambia al estado siguiente
      }
      break;
    //--------------------------------------------------------------------------------------------------------
    //Juego-Movimienti
    //--------------------------------------------------------------------------------------------------------
    case 1:
      unsigned long currentMillis = millis();
      // actualización de frame cada 42ms = 24fps
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        //--------------------------------------------------------------------------------------------------------
        //Mario izquierda
        //--------------------------------------------------------------------------------------------------------
        if (pb1 == 0) { // modificación de atributos de sprite
          mario.x += 4;
          mario.index++;
          mario.index %= 3;
          mario.flip = 1;
        }
        //--------------------------------------------------------------------------------------------------------
        //Mario derecha
        //--------------------------------------------------------------------------------------------------------
        if (pb2 == 0) { //derecha
          mario.x -= 4;
          mario.index++;
          mario.index %= 3;
          mario.flip = 0;
        }
        //--------------------------------------------------------------------------------------------------------
        //Mario sube o baja
        //--------------------------------------------------------------------------------------------------------
        if (((mario.x == 100) | (mario.x == 240)) && mario.y == 111) { //Sube a nivel 1
          mario.y = 33;
          bor.y = 111;
          bor.x = 100;
          FillRect(bor.x, bor.y, bor.height, bor.width, 0x0000);
          bor.x = 240;
          FillRect(bor.x, bor.y, bor.height, bor.width, 0x0000);
        }
        if ((mario.x == 240 | mario.x == 20) && mario.y == 191) { //Sube a nivel 2
          mario.y = 111;
          bor.y = 191;
          bor.x = 240;
          FillRect(bor.x, bor.y, bor.height, bor.width, 0x0000);
          bor.x = 20;
          FillRect(bor.x, bor.y, bor.height, bor.width, 0x0000);
        }
        if ((mario.x == 80 | mario.x == 280) && mario.y == 33) { //Baja a nivel 2
          mario.y = 111;
          bor.y = 33;
          bor.x = 280;
          FillRect(bor.x, bor.y, bor.height, bor.width, 0x0000);
          bor.x = 80;
          FillRect(bor.x, bor.y, bor.height, bor.width, 0x0000);
        }
        //--------------------------------------------------------------------------------------------------------
        //Barill a derecha
        //--------------------------------------------------------------------------------------------------------
        if (pb3 == 0) { //Barril a derecha
          don.index = 1;
          don.flip = 0;
          LCD_Sprite(don.x, don.y, don.width, don.height, donkey, don.columns, don.index, don.flip, don.offset);
          bard.x = 183;
          bard.y = 54;
          movb = 0;
        }

        int barril1_index = (bard.x / 11) % 8;
        switch (movb) {
          case 0:
            if (bard.x < 260 && bard.y == 54) {
              LCD_Sprite(bard.x, bard.y, bard.width, bard.height, barril, 4, barril1_index, 1, 0);
              V_line( bard.x - 1, bard.y, bard.height, 0x0000);
              bard.x++;
            }
            else {
              don.index = 0;
              LCD_Sprite(don.x, don.y, don.width, don.height, donkey, don.columns, don.index, don.flip, don.offset);
              FillRect(bard.x, bard.y, bard.width, bard.height, 0x0000);
              bard.x = 304;
              bard.y = 129;
              movb = 1;
              Serial.println("temino caso 0");
            }
            break;
          case 1:
            Serial.println("inicioo caso 1");
            if (bard.x > 220 && bard.y == 129) {
              LCD_Sprite(bard.x, bard.y, bard.width, bard.height, barril, 4, barril1_index, 0, 0);
              V_line( bard.x + 16, bard.y, bard.height, 0x0000);
              bard.x--;
            }
            else {
              FillRect(bard.x, bard.y, bard.width, bard.height, 0x0000);
              bard.y = 212;
              movb = 2;
              Serial.println("Termino caso 1");
            }
            break;
          case 2:
            if (bard.x > 4 && bard.y == 212) {
              Serial.println("inicioo caso 2");
              LCD_Sprite(bard.x, bard.y, bard.width, bard.height, barril, bard.columns, barril1_index, 1, 0);
              V_line( bard.x + 16, bard.y, bard.height, 0x0000);
              bard.x--;
            }
            else {
              FillRect(bard.x, bard.y, bard.width, bard.height, 0x0000);
              Serial.println("Termino caso 2");
              movb = 3;
            }
            break;
          case 3:
            LCD_Sprite(320, 240, bard.width, bard.height, barril, bard.columns, barril1_index, 1, 0);
            movb = 4;
            Serial.println("Termino");
            Serial.print(bard.x);
            Serial.print("-");
            Serial.println(bard.y);
            break;
        }
        //--------------------------------------------------------------------------------------------------------
        //Barill a izquierda
        //--------------------------------------------------------------------------------------------------------
        if (pb4 == 0) {
          bari.x = 133;
          bari.y = 54;
          don.flip = 1;
          don.index = 1;
          LCD_Sprite(don.x, don.y, don.width, don.height, donkey, don.columns, don.index, don.flip, don.offset);
          movb1 = 0;
        }
        int barril_index = (bari.x / 11) % 8;
        switch (movb1) {
          case 0:
            if (bari.x > 80 && bari.y == 54) {
              LCD_Sprite(bari.x, bari.y, bari.width, bari.height, barril, 4, barril_index, 1, 0);
              V_line( bari.x + 16, bari.y, bari.height, 0x0000);
              bari.x--;
            }
            else {
              don.index = 0;
              LCD_Sprite(don.x, don.y, don.width, don.height, donkey, don.columns, don.index, don.flip, don.offset);
              FillRect(bari.x, bari.y, bari.width, bari.height, 0x0000);
              bari.x = 04;
              bari.y = 129;
              movb1 = 1;
              Serial.println("temino caso 0");
            }
            break;
          case 1:
            Serial.println("inicioo caso 1");
            if (bari.x < 120 && bari.y == 129) {
              bari.x++;
              LCD_Sprite(bari.x, bari.y, bari.width, bari.height, barril, 4, barril_index, 0, 0);
              V_line( bari.x - 1, bari.y, bari.height, 0x0000);
            }
            else {
              FillRect(bari.x, bari.y, bari.width, bari.height, 0x0000);
              bari.x = 120;
              bari.y = 212;
              movb1 = 2;
              Serial.println("Termino caso 1");
            }
            break;
          case 2:
            Serial.println("inicioo caso 2");
            if (bari.x < 304 && bari.y == 212) {
              LCD_Sprite(bari.x, bari.y, bari.width, bari.height, barril, bari.columns, barril_index, 1, 0);
              V_line( bari.x + 16, bari.y, bari.height, 0x0000);
              bari.x++;
            }
            else {
              FillRect(bari.x, bari.y, bari.width, bari.height, 0x0000);
              Serial.println("Termino caso 2");
              movb1 = 3;
            }
            break;
          case 3:
            LCD_Sprite(320, 240, bari.width, bari.height, barril, bari.columns, barril_index, 1, 0);
            movb1 = 4;
            Serial.println("Termino");
            Serial.print(bari.x);
            Serial.print("-");
            Serial.println(bari.y);
            break;
        }
        //---------------------------------------------------------------------------------------------
        //Colisiones
        //---------------------------------------------------------------------------------------------
        collisionover1 = Collision(mario.x, mario.y, mario.width, mario.height,
                                   bard.x, bard.y, bard.width, bard.height); // detección de colisión
        collisionover2 = Collision(mario.x, mario.y, mario.width, mario.height,
                                   bari.x, bari.y, bari.width, bari.height); // detección de colisión
        if (collisionover1 | collisionover2) { //
          GAMEOVER();
        }
        collisionwin = Collision(mario.x, mario.y, mario.width, mario.height,
                                 don.x, don.y, don.width, don.height); // detección de colisión
        if (collisionwin) {
          WINNER();
        }

        if (mario.flip == 1) { // dependiendo de la dirección, se colorea resto del sprite del frame anterior
          FillRect(mario.x - 4, mario.y, 4, mario.height, 0x0000);
        }
        else {
          FillRect(mario.x + mario.width, mario.y, 4, mario.height, 0x0000);
        }
        LCD_Sprite(mario.x, mario.y, mario.width, mario.height, marioBitmap, mario.columns, mario.index, mario.flip, mario.offset);
      }
      break;
  }
} //Fin del Loop



//***************************************************************************************************************************************
// Función para inicializar LCD
//***************************************************************************************************************************************
void LCD_Init(void) {
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_WR, OUTPUT);
  pinMode(LCD_RD, OUTPUT);
  for (uint8_t i = 0; i < 8; i++) {
    pinMode(DPINS[i], OUTPUT);
  }
  //****************************************
  // Secuencia de Inicialización
  //****************************************
  digitalWrite(LCD_CS, HIGH);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_RST, HIGH);
  delay(5);
  digitalWrite(LCD_RST, LOW);
  delay(20);
  digitalWrite(LCD_RST, HIGH);
  delay(150);
  digitalWrite(LCD_CS, LOW);
  //****************************************
  LCD_CMD(0xE9);  // SETPANELRELATED
  LCD_DATA(0x20);
  //****************************************
  LCD_CMD(0x1); // Exit Sleep SLEEP OUT (SLPOUT)
  delay(100);
  //****************************************
  LCD_CMD(0xD1);    // (SETVCOM)
  LCD_DATA(0x00);
  LCD_DATA(0x71);
  LCD_DATA(0x9);
  //****************************************
  LCD_CMD(0xD0);   // (SETPOWER)
  LCD_DATA(0x07);
  LCD_DATA(0x01);
  LCD_DATA(0x08);
  //****************************************
  LCD_CMD(0x36);  // (MEMORYACCESS)
  LCD_DATA(0x40 | 0x80 | 0x20 | 0x08); // LCD_DATA(0x9);
  //****************************************
  LCD_CMD(0x3A); // Set_pixel_format (PIXELFORMAT)
  LCD_DATA(0x05); // color setings, 05h - 16bit pixel, 11h - 3bit pixel
  //****************************************
  LCD_CMD(0xC1);    // (POWERCONTROL2)
  LCD_DATA(0x0);
  LCD_DATA(0x0);
  LCD_DATA(0x02);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC0); // Set Default Gamma (POWERCONTROL1)
  LCD_DATA(0x00);
  LCD_DATA(0x35);
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC5); // Set Frame Rate (VCOMCONTROL1)
  LCD_DATA(0x04); // 72Hz
  //****************************************
  LCD_CMD(0xD2); // Power Settings  (SETPWRNORMAL)
  LCD_DATA(0x01);
  LCD_DATA(0x44);
  //****************************************
  LCD_CMD(0xC8); //Set Gamma  (GAMMASET)
  LCD_DATA(0x04);
  LCD_DATA(0x67);
  LCD_DATA(0x35);
  LCD_DATA(0x04);
  LCD_DATA(0x08);
  LCD_DATA(0x06);
  LCD_DATA(0x24);
  LCD_DATA(0x01);
  LCD_DATA(0x37);
  LCD_DATA(0x40);
  LCD_DATA(0x03);
  LCD_DATA(0x0);
  LCD_DATA(0x08);
  LCD_DATA(0x80);
  LCD_DATA(0x00);
  //****************************************
  LCD_CMD(0x2A); // Set_column_address 320px (CASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x3F);
  //****************************************
  LCD_CMD(0x2B); // Set_page_address 480px (PASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0xE0);
  //  LCD_DATA(0x8F);
  LCD_CMD(0x29); //display on
  LCD_CMD(0x2C); //display on

  LCD_CMD(ILI9341_INVOFF); //Invert Off
  delay(120);
  LCD_CMD(ILI9341_SLPOUT);    //Exit Sleep
  delay(120);
  LCD_CMD(ILI9341_DISPON);    //Display on
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar comandos a la LCD - parámetro (comando)
//***************************************************************************************************************************************
void LCD_CMD(uint8_t cmd) {
  digitalWrite(LCD_RS, LOW);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = cmd;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar datos a la LCD - parámetro (dato)
//***************************************************************************************************************************************
void LCD_DATA(uint8_t data) {
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = data;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para definir rango de direcciones de memoria con las cuales se trabajara (se define una ventana)
//***************************************************************************************************************************************
void SetWindows(unsigned int x, unsigned int y1, unsigned int x2, unsigned int y2) {
  LCD_CMD(0x2a); // Set_column_address 4 parameters
  LCD_DATA(x >> 8);
  LCD_DATA(x);
  LCD_DATA(x2 >> 8);
  LCD_DATA(x2);
  LCD_CMD(0x2b); // Set_page_address 4 parameters
  LCD_DATA(y1 >> 8);
  LCD_DATA(y1);
  LCD_DATA(y2 >> 8);
  LCD_DATA(y2);
  LCD_CMD(0x2c); // Write_memory_start
}
//***************************************************************************************************************************************
// Función para borrar la pantalla - parámetros (color)
//***************************************************************************************************************************************
void LCD_Clear(unsigned int c) {
  unsigned int x, y;
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  SetWindows(0, 0, 319, 239); // 479, 319);
  for (x = 0; x < 320; x++)
    for (y = 0; y < 240; y++) {
      LCD_DATA(c >> 8);
      LCD_DATA(c);
    }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea horizontal - parámetros ( coordenada x, cordenada y, longitud, color)
//***************************************************************************************************************************************
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + x;
  SetWindows(x, y, l, y);
  j = l;// * 2;
  for (i = 0; i < l; i++) {
    LCD_DATA(c >> 8);
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea vertical - parámetros ( coordenada x, cordenada y, longitud, color)
//***************************************************************************************************************************************
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + y;
  SetWindows(x, y, x, l);
  j = l; //* 2;
  for (i = 1; i <= j; i++) {
    LCD_DATA(c >> 8);
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  H_line(x  , y  , w, c);
  H_line(x  , y + h, w, c);
  V_line(x  , y  , h, c);
  V_line(x + w, y  , h, c);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 = x + w;
  y2 = y + h;
  SetWindows(x, y, x2 - 1, y2 - 1);
  unsigned int k = w * h * 2 - 1;
  unsigned int i, j;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      LCD_DATA(c >> 8);
      LCD_DATA(c);
      k = k - 2;
    }
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar texto - parámetros ( texto, coordenada x, cordenada y, color, background)
//***************************************************************************************************************************************
void LCD_Print(String text, int x, int y, int fontSize, int color, int background) {
  int fontXSize ;
  int fontYSize ;

  if (fontSize == 1) {
    fontXSize = fontXSizeSmal ;
    fontYSize = fontYSizeSmal ;
  }
  if (fontSize == 2) {
    fontXSize = fontXSizeBig ;
    fontYSize = fontYSizeBig ;
  }

  char charInput ;
  int cLength = text.length();
  Serial.println(cLength, DEC);
  int charDec ;
  int c ;
  int charHex ;
  char char_array[cLength + 1];
  text.toCharArray(char_array, cLength + 1) ;
  for (int i = 0; i < cLength ; i++) {
    charInput = char_array[i];
    Serial.println(char_array[i]);
    charDec = int(charInput);
    digitalWrite(LCD_CS, LOW);
    SetWindows(x + (i * fontXSize), y, x + (i * fontXSize) + fontXSize - 1, y + fontYSize );
    long charHex ;
    for ( int n = 0 ; n < fontYSize ; n++ ) {
      if (fontSize == 1) {
        charHex = pgm_read_word_near(smallFont + ((charDec - 32) * fontYSize) + n);
      }
      if (fontSize == 2) {
        charHex = pgm_read_word_near(bigFont + ((charDec - 32) * fontYSize) + n);
      }
      for (int t = 1; t < fontXSize + 1 ; t++) {
        if (( charHex & (1 << (fontXSize - t))) > 0 ) {
          c = color ;
        } else {
          c = background ;
        }
        LCD_DATA(c >> 8);
        LCD_DATA(c);
      }
    }
    digitalWrite(LCD_CS, HIGH);
  }
}
//***************************************************************************************************************************************
// Función para dibujar una imagen a partir de un arreglo de colores (Bitmap) Formato (Color 16bit R 5bits G 6bits B 5bits)
//***************************************************************************************************************************************
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 = x + width;
  y2 = y + height;
  SetWindows(x, y, x2 - 1, y2 - 1);
  unsigned int k = 0;
  unsigned int i, j;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k + 1]);
      //LCD_DATA(bitmap[k]);
      k = k + 2;
    }
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una imagen sprite - los parámetros columns = número de imagenes en el sprite, index = cual desplegar, flip = darle vuelta
//***************************************************************************************************************************************
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[], int columns, int index, char flip, char offset) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);

  unsigned int x2, y2;
  x2 =   x + width;
  y2 =    y + height;
  SetWindows(x, y, x2 - 1, y2 - 1);
  int k = 0;
  int ancho = ((width * columns));
  if (flip) {
    for (int j = 0; j < height; j++) {
      k = (j * (ancho) + index * width - 1 - offset) * 2;
      k = k + width * 2;
      for (int i = 0; i < width; i++) {
        LCD_DATA(bitmap[k]);
        LCD_DATA(bitmap[k + 1]);
        k = k - 2;
      }
    }
  }
  else {
    for (int j = 0; j < height; j++) {
      k = (j * (ancho) + index * width + 1 + offset) * 2;
      for (int i = 0; i < width; i++) {
        LCD_DATA(bitmap[k]);
        LCD_DATA(bitmap[k + 1]);
        k = k + 2;
      }
    }
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Funcion para colision
//***************************************************************************************************************************************
bool Collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
  return (x1 < x2 + w2) && (x1 + w1 > x2) && (y1 < y2 + h2) && (y1 + h1 > y2);
}
//***************************************************************************************************************************************
// Función que muestra el menú principal del juego
//***************************************************************************************************************************************
void menu_principal(void) {
  LCD_Clear(0x00);
  String Mun = "Pablo Munoz";
  String Ale = "Alejandro Garcia";
  LCD_Print(Mun, 80, 60, 2, 0xffff, 0x0000);
  LCD_Print(Ale, 30, 130, 2, 0xffff, 0x0000);
  delay(1000);
  LCD_Clear(0x00);
  mapeo_SD("Fonfom.txt");
  //LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
  LCD_Bitmap(0, 0, 320, 240, menu);
  //LCD_Print(String text, int x, int y, int fontSize, int color, int background)

  String titulo = "Donkey Kong";
  String ini_text = "Press START";
  //LCD_Print(titulo, 80, 90, 2, 0xffff, 0x0000);
  LCD_Print(ini_text, 80, 150, 2, 0xffff, 0x0000);
}
//***************************************************************************************************************************************
// Funcion para tocar notas musicales
//***************************************************************************************************************************************
void beep(int note, int duration) {
  tone(buzzerPin, note, duration / 2);
  delay(duration / 2);
  noTone(buzzerPin);
  delay(duration / 2 + 20);
}
//***************************************************************************************************************************************
// Funcion para mapeo de tablero
//***************************************************************************************************************************************
void mapeo (void) {
  for (int x = 0; x < 319; x++) {  //Nivel 1 vigas
    LCD_Bitmap(x, 223, 17, 10, viga);
    x += 15;
  }

  for (int x = 0; x < 120; x++) {  //Nivel 2 viga
    LCD_Bitmap(x, 143, 17, 10, viga);
    x += 15;
  }
  for (int x = 220; x < 319; x++) {
    LCD_Bitmap(x, 143, 17, 10, viga);
    x += 15;
  }

  for (int x = 90; x < 260; x++) {  //Nivel 3 viga
    LCD_Bitmap(x, 65, 17, 10, viga);
    x += 15;
  }
  for (int x = 20; x < 360; x++) {  //Nivel 1 escaleras
    LCD_Bitmap(x, 155, 10, 25, escalera);
    x += 240;
  }
  for (int x = 20; x < 360; x++) {  //
    LCD_Bitmap(x, 170, 10, 25, escalera);
    x += 240;
  }
  for (int x = 100; x < 250; x++) {  //Nivel 2 escaleras
    LCD_Bitmap(x, 77, 10, 25, escalera);
    x += 140;
  }
  for (int x = 100; x < 250; x++) {  //
    LCD_Bitmap(x, 102, 10, 25, escalera);
    x += 140;
  }
  LCD_Sprite(don.x, don.y, don.width, don.height, donkey, don.columns, don.index, don.flip, don.offset);
}
//***************************************************************************************************************************************
// Funcion para menu de GAME OVER
//***************************************************************************************************************************************
void GAMEOVER(void) {
  LCD_Clear(0x00);
  String game_over = "Game over";
  String ini_text = "Press START";
  LCD_Print(game_over, 80, 60, 2, 0xffff, 0x0000);
  LCD_Print(ini_text, 60, 200, 2, 0xffff, 0x0000);
  pulsado_start = 1;
  delay(1000);
  menu_principal();
  estado = 0;
}
//***************************************************************************************************************************************
// Funcion para menu de GANADOR
//***************************************************************************************************************************************
void WINNER(void) {
  LCD_Clear(0x00);
  String winner = "YOU WIN";
  String ini_text = "Press START";
  LCD_Print(winner, 80, 60, 2, 0xffff, 0x0000);
  LCD_Print(ini_text, 60, 200, 2, 0xffff, 0x0000);
  pulsado_start = 1;
  delay(1000);
  menu_principal();
  estado = 0;
}
//***********************************************
//Comunicación
//***********************************************
void comunicacion(void) {
  Serial3.write('h');
  while (Serial3.available() && (cuenta < 1)) {
    delay(10);                    //para dar estabilidad al programa
    c = Serial3.read();    //244
    cuenta++;
  }
  cuenta = 0;
  pb3 = c.toInt();
  c = "";

  Serial3.write('j');
  while (Serial3.available() && (cuenta < 1)) {
    delay(10);                    //para dar estabilidad al programa
    c = Serial3.read();    //244
    cuenta++;
  }
  cuenta = 0;
  pb4 = c.toInt();
  c = "";
}
//***************************************************************************************************************************************
// Función sw mapeo sd
//***************************************************************************************************************************************
int ascii2hex(int a) {
  switch (a) {
    case (48):      //caso 0
      return 0;
    case (49):      //caso 1
      return 1;
    case (50):      //caso 2
      return 2;
    case (51):      //caso 3
      return 3;
    case (52):      //caso 4
      return 4;
    case (53):      //caso 5
      return 5;
    case (54):      //caso 6
      return 6;
    case (55):      //caso 7
      return 7;
    case (56):      //caso 8
      return 8;
    case (57):      //caso 9
      return 9;
    case (97):      //caso A
      return 10;
    case (98):      //caso B
      return 11;
    case (99):      //caso C
      return 12;
    case (100):     //caso D
      return 13;
    case (101):     //caso E
      return 14;
    case (102):     //caso F
      return 15;
  }
}
void mapeo_SD(char doc[]) {
  myFile = SD.open(doc, FILE_READ);   //se toma el archivo de la imagen
  int hex1 = 0;                       //declaracion de variable 1 para valor hex
  int val1 = 0;
  int val2 = 0;
  int mapear = 0;
  int vertical = 0;
  unsigned char maps[640];            //se crea arreglo vacio para almacenar el mapeo

  if (myFile) {
    while (myFile.available() ) {     //se leen datos mientras este disponible
      mapear = 0;
      while (mapear < 640) {          //se limita el rango
        hex1 = myFile.read();         //se lee el archivo con la imagen
        if (hex1 == 120) {
          val1 = myFile.read();       //se lee el primer valor hexadecimal del bitmap
          val2 = myFile.read();       //se lee el segundo valor hexadecimal del bitmap
          val1 = ascii2hex(val1);     //se mapea el primer valor hexadecimal
          val2 = ascii2hex(val2);     //se mapea el segundo valor hexadecimal
          maps[mapear] = val1 * 16 + val2;  //se colona en el arreglo nuevo
          mapear++;                         //se cambia de posicion
        }
      }
      LCD_Bitmap(0, vertical, 320, 1, maps);
      vertical++;
    }
    myFile.close();
  }
  else {
    Serial.println("No se pudo abrir la imagen, prueba nuevamente");
    myFile.close();
  }
}
