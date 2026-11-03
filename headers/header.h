#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#define MAX_PRICE 3000
#define MIN_PRICE 150
#define SIZE 13

typedef  struct  
{
    double value;
    int count;
}BILLS;

double generatePrice()
{
    srand(time(NULL));
    double due_price = rand()%((MAX_PRICE * 100)-(MIN_PRICE * 100)+1)+(MIN_PRICE * 100);
    due_price = due_price/100;
    printf("Hello, you need to pay: RS %.2f\n", due_price);
    
    return due_price;
}

static void clear_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

double ask_to_pay ()
{
    double amount;
    printf("Please enter the amount: ");

    if(scanf("%lf", &amount) != 1)
    {
        clear_buffer();
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
/*
void calcul_change (int new_change)
{
    
    int bills[13] = {{100000, 50000, 20000, 10000, 5000, 2500, 2000, 1000, 500, 100, 50, 20, 5},
                     {1, 2, 4, 1, 3, 2, 7, 4, 2 ,1 ,4, 2, 4, 1}};
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
*/

void refill(BILLS bills[])
{
    int choice;
    do
    {
        printf("Please choose the bills to refill: \n");
        printf("1. RS 1000\n");
        printf("2. RS 500\n");
        printf("3. RS 200\n");
        printf("4. RS 100\n");
        printf("5. RS 50\n");
        printf("6. RS 25\n");
        printf("7. RS 20\n");
        printf("8. RS 10\n");
        printf("9. RS 5\n");
        printf("10. RS 1\n");
        printf("11. RS 0.5\n");
        printf("12. RS 0.2\n");
        printf("13. RS 0.05\n");
        printf("0. quit\n");
        printf(" \n");
        printf("==> ");

        if (scanf("%d", &choice) != 1)
        {
            clear_buffer();
            printf("Wrong format, please try again!\n");
            choice = -1;   /* évite d'utiliser choice non initialisé et force à reboucler */
            continue;
        }

        if (choice == 0)
        {
            printf("leaving ...\n");
        }
        else if (choice >= 1 && choice <= 13)
        {
            int number;
            printf("How many bills of RS %.2f do you want? ", bills[choice - 1].value);

            if (scanf("%d", &number) != 1 || number < 0)
            {
                clear_buffer();
                printf("Wrong format, please try again!\n");
            }
            else
            {
                bills[choice - 1].count += number;
                printf("bills added\n");
            }
        }
        else
        {
            printf("Invalid choice\n");
        }
    } while (choice != 0);

    printf("Refilled successfully\n");
}

void showCash (BILLS bills[])
{
    for (int i = 0; i < SIZE; i++)
    {
        printf("Il y a %d billet(s) de RS %.2f\n", bills[i].count, bills[i].value);
    }
}

