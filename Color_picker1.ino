// กำหนดขา PWM
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
  // ตั้งค่าขาเป็น OUTPUT
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // แสดงสีแดง
  setColor(255, 0, 0);
  delay(1000);

  // แสดงสีเขียว
  setColor(0, 255, 0);
  delay(1000);

  // แสดงสีน้ำเงิน
  setColor(0, 0, 255);
  delay(1000);

  // แสดงสีขาว
  setColor(255, 255, 255);
  delay(1000);
  
  // ปิดไฟ
  setColor(0, 0, 0);
  delay(1000);
}

// ฟังก์ชันตั้งค่าสี
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
