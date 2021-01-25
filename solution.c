#include <unistd.h>
#include <stdio.h>

int main(){
        printf("ID user started the program: %d\n", getuid());
        printf("ID user's group: %d\n", getgid());
        return 0;
}
