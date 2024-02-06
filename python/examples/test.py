import lib16univin
import time

card = lib16univin.SM16univin()
print("================Turn on one by one  =====================")
for i in range(16):
    card.set_led(i+1, 1)
    print("Led " + str(i + 1) + " set to " + str(rel.get(i + 1)))
    print("All leds value: " + str( card.get_all_leds()))
    time.sleep(0.15)
print("================Turn off one by one  =====================")
for i in range(16):
    rel.set(i+1, 0)
    print("Led " + str(i + 1) + " set to " + str(card.get_led(i + 1)))
    print("All leds value: " + str(card.get_all_leds()))
    time.sleep(0.15)
print("================Turn all on  =====================")
time.sleep(1)
card.set_all_leds(65535)
print("All relays: " + str(rel.get_all()))
time.sleep(1)
print("================Turn all off  =====================")
card.set_all_leds(0)
print("All relays: " + str(rel.get_all()))
