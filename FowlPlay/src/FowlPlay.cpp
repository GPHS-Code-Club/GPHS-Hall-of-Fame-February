#include "Game.h"

/*
 * TODO fix command inputs
 * TODO work on normal attacks
 * TODO dodge? shield?
 * TODO egg splat/shell particles
 * TODO pushing chickens physics
 * TODO level layout
 * TODO stage select
 * TODO controller mapping
 * TODO clearing bullets
 * TODO weapons and items
 * TODO more melee attacks
 * TODO frame rate mods
 * TODO optimize vector sorting
 * TODO object setup and destroy functions
 * TODO UI selecting code
 * TODO fucking fix particle pushing back
 * TODO better rumbling (length of immobility, bumping into walls, etc.)
 * TODO fix bullet slashing
 */

int main(int, char *[]) {
	Game *game = Game::instantiate();
	if(game != nullptr) {
		game->init();
		do {
			game->refresh();
		} while(game->is_running());
		game->de_init();
	}
	delete game;

	return 0;
}
