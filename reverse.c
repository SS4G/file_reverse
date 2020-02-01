#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
//#define BLOCK_SIZE 1024llu * 1024llu * 4llu
//#define BLOCK_SIZE 1024llu * 1024llu 

uint64_t get_file_size(char* input_file_name) {
    FILE* fpr = fopen(input_file_name, "rb");
    if (fpr == NULL) {
        printf("file not found!\n");
        exit(1);
    }
    fseek(fpr, 0, SEEK_END);
    uint64_t len = ftell(fpr);
    return len;
}

int reverse_file(char* input_file_name) {
    const uint64_t BLOCK_SIZE = 1024llu * 1024llu * 4llu;
    char output_filename[200];
    uint8_t* buffer = (uint8_t*)malloc(BLOCK_SIZE * sizeof(uint8_t));
    uint64_t total_filesize = get_file_size(input_file_name);
    uint64_t loop_cnt = 0;
    time_t start, now;
    FILE* fpr = fopen(input_file_name, "rb");
    FILE* fpw; //= fopen(output_filename, "wb");

    if (fpr == NULL) {
        printf("file %s not found!\n", input_file_name);
        exit(1);
    }

    printf("total_size=%lld\n", total_filesize);
    strcpy(output_filename, input_file_name);
    strcat(output_filename, ".rev");
    fpw = fopen(output_filename, "wb");
    if (fpw == NULL) {
        printf("file %s create failed!\n", input_file_name);
        exit(1);
    }
    loop_cnt = 0;
    time(&start);
    do {
        fread(buffer, BLOCK_SIZE, 1, fpr);
         
        uint64_t write_size;
        if (ftell(fpr) < total_filesize) {
            write_size = BLOCK_SIZE;
        }
        else {
            write_size = total_filesize % BLOCK_SIZE;
        }

        for (int i = 0; i < write_size; i++) {
            buffer[i] = ~buffer[i];
        }
        fwrite(buffer, write_size, 1, fpw);
        if (loop_cnt % 1 == 0) {
            time(&now);
            printf("time_consume:%lus, progress:%.2f %% \r",(int)now - start, ((float)ftell(fpr)) * 100.0 / total_filesize);
        }
        loop_cnt++;
    } while(ftell(fpr) < total_filesize);
    fclose(fpr);
    fclose(fpw);
    free(buffer);
    printf("\n%s reverse finished\n", input_file_name);
    return 0;
}

int main(int argv, char** argc) {
    reverse_file(argc[1]);
}