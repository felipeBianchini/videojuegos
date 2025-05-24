#ifndef ISENTITYINSIDETHESCREENCOMPONENT_HPP
#define ISENTITYINSIDETHESCREENCOMPONENT_HPP

struct IsEntityInsideTheScreenComponent {
	bool isEntityInsideTheScreen;
	
	IsEntityInsideTheScreenComponent(bool isInside = false) {
		this->isEntityInsideTheScreen = isInside;
	}
};

#endif // !ISENTITYINSIDETHESCREENCOMPONENT_HPP