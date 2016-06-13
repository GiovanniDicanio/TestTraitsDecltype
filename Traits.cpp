///////////////////////////////////////////////////////////////////////////////
//
// Traits Class, Range-For Loop Iteration and decltype
//
// by Giovanni Dicanio <giovanni DOT dicanio@gmail.com>
//
///////////////////////////////////////////////////////////////////////////////


#include <iostream>     // For std::cout
#include <string>       // For std::string
#include <type_traits>  // For std::decay
#include <vector>       // For std::vector

using namespace std;    // Just fine in demo code


//-----------------------------------------------------------------------------
// Generic Traits Class
//-----------------------------------------------------------------------------
template <typename Type>
struct Traits
{
    static int GetSomeProperty(const Type&) 
    {
        cout << "Generic";  
        return 0; 
    }

    //
    // In production code there can be more public static methods here.
    //
};


//-----------------------------------------------------------------------------
// Traits specialized for std::string
//-----------------------------------------------------------------------------
template <>
struct Traits<string>
{
    static int GetSomeProperty(const string&) 
    { 
        cout << "String"; 
        return 1; 
    }
};


//-----------------------------------------------------------------------------
// Test function iterating a generic container and querying some property
// on its elements using the above traits class.
//-----------------------------------------------------------------------------
template <typename Container>
void DoSomething(const Container & c)
{
    for (const auto& elem : c)
    {
        cout << elem << ": ";

// Wrong result, since decltype(elem) is a "const string&", not a "string":
//        const int x = Traits<decltype(elem)>::GetSomeProperty(elem);

// FIX:
//        const int x = Traits<std::decay<decltype(elem)>::type>::GetSomeProperty(elem);

// FIX with better readability:
        typedef std::decay<decltype(elem)>::type ElemType;
        const int x = Traits<ElemType>::GetSomeProperty(elem);

        cout << '\n';
    }
}


//-----------------------------------------------------------------------------
// Test
//-----------------------------------------------------------------------------
int main()
{
    vector<string> test{ "Hello",  "Connie" };
    DoSomething(test);
}


///////////////////////////////////////////////////////////////////////////////
