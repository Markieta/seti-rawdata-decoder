/* Assignment 3
   Program: assign1.c
   Purpose: Decode raw data for hidden message
   Section: OOP244D
   Name: Christopher Markieta
   Student Number: 028580124
   Instructor: Danny Abesdris
   Due Date: Friday, April 5, 2013
   Date Submitted: Wednesday, April 3, 2013

   Student Oath:

   "This assignment represents my own work in accordance
   with Seneca Academic Policy"

   Signature: Christopher Markieta */

#include <stdio.h>
#include <string.h>

#define LAST_LINE 123
#define LINE_LENGTH 61

long analyze(const char*, char*, int, int, int);

/* Decode raw data for hidden message */
long analyze(const char rawData[], char signal[], int frequency, int a, int b)
{
    int asciiFrequency = frequency + '0', vary = 0;

    long i, j = LINE_LENGTH, k = 2 * LINE_LENGTH, signalPosition = 0,
         rawDataLength = strlen(rawData), maxPosition;

    maxPosition = rawDataLength - LAST_LINE; // Max position for valid signal

    for(i = 0; i < maxPosition; i++)
    {
        // Determine if digit greater or equal to frequency and repeats 3 rows
        if(asciiFrequency <= rawData[i] && rawData[i] <= '9' &&
           rawData[i] == rawData[i + j] && rawData[i] == rawData[i + k])
        {
            // Iterate after valid signal found until end of raw data
            for(k += i + 1; k < rawDataLength - 1; k++)
            {
                // Terminate if sequences: "NAK", "NUL" or "ETX" are found
                if((rawData[k - 1] == 'N' && ((rawData[k] == 'A' &&
                   rawData[k + 1] == 'K') || (rawData[k] == 'U' &&
                   rawData[k + 1] == 'L'))) || (rawData[k - 1] == 'E' &&
                   rawData[k] == 'T' && rawData[k + 1] == 'X'))
                {
                    strcpy(signal, "NON-SEQUITOR");
                    return -1;
                }

                if(rawData[k] == ' ')
                {
                    signal[signalPosition] = ' ';
                    signalPosition++;
                    while(rawData[k] == ' ') // Ignore excessive spaces
                        k++;
                }

                // Determine if increase or decrease sequence found
                if(rawData[k] == '>' && rawData[k + 1] == '>')
                {
                    k++;
                    vary = 1;
                }
                else if(rawData[k] == '<' && rawData[k + 1] == '<')
                {
                    k++;
                    vary = -1;
                }

                // Determine if raw data is within range
                else if(a <= rawData[k] && rawData[k] <= b)
                {
                    if(vary != 0) // Increase or decrease character value
                    {
                        signal[signalPosition] = rawData[k] + vary * frequency;
                        signalPosition++;
                        vary = 0;
                    }
                    else
                    {
                        signal[signalPosition] = rawData[k];
                        signalPosition++;
                    }
                }
            }

            signal[signalPosition] = '\0';
            return signalPosition; // String length of valid signal
        }
    }

    strcpy(signal, "NON-SEQUITOR"); // No valid signal found
    return -1;
}
