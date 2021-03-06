#include "miracl.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

char *ecp="FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFF";

char *ecb="64210519E59C80E70FA7E9AB72243049FEB8DEECC146B9B1";
char *ecx="188DA80EB03090F67CBF20EB43A18800F4FF0AFD82FF1012";
char *ecy="07192B95FFC8DA78631011ED6B24CDD573F977A11E794811";

int main(int argc, char const *argv[])
{
    int tmp;
    srand(time(NULL));
    long seed = rand()%100;
    miracl *mip=mirsys(500,0);
    int PKj_D = -1;
    epoint *g,*PKj,*test;
    big ai,skj;
    big a,b,p,x,y;
    irand(seed);
    int driveLicense;
    a=mirvar(0);
    b=mirvar(0);
    p=mirvar(0);
    x=mirvar(0);
    y=mirvar(0);
    skj=mirvar(0);
    ai=mirvar(0);
    mip->IOBASE=16;
    convert(-3,a);
    cinstr(b,ecb);
    cinstr(x,ecx);
    cinstr(y,ecy);
    cinstr(p,ecp);
    bigdig(40,16,skj);

    //  y2 = x3 + Ax + B (mod p) 의형태로 진행
    ecurve_init(a,b,p,MR_BEST);
    g=epoint_init();
    PKj=epoint_init();
    test=epoint_init();
    bigdig(40,16,skj);
    epoint_set(x,y,0,g);

    ecurve_mult(skj,g,PKj);
    PKj_D=epoint_get(PKj,x,x);
    // printf("SKj : ");
    cotnum(skj,stdout);
    // printf("PKj : ");
    cotnum(x,stdout);
    // printf("PKj_D : %d\n",PKj_D);
    printf("%d",PKj_D);
    // cotnum(y,stdout);

    
    return 0;
}
