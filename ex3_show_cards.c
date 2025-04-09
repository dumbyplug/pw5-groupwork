#include <stdio.h>

typedef unsigned short CARD;

void printCardPart(CARD card, int part);

void showCard(CARD card);

void showCards(CARD cards[], int length);

enum cardType {
	spade = 1,
	heart = 2,
	diamond = 3,
	club = 4
};

void printCardPart(CARD card, int part) {
	enum cardType type = card / 100; // spades , hearts etc.
	int cardValue = card % 100; // 1-13

	char cardNumber;
	char symbol;

	if (cardValue < 10 && cardValue > 1) {
		cardNumber = (char)(cardValue + 48);
	}
	else {
		switch (cardValue)
		{
		case 1:
			cardNumber = 'A';
			break;
		case 10:
			cardNumber = 'T';
			break;
		case 11:
			cardNumber = 'J';
			break;
		case 12:
			cardNumber = 'Q';
			break;
		case 13:
			cardNumber = 'K';
			break;
		default:
			cardNumber = '#';
			break;
		}
	}


	switch (type)
	{
	case spade:
		symbol = 'S';
		break;
	case heart:
		symbol = 'H';
		break;
	case diamond:
		symbol = 'D';
		break;
	case club:
		symbol = 'C';
		break;
	default:
		symbol = '#';
		break;
	}


	switch (part)
	{
	case 1:
	case 5:
		printf(" +---+ ");
		break;
	case 2:
		printf(" |  \x1b[1;31m%c\x1b[0m| ", symbol);
		break;
	case 3:
		printf(" | \x1b[1;30m%c\x1b[0m | ", cardNumber);
		break;
	case 4:
		printf(" |\x1b[1;31m%c\x1b[0m  | ", symbol);
		break;
	default:
		printf(" ##### ");
		break;
	}

}

void showCard(CARD card) {
	for (size_t i = 1; i <= 5; i++)
	{
		printCardPart(card, i);
		printf("\n");
	}
}

void showCards(CARD cards[], int length) {

	int repeat = 1;
	float cardLimit = 10.0;
	if (length / cardLimit > 1.0) {
		repeat = length / cardLimit + 1;
	}

	for (size_t r = 1; r <= repeat; r++)
	{
		for (size_t i = 1; i <= 5; i++)
		{
			int len = r * cardLimit;
			if (len > length) len = length;
			for (size_t j = ((r - 1) * cardLimit); j < len; j++)
			{
				printCardPart(cards[j], i);
			}
			printf("\n");
		}
		printf("\n");
	}

}