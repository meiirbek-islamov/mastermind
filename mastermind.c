#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include <time.h>

char* random_number(){
    int d1, d2, d3, d4;
    int i, r, j;
    int number[4];
    srand(time(NULL));
    char* res = malloc(sizeof(char)*4);
    
    while (i < 4){
        r = rand()%9;
        for (j = 0; j < i; j++){
            if (number[j] == r){
                break;
            }
        }
        if(j==i){
            number[i++]=r;
            }
    }
    d1 = number[0]; 
    d2 = number[1]; 
    d3 = number[2]; 
    d4 = number[3];
    sprintf(res, "%d%d%d%d", d1, d2, d3, d4);
    return res;
}

char* read_input(){
    char *input = malloc(sizeof(char) * 100);
    read(0, input, 100);
    return input;
}

int well_placed_pieces(char* input, char* secret_code){

    int res = 0;
    for (int i = 0; i < 4; i ++){
        for (int j = 0; j < 4; j ++){
            if (input[i] == secret_code[j]){
                if (i == j){
                    res ++;
                }
            }
        }

    }
    return res;
}

int misplaced_pieces(char* input, char* secret_code){

    int res = 0;
    for (int i = 0; i < 4; i ++){
        for (int j = 0; j < 4; j ++){
            if (input[i] == secret_code[j]){
                if (i != j){
                    res ++;
                }
            }
        }
    }
    return res;
}

int check_wrong_input(char * input){

    int res = 1;
    if ( ('0' <= input[0] && input[0]> '8') ||
        ('0' <= input[1] && input[1]> '8') ||
        ('0' <= input[2] && input[2]> '8') ||
        ('0' <= input[3] && input[3]> '8')){
            res = 0;
    }
    return res;
}

int check_input_size(char* input){
    int res = 1;
    if (strlen(input) != 5){
        res = 0;
        
    }
    return res;
}

int check_duplicates(char * input){
    int res = 1;
    for (int i = 0; i < strlen(input) - 1; i++){
        for (int j = i + 1; j < strlen(input); j++){
            if (input[i] == input[j]){
                res = 0;
            }
        }
    }
    return res;
}

int mastermind_process(int ac, char **av){
    char *secret_code = malloc(sizeof(char) * 4);
    int maxAttempt = 10;
    int opt;
    int attempt = 0;
    int print_round = 0;
    int well_pp;
    int miss_pp;
    secret_code = random_number();
    
    while ((opt = getopt (ac, av, "c:t:")) != -1)
    switch (opt)
      {
      case 'c':
        secret_code = optarg;
        break;
      case 't':
        maxAttempt = atoi(optarg);
        break;
      }
    
    printf("Will you find the secret code?\n");
    printf("---\n");
    printf("Round %d\n", attempt);

    while(attempt < maxAttempt){

        int k = 0;
        while(print_round != 0 && k < 1) {
            printf("Round %d\n", attempt);
            k++;
        }
        print_round = 1;

        char * input = read_input();
        int res_wrong_input = check_wrong_input(input);
        int input_size = check_input_size(input);
        int duplicate = check_duplicates(input);

        if ((res_wrong_input == 0) || (input_size == 0) || (duplicate == 0)){
            printf("Wrong input!\n");
            print_round = 0;
        }

        else{
            well_pp = well_placed_pieces(input, secret_code);
            miss_pp = misplaced_pieces(input, secret_code);

            if (well_pp == 4){
                printf("Congratz! You did it!\n");
                break;
            }

            printf("Well placed pieces: %d\n", well_pp);
            printf("Misplaced pieces: %d\n", miss_pp);
            printf("---\n");
            attempt ++;
            if (attempt == maxAttempt){
                printf("Game is over, you're lost! The secret code was %s\n", secret_code);
            }
        }
        
    }
}

int main(int ac, char **av){
    mastermind_process(ac, av);
}

