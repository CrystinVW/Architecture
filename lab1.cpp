#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#define ARRAY_MIN (1024)
#define ARRAY_MAX (4096*4096)
int x[ARRAY_MAX];

double get_seconds() {
    __time64_t ltime;
    _time64( &ltime );
    return (double) ltime;

}
int lab(int i) {
    if (i < 1e3) printf("%1dB,",i);
    else if (i <1e6) printf("%1dk,",i/1024);
    else if (i<1e9) printf("%1dM,",i/1048576);
    else printf("%1dG,",i/1073741824);
    return 0;
}
int _tmain(int argc, _TCHAR* argv[]) {
    int register nextstep, i , index, stride;
    int csize;
    double steps, tsteps;
    double loadtime, lastsec, sec0, sec1, sec;

    /* Inistialize output */
    printf(" ,");
    for (stride=1; stride <= ARRAY_MAX; csize=csize*2) {
        label(csize* sizeof(int));
        for (stride=1; stride <= csize/2; stride=stride*2) {
            for(index=0; index < csize; index=index+stride)
                x[index] = index + stride;
            x[index-stride] = 0;

            lastsec = get_seconds();
            sec0 = get_seconds(); while (sec0 == lastsec);

            steps = 0.0;
            nextstep = 0;
            sec0 = get_seconds();
            {
                (i=stride; i!=0; i=i-1) {
                    nextstep = 0;
                    do nextstep = x[nextstep];
                    while (nextstep != 0);

                }
                steps = steps + 1.0;
                sec1 = get_seconds();

            } while ((sec1 - sec0) < 20.0);
            sec = sec1 - sec0;

            tsteps = 0.0;
            sec0 = get_seconds();
            {
                (i=stride; i!=0; i = i-1) {
                    index = 0;
                    do index = index + stride;
                    while (index < csize);
                }
                tsteps = tsteps + 1.0;
                sec1 = get_seconds();
            } while (tsteps<steps);
            sec = sec - (sec1 - sec0);
            loadtime = (sec*1e9)/(steps*csize);
            printf("%4.1f,", (loadtime<0.1) ? 0.1 : loadtime);

        };
        printf("\n");

    };
    return 0;
}
