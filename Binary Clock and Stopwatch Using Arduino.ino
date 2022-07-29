

int SecondLedPin[] = {14, 15, 16, 17, 18, 19};
int MinuteLedPin[] = {3, 4, 5, 6, 7, 8};

int HourLedPin[] = {9, 10, 11, 12};

const int start_but = 2;     
const int stop_but = 13;     

int start_state = 0;         
int but_1_state;
int but_2_state;

int clock_func = 0; 


int SecondCount = 0;   
int MinuteCount = 0;  
int HourCount = 9;  

int stopwatch_sec = 0; 

#define nBitsSec sizeof(SecondLedPin)/sizeof(SecondLedPin[0])
#define nBitsMin sizeof(MinuteLedPin)/sizeof(MinuteLedPin[0])
#define nBitsHr sizeof(HourLedPin)/sizeof(HourLedPin[0])

void setup(void)
{
  Serial.begin(9600);
  pinMode(start_but, INPUT);
  pinMode(stop_but, INPUT);
  for (byte i = 0; i < nBitsSec; i++) {
    pinMode(SecondLedPin[i], OUTPUT);
  }

  for (byte i = 0; i < nBitsMin; i++) {
    pinMode(MinuteLedPin[i], OUTPUT);
  }

  for (byte i = 0; i < nBitsHr; i++) {
    pinMode(HourLedPin[i], OUTPUT);
  }
}



void loop(void)
{
  but_1_state = digitalRead(start_but);
  but_2_state = digitalRead(stop_but);
  Serial.print("Start button state: ");
  Serial.print(but_1_state);
  Serial.print("\n");

  Serial.print("STOP button state: ");
  Serial.print(but_2_state);
  Serial.print("\n");

  if (start_state == 0 & but_1_state == 1){
   
    start_state = 1;
    clock_func = 1;
  } else if (start_state == 1 & but_2_state == 1){
    
    start_state = 0;
    clock_func = 0;
  } else if (start_state == 1 & but_1_state == 1){
    clock_func = 2;
  }

  Serial.print("Clock Func: ");
  Serial.print(clock_func);
  Serial.print("\n");

  if (clock_func == 1){
    display_clock();
  } else if(clock_func == 0){
    digital_reset_pins_hour();
    digital_reset_pins_mins();
    digital_reset_pins_secs();
  } else if(clock_func == 2){
    digital_reset_pins_hour();
    digital_reset_pins_mins();
    digital_reset_pins_secs();
    stopwatch();
  }


  delay(1000);   
  
}



void displaySecondBinary(byte nSec)
{
  for (byte i = 0; i < nBitsSec; i++) {
    digitalWrite(SecondLedPin[i], nSec & 1);
    nSec /= 2;
  }
}

void displayMinuteBinary(byte nMin)
{
  for (byte i = 0; i < nBitsMin; i++) {
    digitalWrite(MinuteLedPin[i], nMin & 1);
    nMin /= 2;
  }
}

void displayHourBinary(byte nHr)
{
  for (byte i = 0; i < nBitsHr; i++) {
    digitalWrite(HourLedPin[i], nHr & 1);
    nHr /= 2;
  }
}

void reset_clock(){

  int SecondCount = 0;   
  int MinuteCount = 0;  
  int HourCount = 9;  
}

void digital_reset_pins_hour(){
  for (byte i = 0; i < nBitsHr; i++) {
    digitalWrite(HourLedPin[i], LOW);
  }
}

void digital_reset_pins_mins(){
  for (byte i = 0; i < nBitsMin; i++) {
    digitalWrite(MinuteLedPin[i], LOW);
  }
}

void digital_reset_pins_secs(){
  for (byte i = 0; i < nBitsSec; i++) {
    digitalWrite(SecondLedPin[i], LOW);
  }
}

void display_clock(){
  SecondCount = (SecondCount + 1);
  if (SecondCount > 59)
    {
      SecondCount = 0;
      MinuteCount = (MinuteCount + 1);
      if (MinuteCount > 59)
      {
        MinuteCount = 0;
        HourCount = (HourCount + 1);
        if (HourCount > 23)
        {
           SecondCount = 0;   
           MinuteCount = 0;  
           HourCount = 9; ;
        }
      }
    }

  displaySecondBinary(SecondCount);
  displayMinuteBinary(MinuteCount);
  displayHourBinary(HourCount);
}

void stopwatch(){
  stopwatch_sec += 1;
  displaySecondBinary(stopwatch_sec);
  if (stopwatch_sec > 59){
    stopwatch_sec = 0;
    clock_func = 1;
  }
}
