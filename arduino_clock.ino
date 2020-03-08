#include <LedControl.h>
#include <Time.h>

#define MATRIX_DATA_IN_PIN 11
#define LOAD_CS_PIN 10
#define CLK_PIN 9
#define MATRIX_COUNT 2
#define HOUR_ADJUST_PIN 8
#define HOUR_ADJUST_OUT_PIN 7

LedControl led_control = LedControl(MATRIX_DATA_IN_PIN, CLK_PIN, LOAD_CS_PIN, MATRIX_COUNT);
int device_count;

byte digits[10][3] = {
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
  pinMode(HOUR_ADJUST_OUT_PIN, OUTPUT);
}

void reset_screen(int device_addr) {
  led_control.shutdown(device_addr, false);
  led_control.setIntensity(0, 8);
}

int second = 51;
int minute = 59;
int hour = 12;
void loop() {
  /*digitalWrite(HOUR_ADJUST_OUT_PIN, HIGH);
    bool hour_change = digitalRead(HOUR_ADJUST_PIN);
    if (!hour_change) {
    hour += 1;
    }*/
  //led_control.clearDisplay(0);
  //led_control.setRow(0, 0, 1);
  update_time_display(0, 1);
  delay(10);
}

void update_time_display(int _hour_display_addr, int _minute_display_addr) {
  second++;
  if (second == 60) {
    second = 0;
    minute++;
  }
  if (minute == 60) {
    minute = 0;
    hour++;
  }
  if (hour == 24) {
    hour = 0;
  }
  display_number(_hour_display_addr, hour);
  display_number(_minute_display_addr, minute);
}

//displays a number between 00 and 99
int offset = 4;
void display_number(int _device_addr, int _number_to_show) {
  int __lower_digit = _number_to_show % 10;
  int __upper_digit = _number_to_show / 10;
  for (int i = 0; i < 3; i++) {
    led_control.setRow(_device_addr, i + 1, digits[__upper_digit][i]);
  }
  for (int i = 0; i < 3; i++) {
    led_control.setRow(_device_addr, i + offset + 1, digits[__lower_digit][i]);
  }
}
