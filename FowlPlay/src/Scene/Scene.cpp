#include "Scene.h"

#include "../Game.h"
#include "Object/ObjectParticle.h"

#include <algorithm>

Scene::Scene(void) : Scene(255, 255, 255) { }
Scene::Scene(Uint8 r, Uint8 g, Uint8 b) {
	this->bg_color = { r, g, b };
	this->objects = nullptr;
}
Scene::~Scene(void) {
	for(Object *object : *this->objects) {
		delete object;
	}
	delete this->objects;
}

void Scene::setup(void) {
	this->objects = new std::vector<Object *>;
}
void Scene::update(void) {
//	for(auto it = this->objects->begin(); it != this->objects->end();) {
//		if((*it) != nullptr && (*it)->marked_for_removal()) {
////			delete *it;
//			it = this->objects->erase(it);
//		} else {
//			(*it)->update();
//			++ it;
//		}
//	}

	this->objects->erase(std::remove_if(this->objects->begin(), this->objects->end(), [] (Object *object) {
		return object->marked_for_removal();
	}), this->objects->end());

	for(Object *object : *this->objects) {
		object->update();
	}
}
void Scene::pre_render(void) {
	std::sort(this->get_objects()->begin(), this->get_objects()->end(), [] (Object *l, Object *r) -> bool {
		return l->get_y_percent() < r->get_y_percent(); // TODO sort based off of y offset for proper positioning of feet of chicken and stuff
	});
	std::sort(this->get_objects()->begin(), this->get_objects()->end(), [] (Object *l, Object *r) -> bool {
		return l->get_z() < r->get_z();
	}); // TODO merge somehow

//	SDL_SetRenderDrawColor(Game::get_instance()->get_renderer(), 32 + (Game::get_instance()->get_frames() / 10) % 255, 255 + (Game::get_instance()->get_frames() / 10) % 255, 128 + (Game::get_instance()->get_frames() / 10) % 255, 255);
	SDL_SetRenderDrawColor(Game::get_instance()->get_renderer(), this->bg_color.r, this->bg_color.g, this->bg_color.b, 255);
	SDL_RenderClear(Game::get_instance()->get_renderer());
}
void Scene::render(void) {
	for(Object *object : *this->objects) {
		object->render();
	}
}
void Scene::post_render(void) {
	SDL_RenderPresent(Game::get_instance()->get_renderer());
}
void Scene::destroy(void) {
	// TODO put destroy on objects
}

void Scene::on_button_press_a(controller_group *player) { }
void Scene::on_button_press_b(controller_group *player) { }
void Scene::on_button_press_y(controller_group *player) { }

void Scene::on_button_release_a(controller_group *player) { }
void Scene::on_button_release_b(controller_group *player) { }
void Scene::on_button_release_y(controller_group *player) { }

void Scene::push_back(Object *object) {
	this->objects->push_back(object);
}
std::vector<Object *> *Scene::get_objects(void) {
	return this->objects;
}
