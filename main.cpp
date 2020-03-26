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

    FloatType(float f) : value(new float(f)) { }
    ~FloatType()
    {
        delete value;
        value = nullptr;
    }

    FloatType& add(float f);
    FloatType& subtract(float f);
    FloatType& multiply(float f);
    FloatType& divide(float f);

    // Not sure how to handle the potential 'else' case here
    operator float() { return *value; }

private:

    float* value = nullptr;
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

    DoubleType& add(double d);
    DoubleType& subtract(double d);
    DoubleType& multiply(double d);
    DoubleType& divide(double d);

    operator double() { return *value; }

private:

    double* value = nullptr;
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

    IntType& add(int i);
    IntType& subtract(int i);
    IntType& multiply(int i);
    IntType& divide(int i);

    operator int() { return *value; }

private:

    int* value = nullptr;
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

int main()
{
    std::cout << std::endl;
    std::cout << "------------------------------Float Type------------------------------" << std::endl;
    FloatType ft(3.1f);
    IntType it(4);
    DoubleType dt(8.2);

    std::cout << std::endl;
    
    std::cout << "ft: multiplying by 5.f, adding 4.2f, subtracting dt, and dividing by it results in " << static_cast<float>(ft.multiply(5.f).add(4.2f).subtract(static_cast<float>(dt)).divide(it)) << std::endl;
    
    std::cout << std::endl;

    std::cout << "------------------------------Double Type------------------------------" << std::endl;
    DoubleType dt2(11.6);
    FloatType ft2(5.f);
    IntType it2(7);

    std::cout << std::endl;
    
    std::cout << "dt2: dividing by 2.1, multiplying by 9.4, addding ft2, and dividing by it2 results in  " <<  static_cast<double>(dt2.divide(2.1).multiply(9.4).add(static_cast<double>(ft2)).divide(it2)) << std::endl;
    
    std::cout << std::endl;

    std::cout << "------------------------------Int Type------------------------------" << std::endl;
    IntType it3(85);
    DoubleType dt3(52.43);
    FloatType ft3(42.1f);

    std::cout << std::endl;
    std::cout << "it3: subtracting 5, dividing by 2, multiplying by dt3, and multiplying again by ft3 results in  " << static_cast<int>(it3.subtract(5).divide(2).multiply(static_cast<int>(dt3)).multiply(static_cast<int>(ft3))) << std::endl;
    std::cout << std::endl;

    it.divide(0);
    dt.divide(0);
    ft.divide(0);

    std::cout << "good to go" << std::endl;
}


