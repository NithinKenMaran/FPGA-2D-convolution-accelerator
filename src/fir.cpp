#include <iostream>
#include <array>

constexpr std::size_t KH=3;
constexpr std::size_t KW=3;
constexpr std::size_t IH=5;
constexpr std::size_t IW=5;
constexpr std::size_t OH=IH-KH+1;
constexpr std::size_t OW=IW-KW+1;

typedef std::array<std::array<float, KW>, KH> Kernel;
typedef std::array<std::array<float, IW>, IH> Image;
typedef std::array<std::array<float, OW>, OH> Output;

//NOTE: check if two brackets are enough
//might need one more curly brace here
constexpr Kernel kernel{
    {
        {1, 2, 1}, 
        {0, 0, 0}, 
        {-1, -2, -1}
    }
};

constexpr Image input{
    {
        {1, 2, 3, 4, 5}, 
        {6, 7, 8, 9, 10}, 
        {11, 12, 13, 14, 15}, 
        {16, 17, 18, 19, 20}, 
        {21, 22, 23, 24, 25}
    }
};

float filter_2d(float x_in) {
    //shift_reg
    static std::array <float, 5> linebuffer3{};
    static std::array <float, 5> linebuffer2{};
    static std::array <float, 5> linebuffer1{};






}

int main(){
    for (int i = 0; i < 5; i++) {
        std::cout << filter(x[i]) << std::endl;
    }
    return 0;
}