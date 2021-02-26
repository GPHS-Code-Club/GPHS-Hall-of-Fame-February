#ifndef SCENE_OBJECT_OBJECTIMAGE_H_
#define SCENE_OBJECT_OBJECTIMAGE_H_

#include "Object.h"
#include "../../Animation/Animator.h"
#include "../../Animation/Detail.h"

#include <functional>
#include <memory>

class ObjectImage : public Object {
	Animator animator;
	animation *a;
	std::function<void(std::unique_ptr<Object *> &)> action;
	Detail<SDL_FPoint> pos_lerper;
	const int x, y;
	const int w, h;
	bool selected;

	public:
		ObjectImage(Scene *scene, const char *path, animation *a, int x, int y, int w, int h, std::function<void(std::unique_ptr<Object *> &)> action);
		virtual ~ObjectImage(void);

		virtual void update(void) override;
		virtual void render(void) override;

		virtual void interact(std::unique_ptr<Object *> &selector);
		void move_to(float x, float y);

		virtual void on_selected(std::unique_ptr<Object *> &selector);
		virtual void on_unselected(std::unique_ptr<Object *> &selector);
		bool is_selected(void) const;
		void set_selected(bool selected);

		void play_animation(void);
		void stop_animation(void);

		animation *get_animation(void) const;
		Animator get_animator(void) const;
};

#endif /* SCENE_OBJECT_OBJECTIMAGE_H_ */
