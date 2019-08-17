#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define NUM_CASES 51 

const char* INPUT_FILE = "tests.txt";
const char* OUTPUT_FILE = "ans.txt";
const char* FLAG_FILE = "flag.txt";

char response[21];

size_t short_size = 20;
size_t long_size = 9000;

int main() {
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	setbuf(stderr, NULL);

    FILE* input = fopen(INPUT_FILE, "r");
    FILE* output = fopen(OUTPUT_FILE, "r");

    if (input == NULL) {
        fprintf(stderr, "something went wrong. please contact an organizer.\n");
        fprintf(stderr, "info: test cases are missing");
    }

    if (output == NULL) {
        fprintf(stderr, "something went wrong. please contact an organizer.\n");
        fprintf(stderr, "info: answer file is missing");
    }

    for (int i = 0; i < NUM_CASES; i++) {
        int n;
        fscanf(input, "%d", &n);
        printf("%d\n", n);

        for (int j = 0; j < n; j++) {
            int num;
            fscanf(input, "%d", &num);
            printf("%d", num);
            
            if (j < n - 1) {
                printf(" ");
            } else {
                printf("\n");
            }
        }

        for (int j = 0; j < n; j++) {
            int num;
            fscanf(input, "%d", &num);
            printf("%d", num);
            
            if (j < n - 1) {
                printf(" ");
            } else {
                printf("\n");
            }
        }

        int ans;
        fscanf(output, "%d", &ans);

        scanf("%20s", response);
        response[10] = 0;

        int res = atoi(response);

        if (res != ans) {
            puts("wrong answer...");
            return 0;
        } 
    }

    FILE* flag_file = fopen(FLAG_FILE, "r");
    char* flag = NULL;
    size_t flag_size = 20;

    if (flag_file == NULL) {
        fprintf(stderr, "something went wrong. please contact an organizer.\n");
        fprintf(stderr, "info: flag file is missing");
    }
     
    getline(&flag, &flag_size, flag_file); 
    puts(flag);
}

