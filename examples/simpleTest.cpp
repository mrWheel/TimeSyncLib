/*
***************************************************************************
**  Program  : simpleTest.cpp
**  Author   : Willem Aandewiel (mrWheel)
**  Date     : 29-04-2021
**
**  Copyright (c) 2024 Willem Aandewiel
**
**  TERMS OF USE: MIT License. See bottom of file.
***************************************************************************
*/

#include <Arduino.h>
#include "myCredentials.h"
#include <TimeSyncLib.h>

#ifdef ESP8266
  #include <ESP8266WiFi.h>
#else 
  #include <WiFi.h>
#endif

TimeSync timeSync;

struct tm timeinfo;
time_t    now;
int status = WL_IDLE_STATUS;


//---------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  while(!Serial) {delay(100);}
  Serial.println("Starting simpleTest example");

  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  // attempt to connect to WiFi network
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to WPA SSID: "); 
    Serial.println(ssid); // print SSID
    // Connect to WPA/WPA2 network
    //WiFi.begin(ssid, password); 
    delay(500);
  }
  Serial.println("Connected to the WiFi network");
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  timeSync.setup();
  timeSync.sync(100);
  time(&now);
  //if (localtime(&now)->tm_year > 120)
  if (timeSync.isSynced())
  {
    //timeSynced = true;
    Serial.println("Time synchronized with NTP Service");
  }
  else
  {
    //timeSynced = false;
    Serial.println("Could not synchronize time with NTP Service");
  }

  time(&now);
  Serial.println("-------------------------------------------------------------------------------");
  if (!timeSync.getTheLocalTime(&timeinfo, 1000))
  {
    Serial.println("Time       : Failed to obtain time!");
  }
  else
  {
    Serial.printf( "Time       : %04d-%02d-%02d %02d:%02d:%02d\r\n", localtime(&now)->tm_year+1900
                   , localtime(&now)->tm_mon+1
                   , localtime(&now)->tm_mday
                   , localtime(&now)->tm_hour
                   , localtime(&now)->tm_min
                   , localtime(&now)->tm_sec);
  }

  timeSync.logTime();  

} // setup()

//---------------------------------------------------------------------
void loop()
{
    if (timeSync.isSynced())
    {
      Serial.println("Time synchronized with NTP Service");
      timeSync.logTime();
    }
    else
    {
      Serial.println("Could not synchronize time with NTP Service");
    }
    time(&now);
    if (!timeSync.getTheLocalTime(&timeinfo, 10000))
    {
      Serial.println("Time       : Failed to obtain time!");
    }
    else
    {
      Serial.printf( "Time       : %02d-%02d-%04d %02d:%02d:%02d\r\n"
                                , localtime(&now)->tm_mday
                                , localtime(&now)->tm_mon+1
                                , localtime(&now)->tm_year+1900
                                , localtime(&now)->tm_hour
                                , localtime(&now)->tm_min
                                , localtime(&now)->tm_sec);
    }

    timeSync.logTime();
    delay(1000);

} // loop()



/***************************************************************************
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit
* persons to whom the Software is furnished to do so, subject to the
* following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
* OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
* THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
****************************************************************************
*/