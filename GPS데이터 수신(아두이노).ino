#include <SPI.h>
#include <RH_RF95.h>

RH_RF95 rf95;
String R_Date = "";

void setup() 
{  
  Serial.begin(9600);

  if (!rf95.init())
    Serial.println("init failed");
  else
    Serial.println("init success");
}

void loop()
{ 
  if (rf95.waitAvailableTimeout(2000))
  {
    char buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len))
    {
      R_Date = buf;

      int one = R_Date.indexOf(",");
      int two = R_Date.indexOf(",",one+1);
      int three = R_Date.indexOf(",",two+1);
      int four = R_Date.indexOf(",",three+1);
      int length = R_Date.length();

      String Name = R_Date.substring(0, one);
      String Latitude = R_Date.substring(one+1, two);
      String Longitude = R_Date.substring(two+1, three);
      String Fine_Dust = R_Date.substring(three+1,four);
      String UFine_Dust = R_Date.substring(four+1,length);

      Serial.print("\"1. Name\" : \"");
      Serial.print(Name);
      Serial.print("\"");
      Serial.print(", ");
      Serial.print("\"2. Latitude\" : ");
      Serial.print(Latitude);
      Serial.print(", ");
      Serial.print("\"3. Longitude\" : ");
      Serial.print(Longitude);
      Serial.print(", ");
      Serial.print("\"4. Fine_Dust\" : ");
      Serial.print(Fine_Dust);
      Serial.print(", ");
      Serial.print("\"5. UFine_Dust\" : ");
      Serial.print(UFine_Dust);
    }
    else
    {
      Serial.println("recv failed");
    }
  }

  delay(3000);
}