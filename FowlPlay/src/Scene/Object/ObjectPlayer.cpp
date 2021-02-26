#include "ObjectPlayer.h"

#include "SDL2/SDL_image.h"
#include "ObjectParticle.h"
#include "ObjectDamager.h"
#include "ObjectSlash.h"
#include "../../Game.h"
#include "../../TextureCache.h"
#include "../../SDLHelpers.h"

#include <cmath>

std::map<controller_group *, ObjectPlayer *> ObjectPlayer::controller_player_map;

ObjectPlayer::ObjectPlayer(Scene *scene, Character *character, int player_index) : Object(scene) {
	this->character = character;
	this->current_health = this->max_health = 200;
	this->max_near_miss = 100;
	this->current_near_miss = 0;
	this->set_can_be_collided_with(true);
	this->set_can_collide(true);
	this->invulnerability_frames = 0;
	this->near_miss_hitbox_percent = { 0, 0, 0, 0 };
	this->flip_scale = 1.0;
	this->flip_left = false;
	this->attacking = false;
	this->player_index = player_index;
	this->player = Game::get_instance()->get_controller(player_index);
	this->damaged_frames = 0;
	this->direction = input::none;
	this->trigger_shooting = false;
	this->inputs_texture = Game::get_instance()->get_cache()->load_texture("Data/Assets/.png/inputs.png");
	this->up_rect = SDL_Rect { 0, 0, 64, 64 };
	this->left_rect = SDL_Rect { 64, 0, 64, 64 };
	this->down_rect = SDL_Rect { 0, 64, 64, 64 };
	this->right_rect = SDL_Rect { 64, 64, 64, 64 };
	this->near_missing_bullet = nullptr;
	this->nm_color = { 255, 128, 64 };
	this->pickup = nullptr;

	this->set_sprite(sprite_ex_f {
		Game::get_instance()->get_renderer(),
		Game::get_instance()->get_cache()->load_texture(character->get_texture_path()),
		SDL_Rect { 0, 0, 64, 64 },
		SDL_FRect { 0, 0, 0, 0 },
		0,
		SDL_FPoint { 0, 0 },
		SDL_FLIP_NONE
	});
	this->shadow = sprite_f {
		Game::get_instance()->get_renderer(),
		Game::get_instance()->get_cache()->load_texture("Data/Assets/.png/shadow.png"),
		SDL_Rect { 0, 0, 64, 32 },
		SDL_FRect { 0, 0, 32, 16 },
	};
	this->reticle = sprite_ex_f {
		Game::get_instance()->get_renderer(),
		Game::get_instance()->get_cache()->load_texture("Data/Assets/.png/reticle.png"),
		SDL_Rect { 0, 0, 16, 16 },
		SDL_FRect { 0, 0, 0, 0 },
		0,
		SDL_FPoint { 0, 0 },
		SDL_FLIP_NONE
	};
	this->pickup_sprite = sprite_ex_f {
		Game::get_instance()->get_renderer(),
		nullptr,
		SDL_Rect { 0, 0, 64, 64 },
		SDL_FRect { 0, 0, 0, 0 },
		0,
		SDL_FPoint { 0, 0 },
		SDL_FLIP_NONE
	};
	this->set_size_percent(0.05, 0.1);
	this->set_deltas_percent(0, 0);
	this->set_hitbox_percent(0.0135, 0.0275, 0.0225, 0.045);
	this->stationary = false;
	this->set_physics_type(Object::physics_type::pushable);

	ObjectPlayer::controller_player_map.insert(std::make_pair(player, this));
}
ObjectPlayer::~ObjectPlayer() {
	delete this->character;
	delete this->player;
	delete this->near_missing_bullet;
	delete this->pickup;
	SDL_DestroyTexture(this->inputs_texture);
}

void ObjectPlayer::hurt(ObjectDamager *source) {
	if(this->player != nullptr) {
		SDL_GameControllerRumble(this->player->game_controller, source->get_damage(), source->get_damage(), 100); // TODO rumble until controllable again
	}

	this->damaged_frames = 500;

	if(this->invulnerability_frames == 0) {
		this->current_health -= source->get_damage();
		this->invulnerability_frames = source->get_iframes();

		if(this->current_health <= 0) {
			this->remove();

			for(int i = 0; i < 8; ++ i) {
				Object *particle = new ObjectParticle(this->get_scene(), static_cast<ObjectPlayer *>(this)->get_character()->get_feather_path(), 750, 0.025, 0.05, 32, 32);
				particle->set_pos_percent(this->get_x_percent() + this->get_w_percent() / 2.0 - (0.025 / 2), this->get_y_percent() + this->get_h_percent() / 2.0 - (0.05 / 2));
				particle->set_deltas_percent((float) std::cos(0.01745329252 * (45 * i)) / 2000.0, ((float) std::sin(0.01745329252 * (45 * i)) / 2000.0) * Game::get_instance()->get_ratio_w_over_h());
				particle->set_angle_delta(1);
				particle->set_rotation(rand() % 360);
//				this->get_scene()->push_back(particle);
			} // TODO fucking fix
		} else {
			for(int i = 0; i < 3; ++ i) {
				Object *particle = new ObjectParticle(this->get_scene(), static_cast<ObjectPlayer *>(this)->get_character()->get_feather_path(), 750, 0.025, 0.05, 32, 32);
				particle->set_pos_percent(source->get_x_percent() + source->get_w_percent() / 2.0 - (0.025 / 2) + source->get_knockback_x() / 100.0, source->get_y_percent() + source->get_h_percent() / 2.0 - (0.05 / 2) + source->get_knockback_y() / 100.0);
				particle->set_deltas_percent(-source->get_dx_percent() / 4 + (rand() % 3 - 1.0) / 2000.0, -source->get_dy_percent() / 4 + (rand() % 3 - 1.0) / 2000.0);
				particle->set_angle_delta(1);
				particle->set_rotation(rand() % 360);
//				this->get_scene()->push_back(particle);
			}
		}

		if(std::abs(source->get_knockback_x()) > 0 || std::abs(source->get_knockback_y()) > 0) {
			this->set_controllable(false);
			this->set_deltas_percent(source->get_knockback_x() * Game::get_instance()->get_width() * 0.000025, source->get_knockback_y() * Game::get_instance()->get_width() * 0.000025);
		}

		source->set_can_be_collided_with(false);
		if(ObjectBullet *bullet = dynamic_cast<ObjectBullet *>(source)) {
			bullet->on_break();
		} else if(source->disappear_on_collision()) {
			source->remove();
		}
	}
}
Character *ObjectPlayer::get_character(void) const {
	return this->character;
}

void ObjectPlayer::update(void) {
	if(this->player == nullptr) {
		this->player = Game::get_instance()->get_controller(this->player_index);
	}

	float old_width = this->get_w_percent();
	this->set_size_percent(0.05 * this->flip_scale, 0.1);
	float new_width = this->get_w_percent();
	this->set_pos_percent(this->get_x_percent() - (new_width - old_width) / 2.0, this->get_y_percent());
	this->set_hitbox_percent(this->get_hitbox_offx_percent() + (new_width - old_width) / 2.0, this->get_hitbox_offy_percent(), this->get_hitbox_w_percent(), this->get_hitbox_h_percent());

	if(!this->is_controllable()) {
		this->set_deltas_percent(this->get_dx_percent() * 0.99, this->get_dy_percent() * 0.99);

		if(std::abs(std::hypot(this->get_dx_percent(), this->get_dy_percent())) < 0.0001) {
			this->set_controllable(true);
		}
	}

	if(this->damaged_frames > 0) {
		-- this->damaged_frames;
	}

	if(this->get_controller_group() != nullptr && this->get_controller_group()->right_trigger == 32767) {
		if(!this->trigger_shooting) {
			this->shoot();
			this->trigger_shooting = true;
		}
	} else {
		this->trigger_shooting = false;
	}

	Sint16 x = 0, y = 0;
	if(this->get_controller_group() != nullptr) {
		if(std::abs(this->get_controller_group()->right_x) > 3000 || std::abs(this->get_controller_group()->right_y) > 3000) { // TODO hypotenuse
			x = this->get_controller_group()->right_x, y = this->get_controller_group()->right_y;
		} else {
			x = this->get_controller_group()->left_x, y = this->get_controller_group()->left_y;
		}
	}

	if(this->direction != input::none && (std::abs(x) <= 3000) && (std::abs(y) <= 3000)) {
		this->direction = input::none;
		this->attack.str("");
		for(input i : this->inputs) {
			this->attack << (char) i;
		}
		if(Game::get_instance()->is_in_debug_mode()) {
			std::cout << std::endl << "storing input " << this->attack.str() << std::endl;
		}
		this->inputs.clear();
	} else if(this->direction != input::down && y >= 28000) {
		this->direction = input::down;
		this->inputs.push_back(input::down);
	} else if(this->direction != input::up && y <= -28000) {
		this->direction = input::up;
		this->inputs.push_back(input::up);
	} else if(this->direction != input::right && x >= 28000) {
		this->direction = input::right;
		this->inputs.push_back(input::right);
	} else if(this->direction != input::left && x <= -28000) {
		this->direction = input::left;
		this->inputs.push_back(input::left);
	} // TODO put in proper controller regions (think x shape (calculate distance of stick to center and once it reaches a threshold determine the input)) // also the "none" region should be circular

	if(this->is_controllable()) {
		if(!this->is_being_pushed()) {
			this->set_deltas_percent(0, 0);
		}

		if(this->get_controller_group() != nullptr && this->get_controller_group()->game_controller != nullptr) {
			if(!this->is_stationary() && (std::abs(this->player->left_x) > 4000 || std::abs(this->player->left_y) > 4000)) {
				double divisor = this->is_attacking() ? this->character->get_high_speed_divisor() : this->character->get_low_speed_divisor();
				this->set_deltas_percent((double) 0.001 * (this->player->left_x / divisor), (double) 0.001 * (this->player->left_y / divisor) * Game::get_instance()->get_ratio_w_over_h());

//					if((this->get_frames_existed() % 50 == 0) && (std::abs(this->player->left_x) > 20000 || std::abs(this->player->left_y) > 20000)) {
//						Object *particle = new ObjectParticle(this->get_scene(), "Data/Assets/.png/dust.png", 1000, 8, 8);
//						particle->set_pos(this->get_x() + (this->get_w() / 2) + 4, this->get_y() + this->get_h() - 8);
//						particle->set_deltas(-this->get_dx() / 4, -this->get_dy() / 4 + (rand() % 3 - 1.0) / 4.0);
//						particle->set_angle_delta(1);
//						this->get_scene()->push_back(particle);
//					} else if((this->get_frames_existed() % 100 == 0) && (std::abs(this->player->left_x) > 10000 || std::abs(this->player->left_y) > 10000)) {
//						Object *particle = new ObjectParticle(this->get_scene(), "Data/Assets/.png/dust.png", 1000, 8, 8);
//						particle->set_pos(this->get_x() + (this->get_w() / 2) + 4, this->get_y() + this->get_h() - 8);
//						particle->set_deltas(-this->get_dx() / 4, -this->get_dy() / 4 + (rand() % 3 - 1.0) / 4.0);
//						particle->set_angle_delta(1);
//						this->get_scene()->push_back(particle);
//					}

					if((this->get_frames_existed() % 50 == 0) && (std::abs(this->player->left_x) > 20000 || std::abs(this->player->left_y) > 20000)) {
						Object *particle = new ObjectParticle(this->get_scene(), "Data/Assets/.png/grass.png", 1000, 0.0125, 0.025, 32, 32);
						particle->set_pos_percent(this->get_x_percent() + (this->get_w_percent() / 2) + 0.0125 / 2, this->get_y_percent() + this->get_h_percent());
						particle->set_deltas_percent(-this->get_dx_percent() / 4, -this->get_dy_percent() / 4 + (rand() % 3 - 1.0) / 4000.0);
						particle->set_angle_delta(0.1);
						particle->set_rotation(rand() % 360);
//						this->get_scene()->push_back(particle);
					} else if((this->get_frames_existed() % 100 == 0) && (std::abs(this->player->left_x) > 10000 || std::abs(this->player->left_y) > 10000)) {
						Object *particle = new ObjectParticle(this->get_scene(), "Data/Assets/.png/grass.png", 1000, 0.0125, 0.025, 32, 32);
						particle->set_pos_percent(this->get_x_percent() + (this->get_w_percent() / 2) + 0.0125 / 2, this->get_y_percent() + this->get_h_percent());
						particle->set_deltas_percent(-this->get_dx_percent() / 4, -this->get_dy_percent() / 4 + (rand() % 3 - 1.0) / 4000.0);
						particle->set_angle_delta(0.1);
						particle->set_rotation(rand() % 360);
//						this->get_scene()->push_back(particle);
					}
			}
		}
	}

	if(this->get_dx_percent() < 0) {
		this->flip_left = true;
//		this->s->flip = SDL_FLIP_HORIZONTAL;
	} else if(this->get_dx_percent() > 0) {
		this->flip_left = false;
//		this->s->flip = SDL_FLIP_NONE;
	}

	if(this->flip_left) {
		if(this->flip_scale > -1.0) {
			this->flip_scale -= 0.02;
		}
	} else {
		if(this->flip_scale < 1.0) {
			this->flip_scale += 0.02;
		}
	}

	if(std::abs(this->get_dx_percent()) > 0 || std::abs(this->get_dy_percent()) > 0) {
		float distance = std::hypot((float) std::abs(this->get_dx_scaled()), (float) std::abs(this->get_dy_scaled()));
		this->animator.set_frame_delay((1.0 / distance) * 20.0);
		this->animator.set_animation(this->character->get_moving_animation(), true);
		this->get_sprite().angle = std::sin((float) this->get_frames_existed() / 50.0) * 5;
	} else {
		if(!this->animator.animation_is(nullptr)) {
			this->animator.set_animating(false);
		}
		this->get_sprite().angle = 0.00001; // UGH why does 0 make me disappear. thank god for doubles i guess
	}

	if(this->invulnerability_frames > 0) {
		-- this->invulnerability_frames;
	}

	for(Object *object : *this->get_scene()->get_objects()) {
		if(ObjectBullet *bullet = dynamic_cast<ObjectBullet *>(object)) {
			if(bullet->get_owner() != this && bullet->get_activates_near_miss()) {
				SDL_Rect this_nm_hitbox = f_rect_to_rect(this->get_nm_hitbox_scaled());
				SDL_Rect bullet_hitbox = f_rect_to_rect(bullet->get_hitbox_scaled());
				if(SDL_HasIntersection(&this_nm_hitbox, &bullet_hitbox) == SDL_TRUE) {
					if(!this->is_near_missing()) {
						this->set_near_missing(true);
						this->near_missing_bullet = bullet;
					}
				} else {
					if(this->is_near_missing() && bullet == this->near_missing_bullet) {
						this->current_near_miss += 10;
						if(this->current_near_miss > this->max_near_miss) {
							this->current_near_miss = this->max_near_miss;
						}
						this->set_near_missing(false);
						bullet->set_activates_near_miss(false);
						this->near_missing_bullet = nullptr;
					}
				}
			}
		}
	}

	Object::update();

	this->set_nm_hitbox_percent(this->get_hitbox_x_percent() - 0.015, this->get_hitbox_y_percent() - 0.03, this->get_hitbox_w_percent() + 0.03, this->get_hitbox_h_percent() + 0.06);
}
void ObjectPlayer::render(void) {
	Uint8 alpha = 255;
	if(this->invulnerability_frames > 0) {
		SDL_GetTextureAlphaMod(this->get_sprite().texture, &alpha);
		SDL_SetTextureAlphaMod(this->get_sprite().texture, (this->invulnerability_frames / 50) % 2 == 0 ? 128 : 0);
	}
	Uint8 r = 0, g = 0, b = 0;
	if(this->damaged_frames > 0) {
		SDL_GetTextureColorMod(this->get_sprite().texture, &r, &g, &b);
		SDL_SetTextureColorMod(this->get_sprite().texture, 255, 128, 128);
	}


	this->shadow.dstrect.x = this->get_hitbox_x_scaled() + this->get_hitbox_w_scaled() / 2 - (float) (Game::get_instance()->get_width() * 0.05 / 2);
	this->shadow.dstrect.y = this->get_y_scaled() + (float) (Game::get_instance()->get_height() * 0.05 * 1.5);
	this->shadow.dstrect.w = (float) (Game::get_instance()->get_width() * 0.05);
	this->shadow.dstrect.h = (float) (Game::get_instance()->get_height() * 0.05);

	sprite_f::render(this->shadow);

	this->animator.update(&this->get_sprite().srcrect);

	Object::render();

	if(this->pickup != nullptr) {
		this->pickup_sprite.dstrect.x = this->get_x_scaled() + this->get_w_scaled() / 2;
		this->pickup_sprite.dstrect.y = this->get_y_scaled() + this->get_h_scaled() / 2;
		this->pickup_sprite.dstrect.w = std::abs(this->get_w_scaled());
		this->pickup_sprite.dstrect.h = this->get_h_scaled();
		sprite_ex_f::render(this->pickup_sprite);
	}

	if(this->invulnerability_frames > 0) {
		SDL_SetTextureAlphaMod(this->get_sprite().texture, alpha);
	}
	if(this->damaged_frames > 0) {
		SDL_SetTextureColorMod(this->get_sprite().texture, r, g, b);
	}

	SDL_SetRenderDrawColor(Game::get_instance()->get_renderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(Game::get_instance()->get_renderer(), new SDL_Rect {
		(int) this->get_hitbox_x_scaled() - 64 + (int) (this->get_hitbox_w_scaled() / 2.0),
		(int) this->get_y_scaled() - 48,
		128,
		16
	});
	SDL_RenderFillRect(Game::get_instance()->get_renderer(), new SDL_Rect {
		(int) this->get_hitbox_x_scaled() - 64 + (int) (this->get_hitbox_w_scaled() / 2.0),
		(int) this->get_y_scaled() - 32,
		(int) 128,
		16
	});

	SDL_SetRenderDrawColor(Game::get_instance()->get_renderer(), 0, 255, 0, 255);
	SDL_RenderFillRect(Game::get_instance()->get_renderer(), new SDL_Rect {
		(int) this->get_hitbox_x_scaled() - 64 + (int) (this->get_hitbox_w_scaled() / 2.0),
		(int) this->get_y_scaled() - 48,
		(int) (128.0 * ((float) this->current_health / (float) this->max_health)),
		16
	});

	if(this->current_near_miss == this->max_near_miss) {
		this->nm_color = {
			(Uint8) (255.0 * std::sin((this->get_frames_existed() - ((255.0 * 3.141592653589793234) / 2.0)) / 255.0)),
			(Uint8) (255.0 * std::sin((this->get_frames_existed() - ((128.0 * 3.141592653589793234) / 3.0)) / 255.0)),
			(Uint8) (255.0 * std::sin((this->get_frames_existed() - ((64.0 * 3.141592653589793234) / 3.0)) / 255.0)),
		};
	}

	SDL_SetRenderDrawColor(Game::get_instance()->get_renderer(), this->nm_color.r, this->nm_color.g, this->nm_color.b, 255);
	SDL_RenderFillRect(Game::get_instance()->get_renderer(), new SDL_Rect {
		(int) this->get_hitbox_x_scaled() - 64 + (int) (this->get_hitbox_w_scaled() / 2.0),
		(int) this->get_y_scaled() - 32,
		(int) (128.0 * ((float) this->current_near_miss / (float) this->max_near_miss)),
		16
	});

	if(Game::get_instance()->is_in_debug_mode()) {
		SDL_SetRenderDrawColor(Game::get_instance()->get_renderer(), 32, 32, 255, 255);
		SDL_FRect nm_hitbox = this->get_nm_hitbox_scaled();
		SDL_RenderDrawRectF(Game::get_instance()->get_renderer(), &nm_hitbox);

		for(unsigned int i = 0; i < this->inputs.size(); ++ i) {
			input button = this->inputs[i];
			SDL_Rect dstrect = {
				96 * (int) i + 64, Game::get_instance()->get_height() - 128, 64, 64
			};
			SDL_Rect srcrect = { 0, 0, 0, 0 };
			switch(button) {
				case input::up:
					srcrect = up_rect;
					break;
				case input::left:
					srcrect = left_rect;
					break;
				case input::right:
					srcrect = right_rect;
					break;
				case input::down:
					srcrect = down_rect;
					break;
				case input::none:
					break;
			}
			SDL_RenderCopy(Game::get_instance()->get_renderer(), this->inputs_texture, &srcrect, &dstrect);
		}
	} // TODO

	this->reticle.dstrect.w = (float) 0.005 * Game::get_instance()->get_width();
	this->reticle.dstrect.h = (float) 0.01 * Game::get_instance()->get_height();
	if(this->get_controller_group() != nullptr) {
		if(std::abs(this->get_controller_group()->right_x) > 4000 || std::abs(this->get_controller_group()->right_y) > 4000) {
			this->reticle.dstrect.x = this->get_x_scaled() + this->get_w_scaled() / 2 - this->reticle.dstrect.w / 2 + (float) (this->get_controller_group()->right_x) / Game::get_instance()->get_width();
			this->reticle.dstrect.y = this->get_y_scaled() + this->get_h_scaled() / 2 - this->reticle.dstrect.h / 2 + (float) (this->get_controller_group()->right_y) / Game::get_instance()->get_width();
		} else {
			this->reticle.dstrect.x = this->get_x_scaled() + this->get_w_scaled() / 2 - this->reticle.dstrect.w / 2 + (float) (this->get_controller_group()->left_x) / Game::get_instance()->get_width();
			this->reticle.dstrect.y = this->get_y_scaled() + this->get_h_scaled() / 2 - this->reticle.dstrect.h / 2 + (float) (this->get_controller_group()->left_y) / Game::get_instance()->get_width();
		}
	} else {
		this->reticle.dstrect.x = this->get_x_scaled() + this->get_w_scaled() / 2 - this->reticle.dstrect.w / 2;
		this->reticle.dstrect.y = this->get_y_scaled() + this->get_h_scaled() / 2 - this->reticle.dstrect.h / 2;
	}

	sprite_ex_f::render(this->reticle);
}

void ObjectPlayer::set_attacking(bool attacking) {
	this->attacking = attacking;
}
bool ObjectPlayer::is_attacking(void) const {
	return this->attacking;
}

void ObjectPlayer::set_stationary(bool stationary) {
	this->stationary = stationary;
}
bool ObjectPlayer::is_stationary(void) const {
	return this->stationary;
}

controller_group *ObjectPlayer::get_controller_group(void) const {
	return this->player;
}

void ObjectPlayer::slash(void) {
	if(!this->is_attacking()) {
		this->set_attacking(true);
		Object *slash = new ObjectSlash(this->get_scene(), this, (double) this->get_controller_group()->left_x / 750000.0, ((double) this->get_controller_group()->left_y / 750000.0) * Game::get_instance()->get_ratio_w_over_h());
		slash->set_pos_percent(this->get_hitbox_x_percent() + this->get_hitbox_w_percent() / 2 - 0.05 / 2, this->get_hitbox_y_percent() + this->get_hitbox_w_percent() / 2 - 0.1 / 2);
		this->get_scene()->push_back(slash);
	}
}
void ObjectPlayer::shoot(void) { // TODO doesn't work?
	if(this->attack.str() == "") {
		for(input i : this->inputs) {
			this->attack << (char) i;
		}
	}

	SDL_GameControllerRumble(this->get_controller_group()->game_controller, 5, 10, 10);

	try {
		std::string key = this->attack.str();
		this->attack.str("");
		BulletAttack bullet_attack = this->get_character()->get_attack(key);
		bullet_attack.activate(this);
		if(Game::get_instance()->is_in_debug_mode()) {
			std::cout << "using " << key << std::endl;
		}
		this->inputs.clear();
	} catch(const std::out_of_range &exception) {
		if(std::abs(this->get_controller_group()->right_x) > 4000 || std::abs(this->get_controller_group()->right_y) > 4000) {
			this->get_character()->do_regular_bullet(this, this->get_controller_group()->right_x, this->get_controller_group()->right_y);
		} else {
			this->get_character()->do_regular_bullet(this, this->get_controller_group()->left_x, this->get_controller_group()->left_y);
		}
		this->inputs.clear();
		this->attack.str("");
	}
}

void ObjectPlayer::set_near_missing(bool near_missing) {
	this->near_missing = near_missing;
}
bool ObjectPlayer::is_near_missing(void) const {
	return this->near_missing;
}

void ObjectPlayer::set_nm_hitbox_percent(float x, float y, float w, float h) {
	this->near_miss_hitbox_percent = SDL_FRect {
		x, y, w, h
	};
}
float ObjectPlayer::get_nm_hitbox_x_percent(void) const {
	return this->near_miss_hitbox_percent.x;
}
float ObjectPlayer::get_nm_hitbox_y_percent(void) const {
	return this->near_miss_hitbox_percent.y;
}
float ObjectPlayer::get_nm_hitbox_w_percent(void) const {
	return this->near_miss_hitbox_percent.w;
}
float ObjectPlayer::get_nm_hitbox_h_percent(void) const {
	return this->near_miss_hitbox_percent.h;
}
float ObjectPlayer::get_nm_hitbox_x_scaled(void) const {
	return this->near_miss_hitbox_percent.x * Game::get_instance()->get_width();
}
float ObjectPlayer::get_nm_hitbox_y_scaled(void) const {
	return this->near_miss_hitbox_percent.y * Game::get_instance()->get_height();
}
float ObjectPlayer::get_nm_hitbox_w_scaled(void) const {
	return this->near_miss_hitbox_percent.w * Game::get_instance()->get_width();
}
float ObjectPlayer::get_nm_hitbox_h_scaled(void) const {
	return this->near_miss_hitbox_percent.h * Game::get_instance()->get_height();
}
SDL_FRect ObjectPlayer::get_nm_hitbox_scaled(void) const {
	return SDL_FRect {
		this->get_nm_hitbox_x_scaled(),
		this->get_nm_hitbox_y_scaled(),
		this->get_nm_hitbox_w_scaled(),
		this->get_nm_hitbox_h_scaled()
	};
}

void ObjectPlayer::set_pickup(Pickup *pickup) {
	this->pickup = pickup;
	this->pickup_sprite.texture = Game::get_instance()->get_cache()->load_texture(pickup->get_texture_path());
}
Pickup *ObjectPlayer::get_pickup(void) const {
	return this->pickup;
}

ObjectPlayer *ObjectPlayer::get_player_from_controller(controller_group *controller) {
	return ObjectPlayer::controller_player_map.at(controller);
}
