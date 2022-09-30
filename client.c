#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include <time.h>

// include header file
#include "server.h"

int main()
{
    printf("hey there, welcome to Mastermind game");
    mastermind();
    return 0;
}