/**
 * @file CounterSystem.hpp
 * @brief Defines the CounterSystem class for managing and displaying counter information
 */

#ifndef COUNTERSYSTEM_HPP
#define COUNTERSYSTEM_HPP
#include <string>
#include "../ECS/ECS.hpp"
#include "../Components/CounterComponent.hpp"
#include "../Components/TextComponent.hpp"

/**
 * @class CounterSystem
 * @brief System responsible for updating text components with counter information
 * 
 * This system processes entities that have both CounterComponent and TextComponent,
 * updating their text display to show game completion messages with death counts.
 */
class CounterSystem : public System {
public:
    /**
     * @brief Constructor for CounterSystem
     * 
     * Sets up the required components for this system: CounterComponent and TextComponent
     */
    CounterSystem() {
        RequiredComponent<CounterComponent>();
        RequiredComponent<TextComponent>();
    }

    /**
     * @brief Updates all counter entities with the current death count
     * 
     * Iterates through all entities with required components and updates their text
     * to display a game completion message including the number of deaths.
     * 
     * @param deathCount The current number of player deaths to display
     */
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