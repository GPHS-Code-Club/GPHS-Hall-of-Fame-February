#ifndef SCENE_OBJECT_OBJECTWALL_H_
#define SCENE_OBJECT_OBJECTWALL_H_

#include "Object.h"

class ObjectWall : public Object {
	public:
		ObjectWall(Scene *scene, float x, float y, float w, float h, bool breaks_bullet);
		virtual ~ObjectWall(void);
};

#endif /* SCENE_OBJECT_OBJECTWALL_H_ */
