#include <assert.h>

int main() {
    int a, b, c;
    a = 30, b = 20, c = 10;
    int result;
    if (a <= b) {
        if (a <= c) {
            result = a;
        } else {
            result = c;
        }
    } else {
        if (b <= c) {
            result = b;
        } else {
            result = c;
        }
    }
    assert(result == 10);
    return 0;
}