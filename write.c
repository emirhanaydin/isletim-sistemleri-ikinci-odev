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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    printf("Uretici islem baslatildi.\n");

    pid_t pid;
    pid = fork(); /* İşlem çatallanır. */
    if (pid == 0) /* Çatallamadan sonra yavru işlem. */
    {

    } else if (pid < 0) {
        perror("fork() basarisiz!\n");
        return -1;
    } else { /* Çatallamadan sonra ebeveyn işlem. */
        key_t anahtar = 214127923;
        const int boyut = 1024;

        int kimlik;
        char *adres, *ptr;
        int sonraki[2];

        /* Allocate a shared memory segment */
        kimlik = shmget(anahtar, boyut, IPC_CREAT | S_IRUSR | S_IWUSR);

        /* Attach the shared memory segment. */
        adres = (char *) shmat(kimlik, NULL, 0);

        printf("Shared memory attached at address %p\n", (void *) adres);

        /* Start to write data/ */
        ptr = adres + sizeof(sonraki);
        sonraki[0] = sprintf(ptr, "Mehmet") + 1;
        ptr += sonraki[0];
        sonraki[1] = sprintf(ptr, "123456789") + 1;
        ptr += sonraki[1];
        sprintf(ptr, "Ahmet");
        memcpy(adres, sonraki, sizeof(sonraki));
        printf("Producer ended.");

        /* Calling the other process */
        system("./read");

        /* Detach the shared memory segment. */
        shmdt(adres);

        /* Deallocate the shared memory segment. */
        shmctl(kimlik, IPC_RMID, 0);
    }

    return 0;
}