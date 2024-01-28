#ifndef PCH_H
#define PCH_H

constexpr auto M_PI = 3.14159265358979323846;

//Frequently used headers
#include <string>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <list>
#include <forward_list>
#include <cmath>
#include <SFML/Window/Mouse.hpp>

//Exceptions
/*class FileNotFoundExeception : public std::runtime_error
{
  public:
        FileNotFoundExeception(std::string const& msg) : std::runtime_error(msg) {}
};*/

//Functions
namespace myfuncs {
    float distance(const float& x1,const float& y1,const float& x2,const float& y2);
    float direction(const float& x1,const float& y1,const float& x2,const float& y2);
    float lengthDirX(const float& len,const float& dir);
    float lengthDirY(const float& len,const float& dir);
};

#endif // PCH_H
