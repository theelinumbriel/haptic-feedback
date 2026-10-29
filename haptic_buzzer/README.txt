HAPTIC BUZZER
=============

WIRING
  Flora pad #9  <-> piezo RED
  Flora pad GND <-> piezo BLACK
  Keep clip jaws from touching. Plug Flora in with a micro-USB data cable.

ARDUINO SETUP (once)
  IDE -> Settings -> Additional boards manager URLs:
    https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
  Tools -> Boards Manager -> install "Adafruit AVR".
  Tools -> Board -> Adafruit AVR Boards -> Adafruit Flora.

UPLOAD
  Open haptic_buzzer.ino, pick the usbmodem port, click Upload.
  One tiny buzz on boot = alive. If upload fails, press the Flora reset button
  the moment the IDE says "Uploading...".

BUZZ
  python3 buzz.py test        (connectivity)
  python3 buzz.py short|long|double
  python3 buzz.py s l s       (pattern)
  Close the Arduino Serial Monitor first.

TUNING
  Change PIEZO_HZ in haptic_buzzer.ino (try 120-400) and re-upload.

VIBRATION MOTOR INSTEAD
  Set USE_PIEZO = false. LilyPad Vibe Board: #9 -> "+", GND -> "-".
