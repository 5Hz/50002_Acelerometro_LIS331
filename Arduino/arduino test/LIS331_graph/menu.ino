void menu(){
  int entradaMenu;
  Serial.println("-------------------5HZ ELECTRONICA---------------------------");
  Serial.println("");
  Serial.println("                     PRESENTA");
  Serial.println("");
  Serial.println("*************************************************************");
  Serial.println("");
  Serial.println("      BIEVENIDO AL PROGRAMA DE PRUEBAS DEL LIS331");
  Serial.println("");
  Serial.println("                 YA TIENES TODO?");
Serial.println("");
    Serial.println("*************************************************************");
  Serial.println("");
  Serial.println("MENU PRINCIPAL");
  Serial.println("1- X");
  Serial.println("2- Y");
  Serial.println("3- Z");
  while(Serial.available()==0){}
  opcion = Serial.read();
}
