#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LETTERS 2
#define CHUNK_SIZE  72
#define STEPS       34

char *letters[MAX_LETTERS]={0};

void show_menu() {
    puts("OPTIONS");
    puts("1) Create a postcard");
    puts("2) Edit a postcard");
    puts("3) Discard a postcard");
    puts("4) Read a postcard");
}

void create_card() {
    int ind = 0;

    puts("Which envelope #?");
    scanf("%d", &ind);

    if(ind < 0) {
        puts("swiper no swipey !");
        return;
    }

    if(ind >= MAX_LETTERS) {
        puts("u so greedy dat when u step on da scale, u see ur credit card number >:O");
        return;
    }

    letters[ind] = malloc(CHUNK_SIZE);
}

void edit_card() {
    int ind = 0;

    puts("Which envelope #?");
    scanf("%d", &ind);

    if(ind < 0 || ind >= MAX_LETTERS) {
        puts("swiper no swipey !");
        return;
    }

    puts("Write.");
    read(0, letters[ind], CHUNK_SIZE);
}

void discard() {
    int ind = 0;

    puts("Which envelope #?");
    scanf("%d", &ind);

    if(ind < 0 || ind >= MAX_LETTERS) {
        puts("swiper no swipey !");
        return;
    }

    free(letters[ind]);
}

void display() {
    int ind = 0;

    puts("Which envelope #?");
    scanf("%d", &ind);

    if(ind < 0 || ind >= MAX_LETTERS) {
        puts("swiper no swipey !");
        return;
    }

    puts(letters[ind]);
}

int main() {
    int choice = -1;

    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setbuf(stderr, NULL);

    for(int i = 0; i < STEPS; i++) {
        show_menu();
        scanf("%d", &choice);

        switch(choice) {
        case 1:
            create_card();
            break;
        case 2:
            edit_card();
            break;
        case 3:
            discard();
            break;
        case 4:
            display();
            break;
        default:
            puts("omggg hacker");
            break;
        }
    }

    return 0;
}

