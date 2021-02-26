#pragma once

#ifndef GAME_H_
#define GAME_H_

#include "SDL2/SDL.h"
#include "controller_group.h"
#include "Scene/Object/Object.h"
#include "Scene/Scene.h"
#include "TextureCache.h"

#include <vector>

class Game {
	static Game *instance;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	std::vector<controller_group *> controllers; // TODO not pointers?

	Scene *scene;

	bool running;

	int window_width, window_height;
	bool debug_mode;

	int frames;

	TextureCache *cache; // TODO not pointer?

	Game(void);

	public:
		virtual ~Game(void);

		void init(void);
		void refresh(void);
		void de_init(void);

		bool is_running(void) const;

		SDL_Renderer *get_renderer(void) const;

		int get_width(void) const;
		int get_height(void) const;
		float get_ratio_w_over_h(void) const;
		float get_ratio_h_over_w(void) const;

		bool is_in_debug_mode(void) const;

		void set_scene(Scene *scene);
		Scene *get_scene(void) const;

		controller_group *get_controller(unsigned int index) const;
		std::vector<controller_group *> get_controllers(void) const;

		int get_frames(void) const;

		TextureCache *get_cache(void) const;

		static Game *instantiate(void);
		static Game *get_instance(void);
};

#endif /* GAME_H_ */
