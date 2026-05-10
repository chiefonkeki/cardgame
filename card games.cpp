#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define deckSize 52

struct Card {
	int values; // (1 = ACE, 11 = JACK, 12 = QUEEN, 13 = KING)
	char *suits;
	int points; // for card comparisons (lucky nine)
	int rank; // for high and low
};

void displayCard (struct Card card) {
	if (card.values == 1) {
		printf ("Ace of %s", card.suits) ;
	} else if (card.values == 11) {
		printf ("Jack of %s", card.suits) ;
	} else if (card.values == 12) {
		printf ("Queen of %s", card.suits) ;
	} else if (card.values == 13) {
		printf ("King of %s", card.suits) ;
	} else {
		printf ("%d of %s", card.values, card.suits);
	}
}

void shuffleDeck (struct Card deck []) {
	for (int i = 0; i < deckSize; i++) { // scans through the whole deck
		int j = rand () % deckSize; // keeps the random numbers be on 0-52, which is the deck size
		
		struct Card temp = deck[i]; // swapping of cards
		deck[i] = deck [j];
		deck[j] = temp;
	}
}
void createDeck (struct Card deck[]) {
	int cardValue[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
	char *cardSuit[] = {"Heart", "Diamond", "Club", "Spade"};
	int i, j;
	int index = 0;
	int ranks[] = {14,2,3,4,5,6,7,8,9,10,11,12,13}; // ACE is high, so 14 in first. it is in order because that is how the program scans and applies through it/
	
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 13; j++) {
			deck[index].suits = cardSuit[i];
			deck[index].values = cardValue[j];
			deck[index].rank = ranks[j];
			if (cardValue[j] >= 10) { // for lucky nine, face cards are fixed to the value of 10
				deck[index].points = 10;
			} else {
				deck[index].points = cardValue[j];
			}
			index++;
		}
	}	
}
void highLow (struct Card deck []) {
	char choice;
	int keepGoing;
	do {
		system("cls");
		
	 	printf("\n=== HIGH/LOW ===\n");
	 	printf("You will get a randomly selected card, the one with the highest value wins!\n");
	 	do {
	 		printf("\nWanna play (Y/N)? ");
	 		scanf("\n%c", &choice);
			if (choice == 'Y' || choice == 'y') {
				keepGoing = 1;
			} else if (choice == 'N' || choice == 'n') {
				keepGoing = 0;
				return;
			} else {
				keepGoing = -1;
				printf("Invalid Input. Try Again.\n");
			} 
		} while (keepGoing == -1);
	 	do {
	 		shuffleDeck(deck);
	 		
	 		struct Card player = deck[0];
			struct Card ai = deck[1];
	
			printf("Your card: ");
			displayCard(player);
	
			printf("\nOpposing card (AI): ");
			displayCard(ai);
	
			printf("\n\n");
	
			if (player.rank > ai.rank) {
				printf ("============\n");
				printf ("| You Win! |\n");
				printf ("============\n");
			} else if (player.rank < ai.rank) {
				printf ("=====================\n");
				printf ("| You Lose! AI wins.| \n");
				printf ("=====================\n");
			} else if  (player.rank == ai.rank) {
				printf ("==================\n");
				printf ("| It's A Tie! |\n");
				printf ("=================\n");
			}
		
			do {
		 		printf ("Play Again (Y/N)? ");
				scanf("\n%c", &choice);
				if (choice == 'Y' || choice == 'y') {
					keepGoing = 1;
				} else if (choice == 'N' || choice == 'n') {
					keepGoing = 0;
				} else {
					keepGoing = -1;
					printf("Invalid Input. Try Again.\n");
				}
			} while (keepGoing == -1);
		 } while (keepGoing == 1);
	} while (keepGoing == 1);
}

void luckyNine(struct Card deck[]) {
	
	char choice;
	int keepGoing;
	char drawChoice;
	
	do {
		system ("cls");
		
	 	printf("\n=== LUCKY NINE ===\n");
	 	printf("You will get two randomly selected cards, the one with the highest combined value wins!\n");
	 	do {
	 		printf("\nWanna play (Y/N)? ");
	 		scanf("\n%c", &choice);
			if (choice == 'Y' || choice == 'y') {
				keepGoing = 1;
			} else if (choice == 'N' || choice == 'n') {
				keepGoing = 0;
				return;
			} else {
				keepGoing = -1;
				printf("Invalid Input. Try Again.\n");
			} 
		} while (keepGoing == -1);
		do {
			shuffleDeck(deck);
			struct Card playerC1 = deck[0]; // player cards
	 		struct Card playerC2 = deck[1];
	 		struct Card aiC1 = deck[2]; // computer cards
	 		struct Card aiC2 = deck[3];
	 	
	 		int playerTotal = (playerC1.points + playerC2.points) % 10;
	 		int aiTotal = (aiC1.points + aiC2.points) % 10;
	 	
	 		printf("\nYour cards:\n");
	 		displayCard(playerC1);
	 		printf("\n");
	 		displayCard(playerC2);
	 		printf("\n");
	 		printf ("Current total: %d", playerTotal);
			do {
		 		printf("\nDraw another card (Y/N)? ");
		 		scanf("\n%c", &drawChoice);
				if (drawChoice == 'Y' || drawChoice == 'y') {
					keepGoing = 1;
					struct Card playerC3 = deck[4];
					printf ("\nYou drew a card\n");
					displayCard (playerC3);
					printf("\n");
					playerTotal += playerC3.points;
					playerTotal %= 10;
					printf ("New total: %d\n", playerTotal);
				} else if (drawChoice == 'N' || drawChoice == 'n') {
					keepGoing = 0;
				} else {
					keepGoing = -1;
					printf("Invalid Input. Try Again.\n");
				}
			} while (keepGoing == -1);
	 	
	 		printf("\nOpposing cards (AI):\n");
	 		displayCard(aiC1);
	 		printf("\n");
	 		displayCard(aiC2);
	 		printf("\n");
	 		if (aiTotal <= 5) {
	 			struct Card aiC3 = deck[5];
				printf ("\nComputer drew a card\n");
				displayCard (aiC3);
				printf("\n");
				aiTotal += aiC3.points;
				aiTotal %= 10;
				printf ("New total: %d\n", aiTotal);
		 	}

	 		if (playerTotal > aiTotal) {
				printf ("\n============\n");
				printf ("| You Win! |\n");
				printf ("============\n");
			} else if (playerTotal < aiTotal) {
				printf ("\n=====================\n");
				printf ("| You Lose! AI wins.| \n");
				printf ("=====================\n");
			} else if  (playerTotal == aiTotal) {
				printf ("\n==================\n");
				printf ("| It's A Tie! |\n");
				printf ("=================\n");
			}
	 	
			do {
				printf("\nPlay Again (Y/N)? ");
				scanf("\n%c", &choice);
				if (choice == 'Y' || choice == 'y') {
					keepGoing = 1;
				} else if (choice == 'N' || choice == 'n') {
					keepGoing = 0;
				} else {
					keepGoing = -1;
					printf("Invalid Input. Try Again.\n");
				}
			} while (keepGoing == -1);
		} while (keepGoing == 1);
	} while (keepGoing == 1);
}

int main () {
	int menuOption; //menu choice
	struct Card deck [deckSize];
	createDeck(deck);    
	srand(time(NULL)); // generates random seed based on time, so that the number generated by rand is not always the same.       
	
	do {
		system("cls");
		printf ("\n==============\n");
		printf ("| CARD GAMES |\n");
		printf ("==============\n");
		printf("Pick your game!\n");
		printf("1. High/Low\n2. Lucky Nine\n3. Exit\n");
		printf("\nEnter your choice: ");
		scanf("%d", &menuOption);
		
		switch (menuOption) {
			case 1:
				highLow(deck);
				break;
			case 2:
				luckyNine(deck);
				break;
			case 3:
				printf("\nThank you for playing ^_^ !\n");
				break;
			default:
				printf("Invalid Input. Try Again.\n");
		}
	} while(menuOption != 3);
	
	return 0;
}