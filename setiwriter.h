/* Assignment 3
   Program: setiwriter.h
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

#include <cstdio>
#include "seti.h"

class SetiWriter
{
        FILE* signal;
    public:
        SetiWriter(const char [], const char []);
        SetiWriter();
        ~SetiWriter();
        long write(const Seti &, bool, int);
};
