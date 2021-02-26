#include "Scenes.h"

#include "SceneGameplay.h"
#include "SceneTitle.h"

Scene *Scenes::gameplay = nullptr;
Scene *Scenes::title = nullptr;

void Scenes::init(void) {
	Scenes::gameplay = new SceneGameplay();
	Scenes::title = new SceneTitle();
}
