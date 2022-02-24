#ifndef _GAME_H_
#define _GAME_H_

typedef enum status {
	EMPTY,
	RIGHT,
	WRONG,
	MAYBE,
} Status;

typedef struct {
	char word[5];
	char matrix[6][5];
	Status statuses[6][5];
	int attempts;
	int finished;
} Game;

/**
 * Create a empty game.
 */
Game* create_game();

/**
 * Set a word to play in the game.
 */
void set_word_to_game(Game*, char[5]);

/**
 * Check statuses for a given word.
 */
Status check_word_at(Game*, char[5], int);

/**
 * Returns 1 if the word exists, 0 otherwise.
 */
int check_word_exists(char[5], char (*)[5], int);

/**
 * Returns 1 if the attempt is right, 0 otherwise.
 */
int play_game(Game*, char[5]);

/**
 * Print the game.
 */
void print_game(Game*);

#endif

