#include <DS1302RTC.h>
#include <Time.h>
#include <TimeLib.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Font_Data.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// Hardware SPI connection
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// inisialisasi ds1302
// pin CE/RST, IO/DAT, CLK
DS1302RTC xRTC(5,6,7);

//tambahan utk menampilkan jam
char szTime[9]; //hh:mm
char szDetik[4];//ss
bool f = false;

void setup(void) {
  
  time_t t;
  tmElements_t tm;

  //bagian ini untuk mengatur jam
  //sesuaikan dulu sebelum di-upload ke Arduino
  tm.Year = CalendarYrToTm(2020);
  tm.Month = 6;
  tm.Day = 21;
  tm.Hour = 11;
  tm.Minute = 50;
  tm.Second = 0;
  t = makeTime(tm);

  setTime(t);
  setSyncProvider(xRTC.get);
  
  P.begin(2);

  //intensitas cahaya led: n: 0-15, z (zona)
  //P.setIntensity(n)
  //atau... P.setIntensity(z, n);
  P.setIntensity(0); 
  
  P.setZone(0, 0, 0);
  P.setZone(1, 1, 3);
  
  P.setFont(0, numeric7Seg);
  P.setFont(1, numeric7Se);
  
}

void loop(void) {
  //P.displayText(szTime, PA_CENTER, 200, 1000, PA_PRINT, PA_NO_EFFECT);
  //sprintf(szTime, "%02d%c%02d%c%02d", hour(), ':', minute(), ':', second());


  P.displayZoneText(1, szTime, PA_CENTER, 200, 1000, PA_PRINT, PA_NO_EFFECT);
  sprintf(szTime, "%02d%c%02d", hour(), ':', minute());

  P.displayZoneText(0, szDetik, PA_LEFT, 200, 1000, PA_PRINT, PA_NO_EFFECT);
  sprintf(szDetik, "%02d", second());
  
  delay(1000);
  
  if(P.displayAnimate()){
    P.displayReset();
  }
}
