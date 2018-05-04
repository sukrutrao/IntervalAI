#include <assert.h>

int main() {
    int n = 3;
    int result = 0;
    if (n == (n / 2) * 2) {
        for (int i = 0; i < n; i++) {
            result += i;
        }
    } else {
        for (int i = 0; i < n; i++) {
            result -= i;
        }
    }
    assert(result == -3);
    return 0;
}