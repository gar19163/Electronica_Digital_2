/*
 * File:          Lab06.c
 * Dispositivo:   Tiva C TM4123G
 * Autor:         Alejandro García Aguirre - 19163
 * Compilador:    Energia 1.8
 * 
 * Programa:      Laboratorio 6 - Juego de carreras
 * Hardware:      
 * Created on     8 de septiembre de 2021
 */
//Constantes

//Variables
int pb1 = 1;
int cont1=0;
int pb2 = 1;
int cont2=0;
void setup() {
  // Conf
  Serial.begin(9600); 
  //Entradas
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
  pinMode(RED_LED,  OUTPUT);
  pinMode(GREEN_LED,  OUTPUT);
  pinMode(BLUE_LED,  OUTPUT);
  pinMode(PB_5,  OUTPUT);
  pinMode(PB_0,  OUTPUT);
  pinMode(PB_4,  OUTPUT);
  pinMode(PE_4,  OUTPUT);
  pinMode(PE_5,  OUTPUT);
  pinMode(PA_5,  OUTPUT);
  pinMode(PA_6,  OUTPUT);
  pinMode(PB_1,  OUTPUT);
  pinMode(PF_2,  OUTPUT); //Contador 2
  pinMode(PB_2,  OUTPUT);
  pinMode(PB_3,  OUTPUT);
  pinMode(PC_5,  OUTPUT);
  pinMode(PC_4,  OUTPUT);
  pinMode(PC_6,  OUTPUT);
  pinMode(PC_7,  OUTPUT);
  pinMode(PD_6,  OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly: 
  pb1 = digitalRead(PUSH1);   //Recibo push
  pb2 = digitalRead(PUSH2);   //Recibo push
  if (pb1 == LOW) {
    delay(200);
    cont1++;
    Serial.print("Contador 1: ");
    Serial.println(cont1);    
  } 
  if (pb2 == LOW) {
    delay(200);
    cont2++;
    Serial.print("Contador 2: ");
    Serial.println(cont2);    
  }
//-----------------------------Primer Contador-------------------------
  switch (cont1){ //Secuencia de leds para contador 1
    case 0:       //Inicialización
      digitalWrite(PB_5, LOW);
      digitalWrite(PB_0, LOW);
      digitalWrite(PB_1, LOW);
      digitalWrite(PE_4, LOW);
      digitalWrite(PE_5, LOW);
      digitalWrite(PB_4, LOW);
      digitalWrite(PA_5, LOW);
      digitalWrite(PA_6, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
      break;
    case 1:
      digitalWrite(RED_LED, HIGH);
      delay(1000);      
      digitalWrite(GREEN_LED, HIGH);
      delay(1000);
      digitalWrite(RED_LED, LOW);
      cont1 = 2;
      cont2 = 2;
      break;
    case 2:
      delay(1);
      break;
    case 3:
      digitalWrite(PB_5, HIGH);
      break;
    case 4:
      digitalWrite(PB_0, HIGH);
      break;
    case 5:
      digitalWrite(PB_1, HIGH);
      break;
    case 6:
      digitalWrite(PE_4, HIGH);
      break;
    case 7:
      digitalWrite(PE_5, HIGH);
      break;
    case 8:
      digitalWrite(PB_4, HIGH);
      break;
    case 9:
      digitalWrite(PA_5, HIGH);
      break;
    case 10:         //Ganador
      digitalWrite(PA_6, HIGH);
      digitalWrite(BLUE_LED, HIGH);
      delay(500);
      cont1 = 0;
      cont2 = 0;
      break;
  }
//------------------------Segundo Contador------------------------------------     
    switch (cont2){ //caso de leds para contador 2 
    case 0:       //Inicialización
      digitalWrite(PF_2, LOW);
      digitalWrite(PB_2, LOW);
      digitalWrite(PB_3, LOW);
      digitalWrite(PC_4, LOW);
      digitalWrite(PC_5, LOW);
      digitalWrite(PC_6, LOW);
      digitalWrite(PC_7, LOW);
      digitalWrite(PD_6, LOW);      
      break;
    case 1:
      digitalWrite(RED_LED, HIGH);
      delay(1000);      
      digitalWrite(GREEN_LED, HIGH);
      delay(1000);
      digitalWrite(RED_LED, LOW);
      cont1 = 2;
      cont2 = 2;
      break;
    case 2:
      delay(1);
      break;
    case 3:
      digitalWrite(PF_2, HIGH);
      break;
    case 4:
      digitalWrite(PB_2, HIGH);
      break;
    case 5:
      digitalWrite(PB_3, HIGH);
      break;
    case 6:
      digitalWrite(PC_4, HIGH);
      break;
    case 7:
      digitalWrite(PC_5, HIGH);
      break;
    case 8:
      digitalWrite(PC_6, HIGH);
      break;
    case 9:
      digitalWrite(PC_7, HIGH);
      break;
    case 10:
      digitalWrite(PD_6, HIGH);
      digitalWrite(BLUE_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      delay(500);
      cont1 = 0;
      cont2 = 0;
      break;
  }   
}
