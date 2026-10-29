HAPTIC CHAT — talk to an AI that answers by buzzing
=====================================================

WHAT YOU NEED
  - The Uno with the haptic_buzzer sketch uploaded (already done) and the piezo on pin 9 + GND.
  - Google Chrome or Arc (Safari can't talk to USB devices).
  - An AI model: either a Claude API key (console.anthropic.com -> API keys),
    or LM Studio running locally (free, no key).

START
  1. Close the Arduino IDE's Serial Monitor (only one program can use the board at a time).
  2. Double-click "Open Haptic Chat (double-click me).command". Chrome opens the page.
  3. Click "Connect buzzer", pick the usbmodem port, click Connect. You feel one short buzz.
  4. Open Settings (bottom), paste your API key (or pick LM Studio).
  5. Ask something.

THE HAPTIC LANGUAGE (the AI knows it too)
  yes = short          no = long          not sure = double tap
  attention = 3 shorts   done = long + short   numbers 1-9 = that many shorts

MODES
  Text + buzz   answer on screen and in your hand
  Buzz only     text is blurred until you click it: answer by feel
  Morse         the AI picks one short word and buzzes it in Morse (dot = short, dash = long)

LM STUDIO (free, local)
  Load a model, open the Developer/server tab, turn on "Enable CORS", press Start.
  In Haptic Chat Settings choose LM Studio and paste the model id.

Your API key only goes to Anthropic. It's kept in the page unless you tick "remember".
