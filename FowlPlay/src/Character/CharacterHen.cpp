#include "CharacterHen.h"

#include "BulletAttack.h"

#include "../Scene/Object/ObjectBullet.h"
#include "../Game.h"

#include <cmath>

CharacterHen::CharacterHen() : Character("Data/Assets/.png/hen.png", "Data/Assets/.png/hen_bullet.png", "Data/Assets/.png/hen_feather.png", "Data/Assets/.png/hen_eggshell", 5, 60000) {
	this->map_command("ldr", BulletAttack([] (Object *owner) {
		Object *bullet_1 = new ObjectBullet(owner->get_scene(), owner, 0, 32, 32);
		bullet_1->set_size_percent(0.025, 0.05);
		bullet_1->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
		bullet_1->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet_1->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet_1->get_h_percent() / 2);
		bullet_1->set_deltas_percent(-0.0005, 0.0005);
		owner->get_scene()->push_back(bullet_1);

		Object *bullet_2 = new ObjectBullet(owner->get_scene(), owner, 50, 32, 32);
		bullet_2->set_size_percent(0.025, 0.05);
		bullet_2->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
		bullet_2->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet_2->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet_2->get_h_percent() / 2);
		bullet_2->set_deltas_percent(0, 0.0007071);
		owner->get_scene()->push_back(bullet_2);

		Object *bullet_3 = new ObjectBullet(owner->get_scene(), owner, 100, 32, 32);
		bullet_3->set_size_percent(0.025, 0.05);
		bullet_3->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
		bullet_3->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet_3->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet_3->get_h_percent() / 2);
		bullet_3->set_deltas_percent(0.0005, 0.0005);
		owner->get_scene()->push_back(bullet_3);
	}));
	this->map_command("rdl", BulletAttack([] (Object *owner) {
		Object *bullet_1 = new ObjectBullet(owner->get_scene(), owner, 100, 32, 32);
		bullet_1->set_size_percent(0.025, 0.05);
		bullet_1->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
		bullet_1->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet_1->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet_1->get_h_percent() / 2);
		bullet_1->set_deltas_percent(-0.0005, 0.0005);
		owner->get_scene()->push_back(bullet_1);

		Object *bullet_2 = new ObjectBullet(owner->get_scene(), owner, 50, 32, 32);
		bullet_2->set_size_percent(0.025, 0.05);
		bullet_2->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
		bullet_2->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet_2->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet_2->get_h_percent() / 2);
		bullet_2->set_deltas_percent(0, 0.0007071);
		owner->get_scene()->push_back(bullet_2);

		Object *bullet_3 = new ObjectBullet(owner->get_scene(), owner, 0, 32, 32);
		bullet_3->set_size_percent(0.025, 0.05);
		bullet_3->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
		bullet_3->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet_3->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet_3->get_h_percent() / 2);
		bullet_3->set_deltas_percent(0.0005, 0.0005);
		owner->get_scene()->push_back(bullet_3);
	}));
	this->map_command("dl", BulletAttack([] (Object *owner) {
		Object *bullet_1 = new ObjectBullet(owner->get_scene(), owner, 0, 32, 32);
		bullet_1->set_size_percent(0.025, 0.05);
		bullet_1->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
		bullet_1->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet_1->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet_1->get_h_percent() / 2);
		bullet_1->set_deltas_percent(0, 0.0007071);
		owner->get_scene()->push_back(bullet_1);

		Object *bullet_2 = new ObjectBullet(owner->get_scene(), owner, 10, 32, 32);
		bullet_2->set_size_percent(0.025, 0.05);
		bullet_2->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
		bullet_2->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet_2->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet_2->get_h_percent() / 2);
		bullet_2->set_deltas_percent(-0.0005, 0.0005);
		owner->get_scene()->push_back(bullet_2);
	}));
	this->map_command("dr", BulletAttack([] (Object *owner) {
		Object *bullet_1 = new ObjectBullet(owner->get_scene(), owner, 0, 32, 32);
		bullet_1->set_size_percent(0.025, 0.05);
		bullet_1->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
		bullet_1->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet_1->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet_1->get_h_percent() / 2);
		bullet_1->set_deltas_percent(0, 0.0007071);
		owner->get_scene()->push_back(bullet_1);

		Object *bullet_2 = new ObjectBullet(owner->get_scene(), owner, 10, 32, 32);
		bullet_2->set_size_percent(0.025, 0.05);
		bullet_2->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
		bullet_2->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet_2->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet_2->get_h_percent() / 2);
		bullet_2->set_deltas_percent(0.0005, 0.0005);
		owner->get_scene()->push_back(bullet_2);
	}));
	this->map_command("ldru", BulletAttack([] (Object *owner) {
		for(int i = 0; i < 16; ++ i) {
			Object *bullet = new ObjectBullet(owner->get_scene(), owner, i * 10, 32, 32);
			bullet->set_size_percent(0.025, 0.05);
			bullet->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
			bullet->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet->get_h_percent() / 2);
			bullet->set_deltas_percent(-std::cos(0.01745329252 * (22.5 * i)) / 2000.0, (std::sin(0.01745329252 * (22.5 * i)) / 2000.0) * Game::get_instance()->get_ratio_w_over_h());
			owner->get_scene()->push_back(bullet);
		}
	}));
	this->map_command("rdlu", BulletAttack([] (Object *owner) {
		for(int i = 0; i < 16; ++ i) {
			Object *bullet = new ObjectBullet(owner->get_scene(), owner, i * 10, 32, 32);
			bullet->set_size_percent(0.025, 0.05);
			bullet->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
			bullet->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet->get_h_percent() / 2);
			bullet->set_deltas_percent(std::cos(0.01745329252 * (22.5 * i)) / 2000.0, (std::sin(0.01745329252 * (22.5 * i)) / 2000.0) * Game::get_instance()->get_ratio_w_over_h());
			owner->get_scene()->push_back(bullet);
		}
	}));
	this->map_command("ldrul", BulletAttack([] (Object *owner) {
		for(int i = 0; i < 16; ++ i) {
			Object *bullet = new ObjectBullet(owner->get_scene(), owner, i * 20, 32, 32);
			bullet->set_size_percent(0.025, 0.05);
			bullet->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
			bullet->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet->get_h_percent() / 2);
			bullet->set_deltas_percent(-std::cos(0.01745329252 * (22.5 * i)) / 4000.0, (std::sin(0.01745329252 * (22.5 * i)) / 4000.0) * Game::get_instance()->get_ratio_w_over_h());
			owner->get_scene()->push_back(bullet);
		}
		for(int i = 16; i > 1; -- i) {
			Object *bullet = new ObjectBullet(owner->get_scene(), owner, i * 20 + 360, 32, 32);
			bullet->set_size_percent(0.025, 0.05);
			bullet->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
			bullet->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet->get_h_percent() / 2);
			bullet->set_deltas_percent(-std::cos(0.01745329252 * (22.5 * i)) / 4000.0, -(std::sin(0.01745329252 * (22.5 * i)) / 4000.0) * Game::get_instance()->get_ratio_w_over_h());
			owner->get_scene()->push_back(bullet);
		}
	}));

	this->map_command("ldrulurdl", BulletAttack([] (Object *owner) {
		for(int i = 0; i < 32; ++ i) {
			for(int j = 0; j < 8; ++ j) {
				Object *bullet = new ObjectBullet(owner->get_scene(), owner, i * 100, 32, 32);
				bullet->set_size_percent(0.025, 0.05);
				bullet->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
				bullet->set_pos_percent((owner->get_x_percent() + owner->get_w_percent() / 2) - bullet->get_w_percent() / 2, (owner->get_y_percent() + owner->get_h_percent() / 2) - bullet->get_h_percent() / 2);
				bullet->set_deltas_percent(
					-std::cos(0.01745329252 * (45 * j - (i * 11.25))) / 4000.0,
					(std::sin(0.01745329252 * (45 * j - (i * 11.25))) / 4000.0) * Game::get_instance()->get_ratio_w_over_h()
				);
				owner->get_scene()->push_back(bullet);
			}
		}
	}));
}
CharacterHen::~CharacterHen() {
	// TODO Auto-generated destructor stub
}

void CharacterHen::do_regular_bullet(Object *object, Sint16 left_x, Sint16 left_y) {
	Object *bullet = new ObjectBullet(object->get_scene(), object, 0, 32, 32);
	bullet->set_size_percent(0.025, 0.05);
	bullet->set_hitbox_percent(0.004, 0.008, 0.0175, 0.035);
	bullet->set_pos_percent((object->get_x_percent() + object->get_w_percent() / 2) - bullet->get_w_percent() / 2, (object->get_y_percent() + object->get_h_percent() / 2) - bullet->get_h_percent() / 2);
	bullet->set_deltas_percent(left_x / 50000000.0, (left_y / (float) 50000000.0) * Game::get_instance()->get_ratio_w_over_h());
	object->get_scene()->push_back(bullet);
}
