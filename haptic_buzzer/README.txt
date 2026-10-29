HAPTIC BUZZER — quick guide
===========================

WIRING (piezo disc, no sewing)
  Flora pad #9   ->  alligator clip  ->  piezo RED wire
  Flora pad GND  ->  alligator clip  ->  piezo BLACK wire
  (#9 and GND are next to each other on the Flora's edge.)
  Keep the two clips' metal jaws from touching each other.
  Plug the Flora into your laptop with a micro-USB DATA cable.

ONE-TIME ARDUINO SETUP FOR THE FLORA (5 minutes)
  1. Open Arduino IDE.  Arduino IDE menu -> Settings...
  2. In "Additional boards manager URLs" paste:
       https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
     Click OK.
  3. Tools -> Board -> Boards Manager. Search "Adafruit AVR". Click Install.
  4. Tools -> Board -> Adafruit AVR Boards -> Adafruit Flora.

UPLOAD
  1. File -> Open -> Desktop/haptic feedback from llm + chat windpw/haptic_buzzer/haptic_buzzer.ino
  2. Tools -> Port -> the one with "usbmodem" in its name.
  3. Click Upload (the right-arrow button). Wait for "Done uploading".
     The piezo gives one tiny buzz when the board starts: it's alive.
  If the upload fails: click Upload again, and the moment the bottom panel
  says "Uploading...", press the Flora's small reset button once.

BUZZ IT (in Terminal, from anywhere)
  python3 ~/Desktop/'haptic feedback from llm + chat windpw'/haptic_buzzer/buzz.py test      (checks it's connected)
  python3 ~/Desktop/'haptic feedback from llm + chat windpw'/haptic_buzzer/buzz.py short
  python3 ~/Desktop/'haptic feedback from llm + chat windpw'/haptic_buzzer/buzz.py long
  python3 ~/Desktop/'haptic feedback from llm + chat windpw'/haptic_buzzer/buzz.py double
  python3 ~/Desktop/'haptic feedback from llm + chat windpw'/haptic_buzzer/buzz.py s l s     (a pattern)
  Nothing to install: buzz.py brings its own copy of pyserial.
  Close the Arduino Serial Monitor first, or buzz.py can't connect.

FEEL IT MORE
  Hold the disc flat between finger and thumb, or press it against your wrist.
  In haptic_buzzer.ino, change PIEZO_HZ (try 120-400) and upload again.

SWITCHING TO A VIBRATION MOTOR LATER
  In haptic_buzzer.ino set  USE_PIEZO = false  and upload again.
  LilyPad Vibe Board: #9 -> "+", GND -> "-".
  A bare coin motor needs a transistor in between: ask Claude.
