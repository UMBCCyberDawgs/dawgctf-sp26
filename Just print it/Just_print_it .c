/*gcc -fno-stack-protector -no-pie -z execstack -g -Wno-implicit-function-declaration in.c -o out*/
#include <stdio.h>
#include <stdlib.h>

void win() {
    FILE *fp;
    char flag[128];

    fp = fopen("flag.txt", "r");
    if (!fp) {
        puts("Error opening flag file.");
        fflush(stdout);
        exit(1);
    }

    fgets(flag, sizeof(flag), fp);
    printf("Flag: %s\n", flag);

    fflush(stdout);
    fclose(fp);
    exit(0);
}

int main() {
    char buffer[128];

    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setbuf(stderr, NULL);

    fflush(stdout);

    fgets(buffer, sizeof(buffer), stdin);

    printf(buffer);
    puts("\nGoodbye!");
    return 0;
}
