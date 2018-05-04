#include <assert.h>

int main() {
    int a = -3, b = -1;
    int result;
    if (a <= b) {
        result = a;
    } else {
        result = b;
    }
    assert(result < b);
    return 0;
}