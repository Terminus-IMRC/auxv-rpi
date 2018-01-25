#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/auxvec.h>
#include <asm/hwcap.h>
#include <elf.h>

static void print_hwcap(const uint32_t v)
{
#define X(f) \
    do { \
        if (v & HWCAP_##f) \
            printf(" %s", #f); \
    } while (0)

    X(JAVA);
    X(FAST_MULT);
    X(EDSP);
    X(VFP);
    X(VFPv3);
    X(VFPv3D16);
    X(VFPv4);
    X(VFPD32);
    X(NEON);
    X(IDIVA);
    X(IDIVT);
    printf("\n");

#undef X
}

static void print_hwcap2(const uint32_t v)
{
#define X(f) \
    do { \
        if (v & HWCAP2_##f) \
            printf(" %s", #f); \
    } while (0)

    X(CRC32);
    printf("\n");

#undef X
}

int main()
{
    int fd;
    Elf32_auxv_t auxv;
    int err;

    fd = open("/proc/self/auxv", O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "error: open: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (; ; ) {
        ssize_t sz = read(fd, &auxv, sizeof(auxv));
        if (sz < 0) {
            fprintf(stderr, "error: read: %s\n", strerror(errno));
            goto failed_read;
        } else if (sz == 0) {
            break;
        } else if (sz != sizeof(auxv)) {
            fprintf(stderr, "Short read: %zd != %zu\n", sz, sizeof(auxv));
            goto failed_read;
        }

        switch (auxv.a_type) {
            case AT_PAGESZ:
                printf("PAGESZ: %u\n", auxv.a_un.a_val);
                break;
            case AT_CLKTCK:
                printf("CLKTCK: %u\n", auxv.a_un.a_val);
                break;
            case AT_PLATFORM:
                printf("PLATFORM: %s\n", (char*) auxv.a_un.a_val);
                break;
            case AT_HWCAP:
                printf("HWCAP:");
                print_hwcap(auxv.a_un.a_val);
                break;
            case AT_HWCAP2:
                printf("HWCAP2:");
                print_hwcap2(auxv.a_un.a_val);
                break;
            default:
                /* Ignore other fields. */
                break;
        }
    }

    err = close(fd);
    if (err) {
        fprintf(stderr, "error: close: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    return 0;

failed_read:
    (void) close(fd);
    exit(EXIT_FAILURE);
}
