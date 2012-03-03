#include <iostream>
#include <cmath> //for sin
#include "omp.h"

#include "DomaineMaths.h"
#include "GLUTWindowManagers.h"
#include "ImageFonctionelSelectionMOOs.h"
#include "GLImageFonctionelSelections.h"
#include "CalibreurCudas.h"

class RiplingFunctionalImage : public ImageFonctionelSelectionMOOs {
    public:
	RiplingFunctionalImage(int m, int n, DomaineMaths domain);

	void setT(float t);

    protected:
	void onDomaineChangePerformed(const DomaineMaths& domainNew);

    private:
	float color(float x, float y);
	float d(float x, float y);

	void refreshAll(const DomaineMaths& domainNew);

	void findMinMax();

	float fMin;
	float fMax;
	float hueMin;
	float hueMax;
	float t;

	CalibreurCudas* calibreur;
};

RiplingFunctionalImage::RiplingFunctionalImage(int m, int n, DomaineMaths domain) : ImageFonctionelSelectionMOOs(m,n,domain), t(1) {
    //findMinMax();

    hueMin = 0.7;
    hueMax = 0;

    //calibreur = new CalibreurCudas(fMin, fMax, hueMin, hueMax);
    onDomaineChangePerformed(domain);
}

void RiplingFunctionalImage::setT(float newT){
    t = newT;

    std::cout << "Changed t to " << t << std::endl;

    refreshAll(getCurrentDomaine());
}

void RiplingFunctionalImage::refreshAll(const DomaineMaths& domainNew){
    std::cout << "refresh all" << std::endl;

    int w = getW();
    int h = getH();

    float dx = (float) (domainNew.dx / (float) w);
        float dy = (float) (domainNew.dy / (float) h);
        float y = domainNew.y0;

        for(int i = 1; i <= h; ++i){
    	float x = domainNew.x0;

    	for(int j = 1; j <= w; ++j){
    	    float c = color(x,y);

    	    //TODO Verify if neccessary to use the calibration
    	    setRGBA(i, j, c, c, c);

    	    x += dx;
    	}

    	y += dy;
    }
}

void RiplingFunctionalImage::onDomaineChangePerformed(const DomaineMaths& domainNew){
    refreshAll(domainNew);
}

float RiplingFunctionalImage::color(float x, float y){
    float p1 = cos(d(x,y) / (float)10 -(t / (float)7));
    float p2 = d(x,y) / 10 + 1;
    float mul = p1 / p2;
    return 128 + 127 * mul;
}

float RiplingFunctionalImage::d(float x, float y){
    float fx = x - getW() / (float) 2;
    float fy = y - getH() / (float) 2;

    return sqrt(fx * fx + fy * fy);
}

void RiplingFunctionalImage::findMinMax(){
    int w = getW();
    int h = getH();

    DomaineMaths currentDomain = getCurrentDomaine();
    float dx = (float) (currentDomain.dx / (float) w);
    float dy = (float) (currentDomain.dy / (float) h);

    fMin = color(currentDomain.x0, currentDomain.y0);
    fMax = fMin;

    float y = currentDomain.y0;

    for(unsigned int i = 0; i <= getH(); ++i){
	float x = currentDomain.x0;

	for(unsigned int j = 0; j <= getW(); ++j){
	    float z = color(x, y);
	    fMin = std::min(z, fMin);
	    fMax = std::max(z, fMax);
	    x += dx;
	}

	y += dy;
    }
}

class RiplingGLImage : public GLImageFonctionelSelections {
    public:
	RiplingGLImage(RiplingFunctionalImage *ptrImageFonctionel);

    private:
	float t;
	float dt;

	void idleFunc();

	RiplingFunctionalImage* image;
};

RiplingGLImage::RiplingGLImage(RiplingFunctionalImage *ptrImageFonctionel) : GLImageFonctionelSelections(ptrImageFonctionel), image(ptrImageFonctionel) {
    t = 1;

    float PI = atan(1) * 4;

    dt = 2 * PI / (float) 360;
}

void RiplingGLImage::idleFunc(){
    t += dt;
    image->setT(t);
    updateView();
}

extern int launchApplication(){
    std::cout << "Launch the application" << std::endl;

    char** argv = NULL;
    GLUTWindowManagers::init(0, argv);

    float xMin = -5;
    float xMax = +5;
    float yMin = -5;
    float yMax = +5;

    DomaineMaths domain(xMin, yMin, xMax - xMin, yMax - yMin);
   
    int w = 800;
    int h = 800;

    RiplingFunctionalImage* functionalImage = new RiplingFunctionalImage(w,h,domain);
    RiplingGLImage* functionSelections = new RiplingGLImage(functionalImage);

    GLUTWindowManagers* windowManager = GLUTWindowManagers::getInstance();
    windowManager->createWindow(functionSelections);
    windowManager->runALL(); //This call is blocking

    return 0;
}
