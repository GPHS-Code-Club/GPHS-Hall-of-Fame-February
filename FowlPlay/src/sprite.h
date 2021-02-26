#pragma once

#ifndef SPRITE_H_
#define SPRITE_H_

#include "SDL2/SDL.h"

struct sprite {
	SDL_Renderer *renderer = nullptr;
	SDL_Texture *texture = nullptr;
	SDL_Rect srcrect = { 0, 0, 0, 0 };
	SDL_Rect dstrect = { 0, 0, 0, 0 };

	static void render(const sprite &s) {
		SDL_RenderCopy(s.renderer, s.texture, &s.srcrect, &s.dstrect);
	}
};
struct sprite_ex {
	SDL_Renderer *renderer = nullptr;
	SDL_Texture *texture = nullptr;
	SDL_Rect srcrect = { 0, 0, 0, 0 };
	SDL_Rect dstrect = { 0, 0, 0, 0 };
	double angle = 0;
	SDL_Point center = { 0, 0 };
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	static void render(const sprite_ex &s) {
		SDL_RenderCopyEx(s.renderer, s.texture, &s.srcrect, &s.dstrect, s.angle, &s.center, s.flip);
	}
};
struct sprite_ex_f {
	SDL_Renderer *renderer = nullptr;
	SDL_Texture *texture = nullptr;
	SDL_Rect srcrect = { 0, 0, 0, 0 };
	SDL_FRect dstrect = { 0, 0, 0, 0 };
	double angle = 0;
	SDL_FPoint center = { 0, 0 };
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	static void render(const sprite_ex_f &s) {
		SDL_RenderCopyExF(s.renderer, s.texture, &s.srcrect, &s.dstrect, s.angle, &s.center, s.flip);
	}
};
struct sprite_f {
	SDL_Renderer *renderer = nullptr;
	SDL_Texture *texture = nullptr;
	SDL_Rect srcrect = { 0, 0, 0, 0 };
	SDL_FRect dstrect = { 0, 0, 0, 0 };

	static void render(const sprite_f &s) {
		SDL_RenderCopyF(s.renderer, s.texture, &s.srcrect, &s.dstrect);
	}
};

#endif /* SPRITE_H_ */
