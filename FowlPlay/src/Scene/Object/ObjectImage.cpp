#include "ObjectImage.h"

#include "../../Game.h"
#include "../../TextureCache.h"

lerper<SDL_FPoint> BEZIER_2 = [] (SDL_FPoint a, SDL_FPoint b, float t) -> SDL_FPoint {
	return SDL_FPoint {
		BEZIER<float>(a.x, b.x, t), BEZIER<float>(a.y, b.y, t)
	};
};

ObjectImage::ObjectImage(Scene *scene, const char *path, animation *a, int x, int y, int w, int h, std::function<void(std::unique_ptr<Object *> &)> action) : Object(scene), x(x), y(y), w(w), h(h) {
	this->set_sprite(sprite_ex_f {
		Game::get_instance()->get_renderer(),
		Game::get_instance()->get_cache()->load_texture(path),
		SDL_Rect { x, y, w, h },
		SDL_FRect { 0, 0, 0, 0 },
		0,
		SDL_FPoint { 0, 0 },
		SDL_FLIP_NONE
	});
	this->a = a;
	this->set_deltas_percent(0, 0);
	if(this->a != nullptr) {
		this->animator.set_animation(this->a, false);
	}
	this->action = action;
	this->pos_lerper = Detail<SDL_FPoint>(&this->get_pos_percent(), BEZIER_2);
	this->selected = false;
} // TODO

ObjectImage::~ObjectImage() {
	delete this->a;
}

void ObjectImage::update(void) {
	this->pos_lerper.update();

	Object::update();
}
void ObjectImage::render(void) {
	this->animator.update(&this->get_sprite().srcrect);

	Object::render();
}

void ObjectImage::interact(std::unique_ptr<Object *> &selector) {
	this->action(selector);
}
void ObjectImage::move_to(float x, float y) {
	this->pos_lerper = Detail<SDL_FPoint>(&this->get_pos_percent(), BEZIER_2);
	this->pos_lerper.animate(this->get_pos_percent(), SDL_FPoint { x, y });
}

void ObjectImage::on_selected(std::unique_ptr<Object *> &selector) {
	this->get_sprite().srcrect = SDL_Rect {
		this->x, this->h + this->y, this->w, this->h
	};
	this->set_selected(true);
}
void ObjectImage::on_unselected(std::unique_ptr<Object *> &selector) {
	this->get_sprite().srcrect = SDL_Rect {
		this->x, this->y, this->w, this->h
	};
	this->set_selected(false);
}
bool ObjectImage::is_selected(void) const {
	return this->selected;
}
void ObjectImage::set_selected(bool selected) {
	this->selected = selected;
}

void ObjectImage::play_animation(void) {
	this->animator.set_animating(true);
}
void ObjectImage::stop_animation(void) {
	this->animator.set_animating(false);
}

animation *ObjectImage::get_animation(void) const {
	return this->a;
}
Animator ObjectImage::get_animator(void) const {
	return this->animator;
}
