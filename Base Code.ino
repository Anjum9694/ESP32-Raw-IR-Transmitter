#include <Wire.h>
#include <RTClib.h>
#include <pgmspace.h>

RTC_DS3231 rtc;

// Constants for IR Transmitter Setup
const int IR_LED = 4;        // GPIO pin connected to the IR LED
const int PWM_CHANNEL = 0;   // LEDC channel used for PWM
const int PWM_FREQ = 38000;  // Frequency of the PWM signal (38kHz for IR transmission)
const int PWM_RES = 8;       // Resolution of PWM (8-bit)
const int DUTY_CYCLE = 85;   // Duty cycle percentage (approx 33%)

struct TemperatureCommand {
  int temp;
  const uint16_t* irData;
  int irLength;
};

struct Schedule {
  uint8_t hour;
  uint8_t minute;
  int temp;
};

// Example raw IR codes (short sample values)
const uint16_t IR_SAMPLE_1[] PROGMEM = {4132, 135, 200, 450, 315};
const uint16_t IR_SAMPLE_2[] PROGMEM = {5120, 250, 180, 370, 420};

// Example schedule (24-hour format)
Schedule schedules[] = {
  {6, 00, 0},   // Example: Perform action at 6:00 AM
  {14, 30, 1},  // Example: Perform action at 2:30 PM
  {22, 15, 2},  // Example: Perform action at 10:15 PM
};

void setupPWM() {
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES);
  ledcAttachPin(IR_LED, PWM_CHANNEL);
  ledcWrite(PWM_CHANNEL, 0);
}

void sendIRCommand(const TemperatureCommand &cmd) {
  for (int i = 0; i < cmd.irLength; i++) {
    unsigned long duration = pgm_read_word_near(&cmd.irData[i]);
    ledcWrite(PWM_CHANNEL, (i % 2 == 0) ? DUTY_CYCLE : 0);
    delayMicroseconds(duration);
  }
  ledcWrite(PWM_CHANNEL, 0);
}

void checkSchedules() {
  static DateTime lastCheck;
  DateTime now = rtc.now();
  if (now.minute() == lastCheck.minute()) return;
  lastCheck = now;
}

void serialTimeSetup() {
  while (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  if (!rtc.begin()) Serial.println("RTC Not Found!");
  if (rtc.lostPower()) rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  setupPWM();
  Serial.println("System Ready");
}

void loop() {
  checkSchedules();
  serialTimeSetup();
  delay(1000);
}
