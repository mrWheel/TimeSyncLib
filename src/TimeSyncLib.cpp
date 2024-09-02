/*
***************************************************************************
**  Program     : TimeSyncLib.cpp
**  Author      : Michael Teeuw (MichMich) 
**  Modified by : Willem Aandewiel (mrWheel)
**  Date        : 29-04-2021
**
**  Copyright (c) 2024 Michael Teeuw
**
**  TERMS OF USE: MIT License. See bottom of file.
***************************************************************************
*/

#include "TimeSyncLib.h"

TimeSync::TimeSync() {}

/**
 * Sets up the time synchronization with the specified timezone.
 *
 * @param timeZone The timezone to set.
 *
 * @return void
 *
 * @throws None
 */
void TimeSync::setup(const char *timeZone)
{
  configTime(0, 0, "pool.ntp.org", "time.nist.gov",  "time.google.com");
  setenv("TZ", timeZone, 1);
  tzset();

  Serial.printf("Timezone set to: %s\r\n", timeZone);
} //  TimeSync::setup()

/**
 * Checks if the system time is synchronized.
 *
 * @return True if the system time is synchronized, false otherwise.
 *
 * @throws None
 */
bool TimeSync::isSynced()
{
  time_t now;
  time(&now);

  return (bool)(localtime(&now)->tm_year > 120);

} // TimeSync::isSynced()

/**
 * Synchronizes the system time with the NTP service.
 *
 * @param maxTry The maximum number of attempts to synchronize the time.
 *
 * @return True if the system time is synchronized with the NTP service,
 *         False otherwise.
 *
 * @throws None
 */
bool TimeSync::sync(uint16_t maxTry)
{
  time_t now;
  time(&now);
  uint8_t tries = 0;

  Serial.print("Get time from NTP service .");
  do
  {
    time(&now);
    delay(250);
    if ((tries%10)==0)
    {
      Serial.print('.');
    }
    tries++;
  } while ((localtime(&now)->tm_year <= 120) && (tries < maxTry));

  if (localtime(&now)->tm_year > 120)
    Serial.println(" Synchronized with NTP Service!");
  else  Serial.println(" NOT (YET) SYNCED!");

  return localtime(&now)->tm_year > 120;

}   // TimeSync::sync()

/**
 * Logs the current time.
 *
 * @return void
 *
 * @throws None
 */
void TimeSync::logTime() 
{
    time_t now;
    time(&now);
    struct tm timeinfo;

    // Initialize timeinfo with local time
    if (!localtime_r(&now, &timeinfo)) 
    {
        Serial.println("Failed to obtain time");
        return;
    }

    // Now timeinfo is properly initialized, safe to use
    Serial.printf("%s", asctime(&timeinfo));

} // TimeSync::logTime()

bool TimeSync::getTheLocalTime(struct tm *info, uint32_t ms)
{
  //-- getLocalTime() is not implemented in the ArduinoIDE
  //-- so this is a 'work around' function
  uint32_t start = millis();
  time_t now;
  while((millis()-start) <= ms)
  {
    time(&now);
    localtime_r(&now, info);
    if(info->tm_year > (2016 - 1900))
    {
      return true;
    }
    delay(100);
  }
  return false;

} // TimeSync::getTheLocalTime()

/**********************************************************************************
 * MIT License
 *
 * Copyright (c) 2024 Michael Teeuw (MichMich)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **********************************************************************************
*/