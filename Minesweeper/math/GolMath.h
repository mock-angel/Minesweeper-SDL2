#ifndef GOLMATH_INCLUDED
#define GOLMATH_INCLUDED
#include <vector>
struct PosRC{
    int r = 0;
    int c = 0;
    int &operator [] (int value)
    {
        switch(value){
        case (0):
            return r;
            break;
        case (1):
            return c;
            break;
        }
    }
};
struct PosXY{
    int x = 0;
    int y = 0;
    int &operator [] (int value)
    {
        if (value == 0) return x;
        else if (value == 1)  return y;
    }
};

template<int I = 0, int J = 0, int K = 0>
struct GolVector3d
{
    std::vector<float> vec;
    GolVector3d(){
        vec[0] = I;
        vec[1] = J;
        vec[2] = K;
    }
    void operator () (int value1, int value2, int value3)
    {
        vec[0] = value1;
        vec[1] = value2;
        vec[2] = value3;
    }
    float &operator [] (int value)
    {
        if (value >=0 and value<=2) return vec[value];
        else {
            printf("Error: GolVector3d::&operator []: Requested value of a non existing coordinate in a 3d vector.\n");
            //return NULL;
        }
    }
};
template<int I = 0, int J = 0>
struct GolVector2d
{
    std::vector<float> vec;
    GolVector2d(){
        vec[0] = I;
        vec[1] = J;
    }
    void operator () (int value1, int value2)
    {
        vec[0] = value1;
        vec[1] = value2;
    }
    int &operator [] (int value)
    {
        if (value >=0 and value<=1) return vec[value];
        else {
            printf("Error: GolVector2d::&operator []: Requested value of a non existing coordinate in a 2d vector.\n");
        }
    }
};
#endif // GOLMATH_INCLUDED
