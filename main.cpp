/*
 Project 4 - Part 3 / 9
 Video: Chapter 4 Part 3 
 Casting

 Create a branch named Part3
 
    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.

 1) remove your functions that accepted a User-Defined Type
 
 2) remove any getValue() functions if you added them
 
 3) move all of your add/subtract/multiply/divide implementations out of the class.
  
 4) add user-defined conversion functions that convert to the numeric type your object holds.
        i.e. if your type holds an int, you'll need an operator int() function.
 
 5) make your member variable private.
         this conversion function should be the ONLY WAY to access the held value.
 
 6) clean up any forward declaration that you might have.
 
 7) make sure it compiles & runs without errors.
 
 8) use your knowledge of casting to remove any conversion warnings. 
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */





#include <iostream>

struct FloatType;
struct DoubleType;
struct IntType;

struct FloatType
{
    float* value = nullptr;

    FloatType(float f) : value(new float(f)) { }
    ~FloatType()
    {
        delete value;
        value = nullptr;
    }

    FloatType& add(float f) 
    { 
        *value += f;
        return *this; 
    }
    FloatType& subtract(float f) 
    { 
        *value -= f;
        return *this; 
    }
    FloatType& multiply(float f) 
    { 
        *value *= f;
        return *this; 
    }
    FloatType& divide(float f) 
    { 
        if(f == 0) { std::cout << "Warning: dividing by 0 results in undefined value!" << std::endl; }
        *value /= f;
        return *this; 
    }

    // add/subtract/multiply/divide IntType 

    FloatType& add(const IntType& it);
    FloatType& subtract(const IntType& it);
    FloatType& multiply(const IntType& it);
    FloatType& divide(const IntType& it);

    // add/subtract/multiply/divide DoubleType 

    FloatType& add(const DoubleType& it);
    FloatType& subtract(const DoubleType& it);
    FloatType& multiply(const DoubleType& it);
    FloatType& divide(const DoubleType& it);
};

struct DoubleType
{
    double* value = nullptr;

    DoubleType(double d) : value(new double(d)) { }
    ~DoubleType()
    {
        delete value;
        value = nullptr;
    }

    DoubleType& add(double d) 
    { 
        *value += d; 
        return *this; 
    }
    DoubleType& subtract(double d) 
    { 
        *value -= d; 
        return *this; 
    }
    DoubleType& multiply(double d) 
    { 
        *value *= d; 
        return *this; 
    }
    DoubleType& divide(double d) 
    { 
        if(d == 0) { std::cout << "Warning: dividing by 0 results in undefined value!" << std::endl; }
        *value /= d; 
        return *this; 
    }

    // add/subtract/multiply/divide IntType 

    DoubleType& add(const IntType& it);
    DoubleType& subtract(const IntType& it);
    DoubleType& multiply(const IntType& it);
    DoubleType& divide(const IntType& it);

    // add/subtract/multiply/divide FloatType 

    DoubleType& add(const FloatType& it);
    DoubleType& subtract(const FloatType& it);
    DoubleType& multiply(const FloatType& it);
    DoubleType& divide(const FloatType& it);
};

struct IntType
{
    int* value = new int;

    IntType(int i) : value(new int(i)) { }
    ~IntType()
    {
        delete value;
        value = nullptr;
    }

    IntType& add(int i) 
    { 
        *value += i; 
        return *this; 
    }
    IntType& subtract(int i) 
    { 
        *value -= i;
        return *this; 
    }
    IntType& multiply(int i) 
    { 
        *value *= i; 
        return *this; 
    }
    IntType& divide(int i) 
    { 
        if(i == 0) 
        { 
            std::cout << "Warning: dividing by 0 results in undefined value!" << std::endl;
        } 
        else 
        {
            *value /= i; 
        }
        return *this;
    }

    // add/subtract/multiply/divide DoubleType 

    IntType& add(const DoubleType& it);
    IntType& subtract(const DoubleType& it);
    IntType& multiply(const DoubleType& it);
    IntType& divide(const DoubleType& it);

    // add/subtract/multiply/divide FloatType 

    IntType& add(const FloatType& it);
    IntType& subtract(const FloatType& it);
    IntType& multiply(const FloatType& it);
    IntType& divide(const FloatType& it);
};

//////// FloatType UDT math

// add/subtract/multiply/divide IntType 

FloatType& FloatType::add(const IntType& it) { return add(*it.value); }
FloatType& FloatType::subtract(const IntType& it) { return subtract(*it.value); }
FloatType& FloatType::multiply(const IntType& it) { return multiply(*it.value); }
FloatType& FloatType::divide(const IntType& it) { return divide(*it.value); }

// add/subtract/multiply/divide DoubleType 

FloatType& FloatType::add(const DoubleType& dt) { return add(*dt.value); }
FloatType& FloatType::subtract(const DoubleType& dt) { return subtract(*dt.value); }
FloatType& FloatType::multiply(const DoubleType& dt) { return multiply(*dt.value); }
FloatType& FloatType::divide(const DoubleType& dt) { return divide(*dt.value); }

//////// DoubleType UDT math

// add/subtract/multiply/divide IntType 

DoubleType& DoubleType::add(const IntType& it) { return add(*it.value); }
DoubleType& DoubleType::subtract(const IntType& it) { return subtract(*it.value); }
DoubleType& DoubleType::multiply(const IntType& it) { return multiply(*it.value); }
DoubleType& DoubleType::divide(const IntType& it) { return divide(*it.value); }

// add/subtract/multiply/divide FloatType 

DoubleType& DoubleType::add(const FloatType& ft){ return add(*ft.value); }
DoubleType& DoubleType::subtract(const FloatType& ft){ return subtract(*ft.value); }
DoubleType& DoubleType::multiply(const FloatType& ft){ return multiply(*ft.value); }
DoubleType& DoubleType::divide(const FloatType& ft){ return divide(*ft.value); }

//////// IntType UDT math

// add/subtract/multiply/divide DoubleType 

IntType& IntType::add(const DoubleType& dt) { return add(*dt.value); }
IntType& IntType::subtract(const DoubleType& dt){ return subtract(*dt.value); }
IntType& IntType::multiply(const DoubleType& dt){ return multiply(*dt.value); }
IntType& IntType::divide(const DoubleType& dt) { return divide(*dt.value); }

// add/subtract/multiply/divide FloatType 

IntType& IntType::add(const FloatType& ft) { return add(*ft.value); }
IntType& IntType::subtract(const FloatType& ft) { return subtract(*ft.value); }
IntType& IntType::multiply(const FloatType& ft) { return multiply(*ft.value); }
IntType& IntType::divide(const FloatType& ft) { return divide(*ft.value); }

int main()
{
    std::cout << std::endl;
    std::cout << "------------------------------Float Type------------------------------" << std::endl;
    FloatType ft(3.1f);
    IntType it(4);
    DoubleType dt(8.2);

    std::cout << std::endl;
    std::cout << "ft: multiplying by 5.f, adding 4.2f, subtracting dt, and dividing by it results in " << *ft.multiply(5.f).add(4.2f).subtract(dt).divide(it).value << std::endl;
    std::cout << std::endl;

    std::cout << "------------------------------Double Type------------------------------" << std::endl;
    DoubleType dt2(11.6);
    FloatType ft2(5.f);
    IntType it2(7);

    std::cout << std::endl;
    std::cout << "dt2: dividing by 2.1, multiplying by 9.4, addding ft2, and dividing by it2 results in  " << *dt2.divide(2.1).multiply(9.4).add(ft2).divide(it2).value << std::endl;
    std::cout << std::endl;

    std::cout << "------------------------------Int Type------------------------------" << std::endl;
    IntType it3(85);
    DoubleType dt3(52.43);
    FloatType ft3(42.1f);

    std::cout << std::endl;
    std::cout << "it3: subtracting 5, dividing by 2, multiplying by dt3, and multiplying again by ft3 results in  " << *it3.subtract(5).divide(2).multiply(dt3).multiply(ft3).value << std::endl;
    std::cout << std::endl;

    it.divide(0);
    dt.divide(0);
    ft.divide(0);

    std::cout << "good to go" << std::endl;
}


