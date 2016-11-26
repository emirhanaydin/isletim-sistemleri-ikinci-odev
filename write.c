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


#include <stdio.h>      /* Standart input-output */
#include <stdlib.h>     /* for rand() */
#include <sys/shm.h>    /* Shared Memory */
#include <sys/stat.h>   /* for shared memory flags */
#include <time.h>       /* for random(time()) */
#include <string.h>     /* for memcpy() */
#include <signal.h>     /* Signal */
#include <unistd.h>     /* Alarm */
#include <stdbool.h>    /* Standart bool */

#define BOYUT 10
#define SHM_SIZE 8*BOYUT

volatile sig_atomic_t kayit_bayragi = false;
volatile sig_atomic_t cikis = false;

struct kayit {
    int seri_no;
    int veri;
};

void kayit_ekle(int sig) {
    kayit_bayragi = true;
}

void sonlandir(int sig) {
    cikis = true;
}

int main(int argc, char **argv) {
    key_t shm_key = 6166525;

    int shm_id;
    void *shmaddr;
    int i = 0;

    struct kayit kayitlar[BOYUT];

    printf("writer started.\n");

    signal(SIGINT, sonlandir);

    /* Allocate a shared memory segment. */
    shm_id = shmget(shm_key, SHM_SIZE, IPC_EXCL | S_IRUSR | S_IWUSR);

    /* Attach the shared memory segment. */
    shmaddr = shmat(shm_id, 0, 0);

    printf("shared memory attached at address %p\n", shmaddr);

    /* Alarm yakalayıcısı kurulur. */
    signal(SIGALRM, kayit_ekle);
    /* Alarm 1 saniye ile başlatılır. */
    alarm(1);

    srand((unsigned int) time(NULL));

    /* Start to write data. */
    int j = 0;
    while (!cikis) {
        if (kayit_bayragi) {
            kayitlar[i].seri_no = i;
            kayitlar[i].veri = rand() % 100;

            memcpy(shmaddr, &kayitlar, sizeof(kayitlar));
            i = (i + 1) % 10;

            kayit_bayragi = false;
            alarm(1);
        }
    }

    printf("writer ended.\n");

    /* Detach the shared memory segment. */
    shmdt(shmaddr);

    /* Deallocate the shared memory segment.*/
    shmctl(shm_id, IPC_RMID, 0);

    return 0;
}