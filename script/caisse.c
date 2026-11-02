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

    double paid_price = ask_to_pay();
    double change = compare(paid_price, due_price);
    printf("\nremain: %.2f\n", change);

    int new_change = (int)round(change * 100);
    printf("\n");
    calcul_change(new_change);

    return 0;
}