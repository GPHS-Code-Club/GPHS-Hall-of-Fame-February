#pragma once

#ifndef SCENE_SCENES_H_
#define SCENE_SCENES_H_

#include "Scene.h"

class Scenes {
	public:
		static Scene *gameplay;
		static Scene *title;

		static void init(void);
};

#endif /* SCENE_SCENES_H_ */
