#include <iostream>
using namespace std;

const float h[] = {3, 2, 1};
const float x[] = {1, 2, 3, 4, 5};

float filter(float x_in) {
    static float shift_reg[3] = {0, 0, 0};
    for (int i = 1; i < 3; i++) {
        shift_reg[i-1] = shift_reg[i];
    }
    shift_reg[2] = x_in;

    float y_out = 0;
    for (int i = 0; i < 3; i++) {
        y_out += h[i] * shift_reg[i];
    }
    return y_out;
}

int main(){
    for (int i = 0; i < 5; i++) {
        cout << filter(x[i]) << endl;
    }
    return 0;
}