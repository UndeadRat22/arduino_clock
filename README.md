# arduino_clock
Software to adjust and display hours and minutes on two MAX7219 8x8 LED matrices.

Secondinary goal of this project was to use as little external libraries as possible, but still ended up using the LedControl library.

![Figure 1-1](images/up_close.jpg?raw=true)

## Possible digits to display
The clock displays digits from the 'digits' array, where the digit 0 is the 0th element of the array. To use different digits, just edit the array elements.

To use a different number system (i.e. hexadecimal) you'd want to set `DIGIT_COUNT` to the number system you want and define the remaining digits in the digit array.

Also you can change the 'width' of the digits by changing `DIGIT_WIDTH` to whatever number you want, and then adding, or removing lines in every element of the digit array.

## Brightness
Brigtness should be configurable in the `reset_screen(int _device_addr)` function, but at least in my case, using the function provided by `LedControl.h` for intensity just doesn't work. 
```C++ 
    int LedControl::setIntensity(int* addr, int brightness);
```
Perhaps my wiring is wrong, but I wired everything according to the diagrams.
## Accuracy

The code for this clock does all the neccesary calculations and displaying for some x time (1-2ms), and then waits for 1 second. Over time this leads to inaccurate time display, as every 1000 seconds there's one or two extra seconds waited. This could be mitigated in a few ways:

1. Using an RTC module to get the time from.
2. Keeping track of how long the calculations take, and adjusting for it. 
    - (Seen some TimeLib that does that, but don't want to use any more libraries than absolutely neccessary).
