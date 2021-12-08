//Gustas Logvinovas, 1 grupė
//This program will read from file and give the output to another file
//The output is every single word in reverse, but the sequence of words is not changed
//arguments given in terminal(input and output filenames), else will ask input file and print results in stdout
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 255

int readFile(char* row, FILE* fpIn){                                ///returns the amount of elements read
    int amount = 0;
    amount = fread(row, sizeof(char), MAX_SIZE, fpIn);
    return amount;
}

void clearLine(char* row, int* j, int* amount, int* clearFlag){     ///skips the leftover symbols if the line is over 255 symbols
    for( ; *j < *amount ; ++(*j)){

        char trash;
        trash = *(row+*j);

        if(trash == '\n'){
            (*clearFlag) = 0;
            break;
        }
    }

}

void clearString(char* word, char* result){
    memset(word,0,strlen(word));
    memset(result,0,strlen(result));
}

void resultWord(char* word, char* result, int* index){
    for(int i = (strlen(word) - 1) ; i >= 0 ; --i){
        result[*index] = word[i];
        (++*index);

    }
}

void reverseRow(char* row, char* word, int* letter, int* indexInLine, int amount, FILE* fpOut, int* clearFlag, int* noOut){

    char* result = calloc(MAX_SIZE, sizeof(char));
    int index = 0, j = 0;

    for(; j < amount ; ++j){
        if(*clearFlag){
            clearLine(row, &j, &amount, clearFlag);
            if(!*clearFlag){
                (*indexInLine) = 0;
            }
            else{
                break;
            }
        }
        if(*indexInLine == (MAX_SIZE-1)){
            *clearFlag = 1;
        }
        char symbol;
        symbol = row[j];
        if(symbol != '\n' && symbol != ' ' && symbol != 9){
            word[*letter] = symbol;
            ++(*letter);
        }
        else if(symbol != '\n'){

            resultWord(word, result, &index);
            if(*noOut){
                fwrite(result, 1, index, stdout);
            }
            else{
                fwrite(result, 1, index, fpOut);
            }
            index = 0;
            (*letter) = 0;
            clearString(word, result);

            char c;                                                 //a simple variable to check hom many more spaces there is
            while(2){

                c = row[j];
                if(*indexInLine == (MAX_SIZE-1)){
                    (*clearFlag) = 1;
                    break;
                }

                if(c == ' ' || c == 9){
                    if(*noOut){
                        fwrite(&c, 1, 1, stdout);
                    }
                    else{
                        fwrite(&c, 1, 1, fpOut);
                    }
                }
                else if(c == '\n'){
                    *indexInLine = 0;
                    if(*noOut){
                        fwrite(&c, 1, 1, stdout);
                    }
                    else{
                        fwrite(&c, 1, 1, fpOut);
                    }
                    break;
                }
                else{                           //if letter, then set letter index to zero and go to another word
                    *letter = 0;
                    word[*letter] = c;
                    ++(*letter);
                    break;
                }
                ++j;                         //because the symbol was scanned
                ++(*indexInLine);
            }

        }
        else{

            resultWord(word, result, &index);
            if(*noOut){
                fwrite(result, 1, index, stdout);
            }
            else{
                fwrite(result, 1, index, fpOut);
            }
            index = 0;
            (*letter) = 0;
            clearString(word, result);

            *indexInLine = -1;
            if(*noOut){
                fwrite("\n", 1, 1, stdout);
            }
            else{
                fwrite("\n", 1, 1, fpOut);
            }
        }
        ++(*indexInLine);

    }
    free(result);
}

int main(int argc, char **argv)
{
    printf("This program will read a text from input file and printf every word in the text in reverse while not changing the word sequence itself \n\n");    //user interface

    char * input = malloc(256);
    char * output = malloc(256);
    FILE *fpIn = NULL;
    FILE *fpOut = NULL;
    if(argc >= 3){
        input = argv[1];
        output = argv[2];
        fpIn = fopen(input, "r");
        fpOut = fopen(output, "r+");     //r+ because the file must exist and cannot be created according to the task
    }
    if(argc == 2){
        input = argv[1];
        fpIn = fopen(input, "r");
    }
        while(!fpIn){
            fclose(fpIn);
            printf("Your input file was not found, please re-enter your file name: ");
            for(int i = 0 ; i < strlen(input) ; ++i){
                input[i] = '\0';            //cleaning the string
            }
            scanf("%s", input);
            fpIn = fopen(input, "r");
            if(fpIn){
                printf("File has been succesfully found. \n\n");
                break;
            }

        }
        int noOut = 0;
        if(!fpOut){
            printf("Your output file was not found, the output will be printed on the screen\n");
            noOut = 1;
        }
                    //letter is an index in a word and indexinline in the current location in the line
        if(noOut){
            printf("The results: \n\n");
        }
        else
            printf("Your results are in your given file.\n");

        char* word  = calloc(MAX_SIZE, sizeof(char));
        int indexInLine = 0, letter = 0, clearFlag = 0;
        while(1){

            char* row = calloc(MAX_SIZE, sizeof(char));
            int amount = 0;                                 ///how many bytes were read
            amount = readFile(row,fpIn);
            if(amount == 0){
                char* result = calloc(MAX_SIZE, sizeof(char));    //in case there is no enter and there is still a word left
                int index = 0;
                resultWord(word, result, &index);

                if(noOut){
                    fwrite(result, 1, index, stdout);
                }
                else{
                    fwrite(result, 1, index, fpOut);
                }
                index = 0;
                letter = 0;
                clearString(word, result);
                free(result);
                break;
            }
            reverseRow(row, word, &letter, &indexInLine, amount, fpOut, &clearFlag, &noOut);
            free(row);
        }
        free(word);
        free(input);
        free(output);
        if(noOut)
            printf("\n\n");

        return 0;

}
