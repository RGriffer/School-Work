#include "field.h"

/** @file field.c
 *  @brief You will modify this file and implement five functions
 *  @details Your implementation of the functions defined in field.h.
 *  You may add other function if you find it helpful. 
 * <p>
 * @author Ryan Griffin
 */

/** @todo Implement in field.c based on documentation contained in field.h */
int getBit (int value, int position) {
	/*int mask = 0x01;
	int bit = value >> position;
	bit = bit & mask;
	return bit; */
	return(value>>position)&0x01;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int setBit (int value, int position) {
	int mask = 0x01 << position;
	int bit = value | mask;
		
	return bit;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int clearBit (int value, int position) {
	int mask = 0x01 << position;
	int bit = ~mask & value;    
	return bit;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int getField (int value, int hi, int lo, bool isSigned) {
	//calculate length (number of bits in our field)
	//not base mask (000.....001)
	//left shift mask the length-1 of our field
	//not mask again	
	//shift value to match field and mask
	// and them together
	//check left most bit field if isSigned
	//if so make everything left of field 1 if leftmost bit of field is 1
	int mask = (1 << (hi - lo + 1)) -1;
		
	int desire = (value >> lo) & mask;
	if (isSigned && getBit(value, hi)) {
		desire = ~desire + 1;
	}
	return desire;
}


