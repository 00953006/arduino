/*****************************************************************
 *  ตัวอย่าง 
 *     - WiFi task  : สำหรับจัดการ WiFi 
 *     - DHT task   : สำหรับ อ่านค่า DHT Sensor อย่างเดียวไปเรื่อยๆ
 *     - Blink task : สำหรับไฟกระพริบ แล้วแต่จะสั่งใช้งาน
 *     - AsyncWebServer task : สำหรับ สร้าง WebServer แบบ Asynchonous ทำงาน 
 *                             ทุกครั้งที่มีการต่อไวไฟสำเร็จ
 *  
 *  หมายเหตุ
 *  ติดตั้ง Library ทั้ง 4 ให้เรียบร้อย
 *  library สำหรับ WebServer แบบ Asynchronous
 *     https://github.com/me-no-dev/AsyncTCP
 *     https://github.com/me-no-dev/ESPAsyncWebServer
 * 
 *  library สำหรับ DHT sensor
 *     https://github.com/adafruit/Adafruit_Sensor
 *     https://github.com/adafruit/DHT-sensor-library
 *
 ******************************************************************/

#include <TridentTD_EasyFreeRTOS32.h>


TridentOS   DHT_task, Blink_task, WiFi_task, AsyncWebServer_task,MPU6050_ACC2CSV;
void DHT_func(void*), Blink_func(void*), WiFi_func(void*), AsyncWebServer_func(void*),MPU6050_ACC2CSV_func(void*);


int     xBlink_Delay;    
float   xDHT_temp;       
float   xDHT_humid;      


void setup(){  // setup() หลักตัวพิมพ์เล็ก
  Serial.begin(115200); Serial.println();
    
  DHT_task.start( DHT_func );
  WiFi_task.start( WiFi_func );  
  MPU6050_ACC2CSV.start( MPU6050_ACC2CSV_func );
}

void loop(){}  // loop() หลักตัวพิมพ์เล็ก ไม่จำเป็นต้องใช้แต่ให้มีไว้เสมอ
