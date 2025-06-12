# StepperControl 🚀 — Arduino Stepper Motor Controller with Buttons
#### Author: Bocaletto Luca

A minimal yet professional Arduino sketch to control a NEMA 17 stepper motor using an A4988 driver and three buttons: Forward, Reverse, and Reset.

📁 File: `StepperControl.ino`  
👤 Author: [bocaletto-luca](https://github.com/bocaletto-luca)  
🔧 License: MIT

---

## 🛠️ Hardware Requirements

| Component         | Quantity |
|------------------|----------|
| NEMA 17 Stepper Motor | 1        |
| A4988 Stepper Driver  | 1        |
| Arduino Uno/Nano/etc. | 1        |
| Push Buttons (FWD, REV, RST) | 3  |
| 10kΩ Resistors (optional) | 3    |
| External Power Supply (e.g., 12V for motor) | 1 |

---

## ⚙️ Wiring

| Arduino Pin | Connected To         |
|-------------|----------------------|
| D2          | A4988 STEP           |
| D3          | A4988 DIR            |
| D4          | A4988 ENABLE         |
| D5          | Button (Forward)     |
| D6          | Button (Reverse)     |
| D7          | Button (Reset)       |
| GND         | Button Grounds + A4988 GND |
| 5V / VCC    | A4988 VDD (logic)    |

> Use INPUT_PULLUP in code or external pull-down resistors.  
> Don’t forget current limit adjustment on A4988 for your stepper.

---

## 🧠 Behavior

- Press **Forward** button → one step forward  
- Press **Reverse** button → one step back  
- Press **Reset** button → reset internal position to zero  
- Step delay is ~1.6ms (800μs HIGH + 800μs LOW)  
- Prints current step via `Serial` at 9600 baud

---

## 📄 Code

```cpp
// StepperControl.ino
// Author: bocaletto-luca
// Control NEMA17 stepper with A4988 and 3 push buttons

const int stepPin = 2;
const int dirPin  = 3;
const int enPin   = 4;

const int btnFwd  = 5;  // Forward button
const int btnRev  = 6;  // Reverse button
const int btnRst  = 7;  // Reset position

long currentStep = 0;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin,  OUTPUT);
  pinMode(enPin,   OUTPUT);
  digitalWrite(enPin, LOW); // Enable motor

  pinMode(btnFwd, INPUT_PULLUP);
  pinMode(btnRev, INPUT_PULLUP);
  pinMode(btnRst, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Stepper ready.");
}

void loop() {
  if (digitalRead(btnFwd) == LOW) {
    moveStepper(1);
    delay(200); // Debounce
  }
  if (digitalRead(btnRev) == LOW) {
    moveStepper(-1);
    delay(200);
  }
  if (digitalRead(btnRst) == LOW) {
    currentStep = 0;
    Serial.println("Position reset.");
    delay(500);
  }
}

void moveStepper(int direction) {
  digitalWrite(dirPin, direction > 0 ? HIGH : LOW);
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(800);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(800);
  currentStep += direction;
  Serial.print("Position: ");
  Serial.println(currentStep);
}
```

---

## 📦 Uploading

1. Open `StepperControl.ino` in Arduino IDE  
2. Select the correct board and port  
3. Click “Upload”  
4. Open Serial Monitor at 9600 baud  

---

## 📷 Optional Enhancements

- Add microstepping config via MS1–MS3  
- Replace buttons with joystick or encoder  
- Add OLED display for position  
- Integrate EEPROM for persistence

---

## 📄 License

GPL License © 2025 [bocaletto-luca](https://github.com/bocaletto-luca)

