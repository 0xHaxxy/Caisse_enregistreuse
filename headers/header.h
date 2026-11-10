#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>   
#include <math.h>      
#include <time.h>
 
#define MAX_PRICE 3000
#define MIN_PRICE 150
#define SIZE 13
 
typedef struct
{
    double value;
    int count;
} BILLS;
 

 
/* FIX (price precision): the old version generated prices in cents (e.g. 12.33)
   but the smallest bill is 0.05, so some amounts could never be given back.
   Now the price is always a multiple of 0.05. */
double generatePrice()
{
    int steps = rand() % ((MAX_PRICE - MIN_PRICE) * 20 + 1) + MIN_PRICE * 20;
    return steps / 20.0;
}
 
void clear_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
 
/* FIX (double truncated with (int)): (int)(x * 100) can lose a cent
   (1234.9999999 -> 1234). lround rounds to the nearest cent instead.
   From here on, money is handled as whole cents (int), not double. */
int to_cents(double v)
{
    return (int)lround(v * 100.0);
}
 
double ask_to_pay()
{
    double amount;
    while (scanf("%lf", &amount) != 1)
    {
        clear_buffer();
        printf("Wrong format, please try again!\n");
    }
    return amount;
}
 
double compare(double paid_price, double due_price)
{
    while (paid_price < due_price)
    {
        printf("Insufficient amount!\n");
        paid_price = ask_to_pay();
    }
    printf("Registering...!\n");
    return paid_price - due_price;
}
 
/* ---------- cash box ---------- */
 
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
            choice = -1;   /* avoids using an uninitialized choice and loops again */
            continue;
        }
 
        if (choice == 0)
        {
            printf("leaving ...\n");
        }
        else if (choice >= 1 && choice <= SIZE)
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
 
    printf("Refilled successfully\n\n");
}
 
/* Rewritten to fix several bugs:
   - FIX (operator precedence): the old "(int)change*100 % (int)bills[i].value*100"
     was evaluated as "(((int)change*100) % (int)bills[i].value) * 100", which is wrong.
     For the 0.5 / 0.2 / 0.05 bills, (int)value is 0, so it was a modulo by zero (crash).
   - FIX (mixed units): "change" started in rupees but became cents after
     "change = remainder", so the next iterations and the final print were wrong.
     Now everything is in cents.
   - FIX (stock never decreased): bills[i].count is now decremented.
   - FIX (after refill): the old "continue" skipped to the next bill without
     recomputing. Now the whole breakdown is recomputed after a refill.
   - FIX (switch default): the old "default: ;" carried on as if nothing happened.
   - The exact breakdown is ALWAYS displayed, even when the stock is too low:
     the bills that are short are flagged with what is available and what is missing.
   - The stock is only modified when every needed bill is available. */
void compute_change(double change, BILLS bills[])
{
    int remaining = to_cents(change);
 
    if (remaining == 0)
    {
        printf("No change to give.\n\n");
        return;
    }
 
    while (true)
    {
        int plan[SIZE];
        int left = remaining;
        bool enough = true;
 
        /* 1. Exact breakdown, ignoring the stock (integer cents, no double drift) */
        for (int i = 0; i < SIZE; i++)
        {
            int unit = to_cents(bills[i].value);
            plan[i]  = left / unit;
            left    -= plan[i] * unit;
        }
 
        /* 2. Display it, and flag the bills the cash box cannot cover */
        printf("Change to give: RS %.2f\n", remaining / 100.0);
        for (int i = 0; i < SIZE; i++)
        {
            if (plan[i] == 0)
                continue;
 
            printf("you'll need: %d x RS %.2f", plan[i], bills[i].value);
            if (plan[i] > bills[i].count)
            {
                enough = false;
                printf("   <-- only %d available, %d missing",
                       bills[i].count, plan[i] - bills[i].count);
            }
            printf("\n");
        }
        if (left > 0)
            printf("there is RS %.2f left (no smaller bill)\n", left / 100.0);
        printf("\n");
 
        /* 3. Enough stock: take the bills out of the cash box */
        if (enough)
        {
            for (int i = 0; i < SIZE; i++)
                bills[i].count -= plan[i];   /* FIX: the stock is now decreased */
            printf("Change given successfully!\n\n");
            return;
        }
 
        /* 4. Not enough stock: close or refill, then recompute */
        printf("Not enough bills in the cash box.\n");
        printf("1. close the cash box\n");
        printf("2. refill cash\n");
        printf("==> ");
 
        int choice;
        if (scanf("%d", &choice) != 1)
        {
            clear_buffer();
            printf("Wrong format, please try again!\n");
            continue;
        }
        if (choice == 1) exit(1);
        if (choice == 2) refill(bills);
        printf("\n");
    }
}
 
/* FIX: the old "%d" with (int)bills[i].value displayed 0 for 0.5, 0.2 and 0.05.
   Now "%.2f" shows the real value. */
void showCash(BILLS bills[])
{
    printf(" \n");
    printf("Those are the available cash:  \n\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("RS %.2f ===>  %d bill(s) \n", bills[i].value, bills[i].count);
    }
    printf(" \n");
}
 
/* ---------- menu ---------- */
 
void menu(BILLS bills[], double *due_price, double *paid_price)
{
    int choice;
    double change = 0;
    printf("Welcome! ");
    do
    {
        printf("Please choose action to perform:\n\n");
        printf("[++++]1. check available bills\n");
        printf("[++++]2. Refill bills\n");
        printf("[++++]3. Show article price\n");
        printf("[++++]4. Ask to pay\n");
        printf("[++++]5. Compute change\n");
        printf("[++++]0. quit\n");
        printf("===>");
 
        if (scanf("%d", &choice) != 1)
        {
            clear_buffer();
            printf("Wrong format, please try again!\n");
            choice = -1;
            continue;
        }
 
        printf(" \n");
        switch (choice)
        {
            case 1:
                showCash(bills);
                break;
            case 2:
                refill(bills);
                break;
            case 3:
                printf("Hello, the price is : RS %.2f\n\n", *due_price);
                break;
            case 4:
                printf("Please enter the amount: ");
                *paid_price = ask_to_pay();
                change = compare(*paid_price, *due_price);
                break;
            case 5:
                compute_change(change, bills);
                change = 0;   /* FIX: reset, otherwise the same change could be given several times */
                break;
            case 0:
                break;
            default:
                printf("Invalid choice\n\n");   /* CHANGE: the old "default: ;" did nothing */
                break;
        }
    } while (choice != 0);
 
    printf("leaving ...\n");
}