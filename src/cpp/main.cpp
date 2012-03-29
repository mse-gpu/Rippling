#include <iostream>
#include <limits.h>

#include "omp.h"

#include "Rippling.hpp"
#include "RipplingSequential.hpp"
#include "RipplingOMP.hpp"

int launchApplication();
int launchApplicationOMP();

int main(void){
    //return launchApplication();
    return  launchApplicationOMP();
}

void display(RipplingImage* image);

int launchApplicationOMP(){
    omp_set_num_threads(THREADS);

    std::cout << "Launch the application with OMP" << std::endl;

    int dim = 600;
    DomaineMaths domain(0, 0, dim, dim);
    display(new RipplingImageOMP(dim, dim, domain));

    return 0;
}

int launchApplication(){
    std::cout << "Launch the application" << std::endl;

    int dim = 600;
    DomaineMaths domain(0, 0, dim, dim);
    display(new RipplingImageSequential(dim, dim, domain));

    return 0;
}

void display(RipplingImage* image){
    char** argv = NULL;
    GLUTWindowManagers::init(0, argv);

    RipplingGLImage* glImage = new RipplingGLImage(image);

    GLUTWindowManagers* windowManager = GLUTWindowManagers::getInstance();
    windowManager->createWindow(glImage);
    windowManager->runALL(); //This call is blocking

    delete image;
    delete glImage;
}
