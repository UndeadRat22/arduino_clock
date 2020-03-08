#include <LedControl.h>
#include <Time.h>

#define MATRIX_DATA_IN_PIN 11
#define LOAD_CS_PIN 10
#define CLK_PIN 9
#define MATRIX_COUNT 2
#define HOUR_ADJUST_PIN 2
#define MINUTE_ADJUST_PIN 3

LedControl led_control = LedControl(MATRIX_DATA_IN_PIN, CLK_PIN, LOAD_CS_PIN, MATRIX_COUNT);
int device_count;

//could be more in hex or less in octal systems
#define DIGIT_COUNT 10
#define DIGIT_WIDTH 3

byte digits[DIGIT_COUNT][DIGIT_WIDTH] = {
  {
    0b01111110,
    0b01000010,
    0b01111110,
  },
  {
    0b00000000,
    0b00000000,
    0b01111110,
  },
  {
    0b01111010,
    0b01001010,
    0b01001110,
  },
  {
    0b01001010,
    0b01001010,
    0b01111110,
  },
  {
    0b00001110,
    0b00001000,
    0b01111110,
  },
  {
    0b01001110,
    0b01001010,
    0b01111010,
  },
  {
    0b01111110,
    0b01001010,
    0b01111010,
  },
  {
    0b00000010,
    0b00000010,
    0b01111110,
  },
  {
    0b01111110,
    0b01001010,
    0b01111110,
  },
  {
    0b01001110,
    0b01001010,
    0b01111110,
  },
};

void setup() {
  device_count = led_control.getDeviceCount();
  for (int device_addr = 0; device_addr < device_count; device_addr++) {
    reset_screen(device_addr);
  }
  pinMode(HOUR_ADJUST_PIN, INPUT_PULLUP);
  pinMode(MINUTE_ADJUST_PIN, INPUT_PULLUP);
}

void reset_screen(int device_addr) {
  led_control.shutdown(device_addr, false);
  led_control.setIntensity(0, 8);
}

int second = 00;
int minute = 00;
int hour = 12;
void loop() {
  bool __had_updates = update_hour_and_minute();
  update_time_display(0, 1);
  if (__had_updates){
    delay(200);
  } else {
    inc_second();
    delay(1000);
  }
}

bool update_hour_and_minute(){
  bool __adj_hour = digitalRead(HOUR_ADJUST_PIN);
  bool __adj_minute = digitalRead(MINUTE_ADJUST_PIN);
  if (__adj_hour){
    inc_hour();
  }
  if (__adj_minute){
    inc_minute();
  }
  return __adj_hour || __adj_minute;
}

void inc_hour(){
  hour++;
  if (hour == 24){
    hour = 0;
  }
}

void inc_minute(){
  minute++;
  if (minute == 60){
    minute = 0;
    inc_hour();
  }
}

void inc_second(){
  second++;
  if (second == 60){
    second = 0;
    inc_minute();
  }
}

void update_time_display(int _hour_display_addr, int _minute_display_addr) {
  display_number(_hour_display_addr, hour);
  display_number(_minute_display_addr, minute);
}

//displays a number between 00 and XX (X is max single digit in a given system, i.e. 9 in decimal)
int offset = 4;
void display_number(int _device_addr, int _number_to_show) {
  int __lower_digit = _number_to_show % DIGIT_COUNT;
  int __upper_digit = _number_to_show / DIGIT_COUNT;
  for (int i = 0; i < DIGIT_WIDTH; i++) {
    led_control.setRow(_device_addr, i + 1, digits[__upper_digit][i]);
  }
  for (int i = 0; i < DIGIT_WIDTH; i++) {
    led_control.setRow(_device_addr, i + offset + 1, digits[__lower_digit][i]);
  }
}
