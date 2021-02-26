#include "TextureCache.h"

#include "SDL2/SDL_image.h"
#include "Game.h"
#include "SDL2/SDL_ttf.h"

#include <iostream>
#include <filesystem>

SDL_Texture *&TextureCache::texture_at(const char * const &key) {
	return TextureCache::texture_cache.at(key);
}
void TextureCache::insert_texture(const char *key, SDL_Texture *texture) {
	TextureCache::texture_cache.insert(std::make_pair(key, texture));
	if(Game::get_instance()->is_in_debug_mode()) {
		std::cout << "caching \"" << key << "\"" << std::endl;
	}
}
SDL_Texture *TextureCache::load_texture(const char *key) {
	SDL_Texture *texture;
	try {
		texture = TextureCache::texture_at(key);
//		std::cout << "\"" << key << "\" is already cached" << std::endl;
	} catch(const std::out_of_range &exception) {
//		std::cout << "key does not exist, inserting... ";
		texture = SDL_CreateTextureFromSurface(Game::get_instance()->get_renderer(), IMG_Load(key));
		TextureCache::insert_texture(key, texture);
	}

//	std::cout << "there are currently " << TextureCache::cache.size() << " entries." << std::endl;

	return texture;
}
void TextureCache::clear_textures(void) {
	if(Game::get_instance()->is_in_debug_mode()) {
		std::cout << "clearing texture cache" << std::endl;
	}
	for(auto [k, v] : this->texture_cache) {
//		delete k;
		SDL_DestroyTexture(v);
	}
	this->texture_cache.clear();
}
void TextureCache::load_all_textures(const char *directory) {
	for(const auto &entry : std::filesystem::directory_iterator(directory)) {
		std::string path = entry.path().string();
		std::replace(path.begin(), path.end(), '\\', '/');
		TextureCache::load_texture(std::move(path.c_str()));
	}
}

SDL_Texture *&TextureCache::text_at(std::tuple<const char *, const char *, int, Uint8, Uint8, Uint8> key) {
	return TextureCache::text_cache.at(key);
}
void TextureCache::insert_text(std::tuple<const char *, const char *, int, Uint8, Uint8, Uint8> key, SDL_Texture *texture) {
	TextureCache::text_cache.insert(std::make_pair(key, texture));
	if(Game::get_instance()->is_in_debug_mode()) {
		std::cout << "caching some text" << std::endl;
	}
}
SDL_Texture *TextureCache::load_text(const char *font, const char *text, int pt, Uint8 r, Uint8 g, Uint8 b) {
	SDL_Texture *texture;
	auto key = std::make_tuple(font, text, pt, r, g, b);
	try {
		texture = TextureCache::text_at(key);
	} catch(const std::out_of_range &exception) {
		texture = SDL_CreateTextureFromSurface(Game::get_instance()->get_renderer(), TTF_RenderText_Blended(TTF_OpenFont(font, pt), text, { r, g, b }));
		TextureCache::insert_text(key, texture);
	}

	return texture;
}
void TextureCache::clear_texts(void) {
	if(Game::get_instance()->is_in_debug_mode()) {
		std::cout << "clearing text cache" << std::endl;
	}
	for(auto [k, v] : this->text_cache) {
		SDL_DestroyTexture(v);
	}
	this->text_cache.clear();
}
