#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/header.h"

int main(void)
{
    srand(time(NULL));

    double due_price = rand()%(MAX_PRICE-MIN_PRICE+1)+MIN_PRICE;
    printf("Hello, you need to pay: %.2f\n", due_price);

    double paid_price = ask_to_pay();
    double change = compare(paid_price, due_price);

    return 0;
}