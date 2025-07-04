/**
 * @file AnimationManager.hpp
 * @brief Header file for animation management system
 */

#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP
#include <map>
#include <string>

/**
 * @struct AnimationData
 * @brief Structure to hold animation configuration data
 * 
 * This struct contains all the necessary information to define an animation,
 * including texture information, dimensions, frame count, and playback settings.
 */
struct AnimationData {
    std::string textureId;    ///< Identifier for the texture/sprite sheet used in the animation
    int width;               ///< Width of each animation frame in pixels
    int height;              ///< Height of each animation frame in pixels
    int numFrames;           ///< Total number of frames in the animation sequence
    int frameSpeedRate;      ///< Speed rate for frame transitions (higher = faster)
    bool isLoop;             ///< Whether the animation should loop continuously
    
    /**
     * @brief Constructor for AnimationData
     * @param textureId Identifier for the texture/sprite sheet (default: empty string)
     * @param width Width of each frame in pixels (default: 0)
     * @param height Height of each frame in pixels (default: 0)
     * @param numFrames Total number of frames (default: 1)
     * @param frameSpeedRate Speed rate for frame transitions (default: 1)
     * @param isLoop Whether animation should loop (default: true)
     */
    AnimationData (const std::string& textureId = "", int width = 0, int height = 0, int numFrames = 1, int frameSpeedRate = 1, bool isLoop = true)
    {
        this->textureId = textureId;
        this->width = width;
        this->height = height;
        this->numFrames = numFrames;
        this->frameSpeedRate = frameSpeedRate;
        this->isLoop = isLoop;
    }
};

/**
 * @class AnimationManager
 * @brief Manages a collection of animation data objects
 * 
 * This class provides functionality to store, retrieve, and manage animation data.
 * It uses a map-based storage system with string identifiers for efficient lookup.
 */
class AnimationManager {
private:
    std::map<std::string, AnimationData> animations;  ///< Container storing animation data mapped by animation ID

public:
    /**
     * @brief Default constructor
     * 
     * Initializes an empty AnimationManager instance.
     */
    AnimationManager();
    
    /**
     * @brief Destructor
     * 
     * Cleans up resources used by the AnimationManager.
     */
    ~AnimationManager();
    
    /**
     * @brief Adds a new animation to the manager
     * @param animationId Unique identifier for the animation
     * @param textureId Identifier for the texture/sprite sheet
     * @param width Width of each frame in pixels
     * @param height Height of each frame in pixels
     * @param numFrames Total number of frames in the animation
     * @param frameSpeedRate Speed rate for frame transitions
     * @param isLoop Whether the animation should loop continuously
     */
    void AddAnimation(const std::string& animationId, const std::string& textureId, int width, int height, int numFrames, int frameSpeedRate, bool isLoop);
    
    /**
     * @brief Retrieves animation data by ID
     * @param animationId Unique identifier of the animation to retrieve
     * @return AnimationData object containing the animation configuration
     */
    AnimationData GetAnimation(const std::string& animationId);
};

#endif // !ANIMATIONMANAGER_HPP