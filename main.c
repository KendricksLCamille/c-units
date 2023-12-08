//
// Created by kendricks on 12/7/23.
//

#include "units.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Hello, World!\n");
    int name = 10;
    const typeof(name) d = 14;
    printf("%d", d);
    return 0;
}
