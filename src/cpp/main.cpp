#include <iostream>
#include <limits.h>

#include "omp.h"

#include "Rippling.hpp"
#include "RipplingSequential.hpp"
#include "RipplingOMP.hpp"

#define DIM 600

int launchApplication();
int launchApplicationOMP();

int main(void){
    //return launchApplication();
    return  launchApplicationOMP();
}

void display(RipplingImage* image);

int launchApplicationOMP(){
    omp_set_num_threads(THREADS);

    std::cout << "Launch the OMP Rippling application" << std::endl;

    DomaineMaths domain(0, 0, DIM, DIM);
    display(new RipplingImageOMP(DIM, DIM, domain));

    return 0;
}

int launchApplication(){
    std::cout << "Launch the sequential Rippling application" << std::endl;

    DomaineMaths domain(0, 0, DIM, DIM);
    display(new RipplingImageSequential(DIM, DIM, domain));

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
