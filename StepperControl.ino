// StepperControl.ino
// Autore: bocaletto-luca
// Controllo base per motore stepper con A4988

const int stepPin = 2;
const int dirPin  = 3;
const int enPin   = 4;

const int btnFwd  = 5;  // Pulsante avanti
const int btnRev  = 6;  // Pulsante indietro
const int btnRst  = 7;  // Pulsante reset

long currentStep = 0;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin,  OUTPUT);
  pinMode(enPin,   OUTPUT);
  digitalWrite(enPin, LOW); // Attiva motore

  pinMode(btnFwd, INPUT_PULLUP);
  pinMode(btnRev, INPUT_PULLUP);
  pinMode(btnRst, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Stepper pronto.");
}

void loop() {
  if (digitalRead(btnFwd) == LOW) {
    moveStepper(1);
    delay(200);
  }
  if (digitalRead(btnRev) == LOW) {
    moveStepper(-1);
    delay(200);
  }
  if (digitalRead(btnRst) == LOW) {
    currentStep = 0;
    Serial.println("Posizione azzerata.");
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
  Serial.print("Posizione: ");
  Serial.println(currentStep);
}
