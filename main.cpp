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

struct A {};

struct HeapA 
{
    A* a = nullptr;

    HeapA() 
    {
        a = new A();
    }

    ~HeapA() 
    {
        delete a;
        a = nullptr;
    }
};

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
        } else 
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

FloatType& FloatType::add(const IntType& it) 
{
    *value += float(*it.value);
    return *this;
}
FloatType& FloatType::subtract(const IntType& it) 
{
    *value -= float(*it.value);
    return *this;
}
FloatType& FloatType::multiply(const IntType& it) 
{
    *value *= float(*it.value);
    return *this;
}
FloatType& FloatType::divide(const IntType& it) 
{
    if(*it.value == 0) { std::cout << "Warning: dividing by 0 results in undefined value!" << std::endl; }
    *value /= float(*it.value); 
    return *this;
}

// add/subtract/multiply/divide DoubleType 

FloatType& FloatType::add(const DoubleType& dt) 
{
    *value += float(*dt.value);
    return *this;
}
FloatType& FloatType::subtract(const DoubleType& dt)
{
    *value -= float(*dt.value);
    return *this;
}
FloatType& FloatType::multiply(const DoubleType& dt)
{
    *value *= float(*dt.value);
    return *this;
}
FloatType& FloatType::divide(const DoubleType& dt)
{
    if(*dt.value == 0) { std::cout << "Warning: dividing by 0 results in undefined value!" << std::endl; }
    *value /= float(*dt.value);
    return *this;
}

//////// DoubleType UDT math

// add/subtract/multiply/divide IntType 

DoubleType& DoubleType::add(const IntType& it) 
{
    *value += double(*it.value);
    return *this;
}
DoubleType& DoubleType::subtract(const IntType& it) 
{
    *value -= double(*it.value);
    return *this;
}
DoubleType& DoubleType::multiply(const IntType& it) 
{
    *value *= double(*it.value);
    return *this;
}
DoubleType& DoubleType::divide(const IntType& it) 
{
    if(*it.value == 0) { std::cout << "Warning: dividing by 0 results in undefined value!" << std::endl; }
    *value /= double(*it.value);
    return *this;
}

// add/subtract/multiply/divide FloatType 

DoubleType& DoubleType::add(const FloatType& ft) 
{
    *value += double(*ft.value);
    return *this;
}
DoubleType& DoubleType::subtract(const FloatType& ft)
{
    *value -= double(*ft.value);
    return *this;
}
DoubleType& DoubleType::multiply(const FloatType& ft)
{
    *value *= double(*ft.value);
    return *this;
}
DoubleType& DoubleType::divide(const FloatType& ft)
{
    if(*ft.value == 0) { std::cout << "Warning: dividing by 0 results in undefined value!" << std::endl; }
    *value /= double(*ft.value);
    return *this;
}

//////// IntType UDT math

// add/subtract/multiply/divide DoubleType 

IntType& IntType::add(const DoubleType& dt) 
{
    *value += int(*dt.value);
    return *this;
}
IntType& IntType::subtract(const DoubleType& dt) 
{
    *value -= int(*dt.value);
    return *this;
}
IntType& IntType::multiply(const DoubleType& dt) 
{
    *value *= int(*dt.value);
    return *this;
}
IntType& IntType::divide(const DoubleType& dt) 
{
    if(*dt.value == 0) { std::cout << "Warning: dividing by 0 results in undefined value!" << std::endl; }
    *value /= int(*dt.value);
    return *this;
}

// add/subtract/multiply/divide FloatType 

IntType& IntType::add(const FloatType& ft) 
{
    *value += int(*ft.value);
    return *this;
}
IntType& IntType::subtract(const FloatType& ft)
{
    *value -= int(*ft.value);
    return *this;
}
IntType& IntType::multiply(const FloatType& ft)
{
    *value *= int(*ft.value);
    return *this;
}
IntType& IntType::divide(const FloatType& ft)
{
    if(*ft.value == 0) { std::cout << "Warning: dividing by 0 results in undefined value!" << std::endl; }
    *value /= int(*ft.value);
    return *this;
}

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


