#ifndef CMYARRAY_CMYARRAY_H
#define CMYARRAY_CMYARRAY_H

template <typename T>
class CMyArray
{
public:
	using ArraySize = unsigned int;

	CMyArray()
		: m_data(nullptr)
		, m_size(0)
		, m_capacity(0){};

	explicit CMyArray(ArraySize capacity)
		: m_data(nullptr)
		, m_size(0)
		, m_capacity(0)
	{
		Resize(capacity);
	};

	CMyArray(const CMyArray& other)
		: m_data(nullptr)
		, m_size(other.m_size)
		, m_capacity(other.m_capacity)
	{
		CMyArray temp(other.m_capacity);
		for (auto i = 0; i < other.m_size; ++i)
		{
			temp.Add(other.m_data[i]);
		}
		Swap(temp);
	}

	CMyArray(CMyArray&& other) noexcept
		: m_data(other.m_data)
		, m_size(other.m_size)
		, m_capacity(other.m_capacity)
	{
		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}

	~CMyArray()
	{
		delete[] m_data;
	}

	void Resize(ArraySize newCapacity)
	{
		if (newCapacity != m_capacity)
		{
			T* newData = new T[newCapacity]();
			ArraySize newSize = (newCapacity < m_size) ? newCapacity : m_size;

			for (ArraySize i = 0; i < newSize; ++i)
			{
				newData[i] = std::move(m_data[i]);
			}

			delete[] m_data;
			m_data = newData;
			m_size = newSize;
			m_capacity = newCapacity;
		}
	}

	void Add(const T& value)
	{
		if (m_size == m_capacity)
		{
			Resize(m_capacity == 0 ? 1 : m_capacity * 2);
		}
		m_data[m_size++] = value;
	}

	void Clear()
	{
		for (auto i = 0; i < m_size; ++i)
		{
			m_data[i] = T();
		}
		m_size = 0;
	}

	[[nodiscard]] ArraySize Size() const
	{
		return m_size;
	}

	[[nodiscard]] ArraySize Capacity() const
	{
		return m_capacity;
	}

	const T& operator[](ArraySize index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_data[index];
	}

	T& operator[](ArraySize index)
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_data[index];
	};

	CMyArray& operator=(CMyArray const& other)
	{
		if (std::addressof(other) != this)
		{
			CMyArray temp(other);
			std::swap(m_data, temp.m_data);
			std::swap(m_size, temp.m_size);
			std::swap(m_capacity, temp.m_capacity);
		}

		return *this;
	}

	CMyArray& operator=(CMyArray&& other) noexcept
	{
		if (std::addressof(other) != this)
		{
			delete[] m_data;
			m_size = 0;
			m_capacity = 0;

			std::swap(m_data, other.m_data);
			std::swap(m_size, other.m_size);
			std::swap(m_capacity, other.m_capacity);
		}

		return *this;
	}

	T* begin()
	{
		return m_data;
	}

	T* end()
	{
		return m_data + m_size;
	}

	const T* begin() const
	{
		return m_data;
	}

	const T* end() const
	{
		return m_data + m_size;
	}

	std::reverse_iterator<T*> rbegin()
	{
		return std::reverse_iterator<T*>(end());
	}

	std::reverse_iterator<T*> rend()
	{
		return std::reverse_iterator<T*>(begin());
	}

	std::reverse_iterator<const T*> rbegin() const
	{
		return std::reverse_iterator<const T*>(end());
	}

	std::reverse_iterator<const T*> rend() const
	{
		return std::reverse_iterator<const T*>(begin());
	}

private:
	void Swap(CMyArray& other) noexcept
	{
		std::swap(m_data, other.m_data);
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
	}

	T* m_data;
	ArraySize m_size;
	ArraySize m_capacity;
};

#endif // CMYARRAY_CMYARRAY_H
