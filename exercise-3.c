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

    if ((val == 1)  || (val == 11))       return 1;
    if ((val == 2)  && (suit == club))    return 2;
    if ((val == 10) && (suit == diamond)) return 3;
    return 0;
}

void deleteCard(CARD cards[], int index, int size){
	int card;
	for(card = index; card < size - 1; card++){
		cards[card] = cards[card + 1];
	}
	cards[card] = NULL_CARD;
}

char combine(CARD board[], int *boardSize, CARD play, int *scores, int *collected){
	int i, j, card, value;
	char match = 0;
    value = play % 100;
	// removes the cards, which match with the played card
	for(card = 0; card < *boardSize; card++){
		if(value == board[card] % 100){
			*scores += point_of_card(play) + point_of_card(board[card]);
			deleteCard(board, card, *boardSize);
	        (*boardSize)--;
			match = 1;
			card = 0;
			*collected += 2;
		} 


		// combining two cards
		if(value <= 10)
		for(i = 0; i < *boardSize; i++){
			if((value == (board[card] + board[i]) % 100) && (card != i)){
				*scores += point_of_card(play) + point_of_card(board[card]) + point_of_card(board[i]);
				deleteCard(board, card, *boardSize);
				(*boardSize)--;
	
				if(card < i){
					deleteCard(board, i - 1, *boardSize);
					(*boardSize)--;
				}
				else {
					deleteCard(board, i, *boardSize);
					(*boardSize)--;
				}
				match = 1;
				card = 0;
				i = 0;
				*collected += 3;
			}
	
			// combining three cards
			for(j = 0; j < *boardSize; j++){
				if((value == (board[card] + board[i] + board[j]) % 100) && (card != i) && (card != j) && (i != j)){
					*scores += point_of_card(play) +point_of_card(board[card]) +point_of_card(board[i]) +point_of_card(board[j]);
					deleteCard(board, card, *boardSize);
					(*boardSize)--;
	
					if(card < i){
						deleteCard(board, i - 1, *boardSize);
						(*boardSize)--;
					}
					else {
						deleteCard(board, i, *boardSize);
						(*boardSize)--;
					}
	
					if((j < card) && (j < i)){
						deleteCard(board, j, *boardSize);
						(*boardSize)--;
					}
					else if((card < j) && (j < i)) {
						deleteCard(board, j - 1, *boardSize);
						(*boardSize)--;
					}
					else {
						deleteCard(board, j - 2, *boardSize);
						(*boardSize)--;
					}
	
					match = 1;
					card = 0;
					i = 0;
					j = 0;
					*collected += 4;
				}
			}
		}
	} 
	return match;
}

void play_turn(CARD hand[], CARD board[], int *boardSize, int *scores, int *collected) {
	int i, card, numCards = 0;

	// getting the number of cards of this player
	char nullCardCheck;
	do {
		nullCardCheck = hand[numCards] != NULL_CARD;
	} while(nullCardCheck && (++numCards < CARDS_PER_PLAYER));


	// printing cards with indexes
    showCards(hand, numCards);
	for(i = 0; i < numCards; i++)
		printf("  (%d)  ", i + 1);
	printf("\n");

	// getting input from user
	CARD play;
	char run = 1;
	do {
		printf("Choose a playable card to play: ");
		scanf("%d", &card);
		scanf("%*[^\n]");

		if((card <= numCards) && (card > 0)){
    		play = hand[card - 1];
			deleteCard(hand, card - 1, CARDS_PER_PLAYER);
			run = 0;
		}

	} while(run);



    printf("Playing: \n");
    showCard(play);

	// if the card is jack and there is card on board, clear the board
	if(((play % 100) == 11) && (*boardSize > 0)){
		for(int i = 0; i < *boardSize; i++){
			*scores += point_of_card(board[i]);
		}
		*boardSize = 0; 
		return;
	}


	// if there is match, end function
	if(combine(board, boardSize, play, scores, collected)){
		if(*boardSize == 0){
			*scores += 10;
		}
		return;
	}

	// add the card to the board
	board[*boardSize] = play;
	(*boardSize)++;
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

		printf("========= Player %d =========\n", player + 1);
        play_turn(players[player], board, &boardSize, &(scores[player]), &(collected[player]));

		player++;
		if(player >= PLAYER_COUNT)
			player = 0;
    }

	int winner_point = 0, winner = 0;

    printf("\n--- Final Scores ---\n");
    for (int p = 0; p < PLAYER_COUNT; p++) {
        printf("Player %d: %d points, %d cards collected\n", p + 1, scores[p], collected[p]);
		if(winner_point < scores[p]){
			winner_point = scores[p];
			winner = p + 1;
		}
    }

	printf("Player %d won!\n", winner);

    return 0;
}
