#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE (16 * 1024)   // Not used now, but kept for comparison look

/* ------------ TIMER UTILITY ------------- */
double now_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

/* ------------ MAIN COPY LOGIC ------------- */
int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    if (!src) { perror("Source open failed"); return 1; }

    FILE *dst = fopen(argv[2], "wb");
    if (!dst) { perror("Destination open failed"); fclose(src); return 1; }

    /* --- Determine full file size --- */
    fseek(src, 0, SEEK_END);
    long filesize = ftell(src);
    fseek(src, 0, SEEK_SET);

    if (filesize <= 0) {
        printf("Empty or invalid file.\n");
        fclose(src);
        fclose(dst);
        return 1;
    }

    /* --- Allocate one big buffer (full file) --- */
    unsigned char *buffer = (unsigned char*)malloc(filesize);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(src);
        fclose(dst);
        return 1;
    }

    double start = now_seconds();

    /* ------------ FULL READ IN ONE GO ------------- */
    size_t r = fread(buffer, 1, filesize, src);
    if (r != filesize) {
        perror("Full read failed");
        free(buffer);
        fclose(src);
        fclose(dst);
        return 1;
    }

    /* ------------ FULL WRITE IN ONE GO ------------- */
    size_t w = fwrite(buffer, 1, filesize, dst);
    if (w != filesize) {
        perror("Full write failed");
        free(buffer);
        fclose(src);
        fclose(dst);
        return 1;
    }

    double end = now_seconds();
    printf("Copy completed in %.6f seconds (full RAM read/write)\n", end - start);

    free(buffer);
    fclose(src);
    fclose(dst);
    return 0;
}

