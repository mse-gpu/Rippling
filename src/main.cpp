#include <iostream>
#include <limits.h>

extern int launchApplication(void);
extern int launchApplicationOMP(void);

int main(void){
    //int code = launchApplication();
    int code = launchApplicationOMP();

    return code;
}
