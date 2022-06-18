#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include "pgm.h"

/* PGM dosyasinin baslik bilgilerini ekrana yazdiran fonksiyon */
void pgm_print_header(PGMInfo pgm_info)
{
    printf("This is a %s type PGM image containing %d x %d pixels\n",
           pgm_info.signature,
           pgm_info.width,
           pgm_info.height);
}

PGMInfo pgm_read(const char *filename)
{
    /* Bu fonksiyon filename stringi ile verilen dosyayi fopen()
     * ile read kipinde acmali ve PGM dosyasinin basligini ve
     * piksellerini PGMInfo turunden bir struct'a atmalidir.
     *
     * Fonksiyon geriye bu struct'i dondurmelidir.
     */

    /* PGMInfo turunden bir degisken yaratip, error uyesini 0 yaptik. */
    PGMInfo pgm_info = {.error = 0};

    /* Dosyadaki satirlari okumak icin bir tampon. */
    char line[LINE_MAX];
    int i = 0;
    int read = 0;

    
    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        pgm_info.error = PGM_ERROR_READ;
        return pgm_info;
    }

   
    fscanf(f, "%s\n", line);
    strcpy(pgm_info.signature, line);
    if (strcmp(line, "P2") != 0 || strcmp(line, "P5") != 0)
    {
        fclose(f);
        pgm_info.error = PGM_ERROR_SIGNATURE;
        return pgm_info;
    }
    /* Comment satirini oku. */
    fscanf(f, "%s\n", pgm_info.comment);

   
    fscanf(f, "%d %d\n", &pgm_info.width, &pgm_info.height);
    /* Max piksel degerini oku */
    fscanf(f, "%d\n", &pgm_info.max_pixel_value);
    
     * Bir piksel bellekte 1 bayt yer istiyor, unutmayalim. */
    pgm_info.pixels = malloc(pgm_info.width * pgm_info.height);

 
     * PGM_ERROR_MALLOC yapip fonksiyonu sonlandirin.*/
    if (pgm_info.pixels == NULL)
    {
        fclose(f);
        pgm_info.error = PGM_ERROR_MALLOC;
        return pgm_info;
    }
    /* 2 farkli dosya bicimi, 2 farkli okuma bicimi.
     * P2 yani ASCII olanda dosyayi fgets() ile satir satir okuyoruz.
     * Okudugumuz satirin sonundaki '\n' karakterini kaldiriyoruz
     * ve elimizde kalan string'i atoi() ile sayiya cevirip pixels
     * dizisine kaydediyoruz.
     *
     * P5 yani binary olanda ise dogrudan fread() ile bir kerede pixels'in icerisine
     * okuma yapiyoruz.
     */
    if (strcmp(pgm_info.signature, "P2") == 0)
    {
        while (!feof(f))
        {
            fscanf(f, "%d\n", &pgm_info.pixels[i]);
            i++;
        }
    }
    read = i;
    if (strcmp(pgm_info.signature, "P5") == 0)
    {
        fread(pgm_info.pixels, (pgm_info.width * pgm_info.height), 1, f);
    }

    /* Eger dogru okuma yapamadiysaniz programiniz assert() sayesinde
     * yarida kesilecek. */
    printf("Read %d bytes. (Should be: %d)\n", read, pgm_info.width * pgm_info.height);
    assert(read == (pgm_info.width * pgm_info.height));

    fclose(f);
    return pgm_info;
}

int pgm_write(const char *filename, PGMInfo pgm_info)
{
    /* Bu fonksiyon filename stringiyle verilen dosyayi write kipinde acarak
     * pgm_info'nun icindeki baslik ve piksel bilgilerini dosyaya yazar.
     * Boylece yeni bir PGM resim dosyasi diske kaydedilmis olur.
     *
     * Fonksiyon herhangi bir hatada 1, basari durumunda 0 dondurmelidir.
     */

    int i = 0;
    FILE *pgm;

    
    pgm = fopen(filename, "w");
    if (pgm == NULL)
    {
        return 1;
    }

    
    fprintf(pgm, "%s\n", pgm_info.signature);
    fprintf(pgm, "%s\n", pgm_info.comment);
    fprintf(pgm, "%d %d\n", pgm_info.width, pgm_info.height);
    fprintf(pgm, "%d\n", pgm_info.max_pixel_value);

    
    if (strcmp(pgm_info.signature, "P2") == 0)
    {
        while (pgm_info.pixels[i] != '\0')
        {
            fprintf(pgm, "%d\n", pgm_info.pixels[i]);
            i++;
        }
    }
    if (strcmp(pgm_info.signature, "P5") == 0)
    {
        fwrite(pgm_info.pixels, (pgm_info.width * pgm_info.height), 1, pgm);
    }
    /* Dosyayi kapatalim. */
    fclose(pgm);
    return 0;
}
