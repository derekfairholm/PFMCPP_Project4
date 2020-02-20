/*
 Project 4 - Part 1 / 9
 video: Chapter 2 Part 7
 Returning Values tasks 

 Create a branch named Part1
 
 1) write 3 UDTs named FloatType, DoubleType, IntType.
 
 2) give each UDT the following member functions:
        add( lhs, rhs );
        subtract( lhs, rhs );
        multiply( lhs, rhs );
        divide( lhs, rhs );
 
 3) make them return the correct primitive type. e.g. if you're implementing the FloatType::add function, your implementation would start like this:
        float FloatType::add( float lhs, float rhs )
 
 4) declare a few instances of each class in main() and call the member functions with the appropriate arguments.
        FloatType ft;
        auto result = ft.add(3.2f, 23.f );
 
 5) print out those results using std::cout:
        std::cout "result of ft.add(): " << result << std::endl;
 
 6) After you finish defining each type/function, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

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


