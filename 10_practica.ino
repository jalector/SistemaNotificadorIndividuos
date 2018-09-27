/**
 * Instituto Tecnológico de Léon
 * 
 * Sistema Notificador de llegada de individuos
 * 
 * @author Juda Alector Vallejo Herrera
 * 
 * @description Un sistema que regula su consumo de energía y 
 *              detecta cuando alguien ya ha llegado.
 *              
 * @date 27 de Septiembre 2018             
 */

#include "LowPower.h"                         // Incluimos la librería 

#define reedswitch 2                          // Definimos el pin para reed Switch

#define led 3                                 // Definimos pin para led para aviso de entrada


volatile  bool powerOn = false;

void setup() {                                // Damos configuración a cada uno de los pines
  pinMode(reedswitch, INPUT);                 // Definimos reed switch cómo input
  pinMode(led, OUTPUT);                       // Definimos pin cómo salida
  digitalWrite(reedswitch, HIGH);             // Activamos reed switch

  Serial.begin( 9600 );                       //Inicializamos el puerto serial
}

void loop( ) {
  // Reviza el reed switch para ejecutar la interrupción
  attachInterrupt(digitalPinToInterrupt( reedswitch ), interrupcion, LOW);    
  // Mandamos a el arduino a dormir para gastar menos voltaje
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);      
  // Das de baja la interrupción
  detachInterrupt(0); 

  if( powerOn ) {                             // Sólo sí se ejecuta la interrupción encenderá
    digitalWrite(led, HIGH);        
    delay(500);
  }
  digitalWrite(led, LOW);                     // Apagamos el led
}

void interrupcion () {                        // La interrupción nos permite cambiar el modo del arduino
  powerOn = !powerOn;
}
