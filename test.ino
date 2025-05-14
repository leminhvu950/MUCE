#include <Ps3Controller.h>
#include <ESP32Servo.h>  // Thư viện đúng cho ESP32

Servo baseServo;
Servo elbowServo;
Servo shoulderServo;
Servo gripperServo;

int baseAngle = 90;
int elbowAngle = 90;
int shoulderAngle = 90;
int gripperAngle = 0;

void onConnect() {
  Serial.println("✅ Tay cầm PS3 đã kết nối!");
}

void onDisconnect() {
  Serial.println("⚠️ Tay cầm PS3 ngắt kết nối!");
}

void setup() {
  Serial.begin(115200);

  baseServo.setPeriodHertz(50);     // Tần số cho servo
  elbowServo.setPeriodHertz(50);
  shoulderServo.setPeriodHertz(50);
  gripperServo.setPeriodHertz(50);

  baseServo.attach(27);
  elbowServo.attach(26);
  shoulderServo.attach(25);
  gripperServo.attach(33);

  baseServo.write(baseAngle);
  elbowServo.write(elbowAngle);
  shoulderServo.write(shoulderAngle);
  gripperServo.write(gripperAngle);

  Ps3.attach(onConnect);
  Ps3.attachOnDisconnect(onDisconnect);
  Ps3.begin("ec:0e:c4:83:04:c7");  // Địa chỉ MAC của PS3 Controller

  Serial.println("🔄 Đang chờ kết nối tay cầm PS3...");
}

void loop() {
  if (!Ps3.isConnected()) return;

  if (Ps3.data.button.triangle) {
    shoulderAngle = constrain(shoulderAngle + 5, 0, 180);
    shoulderServo.write(shoulderAngle);
    delay(100);
  }
  if (Ps3.data.button.cross) {
    shoulderAngle = constrain(shoulderAngle - 5, 0, 180);
    shoulderServo.write(shoulderAngle);
    delay(100);
  }

  if (Ps3.data.button.square) {
    elbowAngle = constrain(elbowAngle + 5, 0, 180);
    elbowServo.write(elbowAngle);
    delay(100);
  }
  if (Ps3.data.button.circle) {
    elbowAngle = constrain(elbowAngle - 5, 0, 180);
    elbowServo.write(elbowAngle);
    delay(100);
  }

  if (Ps3.data.button.l1) {
    baseAngle = constrain(baseAngle - 5, 0, 180);
    baseServo.write(baseAngle);
    delay(100);
  }
  if (Ps3.data.button.r1) {
    baseAngle = constrain(baseAngle + 5, 0, 180);
    baseServo.write(baseAngle);
    delay(100);
  }

  if (Ps3.data.button.l2) {
    gripperAngle = 180;
    gripperServo.write(gripperAngle);
    delay(100);
  }
  if (Ps3.data.button.r2) {
    gripperAngle = 0;
    gripperServo.write(gripperAngle);
    delay(100);
  }
}
