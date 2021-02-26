#ifndef SCENE_H_
#define SCENE_H_

#include "Object/Object.h"
#include "../controller_group.h"

#include <vector>

class Object;

class Scene {
	SDL_Color bg_color;
	std::vector<Object *> *objects;

	public:
		Scene(void);
		Scene(Uint8 r, Uint8 g, Uint8 b);
		virtual ~Scene(void);

		virtual void setup(void);
		virtual void update(void);
		void pre_render(void);
		virtual void render(void);
		void post_render(void);
		virtual void destroy(void);

		virtual void on_button_press_a(controller_group *player);
		virtual void on_button_press_b(controller_group *player);
		virtual void on_button_press_y(controller_group *player);

		virtual void on_button_release_a(controller_group *player);
		virtual void on_button_release_b(controller_group *player);
		virtual void on_button_release_y(controller_group *player);

		void push_back(Object *object);
		std::vector<Object *> *get_objects(void);
};

#endif /* SCENE_H_ */
