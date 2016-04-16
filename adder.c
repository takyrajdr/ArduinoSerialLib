#include <stdio.h>
#include <limits.h>
#define MAX_NUMBER_LEN 10
#define bool short
#define True 1
#define False 0
bool addition_is_safe(uint32_t a, uint32_t b) {
    size_t a_bits=highestOneBitPosition(a), b_bits=highestOneBitPosition(b);
    return (a_bits<32 && b_bits<32);
}

int main(int argc, char const *argv[]){
	uint32_t A[MAX_NUMBER_LEN];
	uint32_t B[MAX_NUMBER_LEN];
	bool over;
	for (uint i = 0; i < MAX_NUMBER_LEN; ++i)
	{
		if(addition_is_safe(A[i],B[i]))
			over = False;
	}
	return 0;
}