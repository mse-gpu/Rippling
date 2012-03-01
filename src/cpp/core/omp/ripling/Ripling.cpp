#include <iostream>
#include "omp.h"

extern int launchApplication(){
    std::cout << "Launch the application" << std::endl;

    return 0;
}
