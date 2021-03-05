#include <iostream>
#include <random>
#include <ctime>


int main(){

    std::discrete_distribution<> dist({1.0,4.,0.9,0,0});
    std::mt19937 eng(time(0));
    for (int i = 0; i<100;i++){
        std::cout << eng << std::endl;
    }
}