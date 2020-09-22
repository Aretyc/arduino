
static const uint8_t inputs[]= {A0,A1,A2,A3,A4,A5};
int notes[] = {38,39,40,41,42,43};

int values[6];
int prevs[6]; 

void setup() {
  // Set MIDI baud rate:
  Serial.begin(115200);

  for(int i =0;i<6;i++)
  {
    values[i]=0;
    prevs[i]=0;
  }
  pinMode(11, OUTPUT);
  analogWrite(11, 30);
}

int maxValue(int array[] ){
  int max=0;
  int maxIndex=0;

  for(int i = 0 ;i<6; i++){
    if(array[i]>max ){
      max = array[i];
      maxIndex = i;
    }
  }
  return maxIndex;
}

void loop() {

    // read inputs values ;
    for(int i=0;i<6;i++)    
      values[i]= analogRead(inputs[i]);   

    // get index with max value 
    int maxInput = maxValue(values);

    
    if(values[maxInput]>prevs[maxInput] && values[maxInput] > 200){
      if(values[maxInput]>1024)values[maxInput] = 1024;
      noteOn(144,notes[maxInput],(values[maxInput]/8)-1);
      for(int i=0;i<6;i++) prevs[i]=values[i];
      analogWrite(11, 100);
      delay(30);
      return;
    }
    for(int i=0;i<6;i++) prevs[i]=values[i];
    analogWrite(11, 30);

}


// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
