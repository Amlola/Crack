#include "../include/crack.h"

int main()
    {
    FILE* comFile = fopen("Break1.COM", "r+b");

    PatchFile(comFile);

    fclose(comFile);

    txPlaySound("eminem.wav");

    VideoPatch();

    return 0;
    }