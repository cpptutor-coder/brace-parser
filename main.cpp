#include "state_machine.h"
#include <iostream>

int main(int argc, char* argv[])
{
    std::string input;

    std::getline(std::cin, input);
    StateMachine sm(input);
    if (!std::cin.fail() && sm.build()) {
        auto const &tokens = sm.generate();
        for (auto &v : tokens) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
}