# Easy Finite State Machine for Arduino

Macros to create a finite state machine in Arduino

Create a finite state machine in 8 steps

1. Include efsm.h
1. Define states
1. Define inital state   
1. Define events
1. Define transitions
1. Define executions
1. Define triggers
1. Enjoy you fsm!

## Include efsm.h

efsm define C Macros to make easy create a fsm.

```c
#include <efsm.h>
```

## Define States

```c
STATES {start, step1, step2, finish};
```

Is translate to:

```c
enum States{start, step1, step2, finish};
```

## Define Initial State

INIT(start);

Is translate to:

enum States state = start;

## Define events

EVENTS {next, back, end};

Is translate to:

enum Events{next, back, end};

## Define transitions

Transitions define changes in state when an event is launched:

**TRANSITION(event,initalState,finalState,function())**


*if(event && state == initalState){  
    state = finalState;  
    call function();  
}*

```c
START_TRANSITIONS

TRANSITION(next,start,step1,printf("next\n"))//execute a function
TRANSITION(next,step1,step2,)//no execute function

END_TRANSITIONS
```

## Define executions

Executions define funtions to call in each state

EXECUTION(executionState,function())

if(state == executionState){
    function();
}

```c
START_EXECUTIONS  

EXECUTION(start,printf("start\n"))  
EXECUTION(step1,printf("step1\n"))  

END_EXECUTIONS  
```

It is not mandatory to use EXECUTIONS  

## TRIGGERS

Define conditions to launch events

There are 3 types:

**COUNTER(initalState,number,event);**

In pseudocode:

*if(state == intialState && timesTriggerIsCalledSinLastEvent >= number){  
    launchEvent(event);  
}*

**TIMER(initalState,milliseconds,event);**

In pseudocode:

*if(state == intialState && millisecondsSinceLastEvent >= milliseconds){  
    launchEvent(event);  
}*

**CONDITIONAL(initalState,condition,event);**

In pseudocode:

*if(state == intialState && condition){  
    launchEvent(event);  
}*

```c
START_TRIGGERS

COUNTER(start,5,next); //State start wait 5 iterations and launch event next  
TIMER(step1,2000,next); //State step1 wait 2 sg and launch event next  
CONDITIONAL(start, digitalRead(buttonPin) == HIGH, restart); //State finish wait until push button an launch event restart  

END_TRIGGERS
```

## Enjoy you fsm!

You need add to loop function:

```c
efsmExecute();
efsmTriggers();
```

## Others macros

**ANY_EVENT**  
**ANY_STATE**

Usefull to define events, transactions and triggers

*isState(state);*

Is true is machine state is *state*

*changeState(state);*

Put machine state to *state*

*resetTimer();*

Reset time since last event

*resetCounter();*

Reset counter since last event
