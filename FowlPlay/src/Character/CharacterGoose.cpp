#include "CharacterGoose.h"

#include "../Scene/Object/ObjectBullet.h"
#include "../Scene/Object/ObjectParticle.h"
#include "../Game.h"

#include <cmath>

CharacterGoose::CharacterGoose(void) : Character("Data/Assets/.png/goose.png", "Data/Assets/.png/goose_bullet.png", "Data/Assets/.png/goose_feather.png", "Data/Assets/.png/goose_eggshell", 10, 45000) {
	this->map_command("ldr", BulletAttack([] (Object *owner) {
		for(int i = 0; i < 3; ++ i) {
			Object *bullet = new ObjectBullet(owner->get_scene(), owner, i * 80, 24, 24);
			bullet->set_size_percent(0.02, 0.04);
			bullet->set_hitbox_percent(0.003, 0.006, 0.017, 0.034);
			bullet->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet->get_h_percent() / 2);
			bullet->set_deltas_percent(0.0008071, 0);
			owner->get_scene()->push_back(bullet);
		}
	}));
	this->map_command("lur", BulletAttack([] (Object *owner) {
		for(int i = 0; i < 3; ++ i) {
			Object *bullet = new ObjectBullet(owner->get_scene(), owner, i * 80, 24, 24);
			bullet->set_size_percent(0.02, 0.04);
			bullet->set_hitbox_percent(0.003, 0.006, 0.017, 0.034);
			bullet->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet->get_h_percent() / 2);
			bullet->set_deltas_percent(0.0008071, 0);
			owner->get_scene()->push_back(bullet);
		}
	}));

	this->map_command("rdl", BulletAttack([] (Object *owner) {
		for(int i = 0; i < 3; ++ i) {
			Object *bullet = new ObjectBullet(owner->get_scene(), owner, i * 80, 24, 24);
			bullet->set_size_percent(0.02, 0.04);
			bullet->set_hitbox_percent(0.003, 0.006, 0.017, 0.034);
			bullet->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet->get_h_percent() / 2);
			bullet->set_deltas_percent(-0.0008071, 0);
			owner->get_scene()->push_back(bullet);
		}
	}));
	this->map_command("rul", BulletAttack([] (Object *owner) {
		for(int i = 0; i < 3; ++ i) {
			Object *bullet = new ObjectBullet(owner->get_scene(), owner, i * 80, 24, 24);
			bullet->set_size_percent(0.02, 0.04);
			bullet->set_hitbox_percent(0.003, 0.006, 0.017, 0.034);
			bullet->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet->get_h_percent() / 2);
			bullet->set_deltas_percent(-0.0008071, 0);
			owner->get_scene()->push_back(bullet);
		}
	}));

	this->map_command("dlu", BulletAttack([] (Object *owner) {
		for(int i = 0; i < 3; ++ i) {
			Object *bullet = new ObjectBullet(owner->get_scene(), owner, i * 80, 24, 24);
			bullet->set_size_percent(0.02, 0.04);
			bullet->set_hitbox_percent(0.003, 0.006, 0.017, 0.034);
			bullet->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet->get_h_percent() / 2);
			bullet->set_deltas_percent(0, -0.0008071);
			owner->get_scene()->push_back(bullet);
		}
	}));
	this->map_command("dru", BulletAttack([] (Object *owner) {
		for(int i = 0; i < 3; ++ i) {
			Object *bullet = new ObjectBullet(owner->get_scene(), owner, i * 80, 24, 24);
			bullet->set_size_percent(0.02, 0.04);
			bullet->set_hitbox_percent(0.003, 0.006, 0.017, 0.034);
			bullet->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet->get_h_percent() / 2);
			bullet->set_deltas_percent(0, -0.0008071);
			owner->get_scene()->push_back(bullet);
		}
	}));

	this->map_command("uld", BulletAttack([] (Object *owner) {
		for(int i = 0; i < 3; ++ i) {
			Object *bullet = new ObjectBullet(owner->get_scene(), owner, i * 80, 24, 24);
			bullet->set_size_percent(0.02, 0.04);
			bullet->set_hitbox_percent(0.003, 0.006, 0.017, 0.034);
			bullet->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet->get_h_percent() / 2);
			bullet->set_deltas_percent(0, 0.0008071);
			owner->get_scene()->push_back(bullet);
		}
	}));
	this->map_command("urd", BulletAttack([] (Object *owner) {
		for(int i = 0; i < 3; ++ i) {
			Object *bullet = new ObjectBullet(owner->get_scene(), owner, i * 80, 24, 24);
			bullet->set_size_percent(0.02, 0.04);
			bullet->set_hitbox_percent(0.003, 0.006, 0.017, 0.034);
			bullet->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet->get_h_percent() / 2);
			bullet->set_deltas_percent(0, 0.0008071);
			owner->get_scene()->push_back(bullet);
		}
	}));
}
CharacterGoose::~CharacterGoose(void) {
	// TODO Auto-generated destructor stub
}

void CharacterGoose::do_regular_bullet(Object *object, Sint16 left_x, Sint16 left_y) {
	Object *bullet = new ObjectBullet(object->get_scene(), object, 0, 24, 24);
	bullet->set_size_percent(0.02, 0.04);
	bullet->set_hitbox_percent(0.003, 0.006, 0.017, 0.034);
	bullet->set_pos_percent((object->get_x_percent() + object->get_w_percent() / 2) - bullet->get_w_percent() / 2, (object->get_y_percent() + object->get_h_percent() / 2) - bullet->get_h_percent() / 2);
	bullet->set_deltas_percent(left_x / 40000000.0, (left_y / (float) 40000000.0) * Game::get_instance()->get_ratio_w_over_h());
	object->get_scene()->push_back(bullet);
}
