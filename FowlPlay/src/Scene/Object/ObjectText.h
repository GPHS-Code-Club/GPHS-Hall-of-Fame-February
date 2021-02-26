#ifndef SCENE_OBJECT_OBJECTTEXT_H_
#define SCENE_OBJECT_OBJECTTEXT_H_

#include "Object.h"

class ObjectText : public Object {
	public:
		ObjectText(Scene *scene, const char *font, const char *text, int pt, Uint8 r, Uint8 g, Uint8 b);
		virtual ~ObjectText(void);
};

#endif /* SCENE_OBJECT_OBJECTTEXT_H_ */
