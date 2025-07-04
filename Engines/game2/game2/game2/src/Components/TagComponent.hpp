#ifndef TAGCOMPONENT_HPP
#define TAGCOMPONENT_HPP
#include <string>

/**
 * @brief A component that holds a string tag for identification purposes.
 * 
 * This structure represents a simple tag component that can be used
 * to label or categorize entities in a component-based system.
 */
struct TagComponent {
    /**
     * @brief The string tag used for identification.
     */
    std::string tag;
    
    /**
     * @brief Constructs a TagComponent with an optional tag string.
     * 
     * @param tag The tag string to assign to this component. Defaults to empty string.
     */
    TagComponent(const std::string& tag = "") {
        this->tag = tag;
    }
};
#endif // !TAGCOMPONENT_HPP