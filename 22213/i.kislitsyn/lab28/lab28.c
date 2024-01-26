#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <unistd.h>

int main() {
    int nums[100];
    FILE *fptrs[2];
    srand((unsigned int)getpid());
    for (int i = 0; i < 100; i++)
    {
        nums[i] = rand() % 100;
    }

    p2open("/bin/sort", fptrs);
    char str[4];
    for (int i = 0; i < 100; i++)
    {
        sprintf(str, "%d", nums[i]);
        fputs(str, fptrs[0]);
    }
    fclose(fptrs[0]);

    for (int i = 0; i < 100; i++)
    {
        fgets(str, 3, fptrs[1]);
        printf("%s ", str);
    }
}