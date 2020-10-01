#include <FastLED.h>
#include "Wire.h"
#define DS1307_ADDRESS 0x68
byte zero = 0x00; 
#define LED_PIN     7
#define NUM_LEDS    58
#define NUM_SEG 14  //numero de leds nos 7 segmentos
#define nulo 80
#define bri  255//brilho
CRGB leds[NUM_LEDS];
char dis[]={0,14,30,44};
char a[10][14]={{nulo,nulo,2,3,4,5,6,7,8,9,10,11,12,13},{nulo,nulo,2,3,nulo,nulo,nulo,nulo,nulo,nulo,nulo,nulo,12,13},{0,1,2,3,4,5,nulo,nulo,8,9,10,11,nulo,nulo},{0,1,2,3,4,5,nulo,nulo,nulo,nulo,10,11,12,13},
{0,1,2,3,nulo,nulo,6,7,nulo,nulo,nulo,nulo,12,13},{0,1,nulo,nulo,4,5,6,7,nulo,nulo,10,11,12,13},{0,1,nulo,nulo,4,5,6,7,8,9,10,11,12,13},{nulo,nulo,2,3,4,5,6,7,nulo,nulo,nulo,nulo,12,13},{0,1,2,3,4,5,6,7,8,9,10,11,12,13},{0,1,2,3,4,5,6,7,nulo,nulo,10,11,12,13}};
char p1=29,p2=28;
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Wire.begin();
  SelecionaDataeHora();

}
void loop() {



  Mostrarelogio();
  ponto(0);
  delay(500);
  ponto(bri);
  delay(500);
  

}


// liga ou desliga o ponto
void ponto(char a){
leds[29]= CRGB(0,a,0);
leds[28]= CRGB(0,a,0);
FastLED.show();
}
// Mostra um determinado numero no display
// p representa o algarismo
// d o numero do display

void disp(char p,char d){
  desl_dis(d);
  for(int i=0;i<14;i++){
    if(a[p][i]!=nulo){
    leds[a[p][i]+dis[d]]= CRGB(0,0,bri);
    
    }  
  }
  FastLED.show();
}
// Desliga apenas um display

void desl_dis(char d){
  for(int i=dis[d];i<(NUM_SEG+dis[d]);i++){
   leds[i]= CRGB(0,0, 0);
   }
}
// Desliga todos os segmentos

void desl_tudo(void){
   for(int  i=0;i<NUM_LEDS;i++){
   leds[i]= CRGB(0,0, 0);
   }
   FastLED.show();
}
byte ConverteParaBCD(byte val){ //Converte o número de decimal para BCD
  return ( (val/10*16) + (val%10) );
}

byte ConverteparaDecimal(byte val)  { //Converte de BCD para decimal
  return ( (val/16*10) + (val%16) );
}

void SelecionaDataeHora()   //Seta a data e a hora do DS1307
{
  byte segundos = 50; //Valores de 0 a 59
  byte minutos = 25; //Valores de 0 a 59
  byte horas = 19; //Valores de 0 a 23
  byte diadasemana = 2; //Valores de 0 a 6 - 0=Domingo, 1 = Segunda, etc.
  byte diadomes = 22; //Valores de 1 a 31
  byte mes = 1; //Valores de 1 a 12
  byte ano = 19; //Valores de 0 a 99
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero); //Stop no CI para que o mesmo possa receber os dados

  //As linhas abaixo escrevem no CI os valores de 
  //data e hora que foram colocados nas variaveis acimac
  Wire.write(ConverteParaBCD(segundos));
  Wire.write(ConverteParaBCD(minutos));
  Wire.write(ConverteParaBCD(horas));
  Wire.write(ConverteParaBCD(diadasemana));
  Wire.write(ConverteParaBCD(diadomes));
  Wire.write(ConverteParaBCD(mes));
  Wire.write(ConverteParaBCD(ano));
  Wire.write(zero); //Start no CI
  Wire.endTransmission(); 
}


void Mostrarelogio()
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  int segundos = ConverteparaDecimal(Wire.read());
  int minutos = ConverteparaDecimal(Wire.read());
  int horas = ConverteparaDecimal(Wire.read() & 0b111111); 
  int diadasemana = ConverteparaDecimal(Wire.read()); 
  int diadomes = ConverteparaDecimal(Wire.read());
  int mes = ConverteparaDecimal(Wire.read());
  int ano = ConverteparaDecimal(Wire.read());
  
  disp(segundos%10,3);
  disp(segundos/10,2);
  disp(minutos%10,1);
  disp(minutos/10,0);
 }
