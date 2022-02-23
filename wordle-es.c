#include <stdio.h>
#include <string.h>
#include "game.h"

void print_usage();

int main() {
	Game* game = create_game();

	print_usage();

	// Setting word
	char input[5] = {'l','a','p','i','z'};
	set_word_to_game(game, input);

	char buffer[64];

	// Print game
	print_game(game);

	while (game->finished == 0) {
		// Prompt and scan
		printf("> ");
		scanf("%s", buffer);

		// Check text length
		if (strlen(buffer) != 5) {
			printf("Only 5-letter words.\n");
			continue;
		}

		int is_good = play_game(game, buffer);

		printf("\n");
		if (is_good) {
			printf("Good.\n");
		} else {
			printf("Bad.\n");
		}

		// Print game
		printf("\n");
		print_game(game);

		if (!is_good && game->finished) {
			printf("\n");
			printf("Finished attempts.\n");
		}
	}
		
	return 0;
}

void print_usage() {
	printf("\n");
	printf("Wordle (ES)\n");
	printf("\n");
	printf("[[w]] -> right.\n");
	printf("[#w#] -> exists, but wrong position.\n");
	printf("[ w!] -> wrong.\n");
	printf("\n");
}
