namespace containers
{
    template <typename T>
    my_vector<T>::my_vector()
    {
        size_ = 0;
        capacity_ = 1;
        array_ = (T *)new char[sizeof(T) * capacity_];
    }

    template <typename T>
    my_vector<T>::my_vector(std::size_t n)
    {
        size_ = n;
        capacity_ = min_power_of_2(n);
        array_ = (T *)new char[sizeof(T) * capacity_];
        for (size_t i = 0; i < size_; ++i)
        {
            new (array_ + i) T();
        }
    }

    template <typename T>
    my_vector<T>::my_vector(const my_vector<T> &other)
    {
        size_ = other.size_;
        capacity_ = other.capacity_;
        array_ = (T *)new char[sizeof(T) * capacity_];
        for (size_t i = 0; i < size_; ++i)
        {
            new (array_ + i) T(other[i]);
        }
    }

    template <typename T>
    my_vector<T> &my_vector<T>::operator=(my_vector<T> other)
    {
        swap(other);
        return *this;
    }

    template <typename T>
    void my_vector<T>::swap(my_vector<T> &other)
    {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(array_, other.array_);
    }

    template <typename T>
    my_vector<T>::~my_vector()
    {
        invoke_destructors();
        delete[] (char *)array_;
    }

    template <typename T>
    void my_vector<T>::invoke_destructors()
    {
        for (size_t i = 0; i < size_; ++i)
        {
            array_[i].~T();
        }
    }

    template <typename T>
    std::size_t my_vector<T>::size() const
    {
        return size_;
    }

    template <typename T>
    std::size_t my_vector<T>::capacity() const
    {
        return capacity_;
    }

    template <typename T>
    bool my_vector<T>::empty() const
    {
        return !size_;
    }

    template <typename T>
    size_t my_vector<T>::min_power_of_2(size_t n) const
    {
        size_t size = 1;
        while (size < n)
        {
            size <<= 1;
        }
        return size;
    }

    template <typename T>
    void my_vector<T>::delete_elements(size_t amount)
    {
        while (amount--)
        {
            array_[--size_].~T();
        }
    }

    template <typename T>
    void my_vector<T>::swap_memory_and_delete(size_t size, size_t capacity)
    {
        capacity_ = capacity;
        T *temp = (T *)new char[sizeof(T) * capacity_];
        std::memcpy(temp, array_, sizeof(T) * size_);
        delete[] (char *)array_;
        array_ = temp;
        size_ = size;
    }

    template <typename T>
    void my_vector<T>::swap_memory_and_delete_default_constructible(size_t size, size_t capacity)
    {
        capacity_ = capacity;
        T *temp = (T *)new char[sizeof(T) * capacity_];
        std::memcpy(temp, array_, sizeof(T) * size_);
        for (size_t i = size_; i < size; ++i)
        {
            new (temp + i) T();
        }
        delete[] (char *)array_;
        array_ = temp;
        size_ = size;
    }

    template <typename T>
    void my_vector<T>::resize(size_t n)
    {
        if (n <= size_)
        {
            delete_elements(size_ - n);
            return;
        }

        swap_memory_and_delete_default_constructible(n, n > capacity_ ? min_power_of_2(n) : capacity_);
    }

    template <typename T>
    void my_vector<T>::reserve(size_t n)
    {
        if (n <= size_)
        {
            size_ = n;
        }

        swap_memory_and_delete(size_, n > capacity_ ? min_power_of_2(n) : capacity_);
    }

    template <typename T>
    void my_vector<T>::push_back(const T &t)
    {
        if (size_ >= capacity_)
        {
            reserve(2 * capacity_);
        }

        new (array_ + size_) T(t);
        ++size_;
    }

    template <typename T>
    void my_vector<T>::pop_back()
    {
        array_[size_ - 1].~T();
        --size_;
    }

    template <typename T>
    void my_vector<T>::clear()
    {
        size_t size = size_;
        for (size_t i = 0; i < size; ++i)
        {
            pop_back();
        }
    }

    template <typename T>
    const T &my_vector<T>::operator[](std::size_t index) const
    {
        return array_[index];
    }

    template <typename T>
    T &my_vector<T>::operator[](std::size_t index)
    {
        return array_[index];
    }

    template <typename U>
    std::ostream &operator<<(std::ostream &out, const my_vector<U> &v)
    {
        for (size_t i = 0; i < v.size(); ++i)
        {
            out << v[i];
            if (i < v.size() - 1)
            {
                out << " ";
            }
        }
        return out;
    }
}