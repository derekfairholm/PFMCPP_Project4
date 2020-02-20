/*
 Project 4 - Part 2 / 9
 Video: Chapter 3 Part 6

 Create a branch named Part2

New/This/Pointers/References conclusion

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 0) in the blank space below, declare/define an empty struct named 'A' on a single Line. 
     on the lines below it, write a struct named 'HeapA' that correctly shows how to own an instance of 'A' 
         on the heap without leaking, without using smart pointers. 
 */











 /*
 1) Edit your 3 structs so that they own a heap-allocated primitive type without using smart pointers  
         IntType should own a heap-allocated int, for example.
 
 2) give it a constructor that takes the appropriate primitive
    this argument will initialize the owned primitive's value.
         i.e. if you're owning an int on the heap, your ctor argument will initialize that heap-allocated int's value.
 
 3) modify those add/subtract/divide/multiply member functions from chapter 2 on it
         a) make them modify the owned numeric type
         b) set them up so they can be chained together.
             i.e.
             DoubleType dt(3.5);
             dt.add(3.0).multiply(-2.5).divide(7.2); //an example of chaining
 
 4) write add/subtract/divide/multiply member functions for each type that take your 3 UDTs
        These are in addition to your member functions that take primitives
        for example, IntType::divide(const DoubleType& dt);
 
 5) print out the results with some creative couts 
    i.e.
         FloatType ft(0.1f);
         IntType it(3);
         std::cout << "adding 3 and subtracting 'it' from 'ft' results in the following value: " << *ft.add(2.f).subtract( it ).value << std::endl;  //note the dereference of the `value` member of `ft`
 
 6) Don't let your heap-allocated owned type leak!
 
 7) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */




#include <iostream>

struct FloatType
{
    float add(float lhs, float rhs) { return lhs + rhs; }
    float subtract(float lhs, float rhs) { return lhs - rhs; }
    float multiply(float lhs, float rhs) { return lhs * rhs; }
    float divide(float lhs, float rhs) { return lhs / rhs; }
};

struct DoubleType
{
    double add(double lhs, double rhs) { return lhs + rhs; }
    double subtract(double lhs, double rhs) { return lhs - rhs; }
    double multiply(double lhs, double rhs) { return lhs * rhs; }
    double divide(double lhs, double rhs) { return lhs / rhs; }
};

struct IntType
{
    int add(int lhs, int rhs) { return lhs + rhs; }
    int subtract(int lhs, int rhs) { return lhs - rhs; }
    int multiply(int lhs, int rhs) { return lhs * rhs; }
    int divide(int lhs, int rhs) 
    { 
        if(rhs == 0) { return 0; }
        return lhs / rhs; 
    }
};

int main()
{
    std::cout << "------------------------------Float Type------------------------------" << std::endl;

    FloatType ft;
    float floatResult = ft.add(2.f, 3.2f);    
    std::cout << "ft.add(): " << floatResult << std::endl;
    floatResult = ft.subtract(8.1f, 4.5f);
    std::cout << "ft.subtract(): " << floatResult << std::endl;
    floatResult = ft.multiply(12.2f, 3.f);
    std::cout << "ft.multiply(): " << floatResult << std::endl;
    floatResult = ft.divide(2.8f, 0);
    std::cout << "ft.divide(): " << floatResult << std::endl;

    std::cout << "------------------------------Double Type------------------------------" << std::endl;

    DoubleType dt;
    double doubleResult = dt.add(2.0, 3.2);    
    std::cout << "dt.add(): " << doubleResult << std::endl;
    doubleResult = dt.subtract(8.1, 4.5);
    std::cout << "dt.subtract(): " << doubleResult << std::endl;
    doubleResult = dt.multiply(12.2, 3.0);
    std::cout << "dt.multiply(): " << doubleResult << std::endl;
    doubleResult = dt.divide(2.8, 0);
    std::cout << "dt.divide(): " << doubleResult << std::endl;

    std::cout << "------------------------------Int Type------------------------------" << std::endl;

    IntType it;
    int intResult = it.add(2, 3);    
    std::cout << "it.add(): " << intResult << std::endl;
    intResult = it.subtract(8, 4);
    std::cout << "it.subtract(): " << intResult << std::endl;
    intResult = it.multiply(12, 3);
    std::cout << "it.multiply(): " << intResult << std::endl;
    intResult = it.divide(2, 0);
    std::cout << "it.divide(): " << intResult << std::endl;
}


