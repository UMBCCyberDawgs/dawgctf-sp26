/*gcc -fno-stack-protector -no-pie -z execstack -g -Wno-implicit-function-declaration in.c -o out*/

#include <stdio.h>
#include <stdlib.h>

void win() {
    FILE *fp;
    char flag[128];

    fp = fopen("flag.txt", "r");
    
    if (!fp) {
        puts("Could not open flag file.");
        fflush(stdout);
        exit(1);
    }
    
    fgets(flag, sizeof(flag), fp);
    puts(flag);
    fflush(stdout);
    fclose(fp);
    exit(0);
}

void vulnerable_function() {
    char buffer[64];
    gets(buffer);
}

int main() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setbuf(stderr, NULL);

    fflush(stdout);

    vulnerable_function();
    printf("win() is at: %p\n", win);
    printf("Better luck next time!\n");
    return 0;
}
