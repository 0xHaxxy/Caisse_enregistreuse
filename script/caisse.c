#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../headers/header.h"


int main(void)
{
    srand(time(NULL));

    double due_price = rand()%((MAX_PRICE * 100)-(MIN_PRICE * 100)+1)+(MIN_PRICE * 100);
    due_price = due_price/100;
    printf("Hello, you need to pay: RS %.2f\n", due_price);

struct  BILLS bills[13] = { {1000, 0}, {500, 0}, {200, 0}, 
{100, 0}, {50, 0}, {25, 0}, {20, 0}, {10, 0}, {5, 0}, {1, 0}, 
{0.5, 0}, {0.2, 0}, {0.05, 0}};
refill(bills);

/*
    double paid_price = ask_to_pay();
    double change = compare(paid_price, due_price);
    printf("\nremain: %.2f\n", change);

    int new_change = (int)round(change * 100);
    printf("\n");
    calcul_change(new_change);
*/

    return 0;
}