//
//  cmdline.cpp
//  MSDscriptCommandLine
//
//  Created by Koffi Danhounsrou on 1/14/24.
//

#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include "cmdline.hpp"
#include <iostream>
#include <cstring>
#include <cstdlib>



// use_arguments function
void use_arguments(int argc, char *argv[]) {
    static bool hasTestArgumentSeen = false;
    static bool isTestArgumentTrue = true;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--help") == 0) {
            std::cout << "Here are existing arguments: \n";
            std::cout << "--test : run the testing program of the system. \n";
            std::cout << "--run : run the program. \n";
            std::cout << "--docs : for more check the documentation. \n";
            std::cout << "--exit : exit the program. \n";
            ;
        } else if (isTestArgumentTrue && strcmp(argv[i], "--test") == 0) {
            // Check if "--test" has been called before
            if (!hasTestArgumentSeen && (Catch::Session().run(1, argv) ==0) ) {
                std::cout << "Tests passed. \n";
                hasTestArgumentSeen = true;
//                exit(1);
            } else {
                std::cerr << "Error: '--test' argument already seen.\n";
                isTestArgumentTrue = false;
                exit(0);
            }
        } else {
            std::cerr << "Invalid or missing argument. Use '--help' for assistance.\n";
            exit(1);
        }
    }
}
