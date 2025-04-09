#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_field(int*);
void generate_new_number(int[]);
void start(int[]);
void key_pressed(char key, int[]);

int main(){
    int field[16];
    char key; 

    //test
    srand(time(NULL));
    start(field);
    print_field(field);

    int game_over = 0;
    while(!game_over){
        scanf(" %c", &key);
        key_pressed(key, field);
        //game_over = check_game_over();    TODO
    }
}

void key_pressed(char key, int field[]){
    int change = 0;
    if(key == 'w'){
        for(int j=0; j<3; j++){
            for(int i=4; i<16; i++){
                if(field[i] != 0 && field[i-4] == 0){
                    field[i-4] = field[i];
                    field[i] = 0;
                    change = 1;
                }
                if(field[i] != 0 && field[i-4] == field[i]){
                    field[i-4] = 2*field[i];
                    field[i] = 0;
                    change = 1;
                }
            }
        }
    }
    if(change == 1){
        generate_new_number(field);
    }
    print_field(field);
}

void start(int field[]){
    for(int i=0; i<16; i++){
        field[i] = 0;
    }
    generate_new_number(field);
    generate_new_number(field);
}

void print_field(int* field){
    for(int i=0; i<=12; i+=4){
        printf("---------------------\n");
        printf("|%4d|%4d|%4d|%4d|\n", field[i], field[i+1], field[i+2], field[i+3]);
    }
    printf("---------------------\n");
}

void generate_new_number(int field[]){
    int n[] = {2,2,2,2,2,2,2,2,2,4};
    int position;
    do{
        position = rand()%16;
    }while(field[position] != 0);
    field[position] = n[rand()%10];
}
