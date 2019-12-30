#include <efsm.h>

int buttonPin = 7;

STATES {start, step1, step2, finish};
EVENTS {next, back, restart};
INIT(start)

void show(){
  Serial.println();
  if(isState(start)){
    Serial.println("X - - -");
  } else if(isState(step1)){
    Serial.println("- X - -");
  } else if(isState(step2)){
    Serial.println("- - X -");
  } else if(isState(finish)){ 
    Serial.println("- - - X");  
  }  
}

START_TRANSITIONS
Serial.print("event: ");
TRANSITION(next,start,step1,Serial.println("next")) //next start -> step1
TRANSITION(next,step1,step2,Serial.println("next")) //next step1 -> step2
TRANSITION(next,step2,finish,Serial.println("next")) //next step2 -> finish
TRANSITION(back,step2,step1,Serial.println("back")) //back step2 -> step1
TRANSITION(restart,ANY_STATE,start,Serial.println("restart")) //restart any state -> start
TRANSITION(ANY_EVENT,ANY_STATE,ANY_STATE,Serial.println("FAIL!!!")) //in any other case
END_TRANSITIONS

START_EXECUTIONS
Serial.print("state: ");
EXECUTION(start,Serial.println("start")) //state is start
EXECUTION(step1,Serial.println("step1")) //state is step1
EXECUTION(step2,Serial.println("step2")) //state is step2
EXECUTION(finish,Serial.println("finish")) //state is finish
END_EXECUTIONS

START_TRIGGERS
Serial.println("Triggers");
COUNTER(start,5,next); //State start wait 5 iterations and launch event next
TIMER(step1,2000,next); //State step1 wait 2 sg and launch event next
CONDITIONAL(start, digitalRead(buttonPin) == HIGH, restart); //State finish wait until push button an launch event restart
END_TRIGGERS

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT); 
  resetTimer();
  resetCounter();  
}

int backFlag = 0;

void loop() {  
  show();

  efsmExecute();
  
  if(isState(finish)){
    backFlag = 0;    
    changeState(start);
  }

  if(isState(step2) && backFlag == 0){
    backFlag = 1;
    efsmEvent(back);  
  } else if(isState(step2) && backFlag == 1){
    efsmEvent(next);
  }
  
  efsmTriggers();
  
  delay(1000);
}
