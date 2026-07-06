#ifndef _RACER_GNSS_H
#define _RACER_GNSS_H

#include <bnp.h>
#include <SparkFun_u-blox_GNSS_v3.h>

SFE_UBLOX_GNSS_SERIAL myGNSS;
//HardwareSerial mySerial(PA2, PA3);

void gnss_init()
{
    bnp::uart[2]->begin(115200);
    //mySerial.begin(115200);
    if (bnp::uart[2] == nullptr) { bnp::panic("uart2 is null"); }
    while (myGNSS.begin(*bnp::uart[2]) == false) //Connect to the u-blox module using mySerial (defined above)
  {
    Serial.println(F("u-blox GNSS not detected. Retrying..."));
    delay (1000);
  }

    myGNSS.setNavigationFrequency(2);
    myGNSS.setUART1Output(COM_TYPE_UBX);
}

static void gnss_task(void *arg)
{
    while (true)
    {
        if (myGNSS.getPVT())
        {
            int32_t latitude = myGNSS.getLatitude();
            int32_t longitude = myGNSS.getLongitude();
            Serial.print("https://www.google.com/maps/?q=");
            Serial.print(latitude / 10000000.0, 6);
            Serial.print(",");
            Serial.print(longitude / 10000000.0, 6);

            int32_t altitude = myGNSS.getAltitudeMSL(); // Altitude above Mean Sea Level
            Serial.print(F(" Alt: "));
            Serial.print(altitude);
            Serial.print(F(" (mm)"));

            Serial.println();
        }
        bnp::sleep(500);
    }
}
#endif