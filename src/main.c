#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rezolvare_cerinte.h"

int main(int argc, char *argv[])
{
    if (!strcmp("-c1", argv[1]))
        rezolvare_cerinta1(argv[2], argv[3]);
    else if (!strcmp("-c2", argv[1]))
        rezolvare_cerinta2(argv[2], argv[3]);
    else if (!strcmp("-c3", argv[1]))
        rezolvare_cerinta3(argv[2], argv[3]);
    else
        printf("Cerinta nu a fost corect specificata.\n");

    return 0;
}
