#include <stdio.h>
#define CARDCOUNT = 52

enum Suit{
    suit_diamonds, suit_clubs, suit_hearts, suit_spades
};

enum Value{
    value_A, value_1, value_2, value_3, value_4, value_5, value_6, value_7, value_8, value_9, value_10, value_J, value_Q, value_K

};

typedef struct card {
    int value; //number
    int suit; //suit
    int revealed; //is the card revealed to user

} card;

void Shuffle() {
    // Shuffle the deck to be dealt randomly. Done at start of the game
}
int is_black(card c) {
	return c.suit == suit_clubs || c.suit == suit_spades;
}

int is_red(card c) {
	return c.suit == suit_hearts || c.suit == suit_diamonds;
}

int is_alternate_color(card first, card second) {
	return is_black(first) != is_black(second);
    //helper function to determine if two cards are alternating colours
}

int is_in_sequence(card lower, card higher) {
	return higher.value == lower.value + 1;
    //helper function to determine if two cards are numerically sequential
}

int can_be_placed_bottom(card parent, card child) {
	return is_alternate_color(parent, child) && is_in_sequence(child, parent);
    //checks to see if a card can be placed on bottom of a stack by calling sequence and colour functions
}

int is_same_suit(card first, card second) {
	return first.suit == second.suit;
    //helper function to determine if two cards are the same suit
}

int can_be_placed_on_foundation(card parent, card child) {
	return is_same_suit(parent, child) && is_in_sequence(parent, child);
    //checks to see if a card can be placed on the foundation by calling suit and sequence function
}

int main(void)
{
    //main functin where game will start
}
