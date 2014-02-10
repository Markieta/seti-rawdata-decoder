/* Assignment 3
   Program: setiwriter.cpp
   Purpose: Write signal message to file
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

#include "setiwriter.h"
#include <new>
#include <cstring>

using namespace std;

/* Opens file with specific name and mode */
SetiWriter::SetiWriter(const char name[], const char mode[])
{
    signal = fopen(name, mode);
}

SetiWriter::SetiWriter()
{
    signal = fopen("seti.dat", "w");
}

SetiWriter::~SetiWriter()
{
    fclose(signal);
}

/* Writes decoded message to file */
long SetiWriter::write(const Seti &r, bool wFlag, int type)
{
    char* message = NULL;

    long messageLength;

    if(!!r) // Seti object's signal is valid
    {
        try
        {                        // String length of signal
            message = new char[r.getLength() + 1];
        }
        catch(bad_alloc)
        {
            message = NULL;
        }
        
        if(wFlag)
        {
            if(type == 1)
                r.copyFibonacci(message);
            else if(type == 3)
                r.copyPrimes(message);
        }
        else
            r.getMessage(message);

        fputs(message, signal);

        messageLength = strlen(message);

        delete [] message;

        return messageLength + 1; // Number of bytes written to file
    }

    return 0;                     // Zero bytes written to file
}
