#include <string>
#include <sstream>
#include <iostream>

template<typename T1>
std::string StrConcat(const T1 &a)
{
    std::string result;
    StrAppend(result, a);
    return result;
}


template<typename T1, typename T2>
std::string StrConcat(const T1 &a, const T2 &b)
{
    std::string result;
    StrAppend(result, a);
    StrAppend(result, b);
    return result;
}

template<typename T1>
void StrAppend(std::string & str, const T1 & a)
{
    std::ostringstream oss;
    oss << a;
    str.append(oss.str());
}

template<typename T1, typename T2>
void StrAppend(std::string & str, const T1 & a, const T2 &b)
{
    StrAppend(str, a);
    StrAppend(str, b);
}

int main()
{
    std::cout << StrConcat(1, "sb") << std::endl;
    return 0;
}
