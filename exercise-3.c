#include "exercise-3.h"

#define TOTAL_CARDS 52
#define PLAYER_COUNT 2
#define CARDS_PER_PLAYER 4
#define MAX_BOARD 52
#define NULL_CARD 65535


void initialize_deck(CARD deck[]) {
    int i = 0, suit, value;
    for (suit = 1; suit <= 4; suit++) {
        for (value = 1; value <= 13; value++) {
            deck[i++] = suit * 100 + value;
        }
    }
}


void shuffle_deck(CARD deck[]) {
	int r;
	CARD temp;
    for (int i = 0; i < TOTAL_CARDS; i++) {
        r = rand() % TOTAL_CARDS;
        temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }
}

void deal_cards(CARD players[][CARDS_PER_PLAYER], CARD deck[], int *deck_index) {
    for (int player = 0;   player < PLAYER_COUNT;   player++) {
        for (int card = 0; card < CARDS_PER_PLAYER; card++) {
            players[player][card] = deck[(*deck_index)++];
        }
    }
}

void initialize_board(CARD board[], int *boardSize, CARD deck[], int *deck_index) {
    int added = 0, index;

    while (added < 4) {
        CARD card = deck[*deck_index];

        if (card % 100 == 11){
			index = *deck_index;
			while(index < TOTAL_CARDS - 1){
				deck[index] = deck[index + 1];
				index++;
			}

			deck[index] = card;
			card = deck[*deck_index];
		}
        board[*boardSize] = card;
		(*deck_index)++;
		(*boardSize)++;
        added++;
    }
}


int point_of_card(CARD card) {
    int val = card % 100;
    int suit = card / 100;

    if (val == 1 || val == 11) return 1;
    if (val == 2 && suit == club) return 2;
    if (val == 10 && suit == diamond) return 3;
    return 0;
}

int deleteCard(CARD hand[], int index){
	if(hand[index] == NULL_CARD){
		return 1;
	}

	int card;
	CARD play = hand[index];
	for(card = index; card < CARDS_PER_PLAYER - 1; card++){
		hand[card] = hand[card + 1];
	}
	hand[card] = NULL_CARD;
	return 0;
}

void play_turn(CARD hand[], CARD board[], int *boardSize) {


	int numCards = 0;

	char nullCardCheck;
	do {
		nullCardCheck = hand[numCards] != NULL_CARD;
	} while(nullCardCheck && (++numCards < CARDS_PER_PLAYER));


    showCards(hand, numCards);

	int card;
	CARD play;
	do {
		printf("Choose a playable card to play: ");
		scanf("%d", &card);

    	play = hand[card - 1];
	} while(deleteCard(hand, card - 1));


    int val = play % 100;

    printf("Playing: \n");
    showCard(play);


    printf("\n");
	board[*boardSize] = play;
	(*boardSize)++;
	/*
    if (val == 11) {  // Jack: take all cards
        if (board_size > 0) {
            scores[player_id] += 1;
            for (int b = 0; b < board_size; b++) {
                scores[player_id] += point_of_card(board[b]);
                collected[player_id]++;
            }
            printf("Jack played! Taking all cards.\n");
            board_size = 0;
        }
    } 
	int found = 0;
	for (int b = 0; b < board_size; b++) {
	    if (board[b] % 100 == val) {
	        // Pairing
	        scores[player_id] += point_of_card(play) + point_of_card(board[b]);
	        collected[player_id] += 2;
	        printf("Pairing with:\n");
	        showCard(board[b]);
	        printf("\n");
	
	        // Bastra: only 1 card on board + not a jack
	        if (board_size == 1) {
	            printf("BASRA!\n");
	            scores[player_id] += 10;
	        }
	
	        // Remove paired card
	        for (int j = b; j < board_size - 1; j++) {
	            board[j] = board[j + 1];
	        }
	        board_size--;
	        found = 1;
	        break;
	    }
	}
	
	if (!found) {
	    board[board_size++] = play;
	    printf("No match, card added to board.\n");
	}
	*/
}

// Main function
int main(void) {
	CARD deck[TOTAL_CARDS];
	CARD players[PLAYER_COUNT][CARDS_PER_PLAYER];
	CARD board[TOTAL_CARDS];
	int boardSize = 0;
	int deck_index = 0;
	int scores[PLAYER_COUNT] = {0};
	int collected[PLAYER_COUNT] = {0};

    srand(time(NULL));

    initialize_deck(deck);
	shuffle_deck(deck);

    //showCards(deck, 52);

    initialize_board(board, &boardSize, deck, &deck_index);

	deal_cards(players, deck, &deck_index);


	int player = 0;
    while (1) {
        if (players[PLAYER_COUNT - 1][0] == NULL_CARD) {
			if(deck_index < 52)
				deal_cards(players, deck, &deck_index);
			else
				break;

        }

    	printf("Board:\n");
    	showCards(board, boardSize);
        play_turn(players[player], board, &boardSize);

		printf("deck index: %d\n", deck_index);


		player++;
		if(player >= PLAYER_COUNT)
			player = 0;
    }

    printf("\n--- Final Scores ---\n");
    for (int p = 0; p < PLAYER_COUNT; p++) {
        printf("Player %d: %d points, %d cards collected\n", p + 1, scores[p], collected[p]);
    }

    return 0;
}
