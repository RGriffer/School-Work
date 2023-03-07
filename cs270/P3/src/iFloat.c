#include "Debug.h"
#include "iFloat.h"

/** @file iFloat.c
 *  @brief You will modify this file and implement nine functions
 *  @details Your implementation of the functions defined in iFloat.h.
 *  You may add other function if you find it helpful. Added function
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 *  <p>
 *  @author <b>Your name</b> goes here
 */

/* declaration for useful function contained in testFloat.c */
const char* getBinary (iFloat_t value);

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetSign (iFloat_t x) {
  return (x>>EXP_BIAS)&1;; /* implement this */
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetExp (iFloat_t x) {
    x=x>>BITS_MANT;
         debug("\nAfter:  %s\n",getBinary(x));
    return x & ((1<<BITS_EXP)-1); /* implement this */
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetVal (iFloat_t x) {
    int s = floatGetSign(x);
    debug("SIGN:%d\nBIN OF X: %s\n",s,getBinary(x));
    if(s){
        return ~((x&((1<<(BITS_MANT))-1))|(1<<BITS_MANT))+1;
    }
    else{
        return (x&((1<<(BITS_MANT))-1))|(1<<BITS_MANT);
    }
}

/** @todo Implement based on documentation contained in iFloat.h */
void floatGetAll(iFloat_t x, iFloat_t* sign, iFloat_t*exp, iFloat_t* val) {
    *sign=floatGetSign(x);
    *exp=floatGetExp(x);
    *val=floatGetVal(x);
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatLeftMost1 (iFloat_t bits) {
    if(bits==0) return -1;
    if(bits<0) return BITS-1;
    if (bits>1){
        bits=bits>>1;
        return 1+floatLeftMost1(bits);
    }
    return 0;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAbs (iFloat_t x) {
    debug("before: %s\n",getBinary(x));
    int mask=(1<<(BITS-1))-1;
    x=x&mask;
    debug("after:  %s\n",getBinary(x));
    return x;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatNegate (iFloat_t x) {
    debug("before: %s\n",getBinary(x));
    if(x&0){
        return x;
    }
    int sign=floatGetSign(x);
    if(sign){
        x=floatAbs(x);
    }else{
        int mask=(1<<(BITS-1));
        debug("mask:   %s\n",getBinary(mask));
        x=x|mask;
    }
    return x;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAdd (iFloat_t x, iFloat_t y) {
  //step1
    debug("%s: bits of x (IEEE 754)", getBinary(x)); // example only
    debug("%s: bits of y (IEEE 754)", getBinary(y)); // example only
    iFloat_t signX, signY, expX, expY, valX, valY;
    floatGetAll(x,&signX,&expX,&valX);
    floatGetAll(y,&signY,&expY,&valY);
    debug("value of y first time: %s",getBinary(valY));
    debug("----step1");
    debug("expX: %s  %s",getBinary(expX),getBinary(expY));
    debug("expY: %s",getBinary(expY));
    debug("valX: %s    ",getBinary(valX));
    debug("valY: %s",getBinary(valY));
    
    //step2
    debug("\n----step2");
    int dif;
    int expR;
    if(expX>expY){
        dif=expX-expY;
        valY=valY>>dif;
        expY=expY+dif;
        expR=expX;
    }
    if(expY>expX){
        dif=expY-expX;
        valX=valX>>dif;
        expX=expX+dif;
        expR=expY;
    }
    else{
        expR=expY;
    }
    debug("expR: %s",getBinary(expR));
    debug("Value of X: %s", getBinary(valX));
    debug("Value of Y: %s", getBinary(valY));
    
    //step3
    int valR=valX+valY;
    debug("----step3");
    debug("valR: %s",getBinary(valR));
    debug("valR: %s",getBinary(valR));
    
    //step4
    debug("----step4");
    int magR;
    int signR=floatGetSign(valR);
    if(valR<0){
        magR=~valR+1;
    }else{
        magR=valR;
    }
    debug("magR BEFORE: %s",getBinary(magR));
    
    //step5
    debug("----step5");
    int lm1 = floatLeftMost1(magR);
    int lmdif = lm1-BITS_MANT;
    debug("LEFTMOST1: %d,     Difference from Bits_mant:%d = %d",lm1,BITS_MANT,lmdif);
    debug("expR BEFORE: %s",getBinary(expR));
    if(lmdif<0){
        lmdif=lmdif*-1;
        magR=magR<<lmdif;
        expR=expR-lmdif;
    }
    else if(lmdif>0){
        magR=magR>>lmdif;
        expR=expR+lmdif;
    }
    debug("signR: %d",signR);
    debug("expR: %s",getBinary(expR));
    debug("magR AFTER: %s",getBinary(magR));
    magR=magR&((1<<BITS_MANT)-1);
    debug("magR: %s",getBinary(magR));
    debug("signR: %d",signR);
    return (signR<<(BITS-1))+(expR<<BITS_MANT)+(magR);
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatSub (iFloat_t x, iFloat_t y) {
    return floatAdd(x,floatNegate(y));
}
