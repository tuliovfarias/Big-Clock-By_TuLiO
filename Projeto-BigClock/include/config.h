#include "NTPClient.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#define FASTLED_ESP8266_RAW_PIN_ORDER      // Define pinagem do ESP.
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER // Não remover e
#define FASTLED_ESP8266_D1_PIN_ORDER     // não trocar de lugar!
#include "FastLED.h"
#include <Ticker.h>

#define SSID_1      "TULIO_1"
#define PASS_1      "1234567890"
#define SSID_2      "TULIO_2"
#define PASS_2      "1234567890"
#define SSID_3      "2G TULIO"
#define PASS_3      "1234567890"
#define UTC         -3  //Fuso horário
#define LED_PIN     D6
#define NUM_LEDS    58
#define NUM_SEG     14  //numero de leds nos 7 segmentos
#define nulo        80
#define GIRAR_180   //definir para deixar o relógio de cabeça pra baixo
#define COR_LED     1   //cor default: AZUL (mudar apenas multiplicador com o index de RGB_colors)
#define BRILHO_LED  200 //brilho dos leds (0-255)

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", UTC*3600, 60000); //UTC -3:00 Brazil
ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80); //Server on port 80
CRGB leds[NUM_LEDS];
CRGBPalette16 RGB_colors(CRGB::Red,CRGB::Blue,CRGB::Green,CRGB::White,CRGB::Red,CRGB::Blue,CRGB::Green,CRGB::White,CRGB::Red,CRGB::Blue,CRGB::Green,CRGB::White,CRGB::Red,CRGB::Blue,CRGB::Green,CRGB::White);

/////////////////////////////////////////////////////////
//Protótipos
/////////////////////////////////////////////////////////
void htmlRelogio();
void htmlCronometro();
void htmlIniciaCronometro();
void htmlZeraCronometro();
void htmlTimer();
void htmlTimerPlay();
void relogio(void);
void cronometro(void);
void timer(void);
void cronometro(void);
void MostraHoras();
void MostraCronometro(void);
void MostraTimer(void);
void MostrarAlgarismo(char alg,char disp);
void MostrarPonto(bool on);
void MostraData();
void ZeraDisplays(void);
void forceUpdate(void);
void desl_display(char disp);
void desl_displays(void);

///////////////////////////////////////////////////////////////////////////////////
//Variáveis Globais
///////////////////////////////////////////////////////////////////////////////////
//Variáveis gerais
char func=0; //função - 0:relógio, 1:cronômetro, 2:timer

//Variáveis relógio
int segundos,minutos,horas,diadasemana,diadomes,mes,ano;
uint32_t currentMillis = 0;
uint32_t previousMillis = 0;

//Variáveis cronômetro
int minutos_cron=0;
int segundos_cron=0;
unsigned int segundos_aux;
unsigned int minutos_aux=0;
unsigned int play_cronometro=0; //-1:nada, 0:zerar, 1:play, 2:pause
bool flag_cron=0; //flag para não incrementar minutos em 00:00
unsigned long int aux_cron,unix_aux;

//Variáveis timer
int timer_min=1; // tempo do timer em minutos
int timer_seg=0;
int minutos_timer=0;
int segundos_timer=0;
unsigned int play_timer=0; //-1:nada, 0:zerar, 1:play, 2:pause

//Variáveis leds
char index_color=16*COR_LED; //define a cor dos leds
char brilho = BRILHO_LED; //define o brilho dos leds
unsigned int x=0;
bool ponto=true; //usado para ligar ou deligar pontos
#ifndef GIRAR_180
  char dis[]={0,14,30,44};
  char a[10][14]={{nulo,nulo,2,3,4,5,6,7,8,9,10,11,12,13},{nulo,nulo,2,3,nulo,nulo,nulo,nulo,nulo,nulo,nulo,nulo,12,13},{0,1,2,3,4,5,nulo,nulo,8,9,10,11,nulo,nulo},{0,1,2,3,4,5,nulo,nulo,nulo,nulo,10,11,12,13},
{0,1,2,3,nulo,nulo,6,7,nulo,nulo,nulo,nulo,12,13},{0,1,nulo,nulo,4,5,6,7,nulo,nulo,10,11,12,13},{0,1,nulo,nulo,4,5,6,7,8,9,10,11,12,13},{nulo,nulo,2,3,4,5,6,7,nulo,nulo,nulo,nulo,12,13},{0,1,2,3,4,5,6,7,8,9,10,11,12,13},{0,1,2,3,4,5,6,7,nulo,nulo,10,11,12,13}};
#else
  char dis[]={44,30,14,0};
  char a[10][14]={{nulo,nulo,2,3,4,5,6,7,8,9,10,11,12,13},{nulo,nulo,nulo,nulo,nulo,nulo,6,7,8,9,nulo,nulo,nulo,nulo},{0,1,2,3,4,5,nulo,nulo,8,9,10,11,nulo,nulo},{0,1,nulo,nulo,4,5,6,7,8,9,10,11,nulo,nulo},
{0,1,nulo,nulo,nulo,nulo,6,7,8,9,nulo,nulo,12,13},{0,1,nulo,nulo,4,5,6,7,nulo,nulo,10,11,12,13},{0,1,2,3,4,5,6,7,nulo,nulo,10,11,12,13},{nulo,nulo,nulo,nulo,nulo,nulo,6,7,8,9,10,11,12,13},{0,1,2,3,4,5,6,7,8,9,10,11,12,13},{0,1,nulo,nulo,4,5,6,7,8,9,10,11,12,13}};
#endif
