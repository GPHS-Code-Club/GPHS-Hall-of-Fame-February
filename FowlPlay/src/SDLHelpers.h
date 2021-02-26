#pragma once

#ifndef SDLHELPERS_H_
#define SDLHELPERS_H_

#include "SDL2/SDL.h"

SDL_FPoint sum(SDL_FPoint left_operand, SDL_FPoint right_operand);
SDL_FPoint difference(SDL_FPoint left_operand, SDL_FPoint right_operand);
SDL_Rect f_rect_to_rect(SDL_FRect f_rect);

#endif /* SDLHELPERS_H_ */
