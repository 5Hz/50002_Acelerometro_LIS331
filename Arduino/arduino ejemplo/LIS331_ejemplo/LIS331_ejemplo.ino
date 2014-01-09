/******************************************************************
** Código creado en Electrónica 5Hz                              **
** www.5hz-electronica.com                                       **
** Por:                                                          **
** Basado en el código de: autorcillo original                   **
** Descripción del código:                                       **
**                                                               **
** Ejemplo para el acelerómetro LIS331                           **
**                                                               **
*******************************************************************

Conexiones:
UNO   LIS331

3.3V  VCC
GND   GND
10    CS
11    SDA/SDI
12    SA0/SDO
13    SCL/SPC
*/

#include <SPI.h>

#define SS 10 // Serial Select -> CS on LIS331
#define MOSI 11 // MasterOutSlaveIn -> SDI
#define MISO 12 // MasterInSlaveOut -> SDO
#define SCK 13 // Serial Clock -> SPC on LIS331

#define SCALE 5400.0 // escala aproximada para convertir el valor dado en G's 
// scale factor: +/-24g = 48G range. 2^16 bits. 48/65536 = 0.0007324

// global acceleration values
double xAcc, yAcc, zAcc;


void setup()
{
  Serial.begin(9600);
  
  // Configura SPI
  SPI_SETUP();
  
  // Configura acelerometro
  Accelerometer_Setup();
  Serial.println("Acelerometro LIS331");
  Serial.println("eje valor   eje valor  eje valor");
}


void loop()
{
  readVal(); // guarda los valores del acelerometro en las variables xAcc, yAcc y zAcc
  Serial.print("x = ");
  if(xAcc >= 0) Serial.print(" ");
  Serial.print(xAcc, 2);
  Serial.print("   y = ");
  if(yAcc >= 0) Serial.print(" ");
  Serial.print(yAcc, 2);
  Serial.print("  z = ");
  if(zAcc >= 0) Serial.print(" ");
  Serial.println(zAcc, 2);
  
  delay(500);
}
