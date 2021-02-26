#include "Game.h"

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Scene/Scenes.h"
#include "TextureCache.h"
#include "Character/Characters.h"
#include "Pickup/Pickups.h"

#include <iostream>
#include <fstream>

Game *Game::instance = nullptr;

Game::Game(void) {
	Game::instance = this;

	this->window = nullptr;
	this->renderer = nullptr;

	this->scene = nullptr;

	this->running = false;

	this->window_width = this->window_height = 0;
	this->debug_mode = true;
	this->cache = nullptr;

	this->frames = 0;
}
Game::~Game(void) {
	for(controller_group *controller : this->controllers) {
		delete controller;
	}

	delete this->scene;

	delete this->cache;

	Game::instance = nullptr;
}

void Game::init(void) {
	std::ofstream *error_log = new std::ofstream("Data/Exports/.txt/error_log.txt");
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		const char *error = SDL_GetError();
		std::cerr << error << std::endl;
		*error_log << error << std::endl;
	}
	if(IMG_Init(IMG_INIT_PNG) != 0) {
		const char *error = IMG_GetError();
		std::cerr << error << std::endl;
		*error_log << error << std::endl;
	}
	if(TTF_Init() != 0) {
		const char *error = TTF_GetError();
		std::cerr << error << std::endl;
		*error_log << error << std::endl;
	}
	error_log->close();
	delete error_log;

	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

//	this->window = SDL_CreateWindow("Fowl Play: Birds 'n' Bullets", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dm.w, dm.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN);
	this->window = SDL_CreateWindow("Fowl Play: Birds 'n' Bullets", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920 / 2, 1080 / 2, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	SDL_GetWindowSize(this->window, &this->window_width, &this->window_height);

	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetWindowIcon(this->window, IMG_Load("Data/Assets/.png/icon.png"));

	Characters::init();
	Scenes::init();
	Pickups::init();

	this->cache = new TextureCache;
//	this->cache->load_all("Data/Assets/.png"); // TODO fix.
	std::cout << std::endl;

	this->running = true;

	this->set_scene(Scenes::title);
}
void Game::refresh(void) {
	++ this->frames;

	SDL_PollEvent(&this->event);
	SDL_PumpEvents();

	switch(this->event.type) {
		case SDL_QUIT:
			this->running = false;
			break;
		case SDL_KEYDOWN:
			if(this->event.key.keysym.sym == SDLK_ESCAPE) {
				this->running = false;
				break;
			} else if(this->event.key.keysym.sym == SDLK_F11) {
				if(SDL_GetWindowFlags(this->window) & SDL_WINDOW_FULLSCREEN) {
					SDL_SetWindowFullscreen(this->window, 0);
				} else {
					SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN);
				}
				break;
			} else if(this->event.key.keysym.sym == SDLK_F1) {
				this->debug_mode = !this->debug_mode;
				if(this->debug_mode) {
					std::cout << "debug mode on" << std::endl;
				} else {
					std::cout << "debug mode off" << std::endl;
				}
			}
			break;
		case SDL_WINDOWEVENT:
			if(this->event.window.event == SDL_WINDOWEVENT_RESIZED) {
				this->window_width = this->event.window.data1;
				this->window_height = this->event.window.data2;
			}
			break;
		case SDL_CONTROLLERAXISMOTION:
			for(controller_group *controller : this->controllers) {
				controller->left_x = SDL_GameControllerGetAxis(controller->game_controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
				controller->left_y = SDL_GameControllerGetAxis(controller->game_controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);

				controller->right_x = SDL_GameControllerGetAxis(controller->game_controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX);
				controller->right_y = SDL_GameControllerGetAxis(controller->game_controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY);

				controller->right_trigger = SDL_GameControllerGetAxis(controller->game_controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
			}

			break;
		case SDL_CONTROLLERBUTTONDOWN:
			for(controller_group *controller : this->controllers) {
				if(controller->button_b == 0) {
					controller->button_b = SDL_GameControllerGetButton(controller->game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A); // switch sucks
					if(controller->button_b == 1) {
						if(this->scene != nullptr) {
							this->scene->on_button_press_b(controller);
						}
					}
				}

				if(controller->button_a == 0) {
					controller->button_a = SDL_GameControllerGetButton(controller->game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B);
					if(controller->button_a == 1) {
						if(this->scene != nullptr) {
							this->scene->on_button_press_a(controller);
						}
					}
				}

				if(controller->button_y == 0) {
					controller->button_y = SDL_GameControllerGetButton(controller->game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X);
					if(controller->button_y == 1) {
						if(this->scene != nullptr) {
							this->scene->on_button_press_y(controller);
						}
					}
				}
			}

			break;
		case SDL_CONTROLLERBUTTONUP:
			for(controller_group *controller : this->controllers) {
				controller->button_b = SDL_GameControllerGetButton(controller->game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A);
				if(controller->button_b == 0) {
					if(this->scene != nullptr) {
						this->scene->on_button_release_b(controller);
					}
				}

				controller->button_a = SDL_GameControllerGetButton(controller->game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B);
				if(controller->button_b == 0) {
					if(this->scene != nullptr) {
						this->scene->on_button_release_b(controller);
					}
				}

				controller->button_y = SDL_GameControllerGetButton(controller->game_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X);
				if(controller->button_y == 0) {
					if(this->scene != nullptr) {
						this->scene->on_button_release_y(controller);
					}
				}
			}

			break;
		case SDL_CONTROLLERDEVICEADDED:
			this->controllers.push_back(new controller_group {
				SDL_GameControllerOpen(this->event.cdevice.which)
			});

			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			for(controller_group *controller : this->get_controllers()) {
				if(SDL_GameControllerGetPlayerIndex(controller->game_controller) == this->event.cdevice.which) {
					std::cout << "Removing controller" << std::endl;
					SDL_GameControllerClose(controller->game_controller);
					this->controllers.erase(std::remove(this->controllers.begin(), this->controllers.end(), controller), this->controllers.end());
				}
			} // TODO figure out

			break;
	}

	if(this->scene != nullptr) {
		this->scene->update();
		this->scene->pre_render();
		this->scene->render();
		this->scene->post_render();
	}
}
void Game::de_init(void) {
	this->set_scene(nullptr);

	for(controller_group *controller : this->controllers) {
		SDL_GameControllerClose(controller->game_controller);
	}

	this->cache->clear_textures();
	this->cache->clear_texts();

	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	IMG_Quit();
	SDL_Quit();
}

bool Game::is_running(void) const {
	return this->running;
}

SDL_Renderer *Game::get_renderer(void) const {
	return this->renderer;
}

int Game::get_width(void) const {
	return this->window_width;
}
int Game::get_height(void) const {
	return this->window_height;
}
bool Game::is_in_debug_mode(void) const {
	return this->debug_mode;
}
float Game::get_ratio_w_over_h(void) const {
	return (float) this->get_width() / (float) this->get_height();
}
float Game::get_ratio_h_over_w(void) const {
	return (float) this->get_height() / (float) this->get_width();
}

void Game::set_scene(Scene *scene) {
	if(this->scene != nullptr) {
		this->scene->destroy();
	}
	this->scene = scene;
	if(this->scene != nullptr) {
		this->scene->setup();
	}
}
Scene *Game::get_scene(void) const {
	return this->scene;
}

controller_group *Game::get_controller(unsigned int index) const {
	try {
		return this->controllers.at(index);
	} catch(const std::out_of_range &exception) {
		return nullptr;
	}
}
std::vector<controller_group *> Game::get_controllers(void) const {
	return this->controllers;
}

int Game::get_frames(void) const {
	return this->frames;
}

TextureCache *Game::get_cache(void) const {
	return this->cache;
}

Game *Game::instantiate(void) {
	if(Game::instance == nullptr) {
		return new Game;
	}
	return nullptr;
}
Game *Game::get_instance(void) {
	return Game::instance;
}
