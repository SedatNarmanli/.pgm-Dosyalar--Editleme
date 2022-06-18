#include "effects.h"

void effect_random_noise(unsigned char *pixels, int width, int height)
{
    int nr_noisy_pixel = (width * height) / 5; // %5 oraninda noise ekle
    int i;

    for (i = 0; i < nr_noisy_pixel; ++i)
    {
        int which_pixel = (rand() % (width * height));
        pixels[which_pixel] = (rand() % 256);
    }
}


void effect_invert(unsigned char *pixels, int width, int height)
{
    int i;
    for (i = 0; i < width * height; i++)
    {
        pixels[i] = 255 - pixels[i];
    }
}


void effect_threshold(unsigned char *pixels, int width, int height, int threshold)
{
    int i;
    for (i = 0; i < width * height; i++)
    {
        if (pixels[i] < threshold)
        {
            pixels[i] = 0;
        }
        else
        {
            pixels[i] = 255;
        }
    }
}

/* 
 * Bu fonksiyon fotograf kontrastini arttirir.
 */
void effect_contrast(unsigned char *pixels, int width, int height)
{
    int i;
    int grey = 127;
    for (i = 0; i < width * height; i++)
    {
        if (pixels[i] > grey)
        {
            pixels[i] -= 30;
        }
    }
}

/* 
 * Bu fonksiyon belli piksel araligindaki renkleri grilestirir. 
 */
void effect_grey(unsigned char *pixels, int width, int height)
{
    int i;

    for (i = 0; i < width * height; i++)
    {
        if (pixels[i] < 70)
        {
            pixels[i] += 30;
        }
        if (pixels[i] > 184)
        {
            pixels[i] -= 30;
        }
    }
}
