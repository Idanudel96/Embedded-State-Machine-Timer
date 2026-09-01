
//###########################################################################
//
// FILE:   StateMachine.h
//
// TITLE:  StateMachine
//
//###########################################################################

//#ifndef StateMachine_H
//#define StateMachine_H
//
//extern void StateMachine(int n);
//extern int MyCounter;
//
//
//
//#endif  // end of LCD2x16DISPLAY_H definition



#ifndef STATEMACHINE_H
#define STATEMACHINE_H

// Define the State enum
typedef enum { LOCKED, OPEN } State;

// Declare MyStateMachine as an external variable
extern State MyStateMachine;

// Function prototype for the state machine
void StateMachine(int flag);

#endif // STATEMACHINE_H
