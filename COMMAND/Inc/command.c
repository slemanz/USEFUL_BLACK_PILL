#include "stm32f401.h"

commandStruct_t commands[] = {
    {"LED_ON", TurnOnLED, "Turn on the LED"},
    {"LED_OFF", TurnOffLED, "Turn off the LED"},
    {"HELP", Help, "List all commands"},
};

#define COMMAND_COUNT (sizeof(commands) / sizeof(commands[0]))

void ProcessCommands(void)
{
    char inputBuffer[50];
    int index = 0;

    // Simple command reading loop
    while (1)
    {
        char c = uart2_receive_char();
        if (c == '\n' || c == '\r')
        { // End of command
            inputBuffer[index] = '\0'; // Null-terminate string

            // Match command
            for (int i = 0; i < COMMAND_COUNT; i++)
            {
                if (strcmp(inputBuffer, commands[i].name) == 0)
                {
                    commands[i].execute(); // Execute the command
                    break;
                }
            }
            index = 0; // Reset index for next command
        } else if (index < sizeof(inputBuffer) - 1)
        {
            inputBuffer[index++] = c; // Store character
        }
    }
}

void TurnOnLED(void)
{
    // Your code to turn on LED here
	uart2_send_string("LED turned ON\n");
}

void TurnOffLED(void) {
    // Your code to turn off LED here
	uart2_send_string("LED turned OFF\n");
}

void Help(void) {
	uart2_send_string("===================================\n");
    for (int i = 0; i < COMMAND_COUNT; i++) {
    	uart2_send_string(commands[i].name);
    	uart2_send_string(": ");
    	uart2_send_string(commands[i].help);
    	uart2_send_string("\n");
    }
    uart2_send_string("===================================\n");
}
