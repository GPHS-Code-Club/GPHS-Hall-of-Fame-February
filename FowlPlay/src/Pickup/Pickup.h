#ifndef PICKUP_PICKUP_H_
#define PICKUP_PICKUP_H_

class Pickup {
	const char *texture_path;

	public:
		enum use_type {
			instant, slash
		};

		Pickup(const char *texture_path, use_type type);
		virtual ~Pickup(void);

		const char *get_texture_path(void) const;
		use_type get_use_type(void) const;

	private:
		use_type type;
};

#endif /* PICKUP_PICKUP_H_ */
