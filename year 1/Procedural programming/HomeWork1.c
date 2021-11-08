///In the sequence of numbers, program finds the numbers which are squares of another number and counts them.
///The program end, when the input is zero
#include <stdio.h>            ///Author : Gustas Logvinovas
#include <math.h>             ///Pirmasis procedurinio programavimo namu darbas, 5-toji uzduotis.
                              ///Programa skaiciu sekoje randa, kitu skaiciu kvadratus ir juos skaiciuoja. Seka baigiasi tada, kai vartojojas iveda 0.

int main()
{
    printf("Please enter an integer number sequence which ends with number zero. \n");
    printf("This program will find integer numbers in a sequence which are equal to another integer powered by two. \n");
    printf("Keep in mind that you can enter it in one line separated by spacebar or enter it one by one.\n");
    printf("Also you can add as much numbers as you want, as long as you don't enter zero, after that, the program will end. \n");
    printf("SEQUENCE: ");

    int num = 0;
    int amount = 0;
    while(1)
    {

        char c;               ///symbol for validation

        if(scanf("%d", &num) == 1 && (scanf("%c", &c), c == ' ' || c == '\n'))         ///validation
        {

            if(num == 0)         ///ending program
            {
                break;
            }
            else                 ///searching for square root and checking if it is a natural number
            {
                double copyNum = num;
                int copy = sqrt(num);
                if(sqrt(copyNum) == copy)
                {
                    amount++;
                }
            }

        }

        else
        {
            printf("INVALID INPUT, ENTER AN INTEGER NUMBER \n");    ///invalid input

            char t;           ///char for clearing the buffer

            while(1)
            {
                scanf("%c", &t);

                if(t == ' ' || t == '\n')
                {
                    break;
                }

            }

        }

    }

    printf("Total amount of integer numbers who are equal to another integer powered by two: %d", amount);       ///output

    return 0;
}
