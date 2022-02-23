#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int count_lines(const char* filename);
void print_usage();

int main() {
	srand(time(NULL));
	Game* game = create_game();
	const char* filename = "allwords";

	print_usage();

	int num_lines = count_lines(filename);
	printf("%d lines loaded.\n", num_lines);
	printf("\n");

	// Load file content
	int index = 0;
	char (*lines)[5] = malloc(sizeof(char[5]) * num_lines);
	FILE *fd;
	int ch = 0;

	fd = fopen(filename, "r");
	if (fd == NULL) {
		printf("Cannot read file '%s'.\n", filename);
		return -1;
	}

	int i = 0;
	while ((ch = fgetc(fd)) != EOF) {
		if (ch == '\n') {
			index++;
			i = 0;
		} else {
			lines[index][i] = ch;
			i++;
		}
	}

	fclose(fd);

	// Test. Show random word
	int choice = (((float) num_lines) / RAND_MAX) * rand();
	printf("The choice is %d.\n", choice);

	// Setting word
	char input[5];
	for (int i = 0; i < 5; i++) {
		input[i] = lines[choice][i];
	}
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

int count_lines(const char* filename) {
	FILE *fd = fopen(filename, "r");
	int ch = 0;
	int lines = 0;

	if (fd == NULL)
		return 0;

	lines++;
	while ((ch = fgetc(fd)) != EOF) {
		if (ch == '\n')
			lines++;
	}
	fclose(fd);
	return lines;
}

