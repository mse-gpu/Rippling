#include <iostream>
#include "omp.h"

#include "Domaines.h"

extern int launchApplication(){
    std::cout << "Launch the application" << std::endl;

    char* argv = NULL;
    GLUTWindowManagers::init(0, argv);

    float xMin = -5;
    float xMax = +5;
    float yMin = -5;
    float yMax = +5;

    Domaines domain(xMin, yMin, xMax - xMin, yMax - yMin);
   
    int w = 800;
    int h = 800;

    RiplingFunctionalImage* functionalImage = new RiplingFunctionalImage(w,h,domain);
    RiplingFunctionSelections* functionSelections = new RiplingFunctionSelections(functionImage);

    GLUTWindowManagers* windowManager = GLUTWindowManagers::getInstance();
    windowManager->createWindow(functionalImage);
    windowManager->runAll();


    return 0;
}
