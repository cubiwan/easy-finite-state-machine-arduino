#include <efsm.h>

STATES {start, step1, step2, finish};
EVENTS {next, back};
INIT(start)

void show(){
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
TRANSITION(next,step1,step2,Serial.println("next")) //next start -> step1
TRANSITION(next,step2,finish,Serial.println("next")) //next start -> step1
TRANSITION(back,step2,step1,Serial.println("back")) //back step2 -> step1
TRANSITION(ANY_EVENT,ANY_STATE,ANY_STATE,Serial.println("FAIL!!!")) //in any other case
END_TRANSITIONS

START_EXECUTIONS
Serial.print("state: ");
EXECUTION(start,Serial.println("start");show()) //state is start
EXECUTION(step1,Serial.println("step1");show()) //state is step1
EXECUTION(step2,Serial.println("step2");show()) //state is step2
EXECUTION(finish,Serial.println("finish");show()) //state is finish
END_EXECUTIONS

START_COUNTERS
COUNTER(step1,10,next);
END_COUNTERS

void setup() {
  Serial.begin(9600); 
}

int transitionNumber = 0;
int executionNumber = 0;
int stepLoop = 0;

void loop() {  
  executionNumber = efsmExecute();

  if(isState(step2) && stepLoop < 5){
    transitionNumber = efsmEvent(back);  
  } else {
    transitionNumber = efsmEvent(next);
  }

  Serial.print("Transition: ");
  Serial.print(transitionNumber);
  Serial.print(transitionNumber);
  Serial.print(transitionNumber);

  if(isState(finish)){    
    changeState(start);
  }

  delay(2000);
}