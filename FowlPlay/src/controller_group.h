#pragma once

#ifndef CONTROLLER_GROUP_H_
#define CONTROLLER_GROUP_H_

#include "SDL2/SDL.h"

struct controller_group {
	SDL_GameController *game_controller = nullptr;
	Sint16 left_x = 0, left_y = 0;
	Sint16 right_x = 0, right_y = 0;
	Sint16 right_trigger = 0;
	Uint8 button_b = 0;
	Uint8 button_a = 0;
	Uint8 button_y = 0;
	unsigned int input_wait = 0;

	~controller_group(void) {
		game_controller = nullptr;
	}
};

#endif /* CONTROLLER_GROUP_H_ */
