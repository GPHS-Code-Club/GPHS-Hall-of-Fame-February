#pragma once

#ifndef ANIMATION_ANIMATOR_H_
#define ANIMATION_ANIMATOR_H_

#include "SDL2/SDL.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

struct animation { // TODO try to make not a pointer
	int frames; // number of frames
	int frameat = 0; // the current game frame
	int framenum = 0; // the current animation frame
	int framedelay = 0; // the number of frames to wait before advancing the animation
	SDL_Rect **framerects = nullptr; // the spritesheet reference
	bool loop = false; // whether or not the animation should restart
	bool animating = false; // whether or not its currently animating

	~animation(void);

	template <int FRAMECOUNT> static animation *create(int framedelay, const char *file, int w, int h, bool loop) {
		animation *a = new animation;
		a->frames = FRAMECOUNT;
		a->framedelay = framedelay;
		a->framerects = load<FRAMECOUNT>(file, w, h);
		a->loop = loop;
		return a;
	}
	template <int FRAMECOUNT> static SDL_Rect **load(const char *location, int w, int h) {
		std::ifstream *file = new std::ifstream;
		file->open(location);
		std::stringstream lines;
		if(!file->is_open()) {
			std::cerr << "error opening animation! " << location << std::endl;
		} else {
			std::string line = "";
			while(std::getline(*file, line)) {
				lines << line;
			}
		}
		file->close();

		int xs[FRAMECOUNT];
		int ys[FRAMECOUNT];
		int co = 0;
		bool do_y = false;
		std::vector<unsigned int> skips;

		for(unsigned int i = 0; i < lines.str().length(); ++ i) {
			char c = lines.str().at(i);

			if(std::find(skips.begin(), skips.end(), i) != skips.end()) {
				continue;
			}

			if(c == ',') {
				do_y = true;
			} else if(c == ';') {
				do_y = false;
				++ co;
			} else if(c != ' ' && std::isdigit(c)) {
				std::stringstream num;
				num << c;

				for(unsigned int j = i + 1; j < lines.str().length(); ++ j) {
					if(std::isdigit(lines.str().at(j))) {
						num << lines.str().at(j);
						skips.push_back(j);
					} else {
						break;
					}
				}

				if(do_y) {
					ys[co] = stoi(num.str());
				} else {
					xs[co] = stoi(num.str());
				}
			}
		}

		SDL_Rect **framerects = new SDL_Rect* [FRAMECOUNT];
		for(int i = 0; i < FRAMECOUNT; ++ i) {
			framerects[i] = new SDL_Rect {
				xs[i] * w, ys[i] * h, w, h
			};
		}

		return framerects;
	}
};

class Animator {
	animation *a;

	public:
		Animator(void);
		virtual ~Animator(void);

		void set_frame_delay(int frame_delay);
		void update(SDL_Rect *srcrect);
		void set_animation(animation *a, bool animating);
		void set_animating(bool animating);
		bool animation_is(animation *a) const;
		bool is_animating(void) const;
};

#endif /* ANIMATOR_H_ */
