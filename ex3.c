#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    printf("CMD Arguments printing:\n");
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s.\n", i, argv[i]);
    }

    int index = 0;
    printf("Enviroment parameters printing:\n");

    while(envp[index] != NULL){
        printf("envp[%d] = %s.\n", index, envp[index]);
        index += 1;
    }

   return 0;
}
