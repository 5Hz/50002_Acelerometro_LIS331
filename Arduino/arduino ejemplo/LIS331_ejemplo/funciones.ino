// lee los valores del acelerometro y los guarda en variables globales
void readVal()
{
  byte xAddressByteL = 0x28; // Low Byte of X value (the first data register)
  byte readBit = B10000000; // bit 7 (MSB) HIGH means read register
  byte incrementBit = B01000000; // el bit 1 alto significa que incremente registros
  // esto permite seguir leyendo registros de datos enviando un byte vacio
  byte dataByte = xAddressByteL | readBit | incrementBit;
  byte b0 = 0x0; // un byte vacio, para incrementar a los registros siguientes
  
  digitalWrite(SS, LOW); // SS debe estar LOW para poder comunicarse
  delay(1);
  SPI.transfer(dataByte); // solicita una lectura, iniciando por el dato X
  byte xL = SPI.transfer(b0); // get the low byte of X data
  byte xH = SPI.transfer(b0); // get the high byte of X data
  byte yL = SPI.transfer(b0); // get the low byte of Y data
  byte yH = SPI.transfer(b0); // get the high byte of Y data
  byte zL = SPI.transfer(b0); // get the low byte of Z data
  byte zH = SPI.transfer(b0); // get the high byte of Z data
  delay(1);
  digitalWrite(SS, HIGH);
  
  // shift the high byte left 8 bits and merge the high and low
  int xVal = (xL | (xH << 8));
  int yVal = (yL | (yH << 8));
  int zVal = (zL | (zH << 8));
  
  // scale the values into G's
  xAcc = xVal / SCALE;
  yAcc = yVal / SCALE;
  zAcc = zVal / SCALE;
}

void SPI_SETUP()
{
  pinMode(SS, OUTPUT);
  
  // wake up the SPI bus
  SPI.begin();
  
  // This device reads MSB first:
  SPI.setBitOrder(MSBFIRST);
  
  /*
  SPI.setDataMode()
  Mode Clock Polarity (CPOL) Clock Phase (CPHA)
  SPI_MODE0 0 0
  SPI_MODE1 0 1
  SPI_MODE2 1 0
  SPI_MODE3 1 1
  */
  SPI.setDataMode(SPI_MODE0);
  
  /*
  SPI.setClockDivider()
  sets SPI clock to a fraction of the system clock
  Arduino UNO system clock = 16 MHz
  Mode SPI Clock
  SPI_CLOCK_DIV2 8 MHz
  SPI_CLOCK_DIV4 4 MHz
  SPI_CLOCK_DIV8 2 MHz
  SPI_CLOCK_DIV16 1 MHz
  SPI_CLOCK_DIV32 500 Hz
  SPI_CLOCK_DIV64 250 Hz
  SPI_CLOCK_DIV128 125 Hz
  */
  
  SPI.setClockDivider(SPI_CLOCK_DIV16); // SPI clock 1000Hz
}

void Accelerometer_Setup()
{
  // Set up the accelerometer
  // write to Control register 1: address 20h
  byte addressByte = 0x20;
  /* Bits:
  PM2 PM1 PM0 DR1 DR0 Zen Yen Xen
  PM2PM1PM0: Power mode (001 = Normal Mode)
  DR1DR0: Data rate (00=50Hz, 01=100Hz, 10=400Hz, 11=1000Hz)
  Zen, Yen, Xen: Z enable, Y enable, X enable
  */
  byte ctrlRegByte = 0x37; // 00111111 : normal mode, 1000Hz, xyz enabled
  
  // Send the data for Control Register 1
  digitalWrite(SS, LOW);
  delay(1);
  SPI.transfer(addressByte);
  SPI.transfer(ctrlRegByte);
  delay(1);
  digitalWrite(SS, HIGH);
  
  delay(100);
  
  // write to Control Register 2: address 21h
  addressByte = 0x21;
  // This register configures high pass filter
  ctrlRegByte = 0x00; // High pass filter off
  
  // Send the data for Control Register 2
  digitalWrite(SS, LOW);
  delay(1);
  SPI.transfer(addressByte);
  SPI.transfer(ctrlRegByte);
  delay(1);
  digitalWrite(SS, HIGH);
  
  delay(100);
  
  // Control Register 3 configures Interrupts
  // Since I'm not using Interrupts, I'll leave it alone
  
  // write to Control Register 4: address 23h
  addressByte = 0x23;
  /* Bits:
  BDU BLE FS1 FS0 STsign 0 ST SIM
  BDU: Block data update (0=continuous update)
  BLE: Big/little endian data (0=accel data LSB at LOW address)
  FS1FS0: Full-scale selection (00 = +/-6G, 01 = +/-12G, 11 = +/-24G)
  STsign: selft-test sign (default 0=plus)
  ST: self-test enable (default 0=disabled)
  SIM: SPI mode selection(default 0=4 wire interface, 1=3 wire interface)
  */
  ctrlRegByte = 0x00; // 00000000 : 6G un cuarto de la escala completa
  
  // Send the data for Control Register 4
  digitalWrite(SS, LOW);
  delay(1);
  SPI.transfer(addressByte);
  SPI.transfer(ctrlRegByte);
  delay(1);
  digitalWrite(SS, HIGH);
}
