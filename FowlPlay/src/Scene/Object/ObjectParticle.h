#pragma once

#ifndef OBJECT_OBJECTPARTICLE_H_
#define OBJECT_OBJECTPARTICLE_H_

#include "Object.h"

class ObjectParticle : public Object {
	const int max_life_time;
	float scale;
	const float w, h;

	public:
		ObjectParticle(Scene *scene, const char *path, int max_life_time, float w, float h, int sprite_w, int sprite_h);
		virtual ~ObjectParticle();

		virtual void update(void) override;
		virtual void render(void) override;
};

#endif /* PARTICLEOBJECT_H_ */
