#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main() {
    key_t shm_key = 214127923;
    const int shm_size = 1024;

    int shm_id;
    char *shmptr, *ptr;
    char *shared_memory[3];
    int *p;

    /* Allocate a shared memory segment/ */
    shm_id = shmget(shm_key, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);

    /* Attach the shared memory segment/ */
    shmptr = (char *) shmat(shm_id, NULL, 0);

    printf("Shared memory attached at address %p\n", shmptr);

    /* Start to read data/ */
    p = (int *) shmptr;
    ptr = shmptr + sizeof(int) * 2;
    shared_memory[0] = ptr;
    ptr += *p++;
    shared_memory[1] = ptr;
    ptr += *p;
    shared_memory[2] = ptr;

    printf("0 = %s\n", shared_memory[0]);
    printf("1 = %s\n", shared_memory[1]);
    printf("2 = %s\n", shared_memory[2]);

    /* Detach the shared memory segment. */
    shmdt(shmptr);
    return 0;
}