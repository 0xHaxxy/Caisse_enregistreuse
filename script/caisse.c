#include "../headers/header.h"


int main(void)
{
    srand(time(NULL));

   // create the cash box:    
    BILLS bills[13] = { {1000, 0}, {500, 0}, {200, 0}, 
    {100, 0}, {50, 0}, {25, 0}, {20, 0}, {10, 0}, {5, 0}, {1, 0}, 
    {0.5, 0}, {0.2, 0}, {0.05, 0}};

    double due_price = generatePrice();
    double paid_price = 0;
    menu(bills, &due_price, &paid_price);

    return 0;
}