#ifndef CIRCLECOLLIDERCOMPONENT_HPP
#define CIRCLECOLLIDERCOMPONENT_HPP

struct CircleColliderComponent {
	int radius;
	CircleColliderComponent(int radius = 0) {
		this->radius = radius;
	}
};

#endif // !CIRCLECOLLIDERCOMPONENT_HPP