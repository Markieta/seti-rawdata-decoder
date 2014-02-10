/* Assignment 3
   Program: seti.cpp
   Purpose: Dynamically allocate memory to store signal message
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

#include "seti.h"
#include "assign1.c"
#include <iostream>
#include <new>
#include <cstring>

#define MAX_LENGTH 60
#define CONVERT_CASE 32

using namespace std;

void Seti::memory(long size)
{
    try
    {
        message = new char[size + 1];
    }
    catch(bad_alloc)
    {
        message = NULL;
    }
}

/* Validate correct values entered */
void Seti::validate(int* freq, int* a, int* b)
{
    mFreq = (0 <= *freq && *freq <= 9)   ? *freq : 0;
    mA    = (0 <= *a    && *a    <= 255) ? *a    : 0;
    mB    = (0 <= *b    && *b    <= 255) ? *b    : 0;
}

/* Parameterized Constructor */
Seti::Seti(const char rawData[], int freq, int a, int b)
{
    validate(&freq, &a, &b);
   
    size = MAX_LENGTH;

    memory(size);
                                     // Decoded signal message
    messageLength = analyze(rawData, message, freq, a, b);
}

Seti::Seti(const char rawData[], int freq, int a, int b, int length)
{
    validate(&freq, &a, &b);

    size = length;

    memory(size);

    messageLength = analyze(rawData, message, freq, a, b);
}

/* Default Constructor */
Seti::Seti()
{
    mFreq = 0;
    mA    = 32;
    mB    = 126;
    size  = MAX_LENGTH;

    memory(size);

    strcpy(message, "NON-SEQUITOR");
    messageLength = -1; // Signal NON-SEQUITOR
}

Seti::Seti(const Seti &from)
{
    mFreq         = from.mFreq;
    mA            = from.mA;
    mB            = from.mB;
    messageLength = from.messageLength;
    size          = from.size;

    memory(size);

    strcpy(message, from.message);
}

Seti::~Seti()
{
    if(message)
        delete [] message;
}

/* return object frequency */
int Seti::getFrequency() const
{
    return mFreq;
}

/* Update parameters with object range */
void Seti::getRanges(int* pa, int* pb) const
{
    *pa = mA;
    *pb = mB;
}

/* Set object range */
void Seti::setRanges(int newA, int newB)
{
    if(0 <= newA && newA <= 255)
        mA = newA;

    if(0 <= newB && newB <= 255)
        mB = newB;
}

/* Copy object message to parameter */
void Seti::getMessage(char* pSignal) const
{
    strcpy(pSignal, message);
}

long Seti::getLength() const
{
    return messageLength;
}

/* Replace character in message at pos with letter */
bool Seti::replaceChar(int pos, char letter)
{   
    // Determine if message is not NON-SEQUITOR and pos is within range
    if(messageLength != -1 && 0 <= pos && pos <= messageLength - 1)
    {
        message[pos] = letter;
        return true;
    }

    return false;
}

/* Copy characters at prime positions */
bool Seti::copyPrimes(char* ppSignal) const
{
    int i, j, k = 0;
    
    bool isPrime;
    
    if(messageLength != -1)
    {
        for(i = 2; i < messageLength; i++)
        {
            isPrime = true;
            for(j = 2; j < i; j++)   // Determine if evenly divisible by all
                if(i % j == 0)
                    isPrime = false; // Value i is not a prime number
            if(isPrime)              // Determine if i is a prime number
            {
                ppSignal[k] = message[i];
                k++;                 // Position of ppSignal
            }
        }

        ppSignal[k] = '\0';
        return true;
    }

        return false;
}

/* Copy characters at positions in Fibonacci sequence */
bool Seti::copyFibonacci(char* fpSignal) const
{
           // F(n-2), F(n-1), F(n) of Fibonacci sequence
    int i, f1, f2, fSum;
    
    if(messageLength != -1)
    {
        i  = f1   = 0;
        f2 = fSum = 1;

        while(f1 < messageLength)
        {
            fpSignal[i] = message[f1];

            // Fibonacci sequence
            f1   = f2;
            f2   = fSum;
            fSum = f1 + f2;

            i++; // Position of fpSignal
        }

        fpSignal[i] = '\0';
        return true;
    }

    return false;
}

/* Convert case of characters in message */
int Seti::initCap()
{
    int i, converted = 0;

    if(messageLength != -1)
    {
        if('a' <= message[0] && message[0] <= 'z')
        {
            message[0] -= CONVERT_CASE;     // Convert to uppercase
            converted++;
        }

        for(i = 1; i < messageLength; i++)
        {
            if('A' <= message[i] && message[i] <= 'Z')
            {
                message[i] += CONVERT_CASE; // Convert to lowercase
                converted++;
            }
            else if(message[i] == ' ')
            {
                do
                    i++;
                while(message[i] == ' ');

                if('a' <= message[i] && message[i] <= 'z')
                {
                    message[i] -= CONVERT_CASE;
                    converted++;
                }
            }
        }
    }

    return converted;                       // Number of characters converted
}

void Seti::operator=(const Seti &from)
{
    mFreq         = from.mFreq;
    mA            = from.mA;
    mB            = from.mB;
    messageLength = from.messageLength;
    size          = from.size;

    if(message)
        delete [] message;

    memory(size);

    strcpy(message, from.message);
}

/* Increase object's frequency by 1 */
Seti Seti::operator++()
{
    if(mFreq < 9)
        mFreq++;

    return *this;
}

/* Determine if signal message is not valid */
bool Seti::operator!() const
{
    return messageLength == -1 ? true : false;
}

/* Join Seti objects */
Seti Seti::operator+(const Seti &from)
{
    return join(*this, from);
}

/* Join object messages and calculate new frequency and range */
Seti join(Seti one, Seti two)
{
    Seti joined;
    
    if(one.messageLength != -1 && two.messageLength != -1)
    {
        joined.mFreq = (one.mFreq < two.mFreq) ? one.mFreq : two.mFreq;
        joined.mA    = (one.mA    < two.mA)    ? one.mA    : two.mA;
        joined.mB    = (one.mB    > two.mB)    ? one.mB    : two.mB;

        joined.messageLength = joined.size = one.messageLength +
                                             two.messageLength;

        delete [] joined.message;

        joined.memory(joined.size);

        strcpy(joined.message, one.message);
        strcat(joined.message, two.message);
    }

    return joined;
}
