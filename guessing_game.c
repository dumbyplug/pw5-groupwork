#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

int min = 1, max = 999;
void start_over();

int computer_choice(){
    /*
    This function generates random number
    Input:
        void
    Output:
        integer: (a random number between 1 and 9)
    */
    return rand() % (max - min + 1) + min;
}

char comparison_for_user_guess(int user, int comp){
    /*
    This function compares numbers;
    Input: 
        user_choice: int
        comp_choice: int
    Output:
        character: f , s , g
    */
    char result;
    if(user < comp){
        result = 's';
    }else if(user == comp){
        result = 'f';
    }else{
        result = 'g';
    }return result;
}

int user_guessing(){
    /*
    This is user's guess
    */
    int user_guess = 0;
    int comp_choice = computer_choice();
    printf("Enter the number you guess:\n");
    scanf("%*[^\n]");
    while(user_guess != comp_choice){ 
        if(!scanf("%d", &user_guess) || (user_guess > 999 || user_guess < 1)){
            printf("Invalid input\n");
        }else{
            char compared = comparison_for_user_guess(user_guess, comp_choice);
            printf("%c\n", compared);
            if(compared == 'n'){
                printf("Invalid answer!|n");
            }else{
                if(compared == 'f'){
                    printf("You guessed it right\n");
                    break;
                }
            }
        }
    }start_over();
}

int user_indicate(int comp_anwer){
    char answer;
    scanf("%*[^\n]");
    scanf(" %c", &answer);
    
    answer = tolower(answer);
    if(answer == 'g'){
        if(comp_anwer < max){
            max = comp_anwer - 1;
        }
    }else if(answer == 's'){
        if(comp_anwer > min){
            min = comp_anwer + 1;
        }
    }else if(answer == 'f'){
        answer = 'f';
    }else{
        answer = 'n';
    }return answer;
}

int comp_guessing(){
    printf("Enter: s, g or f, bases on these conditions: \n1.If computer guess is bigger than your choice: g or G \n2.If computer guess is smaller than your choice: s or S \n3.If computer guess is right: f or F\n");
    int comp_guess = computer_choice();
    printf("%d\n", comp_guess);
    while(user_indicate(comp_guess) != 'f'){
        comp_guess = computer_choice();
        printf("%d\n", comp_guess);
    }printf("You guessed it right!\n");
    start_over();
}

int game(){
    printf("Who do you want to start: \n1.Computer guesses the number\n2. You guess the number\n");
    int turn;
    scanf("%d", &turn);
    if(turn == 1){
        comp_guessing();
    }else if(turn == 2){
        user_guessing();
    }else{
        printf("Invalid answer!\n");
        game();
    }
}

void start_over(){
    printf("Do you want to play again: 1 - start again, 0 - quit\n");
    int answer;
    scanf("%d", &answer);
    if(answer == 1){
        min = 1;
        max = 999;
        game();
    }
}


int main(){
    srand(time(NULL));
    game();
    return 0;
}
