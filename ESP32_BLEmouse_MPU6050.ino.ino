#include "I2Cdev.h"
#include <Wire.h>
#include <MPU6050.h>
#include <BleMouse.h>

//宣告各項變數
BleMouse bleMouse;
MPU6050 imu;
int16_t ax, ay, az, gx, gy, gz;//MPU6050加速度和旋轉
int vx, vy;//滑鼠游標移動
int buttonL = 0; // IO0 button為左鍵

int buttonLstate = HIGH; 

//計算角距離
int angleToDistance(int a)

{
  if (a < -80)
  {
    return -40;
  }
  else if (a < -65) {
    return -20;
  }
  else if (a < -50) {
    return -10;
  }
  else if (a < -15) {
    return -5;
  }
  else if (a < -5) {
    return -1;
  }
  else if (a > 80) {
    return 40;
  }
  else if (a > 65) {
    return 20;
  }
  else if (a > 15) {
    return 10;
  }
  else if (a > 5) {
    return 1;
  }
}


void setup() {
  Serial.begin(115200);
  Wire.begin();
  pinMode(buttonL, INPUT_PULLUP);

  
  Serial.print("MPU6050 initializing");
  imu.initialize();
  while (!imu.testConnection()) { Serial.print("."); }
  Serial.println();  
  Serial.println("BLE Mouse starting !");
  bleMouse.begin();
}

void loop() {
  /* Update IMU sensor values */
  imu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);//取得Acceleration & Rotation
  
  //求出vx & vy，計算出滑鼠游標的移動
  int vx = map(ax, -16000, 16000, 90, -90);

  int vy = map(ay, -16000, 16000, 90, -90);

  
  Serial.print("gx = ");   Serial.print(gx);
  Serial.print(", gy = "); Serial.print(gy);
  Serial.print("\t");
  Serial.print("X = ");    Serial.print(vx);
  Serial.print(", Y = ");  Serial.println(vy);
  
  bleMouse.move(angleToDistance(vx), angleToDistance(vy));//決定滑鼠游標更精準的標移動方向
    
  buttonLstate = digitalRead(buttonL);
   
  
  if (buttonLstate == LOW) { // press button to Ground
    bleMouse.click(MOUSE_LEFT);
    delay(100);
  }
  delay(100);
}
