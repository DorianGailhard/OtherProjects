#include "PCH.h"

float myfuncs::distance(const float& x1,const float& y1,const float& x2,const float& y2) {
    return std::sqrt(std::pow(x2 - x1,2) + std::pow(y2 - y1,2));
}

float myfuncs::direction(const float& x1,const float& y1,const float& x2,const float& y2) {
    return -atan2(y2 - y1,x2 - x1) * 180/M_PI;
}

float myfuncs::lengthDirX(const float& len,const float& dir) {
    return cos(dir * M_PI/180) * len;
}

float myfuncs::lengthDirY(const float& len,const float& dir) {
    return -sin(dir * M_PI/180) * len;
}
