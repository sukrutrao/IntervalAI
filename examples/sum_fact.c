#include <assert.h>

int main() {
    int sum = 0;
    for (int i=1; i<=5; i++) {
        int prod = 1;
        for (int j=2; j<=i; j++) {
            prod *= j;
        }
        sum += prod;
    }
    assert(sum == 1 + 2 + 6 + 24 + 120);
    return 0;
}
