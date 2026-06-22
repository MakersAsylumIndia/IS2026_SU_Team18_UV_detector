unsigned long startTime;
unsigned long currentTime;
int UV_index = 0;
int UV_index_prev = 0;
int time_remaining=0;
float percent_time_left = 100;
bool time_out=false;
bool vitD_maxxed=false;

void setup() {
  startTime = millis();
  time_remaining = 200/(3*UV_index);
}

void loop() {
  UV_index_prev = UV_index;
  //read UV index and store in UV_index
  currentTime = millis();
  int timeElapsed = currentTime-startTime;
  if(UV_index!= UV_index_prev){
    percent_time_left = timeElapsed/time_remaining;
    time_remaining = percent_time_left * 200/(3*UV_index);
    percent_time_left=0;
  }
  if(timeElapsed>= 0.75*time_remaining){
    vitD_maxxed=true;
  }
  else if(timeElapsed>=time_remaining){
    time_out=true;
  }
}