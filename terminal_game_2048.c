#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_field(int*);
void generate_new_number(int[]);
void start(int[]);
int key_pressed(char key, int[]);
void rotate(int, int[]);
int check_game_over(int, int[]);

int main(){
    int field[16];
    char key; 

    //test
    srand(time(NULL));
    start(field);
    print_field(field);

    int game_over = 0;
    while(game_over == 0){
        scanf(" %c", &key);
        game_over = check_game_over(key_pressed(key, field), field);
    }
    printf("Game over!");
}

int check_game_over(int change, int field[]){
    if(change == 1){
        generate_new_number(field);
        print_field(field);
        return 0;
    }
    else{
        for(int k=0; k<4; k++){ // check all four directions
            for(int j=0; j<3; j++){
                for(int i=15; i>3; i--){
                    if(field[i] != 0 && field[i-4] == 0){
                        change = 1;
                    }
                    if(field[i] != 0 && field[i-4] == field[i]){
                        change = 1;
                    }
                }
            }
            rotate(1, field);
        }
        if(change == 1){    // a move is possible
            generate_new_number(field);
            print_field(field);
            return 0;
        } 
        else{
            return 1;
        }
    }
}

int key_pressed(char key, int field[]){
    int change = 0;
    int n=0;
    switch (key) {
        case 'w': n=0; break;
        case 'a': n=3; break;
        case 's': n=2; break;
        case 'd': n=1; break;
    }
    rotate(n, field);
    for(int j=0; j<3; j++){
        for(int i=15; i>3; i--){
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
    rotate(4-n, field);
    return change;
}

void rotate(int n, int field[]){    // rotate field n*90° counter clockwise
    n = n%4;
    if(n > 0){
        int field_copy[16];
        for(int i=0; i<16; i++){
            field_copy[i] = field[i];
        }
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                field[4*i+j] = field_copy[(3-i)%4+4*j];
            }
        }    
        --n;   
        rotate(n, field);
    }
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
    int full = 1;
    for(int i=0; i<16; i++){
        if(field[i]==0){full=0;}    // still 0 left
    }
    if(full==0){
        int n[] = {2,2,2,2,2,2,2,2,2,4};    // 90% probability for 2, 10% for 4
        int position;
        do{
            position = rand()%16;
        }while(field[position] != 0);   // dont replace existing number
        field[position] = n[rand()%10];
    }
}
