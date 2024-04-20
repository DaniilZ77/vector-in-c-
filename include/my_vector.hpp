#pragma once

#include <cstddef>
#include <cstring>
#include <ostream>

namespace containers
{

    template <typename T>
    class my_vector
    {
    public:
        template <typename U>
        friend std::ostream &operator<<(std::ostream &out, const my_vector<U> &v);

        my_vector();
        my_vector(std::size_t n);
        my_vector(const my_vector &other);
        my_vector &operator=(my_vector other);
        ~my_vector();

        std::size_t size() const;
        std::size_t capacity() const;
        bool empty() const;

        void resize(std::size_t n);
        void reserve(std::size_t n);

        const T &operator[](std::size_t index) const;
        T &operator[](std::size_t index);

        void push_back(const T &t);
        void pop_back();
        void clear();

    private:
        size_t min_power_of_2(size_t n) const;
        void delete_elements(size_t amount);
        void swap_memory_and_delete(size_t size, size_t capacity);
        void swap_memory_and_delete_default_constructible(size_t size, size_t capacity);
        void swap(my_vector &other);
        void invoke_destructors();

    private:
        size_t capacity_;
        size_t size_;
        T *array_;
    };

}

#include "my_vector_impl.hpp"