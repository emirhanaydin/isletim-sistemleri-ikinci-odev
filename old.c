/**
* @file pro1.c
* @description Çatallama işleminin ve harici program çağrısının yapılacağı ana program.
* @course 2A
* @assignment 1
* @date 29.10.2016
* @authors 
 *Emirhan Aydın (g141210018@sakarya.edu.tr)
 *Mesut Sertaç Gün (g141210036@sakarya.edu.tr)
 *Abdullah Bahar (g141210090@sakarya.edu.tr)
*/

#include <stdio.h>
#include <unistd.h> // fork()
#include <sys/wait.h> // wait()

int main(int argc, char **argv) {
    pid_t pid;
    pid = fork(); // Çatallama işlemi yapılır ve oluşan çocuk işlemin pid'i değişkene atanır.
    if (pid == 0) // Çatallama başarılı
    {
        execl("./harici", sayi, (char *) 0);
    } else if (pid < 0) // Çatallama başarısız
    {
        printf("fork() basarisiz!\n");
        return 1;
    } else // Çatallamadan sonra ebeveyn işlem
    {
        int donusDurumu;
        wait(&donusDurumu); // Yavru işlem tamamlayıncaya kadar beklenir. Yavru işlemin dönüş değeri değişkene
//        aktarılır.

        if (donusDurumu == 0) // Yavru işlem hatasız bir şekilde sonlandıysa.
        {
            printf("[EBEVEYN] Yavru islem tamamlandi, program sonlandiriliyor.\n");
        } else // Hata koduyla sonlanmışsa dönüş değeri yazdırılır.
        {
            printf("[EBEVEYN] Yavru islem hata ile sonlandirildi! (%d)\n", donusDurumu);
        }
    }

    return 0;
}
