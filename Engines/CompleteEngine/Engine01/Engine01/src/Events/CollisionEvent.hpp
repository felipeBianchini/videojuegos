#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP

#include "../EventManager/Event.hpp"
#include "../ECS/ECS.hpp"

class CollisionEvent : public Event {
public:
	Entity a;
	Entity b;

	CollisionEvent(Entity a, Entity b) : a(a), b(b) {}
};



#endif // !COLLISIONEVENT_HPP