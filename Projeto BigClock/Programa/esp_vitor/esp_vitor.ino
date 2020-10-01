#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    58
#define NUM_SEG 14  //numero de leds nos 7 segmentos
#define nulo 80

CRGB leds[NUM_LEDS];
 
const char *ssid     = "THE_SENA";
const char *password = "553134446198";
 
WiFiUDP ntpUDP;
 
int16_t utc = -3; //UTC -3:00 Brazil
uint32_t currentMillis = 0;
uint32_t previousMillis = 0;
 
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", utc*3600, 60000);
char dis[]={0,14,30,44};
char a[10][14]={{nulo,nulo,2,3,4,5,6,7,8,9,10,11,12,13},{nulo,nulo,2,3,nulo,nulo,nulo,nulo,nulo,nulo,nulo,nulo,12,13},{0,1,2,3,4,5,nulo,nulo,8,9,10,11,nulo,nulo},{0,1,2,3,4,5,nulo,nulo,nulo,nulo,10,11,12,13},
{0,1,2,3,nulo,nulo,6,7,nulo,nulo,nulo,nulo,12,13},{0,1,nulo,nulo,4,5,6,7,nulo,nulo,10,11,12,13},{0,1,nulo,nulo,4,5,6,7,8,9,10,11,12,13},{nulo,nulo,2,3,4,5,6,7,nulo,nulo,nulo,nulo,12,13},{0,1,2,3,4,5,6,7,8,9,10,11,12,13},{0,1,2,3,4,5,6,7,nulo,nulo,10,11,12,13}};

//Variáveis data e hora
int segundos,minutos,horas,diadasemana,diadomes,mes,ano;
char brilho=20;
void setup(){
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 Serial.print("Conectando");
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
     FastLED.clear();   
    Serial.print ( "." );
  }
 Serial.println("conectado");
  timeClient.begin();
  timeClient.update();

//Ligando tudo
     
  for(int i=0;i<=NUM_LEDS;i++){
      leds[i]= CRGB(0,brilho,0);
      FastLED.show();     
    }
  

}
 

 
void loop() {
  //Chama a verificacao de tempo
  checkOST();
  Mostrarelogio();
  MostrarPonto(0);
  delay(500);
  MostrarPonto(1);
  delay(500);
}

////////////////////////////////////////////////////////////////////////////
//Funções
///////////////////////////////////////////////////////////////////////////
// Mostra um determinado numero no display (algarismo, posição do display)
void MostrarAlgarismo(char alg,char disp){
  for(int i=0;i<14;i++){
    if(a[alg][i]!=nulo){
      leds[dis[disp]+i]= CRGB(brilho,0,0);
    }
    else{
      leds[dis[disp]+i]= CRGB(0,0,0);
    }
  }
  FastLED.show();
}

void MostrarPonto(bool on){
  if (on==1){
    leds[28] = CRGB(0,brilho,0);
    leds[29] = CRGB(0,brilho,0);
  }
  else{
    leds[28] = CRGB(0,0,0);
    leds[29] = CRGB(0,0,0);
  }
  FastLED.show();
}

// Desliga apenas 1 display
void desl_display(char disp){
  for(int i=dis[disp];i<(NUM_SEG+dis[disp]);i++){
   leds[i]= CRGB(0,0,0);
   }
}

void Mostrarelogio()
{
  MostrarAlgarismo(minutos%10,3); //mostra unidade de minutos
  MostrarAlgarismo(minutos/10,2); //mostra dezena de minutos
  MostrarAlgarismo(horas%10,1);  //mostra unidade de horas
  MostrarAlgarismo(horas/10,0);  //mostra dezenas de horas
}

void forceUpdate(void) {
  timeClient.forceUpdate();
}
 
void checkOST(void) {
  currentMillis = millis();//Tempo atual em ms
  //Lógica de verificação do tempo
  if (currentMillis - previousMillis > 1000) {
    previousMillis = currentMillis;    // Salva o tempo atual
    printf("Time Epoch: %d: ", timeClient.getEpochTime());
    Serial.println(timeClient.getFormattedTime());
    horas = timeClient.getHours();
    minutos = timeClient.getMinutes();
    segundos = timeClient.getSeconds();
    
  }
}
