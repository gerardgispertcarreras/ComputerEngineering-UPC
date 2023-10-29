#include <stdio.h>

int main(){
    long long int x,y,z;
    x = 665857;
    y = 470832;
    z = (x*x*x*x) - 4*(y*y*y*y) - 4*(y*y);
    printf("%lld\n", z);
}