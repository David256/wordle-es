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
 * Returns 1 if the attempt is right, 0 otherwise.
 */
int play_game(Game*, char[5]);

/**
 * Print the game.
 */
void print_game(Game*);

#endif

