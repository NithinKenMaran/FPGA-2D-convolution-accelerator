#include <iostream>
#include <vector>

constexpr std::size_t KH = 3;
constexpr std::size_t KW = 3;
constexpr std::size_t IH = 5;
constexpr std::size_t IW = 5;
constexpr std::size_t OH = IH+KH-1;
constexpr std::size_t OW = IW+KW-1;

typedef std::array<std::array<float, KW>, KH> Kernel;
typedef std::array<std::array<float, IW>, IH> Image;
typedef std::array<std::array<float, OW>, OH> Output;


Output convolve(const Image& input, const Kernel& kernel) {
    Output output{};
    for (int m = 0; m < (int)OH; m++) {
        for (int n = 0; n < (int)OW; n++) {
            float sum{};

            for (int i = 0; i < (int)KH; i++){
                for (int j = 0; j < (int)KW; j++) {
                    int in_row = m+i - ((int)KH-1);
                    int in_col = n+j - ((int)KW-1);
                    if (in_row >= 0 && in_row < (int)IH && in_col >= 0 && in_col < (int)IW) {
                        sum += input[in_row][in_col] * kernel[i][j];
                    }
                }
            }

            output[m][n] = sum;
        }
    }
    return output;
}

int main() {
    Image input {
        {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
        }
    };
    Kernel kernel {{
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    }};

    Output output = convolve(input, kernel);

    for (const auto& row : output) {
        for (float value : row) {
            std::cout << value << ' ';
        }
        std::cout<< std::endl;
    }
}