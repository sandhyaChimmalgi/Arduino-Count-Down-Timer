#define Units  9
#define Tens 10

#define UpCounter_Button 11
#define DownCounter_Button 12
#define Set_Button 13

#define BuzzerPin A5
int Counter = 0;
unsigned long Timer = 0;
bool CountDownStart = false;

int Zero[7] = {1,1,1,0,1,1,1};
int One[7] = {0,0,1,0,0,0,1};
int Two[7] = {1,1,0,1,0,1,1};
int Three[7] = {0,1,1,1,0,1,1};
int Four[7] = {0,0,1,1,1,0,1};
int Five[7] = {0,1,1,1,1,1,0};
int Six[7] = {1,1,1,1,1,1,0};
int Seven[7] = {0,0,1,0,0,1,1};
int Eight[7] = {1,1,1,1,1,1,1};
int Nine[7] = {0,1,1,1,1,1,1};

void Units_DisplayNumber(int Number[7]){
  for (int i = 0; i < 7; i++){
    if(Number[i] == 1){
      digitalWrite(i+2,HIGH);
    }
    else{
      digitalWrite(i+2,LOW);
    }
  }
  digitalWrite(Units,LOW);
  digitalWrite(Tens,HIGH);
  delay(1);
}

void Tens_DisplayNumber(int Number[7]){
  for (int i = 0; i < 7; i++){
    if(Number[i] == 1){
      digitalWrite(i+2,HIGH);
    }
    else{
      digitalWrite(i+2,LOW);
    }
  }
  digitalWrite(Units,HIGH);
  digitalWrite(Tens,LOW);
  delay(1);
}

void setup(){
  for(int i = 2; i < 9; i++){
    pinMode(i,OUTPUT);
  }
  pinMode(Units, OUTPUT);
  pinMode(Tens, OUTPUT);
  pinMode(UpCounter_Button,INPUT_PULLUP);
  pinMode(DownCounter_Button,INPUT_PULLUP);
  pinMode(Set_Button,INPUT_PULLUP);

  pinMode(BuzzerPin,OUTPUT);
}

void DisplayNumber(int Number){
  int Units_Value = Number % 10;
  int Tens_Value = Number / 10;
    if(Units_Value == 0)   Units_DisplayNumber(Zero);
    else if(Units_Value == 1)  Units_DisplayNumber(One);
    else if(Units_Value == 2)  Units_DisplayNumber(Two);
    else if(Units_Value == 3)  Units_DisplayNumber(Three);
    else if(Units_Value == 4)  Units_DisplayNumber(Four);
    else if(Units_Value == 5)  Units_DisplayNumber(Five);
    else if(Units_Value == 6)  Units_DisplayNumber(Six);
    else if(Units_Value == 7)  Units_DisplayNumber(Seven);
    else if(Units_Value == 8)  Units_DisplayNumber(Eight);
    else if(Units_Value == 9)  Units_DisplayNumber(Nine);

    if(Tens_Value == 0) Tens_DisplayNumber(Zero);
    else if(Tens_Value == 1)  Tens_DisplayNumber(One);
    else if(Tens_Value == 2)  Tens_DisplayNumber(Two);
    else if(Tens_Value == 3)  Tens_DisplayNumber(Three);
    else if(Tens_Value == 4)  Tens_DisplayNumber(Four);
    else if(Tens_Value == 5)  Tens_DisplayNumber(Five);
    else if(Tens_Value == 6)  Tens_DisplayNumber(Six);
    else if(Tens_Value == 7)  Tens_DisplayNumber(Seven);
    else if(Tens_Value == 8)  Tens_DisplayNumber(Eight);
    else if(Tens_Value == 9)  Tens_DisplayNumber(Nine);
}

void loop() {
  if(!digitalRead(UpCounter_Button)){
    Counter++;
    digitalWrite(BuzzerPin,LOW);
    CountDownStart = false;
    delay(200);
  }
  if(!digitalRead(DownCounter_Button)){
    Counter--;
    digitalWrite(BuzzerPin,LOW);
    CountDownStart = false;
    delay(200);
  }
  if(Counter > 99)  Counter = 99;
  else if(Counter < 0)  Counter = 0;

  if(!digitalRead(Set_Button)){
    if(CountDownStart)  CountDownStart = false;
    else  CountDownStart = true;
    delay(200);
  }

  if(CountDownStart){
    if(millis() > Timer+1000){
      Counter--;
      Timer = millis();
    }
  }

  if(Counter == 0 && CountDownStart == true)  digitalWrite(BuzzerPin,HIGH);
  else  digitalWrite(BuzzerPin,LOW);
  
  DisplayNumber(Counter);
}
