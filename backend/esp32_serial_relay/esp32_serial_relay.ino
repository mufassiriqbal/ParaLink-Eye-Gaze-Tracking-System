/*
  9600 baud  
  Python backend  GPIO relays.

  Hardware Map:
  - GPIO 23 -> Light Relay
  - GPIO 22 -> Fan Relay
  - GPIO 21 -> TV Relay
  - GPIO 19 -> AC Relay
  - GPIO 18 -> Router Relay (Optional)

  Command Map:
  - 'A' = Light ON    | 'a' = Light OFF
  - 'B' = Fan ON      | 'b' = Fan OFF
  - 'C' = TV ON       | 'c' = TV OFF
  - 'D' = AC ON       | 'd' = AC OFF
  - 'E' = Router ON   | 'e' = Router OFF
  - 'Z' = All ON      | 'z' = All OFF
*/

// Define Relay Pins
const int RELAY_LIGHT = 23;
const int RELAY_FAN = 22;
const int RELAY_TV = 21;
const int RELAY_AC = 19;
const int RELAY_ROUTER = 18;

void setup() {
  Serial.begin(9600);
  
  pinMode(RELAY_LIGHT, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_TV, OUTPUT);
  pinMode(RELAY_AC, OUTPUT);
  pinMode(RELAY_ROUTER, OUTPUT);

  digitalWrite(RELAY_LIGHT, HIGH);
  digitalWrite(RELAY_FAN, HIGH);
  digitalWrite(RELAY_TV, HIGH);
  digitalWrite(RELAY_AC, HIGH);
  digitalWrite(RELAY_ROUTER, HIGH);

  Serial.println("ESP32 ParaLink Serial Controller Ready");
}

void loop() {
  if (Serial.available() > 0) {
    char incomingCommand = Serial.read();

    switch (incomingCommand) {
      // --- LIGHT ---
      case 'A': digitalWrite(RELAY_LIGHT, LOW); Serial.println("LIGHT_ON"); break;
      case 'a': digitalWrite(RELAY_LIGHT, HIGH); Serial.println("LIGHT_OFF"); break;

      // --- FAN ---
      case 'B': digitalWrite(RELAY_FAN, LOW); Serial.println("FAN_ON"); break;
      case 'b': digitalWrite(RELAY_FAN, HIGH); Serial.println("FAN_OFF"); break;

      // --- TV ---
      case 'C': digitalWrite(RELAY_TV, LOW); Serial.println("TV_ON"); break;
      case 'c': digitalWrite(RELAY_TV, HIGH); Serial.println("TV_OFF"); break;

      // --- AC ---
      case 'D': digitalWrite(RELAY_AC, LOW); Serial.println("AC_ON"); break;
      case 'd': digitalWrite(RELAY_AC, HIGH); Serial.println("AC_OFF"); break;

      // --- ROUTER ---
      case 'E': digitalWrite(RELAY_ROUTER, LOW); Serial.println("ROUTER_ON"); break;
      case 'e': digitalWrite(RELAY_ROUTER, HIGH); Serial.println("ROUTER_OFF"); break;

      // --- ALL DEVICES ---
      case 'Z':
        digitalWrite(RELAY_LIGHT, LOW);
        digitalWrite(RELAY_FAN, LOW);
        digitalWrite(RELAY_TV, LOW);
        digitalWrite(RELAY_AC, LOW);
        digitalWrite(RELAY_ROUTER, LOW);
        Serial.println("ALL_ON");
        break;
        
      case 'z':
        digitalWrite(RELAY_LIGHT, HIGH);
        digitalWrite(RELAY_FAN, HIGH);
        digitalWrite(RELAY_TV, HIGH);
        digitalWrite(RELAY_AC, HIGH);
        digitalWrite(RELAY_ROUTER, HIGH);
        Serial.println("ALL_OFF");
        break;
    }
  }
}
