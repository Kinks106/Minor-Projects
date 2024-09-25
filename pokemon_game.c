#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Function prototypes for Pokémon moves
int ember(int *, int *, char);
int vineWhip(int *, int *, char);
int waterGun(int *, int *, char);
int scratch(int *, int *);
int tackle(int *, int *);
void scaryFace(int *);
void growl(int *);
void tailWhip(int *);
void withdraw(int *);
void growth(int *);

// Define a structure to represent a Pokémon
typedef struct Pokemon {
    int hp;
    int atk;
    int def;
    int spd;
    char type;
    char name[20];
} Pokemon;

// Function prototypes for move sets
void charmanderMoves(Pokemon *attacker, Pokemon *defender, int choice);
void squirtleMoves(Pokemon *attacker, Pokemon *defender, int choice);
void bulbasaurMoves(Pokemon *attacker, Pokemon *defender, int choice);

// Random move generator for opponent
int getRandomMove() {
    return rand() % 4 + 1; // Random number between 1 and 4
}

// Ensure HP doesn't go below zero
void clampHP(int *hp) {
    if (*hp < 0) {
        *hp = 0;
    }
}

// Function to handle opponent's random move based on type
void opponentMoves(Pokemon *attacker, Pokemon *defender) {
    int choice = getRandomMove();  // Randomly choose a move (1-4)
    if (attacker->type == 'f') {
        printf("Opponent's %s uses move %d!\n", attacker->name, choice);
        charmanderMoves(attacker, defender, choice);
    } else if (attacker->type == 'w') {
        printf("Opponent's %s uses move %d!\n", attacker->name, choice);
        squirtleMoves(attacker, defender, choice);
    } else {
        printf("Opponent's %s uses move %d!\n", attacker->name, choice);
        bulbasaurMoves(attacker, defender, choice);
    }
}

// Function to handle player's Charmander moves
void charmanderMoves(Pokemon *attacker, Pokemon *defender, int choice) {
    switch (choice) {
        case 1:
            printf("%s uses Scratch!\n", attacker->name);
            defender->hp -= scratch(&attacker->atk, &defender->def);
            break;
        case 2:
            printf("%s unleashes Ember!\n", attacker->name);
            defender->hp -= ember(&attacker->atk, &defender->def, defender->type);
            break;
        case 3:
            printf("%s uses Scary Face!\n", attacker->name);
            scaryFace(&defender->spd);
            break;
        case 4:
            printf("%s growls to lower the opponent's Attack!\n", attacker->name);
            growl(&defender->atk);
            break;
        default:
            printf("Invalid choice! Please select a valid move.\n");
            break;
    }
}

// Function to handle player's Squirtle moves
void squirtleMoves(Pokemon *attacker, Pokemon *defender, int choice) {
    switch (choice) {
        case 1:
            printf("%s uses Tackle!\n", attacker->name);
            defender->hp -= tackle(&attacker->atk, &defender->def);
            break;
        case 2:
            printf("%s uses Water Gun!\n", attacker->name);
            defender->hp -= waterGun(&attacker->atk, &defender->def, defender->type);
            break;
        case 3:
            printf("%s performs Tail Whip!\n", attacker->name);
            tailWhip(&defender->def);
            break;
        case 4:
            printf("%s withdraws to raise its Defense!\n", attacker->name);
            withdraw(&attacker->def);
            break;
        default:
            printf("Invalid choice! Please select a valid move.\n");
            break;
    }
}

// Function to handle player's Bulbasaur moves
void bulbasaurMoves(Pokemon *attacker, Pokemon *defender, int choice) {
    switch (choice) {
        case 1:
            printf("%s uses Tackle!\n", attacker->name);
            defender->hp -= tackle(&attacker->atk, &defender->def);
            break;
        case 2:
            printf("%s uses Vine Whip!\n", attacker->name);
            defender->hp -= vineWhip(&attacker->atk, &defender->def, defender->type);
            break;
        case 3:
            printf("%s uses Growth!\n", attacker->name);
            growth(&attacker->atk);
            break;
        case 4:
            printf("%s growls to lower the opponent's Attack!\n", attacker->name);
            growl(&defender->atk);
            break;
        default:
            printf("Invalid choice! Please select a valid move.\n");
            break;
    }
}

int main() {
    srand(time(NULL)); // Seed random number generator

    char playAgain;
    do {
        Pokemon player, opponent;

        printf("Welcome to the world of Pokémon Battles!\n");
        printf("Choose your Pokémon:\n");
        printf("1) Charmander: The Flame Pokémon\n");
        printf("2) Squirtle: The Tiny Turtle Pokémon\n");
        printf("3) Bulbasaur: The Seed Pokémon\n");

        int self;
        if (scanf("%d", &self) != 1) {
            // Clear input buffer if input is invalid
            while (getchar() != '\n');
            printf("Invalid input! Starting over...\n");
            continue;
        }

        // Initialize player Pokémon with names
        if (self == 1) {
            player = (Pokemon){78, 109, 78, 100, 'f', "Charmander"};
        } else if (self == 2) {
            player = (Pokemon){79, 85, 100, 83, 'w', "Squirtle"};
        } else if (self == 3) {
            player = (Pokemon){80, 82, 83, 80, 'g', "Bulbasaur"};
        } else {
            printf("Invalid choice! Starting over...\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue; // Restart the loop if the choice is invalid
        }

        // Randomly choose opponent's Pokémon (1-3)
        int opp = rand() % 3 + 1; // Random choice from 1 to 3
        if (opp == 1) {
            opponent = (Pokemon){78, 109, 78, 100, 'f', "Charmander"};
        } else if (opp == 2) {
            opponent = (Pokemon){79, 85, 100, 83, 'w', "Squirtle"};
        } else {
            opponent = (Pokemon){80, 82, 83, 80, 'g', "Bulbasaur"};
        }

        // Dramatic introduction of Pokémon
        printf("\nYou have chosen %s!\n", player.name);
        printf("Your opponent has chosen %s!\n", opponent.name);

        // Battle loop with turn counter to prevent infinite loops
        int turn = 1;
        int maxTurns = 100;
        while (opponent.hp > 0 && player.hp > 0 && turn <= maxTurns) {
            printf("\n--- Turn %d ---\n", turn);
            // Determine who acts first based on speed
            if (player.spd >= opponent.spd) {
                // Player's turn
                int moveChoice;
                printf("Choose your move:\n");
                if (self == 1) {
                    printf("1) Scratch 2) Ember 3) Scary Face 4) Growl\n");
                } else if (self == 2) {
                    printf("1) Tackle 2) Water Gun 3) Tail Whip 4) Withdraw\n");
                } else {
                    printf("1) Tackle 2) Vine Whip 3) Growth 4) Growl\n");
                }

                if (scanf("%d", &moveChoice) != 1) {
                    // Clear input buffer if input is invalid
                    while (getchar() != '\n');
                    printf("Invalid input! Turn skipped.\n");
                } else {
                    if (self == 1) {
                        charmanderMoves(&player, &opponent, moveChoice);
                    } else if (self == 2) {
                        squirtleMoves(&player, &opponent, moveChoice);
                    } else {
                        bulbasaurMoves(&player, &opponent, moveChoice);
                    }
                    clampHP(&opponent.hp);
                }

                // Check if opponent fainted
                if (opponent.hp <= 0) {
                    printf("Your opponent's %s fainted! You win!\n", opponent.name);
                    break;
                }

                // Opponent's turn
                opponentMoves(&opponent, &player);
                clampHP(&player.hp);

                // Check if player fainted
                if (player.hp <= 0) {
                    printf("Your %s fainted. You lost the battle.\n", player.name);
                    break;
                }
            } else {
                // Opponent's turn first
                opponentMoves(&opponent, &player);
                clampHP(&player.hp);

                // Check if player fainted
                if (player.hp <= 0) {
                    printf("Your %s fainted. You lost the battle.\n", player.name);
                    break;
                }

                // Player's turn
                int moveChoice;
                printf("Choose your move:\n");
                if (self == 1) {
                    printf("1) Scratch 2) Ember 3) Scary Face 4) Growl\n");
                } else if (self == 2) {
                    printf("1) Tackle 2) Water Gun 3) Tail Whip 4) Withdraw\n");
                } else {
                    printf("1) Tackle 2) Vine Whip 3) Growth 4) Growl\n");
                }

                if (scanf("%d", &moveChoice) != 1) {
                    // Clear input buffer if input is invalid
                    while (getchar() != '\n');
                    printf("Invalid input! Turn skipped.\n");
                } else {
                    if (self == 1) {
                        charmanderMoves(&player, &opponent, moveChoice);
                    } else if (self == 2) {
                        squirtleMoves(&player, &opponent, moveChoice);
                    } else {
                        bulbasaurMoves(&player, &opponent, moveChoice);
                    }
                    clampHP(&opponent.hp);
                }

                // Check if opponent fainted
                if (opponent.hp <= 0) {
                    printf("Your opponent's %s fainted! You win!\n", opponent.name);
                    break;
                }
            }

            printf("Your %s has %d HP left.\n", player.name, player.hp);
            printf("Opponent's %s has %d HP left.\n", opponent.name, opponent.hp);

            turn++;
        }

        if (turn > maxTurns) {
            printf("\nThe battle has reached the maximum number of turns. It's a draw!\n");
        }

        if (player.hp > 0 && opponent.hp > 0 && turn <= maxTurns) {
            // This condition is already handled within the loop
        }

        // Ask if the player wants to play again
        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playAgain); // Added space before %c to ignore any leftover newline characters
    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}

// Move functions implementation
int ember(int *atk, int *def, char type) {
    float damage;
    if (type == 'g') { // Grass-type is weak to Fire
        damage = 1.92f * (*atk) / (*def) * 10;
    } else {
        damage = 1.92f * (*atk) / (*def) * 5;
    }
    return (int)damage;
}

int vineWhip(int *atk, int *def, char type) {
    float damage;
    if (type == 'w') { // Water-type is weak to Grass
        damage = 1.92f * (*atk) / (*def) * 10;
    } else {
        damage = 1.92f * (*atk) / (*def) * 5;
    }
    return (int)damage;
}

int waterGun(int *atk, int *def, char type) {
    float damage;
    if (type == 'f') { // Fire-type is weak to Water
        damage = 1.92f * (*atk) / (*def) * 10;
    } else {
        damage = 1.92f * (*atk) / (*def) * 5;
    }
    return (int)damage;
}

int scratch(int *atk, int *def) {
    return (int)(1.92f * (*atk) / (*def) * 7);
}

int tackle(int *atk, int *def) {
    return (int)(1.92f * (*atk) / (*def) * 7);
}

void scaryFace(int *spd) {
    if (*spd > 1) {
        *spd = (*spd * 2) / 3;
        if (*spd < 1) *spd = 1;
    }
    printf("Opponent's Speed reduced to %d!\n", *spd);
}

void growl(int *atk) {
    if (*atk > 1) {
        *atk = (*atk * 2) / 3;
        if (*atk < 1) *atk = 1;
    }
    printf("Opponent's Attack reduced to %d!\n", *atk);
}

void tailWhip(int *def) {
    if (*def > 1) {
        *def = (*def * 2) / 3;
        if (*def < 1) *def = 1;
    }
    printf("Opponent's Defense reduced to %d!\n", *def);
}

void withdraw(int *def) {
    *def = (*def * 3) / 2;
    printf("Your Defense increased to %d!\n", *def);
}

void growth(int *atk) {
    *atk = (*atk * 3) / 2;
    printf("Your Attack increased to %d!\n", *atk);
}
