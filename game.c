#include <stdio.h>
#include <stdlib.h>
#include "game.h"

Game* create_game() {
	Game* game = (Game*) malloc(sizeof(Game));
	for (int i = 0; i < 5; i++) {
		game->word[i] = '\0';
	}
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 5; x++) {
			game->matrix[y][x] = '\0';
			game->statuses[y][x] = EMPTY;
		}
	}
	game->attempts = 0;
	game->finished = 0;
	return game;
}

void set_word_to_game(Game* game, char word[5]) {
	for (int i = 0; i < 5; i++) {
		game->word[i] = word[i];
	}
}

Status check_word_at(Game* game, char word[5], int index) {
	if (word[index] == game->word[index]) {
		return RIGHT;
	}
	for (int i = 0; i < 5; i++) {
		if (game->word[i] == word[index]) {
			return MAYBE;
		}
	}
	return WRONG;
}

int play_game(Game* game, char word[5]) {
	int good_ones = 0;
	for (int i = 0; i < 5; i++) {
		Status status = check_word_at(game, word, i);
		if (status == RIGHT) {
			good_ones += 1;
		}
		game->statuses[game->attempts][i] = status;
		game->matrix[game->attempts][i] = word[i];
	}
	if (good_ones == 5) {
		game->finished = 1;
		return 1;
	}
	// Add attempts
	game->attempts += 1;
	// Check if finishing
	if (game->attempts == 6) {
		game->finished = 1;
	}
	return 0;
}

int check_word_exists(char word[5], char (*lines)[5], int size) {
	int exists = 0;
	for (int i = 0; i < size; i++) {
		// Next word
		int same = 1;
		// Check if they are the same word
		for (int j = 0; j < 5; j++) {
			if (word[j] != lines[i][j]) {
				// If any char is different, break this
				same = 0;
				break;
			}
		}
		// If the words are the same, break and set as exist
		if (same) {
			exists = 1;
			break;
		}
	}
	return exists;
}

void print_game(Game* game) {
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 5; x++) {
			switch(game->statuses[y][x]) {
				case EMPTY:
					printf("[ _ ] ");
					break;
				case RIGHT:
					printf("[[%c]] ", game->matrix[y][x]);
					break;
				case WRONG:
					printf("[ %c!] ", game->matrix[y][x]);
					break;
				case MAYBE:
					printf("[#%c#] ", game->matrix[y][x]);
					break;
				default:
					printf("Bad status\n");
			}
		}
		printf("\n");
	}
}


