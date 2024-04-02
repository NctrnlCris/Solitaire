#include <stdio.h>
#define CARDCOUNT = 52

enum Suit{
    DIAMONDS, CLUBS, HEARTS, SPADES
};

enum Value{
    valueA, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, valueJ, valueQ, valueK

};

typedef struct{
    int value;
    int suit;

} Card;

void Shuffle() {
    // Shuffle the deck to be dealt randomly. Done at start of the game
}

int main(void)
{
}
