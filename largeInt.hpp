#ifndef LARGEINT_H
#define LARGEINT_H
#include <iostream>
#include <string>
#include "dLList.cpp"

class largeInt{
    private:
        dLList<int> num_content;
        bool sign;
        friend std::ostream& operator<<(std::ostream& os, largeInt& myInt);
        friend std::istream& operator>>(std::istream& is, largeInt& myInt);

    public:
    //constructor
        largeInt();
    //constructor with string
        largeInt(std::string toConsume);
    //copy constructor
        largeInt(const largeInt& other);
    //get length of the largeInt (number of digits in it)
        int getlength() const;
    // overloaded equal operator
        const largeInt& operator=(const largeInt& other);
    // overloaded equal operator for strings
        largeInt& operator=(std::string toConsume);
    //overloaded addition operator
        largeInt operator+(largeInt& other);
    // overloaded subtraction operator
        largeInt operator-( largeInt& other);
    //overloaded mulptiplication operator
        largeInt operator*(largeInt& other);
    //overloaded division operator
        largeInt operator/(largeInt& other);
    //returns the remaineder after division
        largeInt operator%(largeInt& other);
    //prints the largeInt (use for development)
        void printNum();
    //copy function
        void copy(const largeInt& other);
    //destroy function
        void destroy();
    //overloaded operator== function
        bool operator==(largeInt& other);
    //overloaded greater than operator
        bool operator>(largeInt& other);
    //overloaded greater than or equal to operator
        bool operator>=(largeInt& other);
    //overloaded less than operator
        bool operator<(largeInt& other);
    //overloaded less than or equal to operator
        bool operator<=(largeInt& other);
    //greater than function for absolute values of the largeInts
        bool absGreaterThan(largeInt& other);
    //less than function for absolute values of the largeInts
        bool absLessThan(largeInt& other);
    //greater than oe equal function for absolute values of the largeInts
        bool absGreaterThanOrEqual(largeInt& other);
    //less than or equal function for absolute values of the largeInt
        bool absLessThanOrEqual(largeInt& other);
    //this returns true if the absolute values of the largeInt's are equal
        bool absequal(largeInt& other);
    //Ths function is repsonsible for the addition of absolute values of numbers
        largeInt plus(largeInt& other);
    //Ths function is repsonsible for the subtraction of absolute values of numbers
        largeInt minus( largeInt& other);
    //Ths function is repsonsible for the multiplication of absolute values of numbers
        largeInt multiply(largeInt& other);
    //Ths function is repsonsible for the division of absolute values of numbers
        largeInt divide(largeInt& other);
    //increments the large int by one
        largeInt& operator++();
    //decrements the large int by one
        largeInt& operator--();
    //returns true if number is poisitive
        bool isPositive() const;
    //This removes leading zeros from largeInt.
        void removeleadingZeros();
    //takes in a numeric string and stores in largeint
        void stringToLargeInt(std::string toConsume);
};
#endif