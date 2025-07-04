/**
 * @file Pool.hpp
 * @brief Template-based object pool implementation for ECS component storage
 */

#ifndef POOL_HPP
#define POOL_HPP
#include <vector>
//std::vector<IPool> pools;

/**
 * @class IPool
 * @brief Base interface for type-erased component pools
 * 
 * This interface allows different typed pools to be stored in the same
 * container while maintaining type safety through virtual dispatch.
 */
class IPool {
public:
    /**
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~IPool() = default;
};

/**
 * @class Pool
 * @brief Template-based pool for storing components of a specific type
 * 
 * This class provides efficient storage and access for components in an ECS
 * system. It uses a contiguous vector for cache-friendly memory layout and
 * provides indexed access to components.
 * 
 * @tparam TComponent The type of component to store in this pool
 */
template <typename TComponent>
class Pool : public IPool {
public:
    /**
     * @brief Constructor that initializes the pool with a specified capacity
     * 
     * Creates a pool with preallocated storage to avoid frequent reallocations
     * during component addition.
     * 
     * @param size Initial capacity of the pool (default: 1000)
     */
    Pool(int size = 1000) {
        data.resize(size);
    }
    
    /**
     * @brief Virtual destructor for proper cleanup
     */
    virtual ~Pool() = default;
    
    /**
     * @brief Checks if the pool contains no components
     * 
     * @return true if the pool is empty, false otherwise
     */
    bool isEmpty() const {
        return data.empty();
    }
    
    /**
     * @brief Gets the current size of the pool
     * 
     * @return The number of elements the pool can currently hold
     */
    int GetSize() const {
        return static_cast<int>(data.size());
    }
    
    /**
     * @brief Resizes the pool to a new capacity
     * 
     * This operation may invalidate existing references to components
     * if the new size is smaller than the current size.
     * 
     * @param n New capacity of the pool
     */
    void Resize(int n) {
        data.resize(n);
    }
    
    /**
     * @brief Clears all components from the pool
     * 
     * This operation removes all elements and may deallocate memory,
     * invalidating all existing references to components.
     */
    void Clear() {
        data.clear();
    }
    
    /**
     * @brief Adds a component to the end of the pool
     * 
     * This operation may cause reallocation if the pool is at capacity,
     * potentially invalidating existing references.
     * 
     * @param object The component to add to the pool
     */
    void Add(TComponent object) {
        data.push_back(object);
    }
    
    /**
     * @brief Sets a component at a specific index
     * 
     * This operation overwrites the component at the given index.
     * No bounds checking is performed.
     * 
     * @param index The index where to place the component
     * @param object The component to store at the index
     */
    void Set(unsigned int index, TComponent object) {
        data[index] = object;
    }
    
    /**
     * @brief Gets a reference to the component at a specific index
     * 
     * This operation provides direct access to the component for reading
     * or modification. No bounds checking is performed.
     * 
     * @param index The index of the component to retrieve
     * @return Reference to the component at the specified index
     */
    TComponent& Get(unsigned int index) {
        return static_cast<TComponent&>(data[index]);
    }
    
    /**
     * @brief Operator overload for array-like access to components
     * 
     * Provides convenient syntax for accessing components using square brackets.
     * No bounds checking is performed.
     * 
     * @param index The index of the component to retrieve
     * @return Reference to the component at the specified index
     */
    TComponent& operator[](unsigned int index) {
        return static_cast<TComponent&>(data[index]);
    }
    
private:
    /**
     * @brief Internal storage for components
     * 
     * Uses std::vector for contiguous memory layout and efficient access patterns
     */
    std::vector<TComponent> data;
};
#endif // !POOL_HPP