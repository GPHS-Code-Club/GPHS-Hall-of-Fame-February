#pragma once

#ifndef CHARACTER_CHARACTERHEN_H_
#define CHARACTER_CHARACTERHEN_H_

#include "Character.h"

class CharacterHen : public Character {
	public:
		CharacterHen(void);
		virtual ~CharacterHen(void);

		virtual void do_regular_bullet(Object *object, Sint16 left_x, Sint16 left_y) override;
};

#endif /* CHARACTERHEN_H_ */
