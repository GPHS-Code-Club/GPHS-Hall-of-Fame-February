#pragma once

#ifndef COMMAND_INPUT_H_
#define COMMAND_INPUT_H_

#include "Character/BulletAttack.h"

#include <map>
#include <string>

enum input {
	up = 'u',
	left = 'l',
	down = 'd',
	right = 'r',
	none = 'n'
};

using command_map = std::map<std::string, BulletAttack>;

#endif /* COMMAND_INPUT_H_ */
