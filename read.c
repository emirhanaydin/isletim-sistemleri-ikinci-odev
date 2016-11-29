#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <wait.h>

#define BOYUT 10
#define SHM_SIZE 8*BOYUT
#define SEMADI "/senkronizesem"

struct kayit {
    int seri_no;
    int veri;
};

int main() {
    key_t shm_key = 6166515;
    char key_arr[10];
    sprintf(key_arr, "%d", shm_key);

    int shm_id;
    void *shmaddr;
    int i;

    struct kayit *okunan;

    pid_t pid = fork();
    if (pid == 0) {  /* Yavru işlem */
        execl("./write", key_arr, SEMADI, NULL);
    } else if (pid < 0) {  /* Hata durumu */
        perror("fork basarisiz.");
        return -1;
    } else { /* Ebeveyn işlem */
        printf("reader started.\n");

        /* Allocate a shared memory segment. */
        shm_id = shmget(shm_key, SHM_SIZE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

        /* Attach the shared memory segment. */
        shmaddr = shmat(shm_id, 0, 0);

        printf("shared memory attached at address %p\n", shmaddr);

        /* Diğer işlemde oluşturulmuş olan semafor alınır. */
        sem_t *mutex = sem_open(SEMADI, 0);

        sem_unlink(SEMADI);

        i = 0;
        while (1) {
            /* Start to read data. */
            okunan = shmaddr + i * (sizeof(struct kayit));
            if (okunan->veri < 0) break;
            printf("%d. veri: %02d\n", okunan->seri_no, okunan->veri);
            i = (i + 1) % 10;
        }

        int ret;
        wait(&ret);

        /* Detach the shared memory segment. */
        shmdt(shmaddr);

        /* Deallocate the shared memory segment.*/
        shmctl(shm_id, IPC_RMID, 0);
    }

    return 0;
}