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


card make_card(int suit, int value) {
  card c;
  c.suit = suit;
  c.value = value;
  return c;
  //makes a card
}

card *make_card_ptr(int suit, int value) {
  card *c = mallocz(sizeof(card));
  c->suit = suit;
  c->value = value;
  return c;
  //makes a pointer to a card
}

typedef struct card_node {
  card *value;
  struct card_node *next;
  // defining a card node
} card_node;

typedef struct pile {
  card_node *head;
  int num_cards;
  char type;
  // defining a pile
} pile;

card_node *find_tail(pile *pile) {
  card_node *tail = pile->head;
  if (tail == 0)
    return 0;
  while (tail->next != 0) {
    tail = tail->next;
  }
  // finds the end of the a pile
  return tail;
}

card_node *make_node(card *card) {
  card_node *node = mallocz(sizeof(card_node));
  node->value = card;
  node->next = 0;
  return node;
  //makes a card node
}

int is_empty(pile *pile) 
{ return pile->num_cards == 0; }
// Checking for empty pile

void push(pile *pile, card *card) {
  card_node *tail = find_tail(pile);
  if (tail == NULL) {
    pile->head = make_node(card);
  } else {
    tail->next = make_node(card);
  }
  pile->num_cards++;
  // add card to end of list
}

card *pop(pile *pile) {
  // remove a card from the end of the list
}

void unshift(pile *pile, card *card) {
  // append to the beginning of the list
}


card *shift(pile *pile) {
 // remove a card from the beginning of the list
}

int main(void)
{
    //main functin where game will start
}
