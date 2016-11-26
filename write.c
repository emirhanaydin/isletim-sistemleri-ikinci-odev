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
#include <sys/shm.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

#define BOYUT 10
#define SHM_SIZE 8*BOYUT

struct kayit {
    int seri_no;
    int veri;
};

int main(int argc, char **argv) {
    key_t shm_key = 6166525;

    int shm_id;
    void *shmaddr;
    int i;

    struct kayit kayitlar[BOYUT];

    printf("writer started.\n");

    /* Allocate a shared memory segment. */
    shm_id = shmget(shm_key, SHM_SIZE, IPC_EXCL | S_IRUSR | S_IWUSR);

    /* Attach the shared memory segment. */
    shmaddr = shmat(shm_id, 0, 0);

    printf("shared memory attached at address %p\n", (void *) shmaddr);

    /* Start to write data. */
    srand((unsigned int) time(NULL));

    for (i = 0; i < BOYUT; i++) {
        kayitlar[i].seri_no = i;
        kayitlar[i].veri = rand() % 100;
    }
    memcpy(shmaddr, &kayitlar, sizeof(kayitlar));

    printf("writer ended.\n");

    /* Detach the shared memory segment. */
    shmdt(shmaddr);

    /* Deallocate the shared memory segment.*/
    shmctl(shm_id, IPC_RMID, 0);

    return 0;
}