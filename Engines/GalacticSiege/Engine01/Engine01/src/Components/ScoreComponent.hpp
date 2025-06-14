#ifndef SCORECOMPONENT_HPP
#define SCORECOMPONENT_HPP

/**
 * @brief Component to store the score value for an entity.
 */
struct ScoreComponent {
	int score;  ///< The score value.

    /**
     * @brief Construct a new Score Component object
     *
     * @param score Initial score value (default is 0).
     */
	ScoreComponent(int score = 0) {
		this->score = score;
	}
};

#endif // !SCORECOMPONENT_HPP
