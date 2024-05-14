#include <stdio.h>
#define CARDCOUNT = 52

enum Suit{
    suit_diamonds, suit_clubs, suit_hearts, suit_spades, suit_count
};

enum Value{
    value_A, value_1, value_2, value_3, value_4, value_5, value_6, value_7, value_8, value_9, value_10, value_J, value_Q, value_K, value_count

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
  pile->num_cards--;
  // find the (n-1)th card
  card_node *pre_tail = pile->head;
  for (int i = 0; i < pile->num_cards - 1; i++)
    pre_tail = pre_tail->next;
  card_node *tail = pre_tail->next;
  card *card = tail->value;
  pre_tail->next = 0;
  free(tail);
  return card;
}

void unshift(pile *pile, card *card) {
  // append to the beginning of the list
  card_node *new_head = make_node(card);
  new_head->next = pile->head;
  pile->head = new_head;
  pile->num_cards++;
}


card *shift(pile *pile) {
 // remove a card from the beginning of the list
 pile->num_cards--;
  card_node *old_head = pile->head;
  pile->head = old_head->next;

  card *card = old_head->value;
  free(old_head);
  return card;
}
card *peek_card_at(pile *pile, int index) {
  card_node *head = pile->head;
  for (int i = 0; i < index; i++)
    head = head->next;
  return head->value;
}

card *peek(pile *pile) {
  if (pile->head == NULL) {
    return NULL;
  }
  return pile->head->value;
}

card *peek_last(pile *pile) {
  if (pile->head == NULL) {
    return NULL;
  }
  return peek_card_at(pile, pile->num_cards - 1);
}

pile *make_pile() {
  pile *pile_ptr = mallocz(sizeof(pile));
  pile_ptr->num_cards = 0;
  return pile_ptr;
}

void fill_deck(pile *pile) {
  for (int rank = 0; rank < value_count; rank++) {
    for (int suit = 0; suit < suit_count; suit++) {
      push(pile, make_card_ptr(suit, rank));
    }
  }
}

#define COLUMN_COUNT 7
#define FOUNDATION_COUNT 4

enum {
  PILE_DECK,
  PILE_WASTE,
  PILE_FOUNDATION1,
  PILE_FOUNDATION2,
  PILE_FOUNDATION3,
  PILE_FOUNDATION4,
  PILE_COLUMN1,
  PILE_COLUMN2,
  PILE_COLUMN3,
  PILE_COLUMN4,
  PILE_COLUMN5,
  PILE_COLUMN6,
  PILE_COLUMN7,
  PILE_COUNT
};

char pile_types[] = "dwffffccccccc";

typedef struct game_state {
  pile **piles;
  int pile_count;
  int score;
} game_state;

game_state *make_game_state() {
  game_state *state = mallocz(sizeof(game_state));
  state->piles = mallocz(sizeof(pile *) * PILE_COUNT);
  for (int pile_idx = 0; pile_idx < PILE_COUNT; pile_idx++) {
    state->piles[pile_idx] = make_pile();
    state->piles[pile_idx]->type = pile_types[pile_idx];
  }
  return state;
}

void insert(pile *pile, card *card, int idx) {
  card_node *pre_tail = pile->head;
  for (int i = 0; i < idx; i++)
    pre_tail = pre_tail->next;
  card_node *card_node = make_node(card);
  card_node->next = pre_tail->next;
  pre_tail->next = card_node;
  pile->num_cards++;
}

void shuffle_pile(pile *pile) {
  int shuffle_times = pile->num_cards * 10;
  for (int i = 0; i < shuffle_times; i++) {
    // unshift a card and insert to random place
    int idx = rand() % pile->num_cards - 1;
    card *card = shift(pile);
    insert(pile, card, idx);
  }
}


pile *column(game_state *state, int index_one_based) {
  return state->piles[PILE_COLUMN1 + index_one_based - 1];
}

pile *foundation(game_state *state, int index_one_based) {
  return state->piles[PILE_FOUNDATION1 + index_one_based - 1];
}

// returns 1 if a card was revealed
int reveal(card *card) {
  if (card == NULL)
    return 0;
  card->revealed = 1;
  return 1;
}

void hide(card *card) {
  if (card == NULL)
    return;
  card->revealed = 0;
}

void turn(game_state *state) {
  // moves 1 card from stock to waste
  card *revealed_card = shift(stock(state));
  reveal(revealed_card);
  push(state->piles[PILE_WASTE], revealed_card);
}

void deal(game_state *state) {
  // assuming a shuffled deck
  pile *deck = state->piles[PILE_DECK];
  // deal columns
  for (int i = 0; i < COLUMN_COUNT; i++) {
    int column_idx = i + 1;
    pile *column = state->piles[PILE_COLUMN1 + i];
    // deal N cards in Nth column
    for (int card_num = 0; card_num < column_idx; card_num++) {
      card *card = shift(deck);
      push(column, card);
      // reveal last card from the column
      if (card_num == column_idx - 1) {
        reveal(card);
      }
    }
  }
  // reveal 1 card
  turn(state);
}

int rows, cols;

int main(void)
{
    //main functin where game will start
}
