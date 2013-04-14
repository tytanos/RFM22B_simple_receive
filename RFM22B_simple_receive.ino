// prosty odbiór danyh liczbowych
#include <RF22ReliableDatagram.h>
#include <RF22.h>
#include <SPI.h>

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2

// Singleton instance of the radio
RF22ReliableDatagram rf22(SERVER_ADDRESS);

typedef struct {
	int lp; 
	int liczba;
} Payload;
Payload dane;

 uint8_t len = sizeof(dane);
 uint8_t from;
 uint8_t to;    

void setup() 
{
  Serial.begin(9600);
  if (!rf22.init())
    Serial.println("RF22 init failed");
  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
  
  rf22.setFrequency(434.00, 0.01);
  rf22.setModemConfig(RF22::GFSK_Rb2Fd5); // duża czułość
 // rf22.setFrequency(436.90, 0.01); mały szum
//  436.903320312
  rf22.setTxPower(RF22_TXPOW_20DBM);
}

void loop()
{
   // rf22.waitAvailable();  // czy potrzebne ????
    if (rf22.recvfromAck((uint8_t*)&dane, &len, &from, &to))
    {
      Serial.print("czujka nr ");
      Serial.print(from, DEC);
      Serial.print(": ");
      Serial.print(dane.lp);
      Serial.print(" ");
      Serial.println(dane.liczba);  
   }
   
}

