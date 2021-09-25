/*
 * File:          Lab07.c
 * Dispositivo:   Tiva C TM4123G
 * Autor:         Alejandro García Aguirre - 19163
 * Compilador:    Energia 1.8
 * 
 * Programa:      Laboratorio 7 - Manejo de memoria SD
 * Hardware:      SPI0 para conección con lector de SD
 * Created on     22 de septiembre de 2021
 */
// include the SD library:
#include <SPI.h>
#include <SD.h>
File myFile;
int pb1=1;
int cont1=0;
int pb2=1;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  SPI.setModule(0);
  
  Serial.print("\nInitializando Tarjeta SD...");
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
  pinMode(10, OUTPUT);     // change this to 53 on a mega

  if (!SD.begin(32)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");


  Serial.println("\n--------------Menu--------------------------------- ");
  Serial.println("Archivos encontrados: ");
  myFile = SD.open("/");
  printDirectory(myFile, 0);
  myFile.close();

  Serial.println("\n--------------Selección----------------------------- ");
  Serial.println("Use PUSH1 para selecionar el archivo ");
  Serial.println("Use PUSH2 para aceptar selección ");
}

void loop() { 
//----------------PUSH B-------------------------------------------
  pb1 = digitalRead(PUSH1);   //Recibo push
  pb2 = digitalRead(PUSH2);   //Recibo push
  if (pb1 == LOW) {
    delay(200);
    cont1++;
    if (cont1==4){
      cont1 = 1;
    }
    Serial.print("Opcion a Escoger: ");
    Serial.println(cont1);    
  } 
  if (pb2 == LOW) {   
    delay(200); 
    Serial.print("Aceptar opción: ");
    Serial.print(cont1);    
  }
//-------------------Selecciónador Imagen 1------------------------
   if (cont1==1 && pb2==0){
    Serial.println(" Nave");
    myFile = SD.open("NAVE.txt", FILE_READ);
    if (myFile) {
      printDirectory(myFile, 0);
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      myFile.close();    
    }
    else{
      Serial.println("error opening NAVE.txt");
    }
   }    
//-------------------Selecciónador Imagen 2------------------------
   if (cont1==3 && pb2==0){
    Serial.println(" Alien");
    myFile = SD.open("ALIEN.txt", FILE_READ);
    if (myFile) {
      printDirectory(myFile, 0);
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      myFile.close();    
    }
    else{
      Serial.println("error opening ALIEN.txt");
    }
   }   
//-------------------Selecciónador Imagen 3------------------------
   if (cont1==2 && pb2==0){
    Serial.println(" Minion");
    myFile = SD.open("MINION.txt", FILE_READ);
    if (myFile) {
      printDirectory(myFile, 0);
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      myFile.close();    
    }
    else{
      Serial.println("error opening MINION.txt");
    }
   }
//-------------------Reset de selección-----------------------------
    if (cont1==4){
          cont1=0;    
    }
}
//--------------------Funciones-------------------------------------
void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}
