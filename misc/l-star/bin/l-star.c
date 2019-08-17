#include <stdio.h>
#include <regex.h>
#include <stdlib.h>

int test(char* buf) {
    FILE *f = fopen("yay.txt", "r");
    char *str = NULL;
    ssize_t read;
    size_t len = 0;
    int result = 0;
    regex_t regex = { 0 };

    regcomp(&regex, buf, REG_EXTENDED);
    while ((read = getline(&str, &len, f)) != -1) {        
        if(regexec(&regex, str, 0, NULL, 0) == REG_NOMATCH) {
            result = -1;
            break;
        }
    }
    fclose(f);

    if (result >= 0) {
        f = fopen("nay.txt", "r");
        while ((read = getline(&str, &len, f)) != -1) {
            if(regexec(&regex, str, 0, NULL, 0) == 0) {
                result = -1;
                break;
            }
        }
        fclose(f);
    }

    regfree(&regex);
    free(str);
    return result;
}

int main() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setbuf(stderr, NULL);
    puts("get the show on");

    char buf[90];
    fgets(buf, 90, stdin);
 
    if(test(buf) == 0) {
        FILE *f = fopen("flag.txt", "r");
        char flag[64];
        fgets(flag, 64, f);
        puts(flag);
        fclose(f);
    } else {
        puts("L");
    }
    
    return 0;
}
