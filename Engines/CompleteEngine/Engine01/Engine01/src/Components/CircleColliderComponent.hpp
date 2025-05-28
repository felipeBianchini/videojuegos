#ifndef CIRCLECOLLIDERCOMPONENT_HPP
#define CIRCLECOLLIDERCOMPONENT_HPP

/**
 * @brief Component representing a circular collider for an entity.
 *
 * Contains the radius and dimensions of the collider.
 */
struct CircleColliderComponent {
	int radius; ///< Radius of the circular collider.
	int width;  ///< Width of the collider's bounding box.
	int height; ///< Height of the collider's bounding box.

	/**
	 * @brief Construct a new CircleColliderComponent object.
	 *
	 * @param radius Radius of the circle collider (default 0).
	 * @param width Width of the bounding box (default 0).
	 * @param height Height of the bounding box (default 0).
	 */
	CircleColliderComponent(int radius = 0, int width = 0, int height = 0) {
		this->radius = radius;
		this->width = width;
		this->height = height;
	}
};

#endif // !CIRCLECOLLIDERCOMPONENT_HPP