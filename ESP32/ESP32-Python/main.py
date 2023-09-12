# File:    main.py
# Author:  Corban Pendrak
# Date:    12Sep2023
# Purpose: Test ESP32 Python connection and toggle onboard LED

# Import necessary libraries
from machine import Pin, Timer
import time

# Initialize onboard led
led = Pin(2, Pin.OUT)

# Initialize timer 
timer = Timer(0)
toggled = 0

# Define blink function to control flashing LED
def blink(timer):
    global toggled
    toggled = not toggled
    led.value(toggled)

# Start the timer
timer.init(mode=Timer.PERIODIC, period=1000, callback=blink)

# Allow the timer to run for 30 seconds
time.sleep(30)

# Deactivate timer
timer.deinit()