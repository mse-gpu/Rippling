#include <stdlib.h>
#include <iostream>

extern int launchApplication(void);

int mainCore(void);

int mainCore(void){
    int code = launchApplication();

    return code;
}
