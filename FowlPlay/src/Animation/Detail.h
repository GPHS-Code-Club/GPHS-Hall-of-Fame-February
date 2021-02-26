#pragma once

#ifndef ANIMATION_DETAIL_H_
#define ANIMATION_DETAIL_H_

#include "SDL2/SDL.h"

#include <functional>

template <class T> using lerper = std::function<T (T, T, float)>;

template <class T> lerper<T> LERP = [] (T a, T b, float t) -> T {
	return a + t * (b - a);
};
template <class T> lerper<T> BEZIER = [] (T a, T b, float t) -> T {
	return t * t * (3 * (b - a) - 2 * (b - a) * t) + a;
};

template <class T> class Detail {
	T *t;
	T start, finish;
	bool animating;

	float timer;
	float speed;

	lerper<T> func;

	public:
		Detail(void) {
			this->t = nullptr;

			this->animating = false;

			this->timer = 0;
			this->speed = 0.001;
		}
		Detail(T *t, lerper<T> func) : t(t), start(*t), finish(*t), func(func) {
			this->animating = false;

			this->timer = 0;
			this->speed = 0.001;
		}
		~Detail(void) {
			delete this->t;
		}

		void animate(T start, T finish) {
			this->start = start, this->finish = finish;
			this->animating = true;
		}
		void animate(T finish) {
			this->finish = finish;
			this->animating = true;
		}
		void update(void) {
			if(this->animating) {
				if(this->timer < 1) {
					this->timer += this->speed;
				} else {
					this->animating = false;
					this->timer = 1;
				}

				*this->t = this->func(this->start, this->finish, this->timer);
			}
		}
};

#endif /* ANIMATION_DETAIL_H_ */
