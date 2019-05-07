// Arduino Code for the Piezo Buzzer and Light Synchronization
// Set up of digital pins and song lengthasmeasured per musical note
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;
const int buzzerPin = 12;
const int songLength= 99;

// Below are defined notes and their respectivefrequencies(Hz)that the piezo buzzer can output
// Frequency values are from: http://www.seventhstring.com/resources/notefrequencies.html

char names[] = {'D', 'E', 'F', 'G', 'A', 'B', 'C', 'd', 'e', 'f', 'g', 'a', 'b', 'c'};
int frequencies[] = {587, 659, 699, 784, 880, 988, 1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093};

// The following notes and their lengthshave been extracted from a music sheet with
// the help of background knowledge in interpretingmusic
// Jingle Bells music sheet from: http://pianoandsynth.com/jingle-bells-piano/

char notes[] = "eeeeeeegCdefffffeeeeeddedgeeeeeeegCdefffffeeeeggfdCGedCGGGGedCAAfedBggfdeGedCGGGGedCAAfedgggggagfdC";

// Eighth notes are defined as 1's, quarter notes as 2's, half notes as 4's and so on

int beats[] = {2,2,4, 2,2,4, 2,2,3,1, 8, 2,2,3,1, 2,2,2,1,1, 2,2,2,2, 4,4, 2,2,4, 2,2,4, 2,2,3,1, 8, 2,2,3,1, 2,2,2,1,1, 2,2,2,2, 8, 2,2,2,2, 6,1,1, 2,2,2,2, 8, 2,2,2,2, 8, 2,2,2,2, 8, 2,2,2,2, 6,1,1, 2,2,2,2, 8, 2,2,2,2, 2,2,2,1,1, 2,2,2,2, 8};

// Used to define the “speed” of the song

int tempo = 100;

void setup(){
  pinMode(RED_PIN, OUTPUT); // Configured Arduino pins are used to drive the
  pinMode(GREEN_PIN, OUTPUT); // RGB LED and buzzer as outputs
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

// Defined loop that steps through each notespecified
void loop(){
  int i, duration; // Variable i & duration defined
  for (i = 0; i < songLength; i++) // Step through each note of the songs’ length
  {
    duration = beats[i] * tempo; // Duration defines the length of the note or rest in ms
    if (notes[i] == ' ') // Ifstatement used to distinguish between rests and notes
    {
      delay(duration); // Pause for the duration of the rest
    }
    else // Otherwise, play the note specified
    {
      tone(buzzerPin, frequency(notes[i]), duration);// Function to play a note on the piezo buzzer
      if (frequency(notes[i]) <= 1047) // For frequencies lower than 1047 Hz
      {
        digitalWrite(RED_PIN, HIGH); // Turn on Red LED and hold for duration of note
        delay(duration);
      }
      else if (frequency(notes[i]) <= 1319) // For frequencies lower than 1319 Hz
      {
        digitalWrite(GREEN_PIN, HIGH); // Turn on Green LED and hold for duration of note
        delay(duration);
      }
      else // For any frequency higher than 1319 Hz
      {
        digitalWrite(BLUE_PIN, HIGH); // Turn on Blue LED and hold for duration of note
        delay(duration);
      }
    }
    digitalWrite(RED_PIN, LOW); // After the notes duration turn off the LED
    digitalWrite(GREEN_PIN, LOW); // This applies to the LED that was on
    digitalWrite(BLUE_PIN, LOW);
    delay(tempo/2);                // Brief pause between notes; avoid overlapping
    }
    while(true)                      // Function serves to stop the song from looping forever
    {
      noTone(buzzerPin);            // Stops the song after running through once
      digitalWrite(RED_PIN, LOW);// Turns off the LEDs
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(BLUE_PIN, LOW);
    }
  }
// Thefunction below takes a note character, and returns the
// corresponding frequency in Hz for the tone() function
int frequency(char note) {
  int i; // Variable i definedconst
  int numNotes = 14; // Number of notes stored which is 14 (2 octaves)
  for (i = 0; i < numNotes; i++) //  For loop is used to search through the letters
  {
    if (names[i] == note) // If this is a specifiednote
    {
      return(frequencies[i]); // Return the frequency
    }
  }return(0); // Otherwise don't return anything
}

