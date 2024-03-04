#include "../include/crack.h"


void PatchFile(FILE* file) 
    {
    char nope_buffer[] = {0x90, 0x90};                 

    size_t offset = 82;

    fseek(file, offset, SEEK_SET);

    fwrite(nope_buffer, sizeof(char), 2, file);

    offset = 88;

    fseek(file, offset, SEEK_SET);

    fwrite(nope_buffer, sizeof(char), 2, file);

    return;
    }


void VideoPatch() 
    {
    txCreateWindow(800, 600);

    txSetColor(TX_BLACK);

    txSetFillColor(TX_WHITE);

    char* image_name[9] = {"img/picture1.bmp", "img/picture2.bmp", "img/picture3.bmp", "img/picture4.bmp", "img/picture5.bmp",
                          "img/picture6.bmp", "img/picture7.bmp", "img/picture8.bmp", "img/picture9.bmp"};

    HDC images[9] = {0};

    for (size_t i = 0; i < 9; i++) 
        {
        images[i] = txLoadImage(image_name[i], 800, 600);
        }

    int delta_x = 5;

    int x_start = 0;

    HDC save = txCreateCompatibleDC(400, 20);

    txSetFillColor (TX_WHITE, save);

    txRectangle(0, 0, 400, 20, save);

    txSetFillColor (TX_LIGHTGREEN, save);

    size_t num_pict = 0;

    size_t str_num = 0;

    for (size_t i = 0; i < 80; i++)
        {      
        if (i % 9 == 0) 
            {
            txBitBlt(txDC(), 0, 0, 0, 0, images[num_pict]);

            txDeleteDC(images[num_pict]);

            num_pict++;
            }     

        if (i % 3 == 0) 
            {
            txRectangle(250, 470, 550, 490);

            txDrawText(300, 470, 500, 490, PHRAZES[str_num]);

            str_num++;
            }     

        txRectangle(x_start, 0, x_start + delta_x, 20, save);

        txBitBlt(txDC(), 200, 450, 0, 0, save);

        x_start += delta_x;

        if (i == 79) 
            txSleep(500);

        else
            txSleep(1000);
        }

    txSetFillColor(TX_BLUE);
    txClear();

    txSelectFont("Arial", 80);

    txSetFillColor(TX_WHITE);

    txRectangle(200, 100, 600, 500);

    txDrawText(200, 100, 600, 500, "SUCCESS!!!");

    txDeleteDC(save);
    }