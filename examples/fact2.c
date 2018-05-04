#include <assert.h>

int main()
{
	int n = 10;
	int fact2 = 1;
	for (int i=n; i>=2; i--) {
		if (i == (i/2)*2) {
			fact2 *= i;
		}
	}
	assert(fact2 == 10*8*6*4*2);
	return 0;
}