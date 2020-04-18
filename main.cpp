
#include <iostream>
/*
Project 4: Part 5 / 9
 video: Chapter 5 Part 2
 Operator Overloading.

Do not delete your previous main. 

 Create a branch named Part5

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) replace the add/subtract/multiply/etc functions with overloaded math operators 
        e.g. add() would become operator+=() because it modifies the internal heap-allocated object.
 
 2) Your overloaded operators should only take primitives, passed by value.
 
 3) don't delete your conversion functions.
         if you removed them in Chapter 4 Part 7, put them back in.
         uncomment them if you commented them in Chapter 4 Part 7
 
 4) your main() function should be the same as Chapter 4 Part 7.  
     
 5) if your Chapter4 Part7 task didn't use any [+ - * or /], 
         add some in and fix the build errors that might result via the techniques you have learned in the previous weeks (hint: casting)
         i.e.
 */
#if false
namespace Example
{
    int main()
    {
        FloatType floatNum(4.3f);
        IntType intNum(2);
        IntType intNum2(6);

        /* 
        if you previously had a line like this demonstrating chaining:
            
            intNum.add(3).add(4.5f).divide(floatNum); 

        it should become:
        */
        intNum += 3;
        intNum += 4.5f;
        intNum /= floatNum;
        std::cout << "intNum: " << intNum << std::endl;
        
        return 0;
    }
}
#endif
 /*
 6) compile/link/run to make sure you don't have any errors
 
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

    Point& multiply(FloatType& f);
    Point& multiply(DoubleType& d);
    Point& multiply(IntType& i);

    void toString();

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


