// Simple Arduino test sketch: blinks the built-in LED and prints a counter.
// Send a number (ms) over serial to set the blink interval, e.g. "250".

const unsigned long MIN_INTERVAL = 10;    // ms, fastest allowed
const unsigned long MAX_INTERVAL = 60000; // ms, slowest allowed

unsigned long blinkInterval = 1000; // ms, adjustable via serial
unsigned long previousMillis = 0;
bool ledState = false;
unsigned long counter = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Arduino test program started");
  Serial.println("Send blink interval in ms (e.g. 250) to change speed.");
}

void handleSerialInput() {
  if (Serial.available() > 0) {
    long value = Serial.parseInt();

    // Discard the rest of the line (newline, extra chars).
    while (Serial.available() > 0) {
      Serial.read();
    }

    if (value >= (long)MIN_INTERVAL && value <= (long)MAX_INTERVAL) {
      blinkInterval = (unsigned long)value;
      Serial.print("Blink interval set to ");
      Serial.print(blinkInterval);
      Serial.println(" ms");
    } else if (value != 0) {
      Serial.print("Ignored value ");
      Serial.print(value);
      Serial.print(" (allowed ");
      Serial.print(MIN_INTERVAL);
      Serial.print("-");
      Serial.print(MAX_INTERVAL);
      Serial.println(" ms)");
    }
  }
}

void loop() {
  handleSerialInput();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState ? HIGH : LOW);

    Serial.print("Blink #");
    Serial.print(++counter);
    Serial.print(" - LED ");
    Serial.println(ledState ? "ON" : "OFF");
  }
}
