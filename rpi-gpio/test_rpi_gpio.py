import time
import RPi.GPIO as GPIO

if __name__ == "__main__":
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)

    # LED 
    GPIO.setup(13, GPIO.OUT)
    # Button -> Low Activate
    GPIO.setup(27, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    
    print("GPIO Test Start!")
    while True:
        button_state = GPIO.input(27)
        if GPIO.input(27) == False:
            GPIO.output(13, 1)
            print("Button Pressed!")
            time.sleep(0.5)
        else:
            GPIO.output(13, 0)