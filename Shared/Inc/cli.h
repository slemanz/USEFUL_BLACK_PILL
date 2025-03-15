/*
 * command.h
 *
 *  Created on: Jul 29, 2024
 *      Author: sleman
 */

#ifndef COMMAND_H_
#define COMMAND_H_

// Function pointer type
typedef void(*function_t)(void);

// Structure to hold command information
typedef struct
{
    char const *name;
    function_t execute;
    char const *help;
}commandStruct_t;

void ProcessCommands(void);

// Function prototypes for command handlers
void TurnOnLED(void);
void TurnOffLED(void);
void Help(void);

#endif /* COMMAND_H_ */
