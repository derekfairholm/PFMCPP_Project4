/*
Project 4: Part 4 / 9
 Chapter 4 Part 7
 Function/Constructor Overloading

 Create a branch named Part4
 
 Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add pow() functions, and a powInternal() function to each of your UDTs
     a) your pow() functions should call powInternal()
     b) add a pow() whose argument type is the primitive your UDT owns.  the argument should be passed by copy.
     c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
         the argument should be passed as const ref
         i.e. if you had UDTs named IntType, FloatType, DoubleType
             in your IntType class, you'd have:
                 pow(const IntType&),
                 pow(const FloatType&),
                 pow(const DoubleType&),
                 and pow(int)
     d) be sure to remember the rules about what member functions can be called on const objects.
             (const objects can only call their const member functions)
     e) the pow() functions should be chainable.
 
 2) your powInternal() function should do something like this in its body:    *val = std::pow( *val, arg );
         where 'arg' is the passed-in type, converted to whatever type your object is holding.
             if your UDT owns an int, then arg would be an int.
             if your UDT owns a float, then arg would be a float.
         std::pow's documentation is found here: https://en.cppreference.com/w/cpp/numeric/math/pow so be sure to include
             the proper header file listed there.
         powInternal() should be chainable.
 
 3) modify the Point class below to have Constructors that accept your UDTs.
     a) make the Constructor's UDT arguments initialize the Point class's two member variables.
     b) overload the multiply() function so it can accept each of your UDTs.  I've added an implementation you can mimick for this function.
     c) add a toString() function to the Point class that prints out the x and y members via std::cout.
 
 4) Add to main()
     a) use your new pow() function in main for all of your types and print out the results.
     b) use the Point class in main and multiply some Point instances with your UDTs
     c) use the Point::toString() function to print out the results.
 
 
 5) make sure it compiles without errors.
 
 You will need to use Forward Declaration and out-of-class definitions to complete this.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

#include <iostream>
#include <cmath>

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

    void toString();

    Point& multiply(FloatType& f);
    Point& multiply(DoubleType& d);
    Point& multiply(IntType& i);

private:
    float x{0}, y{0};
};

struct FloatType
{

    FloatType(float f) : value(new float(f)) { }
    ~FloatType()
    {
        delete value;
        value = nullptr;
    }

    FloatType& pow(float f);
    FloatType& pow(const FloatType& f);
    FloatType& pow(const IntType& i);
    FloatType& pow(const DoubleType& d);

    FloatType& add(float f);
    FloatType& subtract(float f);
    FloatType& multiply(float f);
    FloatType& divide(float f);

    operator float() const { return *value; }

private:
    float* value = nullptr;
    FloatType& powInternal(const float f);
};

FloatType& FloatType::add(float f)
{
    *value += f;
    return *this;
}
FloatType& FloatType::subtract(float f)
{
    *value -= f;
    return *this;
}
FloatType& FloatType::multiply(float f)
{
    *value *= f;
    return *this;
}
FloatType& FloatType::divide(float f)
{
    if(f == 0.0f) { std::cout << "Warning: dividing by 0 results in undefined value!" << std::endl; }
    *value /= f;
    return *this;
}

struct DoubleType
{

    DoubleType(double d) : value(new double(d)) { }
    ~DoubleType()
    {
        delete value;
        value = nullptr;
    }

    DoubleType& pow(double d);
    DoubleType& pow(const DoubleType& d);
    DoubleType& pow(const IntType& i);
    DoubleType& pow(const FloatType& f);

    DoubleType& add(double d);
    DoubleType& subtract(double d);
    DoubleType& multiply(double d);
    DoubleType& divide(double d);

    operator double() const { return *value; }

private:
    double* value = nullptr;
    DoubleType& powInternal(const double d);
};

DoubleType& DoubleType::add(double d)
{
    *value += d;
    return *this;
}

DoubleType& DoubleType::subtract(double d)
{
    *value -= d;
    return *this;
}

DoubleType& DoubleType::multiply(double d)
{
    *value *= d;
    return *this;
}

DoubleType& DoubleType::divide(double d)
{
    if(d == 0.0) { std::cout << "Warning: dividing by 0 results in undefined value!" << std::endl; }
    *value /= d;
    return *this;
}

struct IntType
{
    IntType(int i) : value(new int(i)) { }
    ~IntType()
    {
        delete value;
        value = nullptr;
    }

    IntType& pow(int i);
    IntType& pow(const IntType& i);
    IntType& pow(const DoubleType& d);
    IntType& pow(const FloatType& f);

    IntType& add(int i);
    IntType& subtract(int i);
    IntType& multiply(int i);
    IntType& divide(int i);

    operator int() const { return *value; }

private:
    int* value = nullptr;
    IntType& powInternal(const int i);
};

IntType& IntType::add(int i)
{
    *value += i;
    return *this;
}
IntType& IntType::subtract(int i)
{
    *value -= i;
    return *this;
}
IntType& IntType::multiply(int i)
{
    *value *= i;
    return *this;
}
IntType& IntType::divide(int i)
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

Point::Point(const FloatType& f) : x(f), y(f) {}
Point::Point(const DoubleType& d) : x(static_cast<float>(d)), y(static_cast<float>(d)) {}
Point::Point(const IntType& i) : x(static_cast<float>(i)), y(static_cast<float>(i)) {}

// ===== Point Member Function Implementations ===== //

void Point::toString()
{
    std::cout << "x: " << x << " y: " << y << std::endl;
}

Point& Point::multiply(FloatType& f)
{
    x *= f;
    y *= f;
    return *this;
}

Point& Point::multiply(DoubleType& d)
{
    x *= static_cast<float>(d);
    y *= static_cast<float>(d);
    return *this;
}

Point& Point::multiply(IntType& i)
{
    x *= static_cast<float>(i);
    y *= static_cast<float>(i);
    return *this;
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
    return powInternal(static_cast<double>(d));
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
        *value = std::pow(*value, i);
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

    std::cout << std::endl;
    
    std::cout << "ft: multiplying by 5.f, adding 4.2f, subtracting dt, and dividing by it results in " << static_cast<float>(floatType.multiply(5.f).add(4.2f).subtract(static_cast<float>(doubleType)).divide(intType)) << std::endl;

    std::cout << "The above result to the power of intType, then to the power of doubleType: " << static_cast<float>(floatType.pow(intType).pow(doubleType)) << std::endl;
    
    std::cout << std::endl;

    std::cout << "------------------------------Double Type------------------------------" << std::endl;
    DoubleType doubleType2(5.6);
    FloatType floatType2(4.1f);
    IntType intType2(3);

    std::cout << std::endl;
    
    std::cout << "doubleType2: dividing by 2.1, multiplying by 9.4, addding floatType2, and dividing by intType2 results in  " <<  static_cast<double>(doubleType2.divide(2.1).multiply(9.4).add(static_cast<double>(floatType2)).divide(intType2)) << std::endl;

    std::cout << "The above result to the power of floatType2, then to the power of intType2: " << static_cast<double>(doubleType2.pow(floatType2).pow(intType2)) << std::endl;
    
    std::cout << std::endl;

    std::cout << "------------------------------Int Type------------------------------" << std::endl;
    IntType intType3(14);
    DoubleType doubleType3(5.43);
    FloatType floatType3(1.1f);

    std::cout << std::endl;
    std::cout << "intType3: subtracting 5, dividing by 2, multiplying by doubleType3, and multiplying again by floatType3 results in:  " << static_cast<int>(intType3.subtract(5).divide(2).multiply(static_cast<int>(doubleType3)).multiply(static_cast<int>(floatType3))) << std::endl;

    std::cout << "The above result to the power of doubleType3, then to the power of floatType3: " << static_cast<double>(intType3.pow(doubleType3).pow(floatType3)) << std::endl;

    std::cout << std::endl;

    floatType.divide(0);
    doubleType.divide(0);
    intType.divide(0);

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


