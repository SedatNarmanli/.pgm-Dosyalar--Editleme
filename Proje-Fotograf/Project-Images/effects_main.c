#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Kendi baslik dosyalarimizi include ediyoruz */
#include "pgm.h"
#include "effects.h"

/* PROGRAMIN ORNEK KULLANIMI:
 *
 *      $ ./pgm_efekt
 *      Usage: ./pgm_efekt <invert|binarize|noise|smooth> <PGM image 1> <PGM image 2> ... <PGM image N>
 *
 *      $ ./pgm_efekt invert effect_images/man_ascii.pgm
 *      (Invert efekti uygulanan resim effect_images/man_ascii.pgm.invert olarak kaydedilir)
 */

int main(int argc, char *argv[])
{
   
    if (argc < 3)
    {
        printf("Usage: %s <invert|binarize|noise|contrast|grey> <PGM image 1> <PGM image 2> ... <PGM image N>\n", argv[0]);
        return 1;
    }
    int i;
    /* Komut satirindan gelen efekt adi */
    char *effect_name = argv[1];

  
    int threshold = rand() % 255;
    /* argv[0]:     Programin adi
     * argv[1]:     Efekt cesidi: invert, binarize, noise, smooth
     * argv[2] ...  argv[argc-1]: Dosya adi veya adlari
     */

    /* Butun argumanlari gez. Her biri bir resim dosyasi adi */
    /* TODO: PGM dosyasini oku */
    /* Hata olduysa ekrana hata mesajini yazdir */
    /* Hata yoksa resmin baslik bilgisini ekrana yazdir,
         * resme efekt uygula ve yeni dosyaya kaydet. */
    /* Yeni bir string olustur. Bu string efekt uygulanmis
             * dosyanin adini tutacaktir. */

    /* Hangi efekt istendiyse ilgili fonksiyon cagir*/
    PGMInfo pgm_info;
    char effectedPhoto[25];
    int return_val;
    if (strcmp(effect_name, "invert") == 0)
    {
        for (i = 2; i < argc; i++)
        {
            pgm_info = pgm_read(argv[i]);

            strcpy(effectedPhoto, argv[i]);
            strcat(effectedPhoto, ".invert");
            if (pgm_info.error != 0)
            {
                printf("%s\n", pgm_error_messages[pgm_info.error]);
            }
            else
            {
                pgm_print_header(pgm_info);
                effect_invert(pgm_info.pixels, pgm_info.width, pgm_info.height);

                return_val = pgm_write(effectedPhoto, pgm_info); //PGM dosyasi olusturulur
                if (return_val == 1)
                {
                    printf("PGM dosyasi olusturulurken hata meydana geldi.");
                }

                free(pgm_info.pixels);
            }
        }
    }
    else if (strcmp(effect_name, "binarize") == 0)
    {
        for (i = 2; i < argc; i++)
        {
            pgm_info = pgm_read(argv[i]);

            strcpy(effectedPhoto, argv[i]);
            strcat(effectedPhoto, ".binarize");
            if (pgm_info.error != 0)
            {
                printf("%s\n", pgm_error_messages[pgm_info.error]);
            }
            else
            {
                pgm_print_header(pgm_info);
                effect_threshold(pgm_info.pixels, pgm_info.width, pgm_info.height, threshold);

                return_val = pgm_write(effectedPhoto, pgm_info);
                if (return_val == 1)
                {
                    printf("PGM dosyasi olusturulurken hata meydana geldi.");
                }

                free(pgm_info.pixels);
            }
        }
    }
    else if (strcmp(effect_name, "noise") == 0)
    {
        for (i = 2; i < argc; i++)
        {
            pgm_info = pgm_read(argv[i]);

            strcpy(effectedPhoto, argv[i]);
            strcat(effectedPhoto, ".noise");
            if (pgm_info.error != 0)
            {
                printf("%s\n", pgm_error_messages[pgm_info.error]);
            }
            else
            {
                pgm_print_header(pgm_info);
                effect_random_noise(pgm_info.pixels, pgm_info.width, pgm_info.height);
                return_val = pgm_write(effectedPhoto, pgm_info);

                if (return_val == 1)
                {
                    printf("PGM dosyasi olusturulurken hata meydana geldi.");
                }

                free(pgm_info.pixels);
            }
        }
    }
    else if (strcmp(effect_name, "contrast") == 0)
    {
        for (i = 2; i < argc; i++)
        {
            pgm_info = pgm_read(argv[i]);

            strcpy(effectedPhoto, argv[i]);
            strcat(effectedPhoto, ".contrast");
            if (pgm_info.error != 0)
            {
                printf("%s\n", pgm_error_messages[pgm_info.error]);
            }
            else
            {
                pgm_print_header(pgm_info);
                effect_contrast(pgm_info.pixels, pgm_info.width, pgm_info.height);
                return_val = pgm_write(effectedPhoto, pgm_info);

                if (return_val == 1)
                {
                    printf("PGM dosyasi olusturulurken hata meydana geldi.");
                }

                free(pgm_info.pixels);
            }
        }
    }
    else if (strcmp(effect_name, "grey") == 0)
    {
        for (i = 2; i < argc; i++)
        {
            pgm_info = pgm_read(argv[i]);

            strcpy(effectedPhoto, argv[i]);
            strcat(effectedPhoto, ".grey");
            if (pgm_info.error != 0)
            {
                printf("%s\n", pgm_error_messages[pgm_info.error]);
            }
            else
            {
                pgm_print_header(pgm_info);
                effect_grey(pgm_info.pixels, pgm_info.width, pgm_info.height);
                return_val = pgm_write(effectedPhoto, pgm_info);

                if (return_val == 1)
                {
                    printf("PGM dosyasi olusturulurken hata meydana geldi.");
                }

                free(pgm_info.pixels);
            }
        }
    }

    

    return 0;
}
