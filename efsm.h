/*
	efsm.h -  Easy Finite State Machine for Arduino
	Created by Cubiwan 2019
	Released into the public domain.
*/

#ifndef efsm_h
	#define efsm_h

	#define ANY_STATE efsmState
	#define ANY_EVENT efsmEvent

	#define START_TRANSITIONS \
	int efsmEvent(enum efsmEvents efsmEvent){ \
		efsmTimer = millis();\
		efsmCounter = 0;\

	#define TRANSITION(E,Ss,Sf,F) \
		if(efsmEvent == E && efsmState == Ss){ \
			efsmState = Sf; \
			F; \
			return 1; \
		}\

	#define END_TRANSITIONS \
		return 0; \
	} \

	#define START_EXECUTIONS \
	int efsmExecute(){ \

	#define EXECUTION(S,F) \
		if(efsmState == S){ \
			F; \
			return 1; \
		}\

	#define END_EXECUTIONS \
		return 0; \
	} \

	#define START_TRIGGERS \
	int efsmTriggers(){ \
		efsmCounter++; \
		unsigned long diff = millis()-efsmTimer;\

	#define COUNTER(S,N,E) \
		if(efsmState == S && efsmCounter >= N){ \
			return efsmEvent(E); \
		}\

	#define TIMER(S,M,E) \
		if(efsmState == S && diff >= M){ \
			return efsmEvent(E); \
		}\

	#define CONDITIONAL(S,C,E) \
		if(efsmState == S && C){ \
			return efsmEvent(E); \
		}\


	#define END_TRIGGERS \
		return 0; \
	} \

	#define EVENTS enum efsmEvents

	#define STATES enum efsmStates

	#define INIT(S) \
	enum efsmStates efsmState = S;\
	unsigned long efsmCounter = 0; \
	unsigned long efsmTimer = 0; \

	#define isState(S) efsmState == S
	#define changeState(S) efsmState = S
	#define resetTimer() efsmTimer = millis()
	#define resetCounter() efsmCounter = 0
#endif
