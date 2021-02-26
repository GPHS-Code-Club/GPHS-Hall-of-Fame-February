#include "ObjectText.h"

#include "../../Game.h"
#include "SDL2/SDL_ttf.h"

ObjectText::ObjectText(Scene *scene, const char *font, const char *text, int pt, Uint8 r, Uint8 g, Uint8 b) : Object(scene) {
	SDL_Surface *surface = TTF_RenderText_Blended(TTF_OpenFont(font, pt), text, { r, g, b });
	this->set_sprite(sprite_ex_f {
		Game::get_instance()->get_renderer(),
		SDL_CreateTextureFromSurface(Game::get_instance()->get_renderer(), surface),
		SDL_Rect { 0, 0, surface->w, surface->h },
		SDL_FRect { 0, 0, 0, 0 },
		0,
		SDL_FPoint { 0, 0 },
		SDL_FLIP_NONE
	});
}

ObjectText::~ObjectText() {
	// TODO Auto-generated destructor stub
}

