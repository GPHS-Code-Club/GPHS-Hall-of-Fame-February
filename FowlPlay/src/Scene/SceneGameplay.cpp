#include "SceneGameplay.h"

#include "Object/ObjectPlayer.h"
#include "Object/ObjectParticle.h"
#include "Object/ObjectSlash.h"
#include "Object/ObjectWall.h"
#include "Object/ObjectPickup.h"
#include "../Character/Characters.h"
#include "../Game.h"
#include "../TextureCache.h"
#include "../Pickup/Pickups.h"

SceneGameplay::SceneGameplay(void) : Scene(36, 184, 61) {
	this->pond_wall = nullptr;
	this->left_fence_wall = nullptr;
	this->top_fence_wall = nullptr;
	this->right_fence_wall = nullptr;
}
SceneGameplay::~SceneGameplay(void) {
	// TODO
}

void SceneGameplay::setup(void) {
	Scene::setup();

	this->pond_wall = new ObjectWall(this, 0.395, 0.335, 0.21, 0.2, false);
	this->push_back(this->pond_wall);

	this->left_fence_wall = new ObjectWall(this, 0.0165, 0.025, 0.0171, 0.9325, true);
	this->push_back(this->left_fence_wall);

	this->top_fence_wall = new ObjectWall(this, 0.0165, 0.025, 0.962, 0.05, true);
	this->push_back(this->top_fence_wall);

	this->right_fence_wall = new ObjectWall(this, 0.9625, 0.025, 0.0171, 0.9325, true);
	this->push_back(this->right_fence_wall);

	Object *cowtana = new ObjectPickup(this, Pickups::cowtana);
	cowtana->set_pos_percent(0.25, 0.25);
	this->push_back(cowtana);

	Object *player = new ObjectPlayer(this, Characters::goose, 0);
	player->set_pos_percent(0.25, 0.5);
	this->push_back(player);

	this->map.insert(std::make_pair(0, SDL_Point { 0 * 64, 0 * 64 }));
	this->map.insert(std::make_pair(1, SDL_Point { 1 * 64, 0 * 64 }));
	this->map.insert(std::make_pair(2, SDL_Point { 2 * 64, 0 * 64 }));

	this->map.insert(std::make_pair(3, SDL_Point { 0 * 64, 1 * 64 }));
	this->map.insert(std::make_pair(4, SDL_Point { 1 * 64, 1 * 64 }));
	this->map.insert(std::make_pair(5, SDL_Point { 2 * 64, 1 * 64 }));
	this->map.insert(std::make_pair(6, SDL_Point { 3 * 64, 1 * 64 }));

	this->map.insert(std::make_pair(7, SDL_Point { 0 * 64, 2 * 64 }));
	this->map.insert(std::make_pair(8, SDL_Point { 1 * 64, 2 * 64 }));
	this->map.insert(std::make_pair(9, SDL_Point { 2 * 64, 2 * 64 }));
	this->map.insert(std::make_pair(10, SDL_Point { 3 * 64, 2 * 64 }));

	this->map.insert(std::make_pair(11, SDL_Point { 0 * 64, 3 * 64 }));
	this->map.insert(std::make_pair(12, SDL_Point { 1 * 64, 3 * 64 }));
	this->map.insert(std::make_pair(13, SDL_Point { 2 * 64, 3 * 64 }));
	this->map.insert(std::make_pair(14, SDL_Point { 3 * 64, 3 * 64 }));

	this->map.insert(std::make_pair(15, SDL_Point { 0 * 64, 4 * 64 }));
	this->map.insert(std::make_pair(16, SDL_Point { 1 * 64, 4 * 64 }));
	this->map.insert(std::make_pair(17, SDL_Point { 2 * 64, 4 * 64 }));
	this->map.insert(std::make_pair(18, SDL_Point { 3 * 64, 4 * 64 }));
}
void SceneGameplay::update(void) {
	Scene::update();
}
void SceneGameplay::render(void) {
	int x_tiles = 20, y_tiles = 12;
	float w = Game::get_instance()->get_width() / (int) x_tiles, h = Game::get_instance()->get_height() / (int) y_tiles;
	for(int i = 0; i < x_tiles; ++ i) {
		for(int j = 0; j < y_tiles; ++ j) {
			SDL_RenderCopyF(Game::get_instance()->get_renderer(),
				Game::get_instance()->get_cache()->load_texture("Data/Assets/.png/tile_sheet.png"),
				new SDL_Rect { this->map.at(this->tiles[j][i]).x, this->map.at(this->tiles[j][i]).y, 64, 64 },
				new SDL_FRect { (float) i * (float) w,  (float) j * (float) h, (float) w, (float) h }
			);
		}
	}

//	SDL_RenderCopy(Game::get_instance()->get_renderer(), Game::get_instance()->get_cache()->load("Data/Assets/.png/stage.png"), nullptr, nullptr);

	Scene::render();
}
void SceneGameplay::destroy(void) {
	Scene::destroy();
}

void SceneGameplay::on_button_press_a(controller_group *player) {
	ObjectPlayer::get_player_from_controller(player)->slash();
}
void SceneGameplay::on_button_press_b(controller_group *player) {
	ObjectPlayer::get_player_from_controller(player)->shoot();
}
void SceneGameplay::on_button_press_y(controller_group *player) {
	ObjectPlayer::get_player_from_controller(player)->set_stationary(true);
}

void SceneGameplay::on_button_release_a(controller_group *player) { }
void SceneGameplay::on_button_release_b(controller_group *player) { }
void SceneGameplay::on_button_release_y(controller_group *player) {
	ObjectPlayer::get_player_from_controller(player)->set_stationary(false);
}
