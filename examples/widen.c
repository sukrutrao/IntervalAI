#include <assert.h>

int main() {
	int n = 150;
	int i = 0;
	int sum = 0;
	while (1 == 1) {
		sum += i;
		if (i == n) {
			break;
		}
		i++;
	}
	assert(sum == (n*(n+1))/2);
	return 0;
}