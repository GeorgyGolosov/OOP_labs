#include "../include/lab1.h"
#include <cmath>
#include <string>

long eliminate_unset_bits(std::string number){
    long result;
    int c = 0;
    int n = number.size();
    for (int i = 0; i < n; ++i){
        if (number[i] == '1'){
            c += 1;
        }
    }
    result = pow(2, c) - 1;

    return result;
}
