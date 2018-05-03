int sum_(int n) {
    int sum = 0;
    for (int i=1; i<=n; i++) {
        sum += i;
    }
    for (int i=0; i<10; i++) {
        int j = 2 + 3;
    }
    return sum;
}

int main() {
    int sum = 0;
    int n = 10;
    sum = sum_(n);
    assert(sum == (n*(n+1))/2);
    return 0;
}
