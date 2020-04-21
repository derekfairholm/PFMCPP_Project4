
#include <iostream>
/*
Project 4: Part 7 / 9
Video: Chapter 5 Part 4

Create a branch named Part7

Do not delete your previous main. you will be adding to it.

Templates and Containers

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 

#1) if you're not using std::unique_ptr to own your heap-allocated type as a member variable, 
    replace your manual memory management techniques with a private std::unique_ptr member variable.

#2) replace your Heap-Allocated Numeric Type-owning class with a templated class called Numeric.
        replace all of your previous instances of your separate classes with this templated class.

#3) add a 'using <some name> = <your class template parameter>;' 
        treat this type declaration via 'using' as a static member variable
        use this Type alias as the argument everywhere you previously used the template argument.
        this will make it very easy to change the type if needed.
            i.e. if you have 'std::unique_ptr<NumericType> value;' before
                you'd replace NumericType in that variable declaration with '<some name>'
        
#4) you'll need to pair it with decltype() to help the compiler figure out the type of the object 
    your class owns when you make your lambda and free function that takes your unique_ptr.  
    i.e. like this for determining the template parameter of the unique_ptr function argument to your class's apply() function
        std::unique_ptr< decltype( <instance of class> )::<some name> >
    
#5) template your free function for the apply() that takes a function pointer so it can be used with your Wrapper class's apply() function

#6) add an explicit template specialization for 'double' of your wrapper class
        this template specialization will have one apply() function instead of 2. 

#7) this apply() function will be templated, and expect a Callable object, not std::function<>. 
        the function should allow for chaining.  
        the callable object should return void, like the function pointer-based apply() function in the primary class template

#8) instantiate your explicit template specialization

#9) call the apply function twice, once with a lambda and once with the free function
        the free function is templated, so you might need to call it including the template arguments.
        
#10) in addition to using the lambda argument to modify the owned object:  (your previous task's lambdas did this same thing) 
        make the lambda use your explicit template instance (maybe via a std::cout), 

#11) now that your class is templated, you'll need to adjust your logic in your division function to handle if your input is a zero or not, based on your templated type.  
        - look up how to use std::is_same<>::value on cppreference to determine the type of your template parameter.
        
        - look up how to use std::numeric_limits<>::epsilon() to determine if you're dividing by a floating point 0
        
        - read about Knuth's algorithm here: https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/

        - in plain-english, you'll need to implement logic like this:
        if your template type is an int
                if your parameter's type is also an int
                        if your parameter is 0
                                don't do the division
                else if it's less than epsilon
                        dont do the divison
        else if it's less than epsilon
                warn about doing the division

        - to make these checks work during compilation, your if() statements will need to be 'constexpr':  if constexpr (expression)

compile/link/run to make sure you don't have any errors

Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.

If you need to view an example, see: https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part7Example.cpp
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

struct FloatType
{

    FloatType(float f) : value(new float(f)) { }
    ~FloatType()
    {
        delete value;
        value = nullptr;
    }

    FloatType& apply(std::function<FloatType&(float&)>);

    using FloatFunctionPtr = void(*)(float&);
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

struct DoubleType
{

    DoubleType(double d) : value(new double(d)) { }
    ~DoubleType()
    {
        delete value;
        value = nullptr;
    }

    DoubleType& apply(std::function<DoubleType&(double&)>);

    using DoubleFunctionPtr = void(*)(double&);
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

struct IntType
{
    IntType(int i) : value(new int(i)) { }
    ~IntType()
    {
        delete value;
        value = nullptr;
    }

    IntType& apply(std::function<IntType&(int&)>);

    using IntFunctionPtr = void(*)(int&);
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

    floatType.apply([&floatType](float& f) -> FloatType&
    {
        f *= 8.f;
        return floatType;
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

    doubleType2.apply([&doubleType2](double& d) -> DoubleType& 
    {
        d *= 8.0;
        return doubleType2;
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

    intType3.apply([&intType3](int& i) -> IntType& 
    {
        i *= 8;
        return intType3;
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


