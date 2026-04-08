#include <iostream>
#include <array>

// constexpr float h[] = {3, 2, 1};
// constexpr float x[] = {1, 2, 3, 4, 5};
constexpr std::array <float, 3> h = {3, 2, 1};
constexpr std::array <float, 5> x = {1, 2, 3, 4, 5};

float filter(float x_in) {
    static std::array <float, 3> shift_reg = {0, 0, 0};
    for (std::size_t i = 1; i < shift_reg.size(); i++) {
        shift_reg[i-1] = shift_reg[i];
    }
    // for (int i = 1; i < 3; i++) {
    //     shift_reg[i-1] = shift_reg[i];
    // }
    shift_reg[shift_reg.size() - 1] = x_in;

    float y_out = 0;
    // for (int i = 0; i < 3; i++) {
    //     y_out += h[i] * shift_reg[i];
    // }
    for (std::size_t i = 0; i < h.size(); i++){
        y_out += h[i] * shift_reg[i];
    }
    return y_out;
}

int main(){
    for (int i = 0; i < 5; i++) {
        std::cout << filter(x[i]) << std::endl;
    }
    return 0;
}