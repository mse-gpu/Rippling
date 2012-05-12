#include <iostream>
#include <limits.h>
#include <math.h>

#include "omp.h"

#include "ChronoOMPs.h"

#include "Rippling.hpp"
#include "RipplingSequential.hpp"
#include "RipplingOMP.hpp"

#define DIM 600

int launchApplication();
int launchApplicationOMP();
int bench();

int main(void){
    //return launchApplication();
    //return  launchApplicationOMP();
    return bench();
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

#define DIM_H 25000
#define DIM_W 25000
#define TIMES 25

#define THREADS 24

struct rgba {
	int r;
	int g;
	int b;
	int a;
};

void setFloatRGBA(rgba* image, int i, int j, int r, int g, int b, int a){
    image[i * (DIM_H) + j].r = r;
    image[i * (DIM_H) + j].g = g;
    image[i * (DIM_H) + j].b = b;
    image[i * (DIM_H) + j].a = a;
}

float d(float x, float y){
    float fx = x - (DIM_W / 2);
    float fy = y - (DIM_H / 2);

    return sqrt(fx * fx + fy * fy);
}

float color(float x, float y, int t){
    return 128 + 127 * ((cos(d(x,y) / (float)10 -(t / (float)7))) / (d(x,y) / 10 + 1));
}

inline void benchSequential(rgba* image){
    DomaineMaths domain(0, 0, DIM_W, DIM_H);

    float dx = (float) (domain.dx / (float) DIM_W);
    float dy = (float) (domain.dy / (float) DIM_H);
    float y = domain.y0;

    float t = 1;

    for(int i = 1; i <= DIM_W; ++i){
	float x = domain.x0;

	for(int j = 1; j <= DIM_H; ++j){
	    float c = color(x,y,t);

	    x += dx;
	}

	y += dy;
    }
}

inline void benchParallel(rgba* image){
    DomaineMaths domain(0, 0, DIM_W, DIM_H);

    const float dx = (float) (domain.dx / (float) DIM_W);
    const float dy = (float) (domain.dy / (float) DIM_H);

    float t = 1;

    #pragma omp parallel
    {
	int tid = omp_get_thread_num();
	int i = tid + 1;

	float y = domain.y0 + tid * dy;

	while(i <= DIM_W){
	    float x = domain.x0;

	    for(int j = 1; j <= DIM_H; ++j){
		float c = color(x,y,t);

		x += dx;
	    }

	    y += THREADS * dy;

	    i += THREADS;
	}
    }
}

int bench(){
    std::cout << "Launch the Rippling benchmark" << std::endl;

    rgba* image = (rgba*) calloc(sizeof(rgba),  (DIM_H + 1) * (DIM_W + 1));

    ChronoOMPs chronos;
    chronos.start();

    for(int i = 0; i < TIMES; ++i){
	benchSequential(image);
    }

    double timeSequential = chronos.timeElapse();
    std::cout << "Sequential Total (" << TIMES << " times) " << timeSequential << "s" << std::endl;
    std::cout << "Sequential Mean  (" << TIMES << " times) " << (timeSequential / TIMES) << "s" << std::endl;

    chronos.start();

    for(int i = 0; i < TIMES; ++i){
	benchParallel(image);
    }

    double timeParallel = chronos.timeElapse();
    std::cout << "OMP Total (" << TIMES << " times) " << timeParallel << "s" << std::endl;
    std::cout << "OMP Mean  (" << TIMES << " times) " << (timeParallel / TIMES) << "s" << std::endl;

    std::cout << "Factor=" << (timeSequential / timeParallel) << std::endl;

    free(image);

    return 0;
}
