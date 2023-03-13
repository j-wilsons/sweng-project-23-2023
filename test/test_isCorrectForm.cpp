#include "../include/client.hpp"


int test_isCorrectForm() {
    // valid
    if (!isCorrectForm("Buy 100 VAL")) return false;
    if (!isCorrectForm("Buy 200 VAL")) return false;
    if (!isCorrectForm("Buy 243101 MONEY")) return false;
    if (!isCorrectForm("Buy 1 1")) return false;
    if (!isCorrectForm("Sell 2  ")) return false;
    if (!isCorrectForm("Sell 0 3")) return false;
    if (!isCorrectForm("Sell 001 eggs")) return false;
    if (!isCorrectForm("Sell 100000000 uhnjiofeau284uroeuefoiERI")) return false;

    // invalid
    if (isCorrectForm("buy 100 val")) return false;
    if (isCorrectForm("byy 200 11")) return false;
    if (isCorrectForm("BUY 40.5 guns")) return false;
    if (isCorrectForm("BYU -12 apples for me please thank you")) return false;
    if (isCorrectForm("")) return false;
    if (isCorrectForm("   ")) return false;
    if (isCorrectForm(" 100 e")) return false;
    if (isCorrectForm("sell fifty NIKE")) return false;
    if (isCorrectForm("SELL 800 Ls")) return false;
    if (isCorrectForm("Slel 800 dsfrwergt")) return false;
    if (isCorrectForm("Slel 800 dsfrwergt")) return false;

    return true;
}

int main() {
    // if this value is not 0, the tests fail
    return (int)!test_isCorrectForm(); 
}
