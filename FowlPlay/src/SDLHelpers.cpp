#include "SDLHelpers.h"

SDL_FPoint sum(SDL_FPoint left_operand, SDL_FPoint right_operand) {
	return SDL_FPoint {
		left_operand.x + right_operand.x,
		left_operand.y + right_operand.y
	};
}
SDL_FPoint difference(SDL_FPoint left_operand, SDL_FPoint right_operand) {
	return SDL_FPoint {
		left_operand.x - right_operand.x,
		left_operand.y - right_operand.y
	};
}
SDL_Rect f_rect_to_rect(SDL_FRect f_rect) {
	return SDL_Rect {
		(int) f_rect.x, (int) f_rect.y, (int) f_rect.w, (int) f_rect.h
	};
}
