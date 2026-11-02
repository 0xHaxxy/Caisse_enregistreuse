#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#define MAX_PRICE 3000
#define MIN_PRICE 150

double ask_to_pay ()
{
    double amount;
    printf("Please enter the amount: ");

    if(scanf("%lf", &amount) != 1)
    {
    // getchar va prendre les caractères dans le buffer. Les caractères différents de "n" et "EOF" seront jetté car on n'utilise pas int c:
    // il sert juste à stocké les valeurs récupérées.
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
            printf("Thanks!\n");
            return paid_price - due_price;
            break;
        }
    }
}

void calcul_change (int new_change)
{
    
    int bills[13] = {100000, 50000, 20000, 10000, 5000, 2500, 2000, 1000, 500, 100, 50, 20, 5};
    for (int i = 0; i < sizeof(bills)/sizeof(bills[0]); i++)
    {
        //to check if bills is needed or not
        int needed = new_change / bills[i];
        
        if (needed >= 1)
            {
                printf("you'll need:%d x RS %d\n", needed, bills[i]/100);
            }    
        int remainder = new_change % bills[i];
        new_change = remainder;
    }if (new_change != 0){printf("there is RS %.2f left\n", (double)new_change/100);}
}
