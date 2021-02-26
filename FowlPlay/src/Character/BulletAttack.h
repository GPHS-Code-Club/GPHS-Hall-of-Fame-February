#pragma once

#ifndef CHARACTER_BULLETATTACK_H_
#define CHARACTER_BULLETATTACK_H_

#include "../Scene/Object/Object.h"

#include <functional>

class BulletAttack {
	std::function<void(Object *)> action;

	public:
		BulletAttack(std::function<void(Object *)> action);
		virtual ~BulletAttack(void);

		void activate(Object *object) const;
};

#endif /* BULLETATTACK_H_ */
