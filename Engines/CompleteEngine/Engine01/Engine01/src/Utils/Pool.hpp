#ifndef POOL_HPP
#define POOL_HPP

#include <vector>

/**
 * @brief A global vector to store IPool objects (commented out).
 * @note Currently disabled in the code.
 */
 //std::vector<IPool> pools;

 /**
  * @class IPool
  * @brief Abstract base class for a pool of components.
  *
  * This interface defines the basic structure for a pool that can be extended by
  * derived classes to manage specific component types.
  */
class IPool {
public:
	/**
	 * @brief Virtual destructor to ensure proper cleanup of derived classes.
	 */
	virtual ~IPool() = default;
};

/**
 * @class Pool
 * @brief A template class for managing a pool of components of type TComponent.
 *
 * This class implements the IPool interface and provides functionality to store,
 * access, and manipulate a collection of components in a vector.
 *
 * @tparam TComponent The type of component to be stored in the pool.
 */
template <typename TComponent>
class Pool : public IPool {
public:
	/**
	 * @brief Constructs a pool with a specified initial size.
	 *
	 * @param size The initial size of the pool (default is 1000).
	 */
	Pool(int size = 1000) {
		data.resize(size);
	}
	/**
	 * @brief Virtual destructor to ensure proper cleanup.
	 */
	virtual ~Pool() = default;
	/**
	 * @brief Checks if the pool is empty.
	 *
	 * @return True if the pool contains no components, false otherwise.
	 */
	bool isEmpty() const {
		return data.empty();
	}
	/**
	 * @brief Gets the current size of the pool.
	 *
	 * @return The number of components in the pool.
	 */
	int GetSize() const {
		return static_cast<int>(data.size());
	}
	/**
	 * @brief Resizes the pool to a new size.
	 *
	 * @param n The new size of the pool.
	 */
	void Resize(int n) {
		data.resize(n);
	}
	/**
	 * @brief Clears all components from the pool.
	 */
	void Clear() {
		data.clear();
	}
	/**
	 * @brief Adds a component to the end of the pool.
	 *
	 * @param object The component to add.
	 */
	void Add(TComponent object) {
		data.push_back(object);
	}
	/**
	 * @brief Sets a component at the specified index.
	 *
	 * @param index The index where the component will be set.
	 * @param object The component to set.
	 */
	void Set(unsigned int index, TComponent object) {
		data[index] = object;
	}
	/**
	 * @brief Gets a reference to the component at the specified index.
	 *
	 * @param index The index of the component to retrieve.
	 * @return A reference to the component at the specified index.
	 */
	TComponent& Get(unsigned int index) {
		return static_cast<TComponent&>(data[index]);
	}
	/**
	 * @brief Accesses a component at the specified index using the subscript operator.
	 *
	 * @param index The index of the component to access.
	 * @return A reference to the component at the specified index.
	 */
	TComponent& operator[](unsigned int index) {
		return static_cast<TComponent&>(data[index]);
	}
private:
	/**
	 * @brief The underlying vector that stores the components.
	 */
	std::vector<TComponent> data;
};

#endif // !POOL_HPP
