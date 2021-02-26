#pragma once

#ifndef SCENE_SCENEGAMEPLAY_H_
#define SCENE_SCENEGAMEPLAY_H_

#include "Scene.h"

#include "../input.h"
#include <sstream>

class SceneGameplay : public Scene {
	Object *pond_wall;
	Object *left_fence_wall;
	Object *top_fence_wall;
	Object *right_fence_wall;

	std::map<unsigned int, SDL_Point> map;
	unsigned int tiles[12][20] = {
		{ 0,  1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1, 1, 1, 1, 1, 1, 2 },
		{ 3,  4, 4, 4, 4, 4, 4, 4,  4,  4,  4,  4,  4,  4, 4, 4, 4, 4, 4, 5 },
		{ 7,  6, 6, 6, 6, 6, 6, 6,  6,  6,  6,  6,  6,  6, 6, 6, 6, 6, 6, 7 },
		{ 7,  6, 6, 6, 6, 6, 6, 6,  6,  6,  6,  6,  6,  6, 6, 6, 6, 6, 6, 7 },
		{ 7,  6, 6, 6, 6, 6, 6, 8,  9,  9,  9,  9,  10, 6, 6, 6, 6, 6, 6, 7 },
		{ 7,  6, 6, 6, 6, 6, 6, 12, 13, 13, 13, 13, 14, 6, 6, 6, 6, 6, 6, 7 },
		{ 7,  6, 6, 6, 6, 6, 6, 12, 13, 13, 13, 13, 14, 6, 6, 6, 6, 6, 6, 7 },
		{ 7,  6, 6, 6, 6, 6, 6, 16, 17, 17, 17, 17, 18, 6, 6, 6, 6, 6, 6, 7 },
		{ 7,  6, 6, 6, 6, 6, 6, 6,  6,  6,  6,  6,  6,  6, 6, 6, 6, 6, 6, 7 },
		{ 7,  6, 6, 6, 6, 6, 6, 6,  6,  6,  6,  6,  6,  6, 6, 6, 6, 6, 6, 7 },
		{ 11, 6, 6, 6, 6, 6, 6, 6,  6,  6,  6,  6,  6,  6, 6, 6, 6, 6, 6, 11 },
		{ 15, 6, 6, 6, 6, 6, 6, 6,  6,  6,  6,  6,  6,  6, 6, 6, 6, 6, 6, 15 }
	};

	public:
		SceneGameplay(void);
		virtual ~SceneGameplay(void);

		virtual void setup(void) override;
		virtual void update(void) override;
		virtual void render(void) override;
		virtual void destroy(void) override;

		virtual void on_button_press_a(controller_group *player) override;
		virtual void on_button_press_b(controller_group *player) override;
		virtual void on_button_press_y(controller_group *player) override;

		virtual void on_button_release_a(controller_group *player) override;
		virtual void on_button_release_b(controller_group *player) override;
		virtual void on_button_release_y(controller_group *player) override;
};

#endif /* SCENE_SCENEGAMEPLAY_H_ */
