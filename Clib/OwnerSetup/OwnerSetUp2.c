#include "miracl.h"
#include "setup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

char *ecp="FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFF";

char *ecb="64210519E59C80E70FA7E9AB72243049FEB8DEECC146B9B1";
char *ecx="3B5EFCFF203B1934E7CD717CD186AB00F79058E8831BDC73";

char *egx="188DA80EB03090F67CBF20EB43A18800F4FF0AFD82FF1012";
char *egy="07192B95FFC8DA78631011ED6B24CDD573F977A11E794811";

int main(int argc, char const *argv[]){
    // if(argc!=2){
    //     perror("argument is not found\n");
    //     return 0;
    // }
    srand(time(NULL));
    long seed = rand()%100;
    miracl *mip=mirsys(500,0);
    int PKta_D = -1, Rj_D= -1;
    big rj,CID,ID,hashing_result,Rj,zj,PKj;
    epoint *g,*PKTA, *tmpResult;
    big a,b,p,PKta,y,gx,gy,SKta;
    irand(seed);
    rj=mirvar(0);
    CID=mirvar(0);
    ID=mirvar(0);
    PKj=mirvar(0);
    //ECC 설정 
    a=mirvar(0);
    b=mirvar(0);
    p=mirvar(0);
    PKta=mirvar(0);
    SKta=mirvar(0);
    gx=mirvar(0);
    gy=mirvar(0);
    y=mirvar(0);
    zj=mirvar(0);
    Rj=mirvar(0);
    mip->IOBASE=16;
    // argv 값 넣어주기
    cinstr(PKj,"8FFBFDA5FCF8C72A230FDE4B49C310DA3DEB7D394CE85B3D");
    cinstr(PKta,"56F86E30F456E4296E7F3DA9AB16A262320A16001BCBED4E");
    PKta_D = 1;
    cinstr(SKta,"7B4FCDB11F9287782376A2C36B19A1CC5F8D0E0B");
    bytes_to_big(strlen("kimud6003"),"kimud6003",ID);

    //ECC 설정 
    convert(-3,a);
    cinstr(b,ecb);
    cinstr(gx,egx);
    cinstr(gy,egy);
    cinstr(p,ecp);

    ecurve_init(a,b,p,MR_BEST);
    g=epoint_init();
    tmpResult=epoint_init();
    PKTA=epoint_init();
    epoint_set(PKta,PKta,PKta_D,PKTA); //ECC 설정완료
    epoint_set(gx,gy,0,g); //ECC 설정완료

    bigdig(40,16,rj);
    ecurve_mult(rj,PKTA,tmpResult);
    epoint_get(tmpResult,y,y);
    CID=XOR(ID,hashing1(y));
    printf("CID : ");
    cotnum(CID,stdout);

    ecurve_mult(rj,g,tmpResult);
    Rj_D =epoint_get(tmpResult,Rj,Rj);
    printf("Rj : ");
    cotnum(Rj,stdout);
    printf("Rj_D : %d,\n",Rj_D);

    multiply(hashing1(concat(concat(CID,Rj),PKj)),SKta,zj);
    epoint_get(tmpResult,y,y);
    add(rj,y,zj);
    printf("zj : ");
    cotnum(zj,stdout);


    return 0;
}

