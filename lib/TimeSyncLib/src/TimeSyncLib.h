/*
***************************************************************************
**  Program     : TimeSyncLib.h
**  Author      : Michael Teeuw (MichMich) 
**  Modified by : Willem Aandewiel (mrWheel)
**  Date        : 29-04-2021
**
**  Copyright (c) 2024 Michael Teeuw
**
**  TERMS OF USE: MIT License. See bottom of file.
***************************************************************************
*/

#ifndef TIMESYNCLIB_H
#define TIMESYNCLIB_H


#include <Arduino.h>

class TimeSync 
{
    public:
        TimeSync();
        void setup(const char *timeZone = "CET-1CEST,M3.5.0,M10.5.0/3");
        bool sync(uint16_t maxTry);
        bool isSynced();
        void logTime();
        bool getTheLocalTime(struct tm *info, uint32_t ms);

};

#endif // TIMESYNCLIB_H

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