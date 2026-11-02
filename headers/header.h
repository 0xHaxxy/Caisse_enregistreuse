#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_PRICE 1000
#define MIN_PRICE 200

double ask_to_pay ()
{
    double amount;
    printf("Please enter the amount: ");

    if(scanf("%lf", &amount) != 1)
    {
    // getchar va prendre les caractères dans le buffer et ils seront jettés vu que on assigne getchar à rien ici.
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        printf("Wrong format, please try again!\n");
        return ask_to_pay();  // réessayer
    }
    return amount;
}

double compare(double paid_price, double due_price)
{
   while (true)
   {
        if (paid_price < due_price)
        {
           printf("Insuffisant amount!\n");
           paid_price = ask_to_pay();
            continue;
        }
        
        else if (paid_price >= due_price)
        {
            printf("Thanks! to return: %.2f\n", paid_price - due_price);
            return paid_price - due_price;
            break;
        }
    }
}