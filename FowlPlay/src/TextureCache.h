#pragma once

#ifndef TEXTURECACHE_H_
#define TEXTURECACHE_H_

#include "SDL2/SDL.h"

#include <map>

class TextureCache {
	std::map<const char *, SDL_Texture *> texture_cache;
	std::map<std::tuple<const char *, const char *, int, Uint8, Uint8, Uint8>, SDL_Texture *> text_cache;

	public:
		SDL_Texture *&texture_at(const char * const &key);
		void insert_texture(const char *key, SDL_Texture *texture);
		SDL_Texture *load_texture(const char *key);
		void clear_textures(void);
		void load_all_textures(const char *directory);

		SDL_Texture *&text_at(std::tuple<const char *, const char *, int, Uint8, Uint8, Uint8> key);
		void insert_text(std::tuple<const char *, const char *, int, Uint8, Uint8, Uint8> key, SDL_Texture *texture);
		SDL_Texture *load_text(const char *font, const char *text, int pt, Uint8 r, Uint8 g, Uint8 b);
		void clear_texts(void);
};

#endif /* TEXTURECACHE_H_ */
