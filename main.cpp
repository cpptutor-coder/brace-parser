#include "state_machine.h"
#include <iostream>

int main(int argc, char* argv[])
{
    std::string input;
    // VIK_TODO: Maybe do error checking for getline
    std::getline(std::cin, input);
    //std::cout << "Processing input: " << input << std::endl;
    StateMachine sm;

    // VIK_TODO: Do sanity check probably in the build
    //if (is_input_valid(input) && sm.build(input)) {
    if (sm.build(input)) {
        auto const &tokens = sm.generate();
        for (auto &v : tokens) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    /*
    else {
        std::cout << "\"" << input << "\" is not valid" << std::endl;
    }
    */

}

// Nice to have give the index of the invalid character
// Initially when checking the string, output what are the valid characters
// Find better way to send alpha