#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CASES   20

void print_file(char * path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(-1);
    }

    char line[256];
    while(1) {
        int cnt = read(fd, line, 256);
        if (cnt <= 0) {
            break;
        }
        write(1, line, cnt);
    }

    close(fd);
}

void test() {
#define MAX_PATH_LEN    64
    int good = 1;
    for(int i = 1; i <= CASES; i++) {
        //char path1[MAX_PATH_LEN];
        //snprintf(path1, MAX_PATH_LEN, "./data/%d.in", i);
        //print_file(path1);
        
        char thing[32];
        snprintf(thing, 32, "Case %d:", i);
        puts(thing);

        char path2[MAX_PATH_LEN];
        snprintf(path2, MAX_PATH_LEN, "./data/%d.out", i);

        int a = 0;
        scanf("%d", &a);
        
        FILE* f = fopen(path2, "r");
        if (f == NULL) {
            puts("something wrong ...");
            exit(-1);
        }
        int b = 0;
        fscanf(f,"%d", &b);
        fclose(f);

        if(a != b) {
            good = 0;
        }
    }
    if(good) print_file("flag.txt");
}

int main() {
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	setbuf(stderr, NULL);

    print_file("statement.txt");    
    test();
}

