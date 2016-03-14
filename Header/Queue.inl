namespace Library
{
	template <typename T>
	Queue<T>::Queue() :
		mList(SList<T>())
	{}

	template <typename T>
	Queue<T>::Queue(const Queue<T>& rhs) :
		Queue()
	{
		operator=(rhs);
	}

	template <typename T>
	Queue<T>& Queue<T>::operator=(const Queue<T>& rhs)
	{
		if (this != &rhs)
		{
			mList = rhs.mList;
		}
		return *this;
	}

	template <typename T>
	void Queue<T>::Push(const T& item)
	{
		mList.PushBack(item);
	}

	template <typename T>
	void Queue<T>::Pop()
	{
		mList.PopFront();
	}

	template <typename T>
	T& Queue<T>::Top()
	{
		return mList.Front();
	}

	template <typename T>
	const T& Queue<T>::Top() const
	{
		return mList.Front();
	}

	template <typename T>
	std::uint32_t Queue<T>::Size() const
	{
		return mList.Size();
	}

	template <typename T>
	bool Queue<T>::IsEmpty() const
	{
		return mList.IsEmpty();
	}

	template <typename T>
	void Queue<T>::Clear()
	{
		mList.Clear();
	}
}