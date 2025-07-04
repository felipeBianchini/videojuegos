/**
 * @file CounterComponent.hpp
 * @brief Component for marking entities as counters or counting elements
 */

#ifndef COUNTERCOMPONENT_HPP
#define COUNTERCOMPONENT_HPP

/**
 * @struct CounterComponent
 * @brief Tag component that marks an entity as a counter or counting element
 * 
 * This is a marker component used to identify entities that serve as counters
 * in the game system. It contains no data and serves purely as a flag for
 * systems to recognize counter entities. May be used for UI counters, score
 * displays, or other numerical tracking elements.
 */
struct CounterComponent {
    /**
     * @brief Default constructor for CounterComponent
     * 
     * Creates an empty marker component with no initialization required.
     * The presence of this component on an entity signals to relevant systems
     * that this entity functions as a counter.
     */
    CounterComponent() {}
};

#endif // COUNTERCOMPONENT_HPP