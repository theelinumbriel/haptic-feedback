HAPTIC CHAT
===========

Talk to an AI that answers by buzzing.

NEEDS
  - Uno flashed with haptic_buzzer (piezo on pin 9 + GND)
  - Chrome or Arc (Safari can't talk to USB)
  - A Claude API key, or LM Studio running locally

START
  1. Close the Arduino Serial Monitor.
  2. Open haptic_chat.html in Chrome.
  3. Connect buzzer -> pick the usbmodem port. One short buzz = ok.
  4. Settings -> paste API key (or pick LM Studio).

LANGUAGE
  yes = short     no = long     not sure = double tap
  attention = 3 shorts    done = long + short
  numbers 1-9 = that many shorts

MODES
  Text + buzz   - answer on screen and in your hand
  Buzz only     - text is blurred until clicked
  Morse         - the AI picks one short word and buzzes it

LM STUDIO
  Load a model, Developer tab -> enable CORS, start the server. Settings -> LM Studio, paste model id.

The API key is kept in the page unless you tick "remember"; it only goes to Anthropic.
