#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define BOYUT 10
#define SHM_SIZE 8*BOYUT

struct kayit {
    int seri_no;
    int veri;
};

int main() {
    key_t shm_key = 6166525;

    int shm_id;
    void *shmaddr;
    int i;

    struct kayit *okunan;

    printf("reader started.\n");

    /* Allocate a shared memory segment. */
    shm_id = shmget(shm_key, SHM_SIZE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    /* Attach the shared memory segment. */
    shmaddr = shmat(shm_id, 0, 0);

    printf("shared memory attached at address %p\n", shmaddr);

    system("./write");

    /* Start to read data. */
    for (i = 0; i < BOYUT; i++) {
        okunan = shmaddr + i * (sizeof(struct kayit));
        printf("%d. veri: %02d\n", okunan->seri_no, okunan->veri);
    }

    /* Detach the shared memory segment. */
    shmdt(shmaddr);

    /* Deallocate the shared memory segment.*/
    shmctl(shm_id, IPC_RMID, 0);

    return 0;
}