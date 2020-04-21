/*
Project 4 - Part 6 / 9
Video: Chapter 5 Part 3
 
Create a branch named Part6
 
 Lambdas
 
    Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add two member functions named "apply()" to each of your Heap-Allocated Numeric Type wrappers.
         both apply() functions should work with chaining
 
 2) One of the apply() functions should takes a std::function<> object as the function argument.
    the std::function<> object should return *this;
 
 3) the other apply() function should take a function pointer. 
    the function pointer should return void.
 
 4) Make both of the member functions's Callable Function Parameter use your owned object as it's single parameter.
         e.g. if you manage your owned object via std::unique_ptr<T>, you'd use this for your std::function argument:
             std::function< OwnedT&(std::unique_ptr<T>&)>
             
         if you managed your owned object via a raw pointer, you'd use this for your std::function argument:
             std::function<OwnedT&(T&)>    
 
 5) call that Callable Function Parameter in the apply() member function.
         be sure to practice safe std::function usage (make sure it's not a nullptr function being called)
 
 6) Using one instance of each of your Heap-Allocated Numeric Type wrappers: Call your apply() member function twice in main()
         a) once with a lambda as the argument
         b) once with a free function as the argument.
         c) there will be a total of 6 calls to apply() in main(), 2x per HeapType, IntType, DoubleType instance.
         If this confuses you, rewatch the video where I pass a free function in to a function that wants a function pointer
 
 8) Make your lambda & free function update the value of your held object
 
 9) use std::cout statements to print out the results of calling apply()
 
build/run to make sure you don't have any errors

Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 
 If you need to see an example, look at https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part6Example.cpp
 */






#include <iostream>
#include <cmath>
#include <functional>

struct FloatType;
struct DoubleType;
struct IntType;

struct Point
{
    Point(float x_, float y_) : x(x_), y(y_) {}

    Point(const FloatType&);
    Point(const DoubleType&);
    Point(const IntType&);

    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }

    Point& multiply(FloatType&);
    Point& multiply(DoubleType&);
    Point& multiply(IntType&);

    void toString();

private:
    float x{0}, y{0};
};

using FloatFunctionPtr = void(*)(float&);

struct FloatType
{

    FloatType(float f) : value(new float(f)) { }
    ~FloatType()
    {
        delete value;
        value = nullptr;
    }

    FloatType& apply(std::function<FloatType&(float&)>);
    FloatType& apply(FloatFunctionPtr);

    FloatType& pow(float f);
    FloatType& pow(const FloatType& f);
    FloatType& pow(const IntType& i);
    FloatType& pow(const DoubleType& d);

    FloatType& operator+=(float f);
    FloatType& operator-=(float f);
    FloatType& operator*=(float f);
    FloatType& operator/=(float f);

    operator float() const { return *value; }

private:
    float* value = nullptr;
    FloatType& powInternal(const float f);
};

// ====== Apply() implementation =========== //

FloatType& FloatType::apply(std::function<FloatType&(float&)> floatFunc) 
{
    if(floatFunc)
    {
        return floatFunc(*value);
    }
    std::cout << "ERROR: nullptr passed as argument" << std::endl;
    return *this;
}

FloatType& FloatType::apply(FloatFunctionPtr funcPtr) 
{
    if(funcPtr)
    {
        funcPtr(*value);
    }
    return *this;
}

// Free Function

void freeFloatFunc(float& f)
{
    f *= 4.f;
}

// ========================================= //

FloatType& FloatType::operator+=(float f)
{
    *value += f;
    return *this;
}
FloatType& FloatType::operator-=(float f)
{
    *value -= f;
    return *this;
}
FloatType& FloatType::operator*=(float f)
{
    *value *= f;
    return *this;
}
FloatType& FloatType::operator/=(float f)
{
    if(f == 0.0f) { std::cout << "Warning: dividing by 0 results in undefined value!" << std::endl; }
    *value /= f;
    return *this;
}

using DoubleFunctionPtr = void(*)(double&);

struct DoubleType
{

    DoubleType(double d) : value(new double(d)) { }
    ~DoubleType()
    {
        delete value;
        value = nullptr;
    }

    DoubleType& apply(std::function<DoubleType&(double&)>);
    DoubleType& apply(DoubleFunctionPtr);

    DoubleType& pow(double d);
    DoubleType& pow(const DoubleType& d);
    DoubleType& pow(const IntType& i);
    DoubleType& pow(const FloatType& f);

    DoubleType& operator+=(double d);
    DoubleType& operator-=(double d);
    DoubleType& operator*=(double d);
    DoubleType& operator/=(double d);

    operator double() const { return *value; }

private:
    double* value = nullptr;
    DoubleType& powInternal(const double d);
};

// ====== Apply() implementation =========== //

DoubleType& DoubleType::apply(std::function<DoubleType&(double&)> doubleFunc) 
{
    if(doubleFunc)
    {
        return doubleFunc(*value);
    }
    std::cout << "ERROR: nullptr passed as argument" << std::endl;
    return *this;
}

DoubleType& DoubleType::apply(DoubleFunctionPtr funcPtr) 
{
    if(funcPtr)
    {
        funcPtr(*value);
    }
    return *this;
}

// Free Function

void freeDoubleFunc(double& d)
{
    d *= 4.0;
}

// ========================================= //

DoubleType& DoubleType::operator+=(double d)
{
    *value += d;
    return *this;
}

DoubleType& DoubleType::operator-=(double d)
{
    *value -= d;
    return *this;
}

DoubleType& DoubleType::operator*=(double d)
{
    *value *= d;
    return *this;
}

DoubleType& DoubleType::operator/=(double d)
{
    if(d == 0.0) { std::cout << "Warning: dividing by 0 results in undefined value!" << std::endl; }
    *value /= d;
    return *this;
}

using IntFunctionPtr = void(*)(int&);

struct IntType
{
    IntType(int i) : value(new int(i)) { }
    ~IntType()
    {
        delete value;
        value = nullptr;
    }

    IntType& apply(std::function<IntType&(int&)>);
    IntType& apply(IntFunctionPtr);

    IntType& pow(int i);
    IntType& pow(const IntType& i);
    IntType& pow(const DoubleType& d);
    IntType& pow(const FloatType& f);

    IntType& operator+=(int i);
    IntType& operator-=(int i);
    IntType& operator*=(int i);
    IntType& operator/=(int i);

    operator int() const { return *value; }

private:
    int* value = nullptr;
    IntType& powInternal(const int i);
};

// ====== Apply() implementation =========== //

IntType& IntType::apply(std::function<IntType&(int&)> intFunc) 
{
    if(intFunc)
    {
        return intFunc(*value);
    }
    std::cout << "ERROR: nullptr passed as argument" << std::endl;
    return *this;
}

IntType& IntType::apply(IntFunctionPtr funcPtr) 
{
    if(funcPtr)
    {
        funcPtr(*value);
    }
    return *this;
}

// Free Function

void freeIntFunc(int& i)
{
    i *= 4;
}

// ========================================= //

IntType& IntType::operator+=(int i)
{
    *value += i;
    return *this;
}
IntType& IntType::operator-=(int i)
{
    *value -= i;
    return *this;
}
IntType& IntType::operator*=(int i)
{
    *value *= i;
    return *this;
}
IntType& IntType::operator/=(int i)
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

// ===== Point Constructors ===== //

Point::Point(const FloatType& f) : Point(f,f) {}
Point::Point(const DoubleType& d) : Point(static_cast<float>(d),static_cast<float>(d)) {} 
Point::Point(const IntType& i) : Point(static_cast<float>(i),static_cast<float>(i)) {}

// ===== Point Member Function Implementations ===== //

void Point::toString()
{
    std::cout << "x: " << x << " y: " << y << std::endl;
}

Point& Point::multiply(FloatType& f)
{ 
    return multiply(static_cast<float>(f));
}

Point& Point::multiply(DoubleType& d)
{
    return multiply(static_cast<float>(d));
}

Point& Point::multiply(IntType& i)
{
    return multiply(static_cast<float>(i));
}
 
// ===== pow() implementation - Float Type ==== //

FloatType& FloatType::powInternal(const float f)
{
    if(value)
    {
        *value = std::pow(*value, f);
    }
    return *this;
}

FloatType& FloatType::pow(float f)
{
    return powInternal(f);
}

FloatType& FloatType::pow(const IntType& i)
{
    return powInternal(static_cast<float>(i));
}

FloatType& FloatType::pow(const DoubleType& d)
{
    return powInternal(static_cast<float>(d));
}

// ===== pow() implementation - Double Type ==== //

DoubleType& DoubleType::powInternal(const double d)
{
    if(value)
    {
        *value = std::pow(*value, d);
    }
    return *this;
}

DoubleType& DoubleType::pow(double d)
{
    return powInternal(d);
}

DoubleType& DoubleType::pow(const IntType& i)
{
    return powInternal(static_cast<double>(i));
}

DoubleType& DoubleType::pow(const FloatType& f)
{
    return powInternal(static_cast<double>(f));
}

// ===== pow() implementation - Int Type ==== //

IntType& IntType::powInternal(const int i)
{
    if(value)
    {
        *value = static_cast<int>(std::pow(*value, i));
    }
    return *this;
}

IntType& IntType::pow(int i)
{
    return powInternal(i);
}

IntType& IntType::pow(const DoubleType& d)
{
    return powInternal(static_cast<int>(d));
}

IntType& IntType::pow(const FloatType& f)
{
    return powInternal(static_cast<int>(f));
}

// ============================= //

int main()
{
    std::cout << std::endl;
    std::cout << "------------------------------Float Type------------------------------" << std::endl;
    FloatType floatType(3.1f);
    IntType intType(2);
    DoubleType doubleType(3.1);

    // Float Type: Apply() passing a lambda

    floatType.apply([&ft = floatType](float& f) -> FloatType&
    {
        f *= 8.f;
        return ft;
    });

    std::cout << "floatType.apply() with lamba: " << floatType << std::endl;

    // Float Type: Apply() passing a free function

    floatType.apply(freeFloatFunc);

    std::cout << "floatType.apply() with free function: " << floatType << std::endl;

    floatType *= 5.f;
    floatType += 4.2f;
    floatType -= static_cast<float>(doubleType);
    floatType /= static_cast<float>(intType);

    std::cout << std::endl;

    std::cout << "ft: multiplying by 5.f, adding 4.2f, subtracting dt, and dividing by it results in " << floatType << std::endl;

    std::cout << "The above result to the power of intType, then to the power of doubleType: " << static_cast<float>(floatType.pow(intType).pow(doubleType)) << std::endl;
    
    std::cout << std::endl;

    std::cout << "------------------------------Double Type------------------------------" << std::endl;
    DoubleType doubleType2(5.6);
    FloatType floatType2(4.1f);
    IntType intType2(3);

    // Double Type: Apply() passing a lambda

    doubleType2.apply([&dt = doubleType2](double& d) -> DoubleType& 
    {
        d *= 8.0;
        return dt;
    });

    std::cout << "doubleType2.apply() with lamba: " << doubleType2 << std::endl;

    // Double Type: Apply() passing a free function

    doubleType2.apply(freeDoubleFunc);

    std::cout << "doubleType2.apply() with free function: " << doubleType2 << std::endl;

    doubleType2 /= 2.1;
    doubleType *= 9.4;
    doubleType += static_cast<double>(floatType2);
    doubleType /= static_cast<double>(intType2);

    std::cout << std::endl;

    std::cout << "doubleType2: dividing by 2.1, multiplying by 9.4, addding floatType2, and dividing by intType2 results in  " <<  doubleType << std::endl;

    std::cout << "The above result to the power of floatType2, then to the power of intType2: " << static_cast<double>(doubleType2.pow(floatType2).pow(intType2)) << std::endl;
    
    std::cout << std::endl;

    std::cout << "------------------------------Int Type------------------------------" << std::endl;
    IntType intType3(14);
    DoubleType doubleType3(5.43);
    FloatType floatType3(1.1f);

    // Int Type: Apply() passing a lambda

    intType3.apply([&it = intType3](int& i) -> IntType& 
    {
        i *= 8;
        return it;
    });

    std::cout << "intType3.apply() with lamba: " << intType3 << std::endl;

    // Int Type: Apply() passing a free function

    intType3.apply(freeIntFunc);

    std::cout << "intType3.apply() with free function: " << intType3 << std::endl;

    intType3 -= 5;
    intType3 /= 2;
    intType3 *= static_cast<int>(doubleType3);
    intType3 *= static_cast<int>(floatType3);

    std::cout << std::endl;

    std::cout << "intType3: subtracting 5, dividing by 2, multiplying by doubleType3, and multiplying again by floatType3 results in:  " << intType3 << std::endl;

    std::cout << "The above result to the power of doubleType3, then to the power of floatType3: " << static_cast<double>(intType3.pow(doubleType3).pow(floatType3)) << std::endl;

    std::cout << std::endl;

    floatType /= 0;
    doubleType /= 0;
    intType /= 0;

    Point point(floatType2);
    Point point2(doubleType2);
    Point point3(intType2);

    point.multiply(doubleType3);
    point.toString();

    point2.multiply(intType3);
    point2.toString();

    point3.multiply(floatType3);
    point3.toString();

    std::cout << "good to go" << std::endl;
}


