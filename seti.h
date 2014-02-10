/* Assignment 3
   Program: seti.h
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

class Seti
{
        char* message;
        int mFreq, mA, mB, size;
        long messageLength;
        void memory(long);
        void validate(int*, int*, int*);
    public:
        Seti(const char [], int, int, int);
        Seti(const char [], int, int, int, int);
        Seti();
        Seti(const Seti &);
        ~Seti();
        int getFrequency() const;
        void getRanges(int*, int*) const;
        void setRanges(int, int);
        void getMessage(char*) const;
        long getLength() const;
        bool replaceChar(int, char);
        bool copyPrimes(char*) const;
        bool copyFibonacci(char*) const;
        int initCap();
        void operator=(const Seti &);
        Seti operator++();
        bool operator!() const;
        Seti operator+(const Seti &);
        friend Seti join(Seti, Seti);
};
