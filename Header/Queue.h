#pragma once
namespace Library {
	template <typename T>
	//! Queue Adaptor Class
	/*! Class template for a Queue. Contains operations for insertion/removal in
	a first-in first-out manner.*/
	class Queue
	{
	public:
		//! Default Constructor
		/*! Creates an empty Queue */
		Queue();

		//! Copy Constructor
		/*! Creates a deep-copy
		\param rhs The Queue to be copied*/
		Queue(const Queue& rhs);

		/*! Operator "=" Overload
		Creates a deep-copy
		\param rhs The Queue to be copied
		\return A reference to "this" Queue */
		Queue& operator=(const Queue& rhs);

		//! Destructor
		/*! Pops all elements off of the Queue before deleting itself*/
		~Queue() = default;

		//! Push to Back of the Queue
		/*! \param item The element to insert.*/
		void Push(const T& item);

		//! Pop from the Top of the Queue
		/*! Removes the item sitting at the top of the Queue.*/
		void Pop();

		//! Peek
		/*! \return A reference to the item at the top of the Queue.*/
		T& Top();

		//! Peek for Const Queues
		/*! \return A constant reference to the item at the top of the Queue.*/
		const T& Top() const;

		//! Get Size
		/*! \return How many items are contained in the Queue*/
		std::uint32_t Size() const;

		//! Is Empty
		/*! \return Indicates whether or not the size of the Queue is zero*/
		bool IsEmpty() const;

		//! Clear
		/*! Removes all items in the Queue*/
		void Clear();
	private:
		SList<T> mList;	//!< Underlying linked-list container that holds our elements
	};
}

#include "Queue.inl"