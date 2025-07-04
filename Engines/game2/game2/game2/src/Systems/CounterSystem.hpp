#ifndef COUNTERSYSTEM_HPP
#define COUNTERSYSTEM_HPP

#include <string>

#include "../ECS/ECS.hpp"
#include "../Components/CounterComponent.hpp"
#include "../Components/TextComponent.hpp"

class CounterSystem : public System {
public:
    CounterSystem() {
        RequiredComponent<CounterComponent>();
        RequiredComponent<TextComponent>();
    }

    void Update(int deathCount) {
        auto entities = GetSystemEntiities();
		for (auto i = entities.begin(); i != entities.end(); i++) {
            Entity a = *i;
            auto& aText = a.GetComponent<TextComponent>();
            aText.text = "Felicidades! Ha terminado el juego. Ha muerto: " + std::to_string(deathCount) + " veces";
        }
    }
};

#endif // COUNTERSYSTEM_HPP