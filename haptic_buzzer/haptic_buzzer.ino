// haptic_buzzer.ino — piezo buzzes + a 7-segment display, driven from your computer.
//
// Piezo: pin 9 -> red wire, GND -> black wire.
// Display: each segment -> 220 ohm resistor -> its own pin (see PINS below).
//          Display middle pin (COM) -> GND.
//
// AT POWER-UP all segments flash once briefly ("I'm alive").
// SEGMENT TEST (command T, or: python3 buzz.py segtest): one tiny tick, then one
// segment lights for 1.5 s, for each of the 8 pins in the order of PINS.
//
// Commands over USB serial (9600 baud). The board replies "OK <c>" to each.
//   s short buzz   l long buzz   d double tap   p ping (no buzz)
//   0-9  show that digit
//   t    "thinking" spinner (runs until the next display command)
//   cN   confidence meter: N = 0..8 segments lit, e.g. c5
//   mXX  raw glyph: XX = two hex digits, bit0=a .. bit6=g, bit7=dot, e.g. m49
//   x    clear the display
//   T    run the segment test again
// The dot lights whenever the piezo buzzes, so buzzes are also visible.

const bool COMMON_ANODE = false;   // flip to true if nothing lights (and COM goes to 5V)
const bool USE_PIEZO = true;
const int PIEZO_HZ = 180;
const int MOTOR_PIN = 9;
const int SHORT_MS = 150;
const int LONG_MS = 600;

// Segment order:          a  b  c  d  e  f  g  dot
const int PINS[8]       = {2, 3, 4, 5, 6, 7, 8, 10};

const byte DIGITS[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
const byte SPIN[6] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20};   // a b c d e f around the edge
const byte METER[9] = {0x00, 0x08, 0x0C, 0x0E, 0x0F, 0x2F, 0x3F, 0x7F, 0xFF};  // fills up from the bottom

byte shown = 0;
bool spinning = false;
int spinStep = 0;
unsigned long spinAt = 0;

void writeSeg(int i, bool on) { digitalWrite(PINS[i], (on != COMMON_ANODE) ? HIGH : LOW); }

void show(byte mask) {
  shown = mask;
  for (int i = 0; i < 8; i++) writeSeg(i, mask & (1 << i));
}

void buzz(int ms) {
  digitalWrite(LED_BUILTIN, HIGH);
  writeSeg(7, true);                       // dot on while buzzing
  if (USE_PIEZO) { tone(MOTOR_PIN, PIEZO_HZ); delay(ms); noTone(MOTOR_PIN); }
  else { digitalWrite(MOTOR_PIN, HIGH); delay(ms); digitalWrite(MOTOR_PIN, LOW); }
  writeSeg(7, shown & 0x80);
  digitalWrite(LED_BUILTIN, LOW);
}

void selfTest() {
  spinning = false;
  for (int i = 0; i < 8; i++) {
    show(0);
    tone(MOTOR_PIN, PIEZO_HZ); delay(40); noTone(MOTOR_PIN);   // tick = "next one"
    delay(400);
    writeSeg(i, true);
    Serial.print("TEST pin "); Serial.println(PINS[i]);
    delay(1500);
  }
  show(0xFF); delay(1000); show(0);
}

int readNext() {                            // second character of a 2-3 char command
  unsigned long t = millis();
  while (!Serial.available()) if (millis() - t > 300) return -1;
  return Serial.read();
}

int hexVal(int c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return -1;
}

void setup() {
  for (int i = 0; i < 8; i++) pinMode(PINS[i], OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  show(0);
  Serial.begin(9600);
  show(0xFF); delay(300); show(0);
  Serial.println("READY");
}

void loop() {
  if (spinning && millis() - spinAt > 110) {
    spinAt = millis();
    spinStep = (spinStep + 1) % 6;
    show(SPIN[spinStep]);
  }
  if (!Serial.available()) return;
  char c = Serial.read();
  if (c == 's') buzz(SHORT_MS);
  else if (c == 'l') buzz(LONG_MS);
  else if (c == 'd') { buzz(SHORT_MS); delay(120); buzz(SHORT_MS); }
  else if (c == 'p') { }
  else if (c >= '0' && c <= '9') { spinning = false; show(DIGITS[c - '0']); }
  else if (c == 't') { spinning = true; spinAt = 0; }
  else if (c == 'x') { spinning = false; show(0); }
  else if (c == 'T') selfTest();
  else if (c == 'c') {
    int n = readNext() - '0';
    if (n < 0 || n > 8) return;
    spinning = false; show(METER[n]);
  }
  else if (c == 'm') {
    int h = hexVal(readNext()), l = hexVal(readNext());
    if (h < 0 || l < 0) return;
    spinning = false; show((h << 4) | l);
  }
  else return;                            // ignore anything else (newlines etc.)
  Serial.print("OK "); Serial.println(c);
}
