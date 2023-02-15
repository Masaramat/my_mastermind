#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

//function validates input to make sure it is only ontegers
int validateInput(char* param_1){
    int status = 0;
    for(int i=0; i<(int)strlen(param_1); i++){
        if(param_1[i] >= 48 && param_1[i] <= 57){
            status = 1;
        }
        else{
            status = 0;
            break;
        }
    }
    return status;
    
}

//putchar function to write characters to the standard output
int my_putchar(char c) {
  return write(1, &c, sizeof(c));
}
//putstr function to write a string to the standard output
void my_putstr(char* param_1)
{
    int index = 0;
     while (param_1[index] != '\0') {
        my_putchar(param_1[index]);
        index++;
    }
    printf("\n");

}


//function generates random integer and converts it to string when no -c is not supplied
char* getRandom(){
     char* hidden_number = (char*) malloc(sizeof(char*) * 4);
    srand(time(0));
    printf("no value entered");
    int random_number;
    // generates four random nimbers
    for(int i =0; i<4; i++){
        random_number = rand() % 8;
        //converts the random number to a character and adds it to a string
        hidden_number[i] = random_number + '0';
    }
    
    return hidden_number;
}
//compares the hidden code with the user's guess
void compareStrings(char* guess, char* hiddenNumber){
    int rightPlaced = 0;
    int wrongPlaced = 0;

    for(int i=0; i<(int)strlen(guess); i++){
        for(int j=0; j<(int)strlen(hiddenNumber); j++){
            if(guess[i] == hiddenNumber[j] && i==j){
                rightPlaced += 1;
            }else if(guess[i] == hiddenNumber[j] && i!=j){
                wrongPlaced += 1;
            }
        }
    }
    printf("Well placed pieces: %d\n", rightPlaced);
    printf("Misplaced pieces: %d\n", wrongPlaced);
}

//gives instruction and collects input from the user
int checkInput(char* hidden_number, int round){
    char* input =(char*) malloc(sizeof(char) * 4);
    my_putstr("---");
    char str[12]  = "Round ";
    char ch = round + '0';
    str[strlen(str)] = ch;
    my_putstr(str);
    my_putchar('>');
    char c;
    //collects input in the std i
    for(int i=0; i<5; i++){
        if(read(0, &c, 1) == '\0'){
             my_putstr("^D");
            return 1;
        }
        if(i == 4)break;
        input[i] = c;

    }  
       
      
    //does the comparison
    if(strcmp(input, hidden_number) == 0){
        my_putstr("Congratz you did it!");
        return -1;
    }else if(validateInput(input) == 0){
        while (validateInput(input) == 0) {
            printf("Wrong input!\n");
           return 2;
        }

    }else if(validateInput(input) == 1){
        compareStrings(input, hidden_number);
    }
      
        

        return 0;
}
//main method
int main (int numArgs, char* args[]){
    char* hidden_number = (char*) malloc(sizeof(char*) * 4);
    int rounds;
    if(numArgs <= 1){
        rounds = 10;
        hidden_number = getRandom();
    }else if(numArgs == 3){
        //checks for the right flag for the hidden code
        if (strcmp(args[1], "-c") == 0)  {
            rounds = 10;
            hidden_number = args[2];
            if (validateInput(hidden_number) == 0){
                printf("Only integers accepted\n");
                return 1;
            } 
        }else {
            printf("invalid flag, expects -c number or -t number of rounds\n");
            return 1;
        }
    //validates when two flags are received for the hidden code and the number of rounds
    }else if(numArgs == 2){
        //checks for the right flag for the hidden code
        if (strcmp(args[1], "-c") == 0)  {
            rounds = 10;  
        }else {
            printf("invalid flag, expects -c number or -t number of rounds ");
            return 1;
        }
    //validates when two flags are received for the hidden code and the number of rounds
    }else if(numArgs == 5){
        if (strcmp(args[1], "-c") == 0 && strcmp(args[3], "-t") == 0){
            hidden_number = args[2];
            rounds = atoi(args[4]);
        }else if(strcmp(args[1], "-t") == 0 && strcmp(args[3], "-c") == 0){
             hidden_number = args[2];
            rounds = atoi(args[4]);
        } else{
            printf("invalid flag, expects -c number or -t number of rounds ");
            return 1;
        }
    }else {
        //when inappropriate number of arguments are given
         printf("invalid number of arguments");
            return 1;
    }
    my_putstr("Will you find the secret code?");
    my_putstr("Please enter a valid guess");
    int i = 0;
    while (i < rounds) {
        int value = checkInput(hidden_number, i);
        if(value == 1){
            return 1;
        }else if(value == -1){
            break;
            return 0;
        }else if(value == 2){
            i--;
        }
        i++;
    }


    return 0;
}