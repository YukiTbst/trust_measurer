#include "Arduino.h"
#include "uRTCLib.h"
#include <Wire.h>

#include <WiFi.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "EEPROM.h"

#include <Arduino.h>
#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/22, /* data=*/21); // ESP32 Thing, HW I2C with pin remapping

uRTCLib rtc(0x68);//时钟芯片

String wifi__ssid="HONOR 30 Pro+";//wifi账号和密码，用于同步时间
String wifi_password="16219443";
const char *ntpServer = "pool.ntp.org";
#define NTP1  "ntp1.aliyun.com"
#define NTP2  "ntp2.aliyun.com"
#define NTP3  "ntp3.aliyun.com"
const long gmtOffset_sec = 8 * 3600;
const int daylightOffset_sec = 0;
bool get_time=true;


void wifi_connect()
{
    WiFi.begin(&wifi__ssid[0], &wifi_password[0]);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    Serial.println("WiFi connected!");
}
void RTC_set(void * parameter)//连接网络同步当前时间
{

    while (1)
    {
        if(WiFi.status() != WL_CONNECTED)
        {
            wifi_connect();
        }
        if(get_time)
        {
            configTime(8 * 3600, 0, NTP1, NTP2,NTP3);
            struct tm timeinfo;
            if (getLocalTime(&timeinfo))
            {
                rtc.set(timeinfo.tm_sec,timeinfo.tm_min, timeinfo.tm_hour, timeinfo.tm_wday, timeinfo.tm_mday, timeinfo.tm_mon+1, (timeinfo.tm_year-100 ));
                get_time=false;
                Serial.print(asctime(&timeinfo));
                rtc.refresh();
            }
            else
            {
                Serial.print("failed");
            }
        }
        delay(1000);
        /* code */
    }
}

void creat_dir( String dir_path)
{
    if(SD.exists(dir_path))
    {
        return;
    }
    else
    {
        SD.mkdir(dir_path);
    }
    return;
}
String file_path;
void append_file( String file_path, String file_context)
{
    File file;
    if(SD.exists(file_path))
    {
        file=SD.open(file_path, FILE_APPEND);
    }
    else
    {
        file=SD.open(file_path, FILE_WRITE);
    }
    file.print(file_context);
    file.close();
    return;
}
void setup() {
    delay (2000);
	Serial.begin(115200);

    u8g2.begin();
  u8g2.enableUTF8Print();

    Wire.begin();
    Wire.setPins(SDA, SCL);
    Wire.setClock(100000);
    
    
    xTaskCreatePinnedToCore(
            RTC_set,          
            "RTC_set",        
            10000,            
            NULL,             
            3,               
            NULL,
            0);
   
}

void loop() {    
    rtc.refresh();
    u8g2.setFont(u8g2_font_unifont_t_chinese2); // use chinese2
  u8g2.firstPage();
  do
  {
    u8g2.setCursor(0, 20);
    u8g2.print("helloworld"); // Chinese "Hello World"
    u8g2.setCursor(0, 40);
    u8g2.print("你好世界"); // Chinese "Hello World"
  } while (u8g2.nextPage());
  delay(1000);

    
}