#include <iostream>
#include <limits.h>

#include "omp.h"

#include "Rippling.hpp"
#include "RipplingSequential.hpp"
#include "RipplingOMP.hpp"

int launchApplication();
int launchApplicationOMP();

int main(void){
    //int code = launchApplication();
    int code = launchApplicationOMP();

    return code;
}

int launchApplicationOMP(){
    omp_set_num_threads(THREADS);

    std::cout << "Launch the application with OMP" << std::endl;

    char** argv = NULL;
    GLUTWindowManagers::init(0, argv);

    int dim = 600;

    DomaineMaths domain(0, 0, dim, dim);

    RipplingImageOMP* functionalImage = new RipplingImageOMP(dim, dim, domain);
    RipplingGLImage* functionSelections = new RipplingGLImage(functionalImage);

    GLUTWindowManagers* windowManager = GLUTWindowManagers::getInstance();
    windowManager->createWindow(functionSelections);
    windowManager->runALL(); //This call is blocking

    return 0;
}

int launchApplication(){
    std::cout << "Launch the application" << std::endl;

    char** argv = NULL;
    GLUTWindowManagers::init(0, argv);

    int dim = 600;

    DomaineMaths domain(0, 0, dim, dim);

    RipplingImageSequential* functionalImage = new RipplingImageSequential(dim, dim, domain);
    RipplingGLImage* functionSelections = new RipplingGLImage(functionalImage);

    GLUTWindowManagers* windowManager = GLUTWindowManagers::getInstance();
    windowManager->createWindow(functionSelections);
    windowManager->runALL(); //This call is blocking

    return 0;
}
