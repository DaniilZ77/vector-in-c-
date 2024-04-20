#include <iostream>
#include <cassert>
#include <cstring>
#include <ostream>

#include "my_vector.hpp"

namespace product
{

    class Product
    {
    public:
        friend std::ostream &operator<<(std::ostream &out, const Product &product);
        Product(const char *name, int quantity, double price);
        Product(const Product &other);
        Product &operator=(Product other);
        ~Product();
        bool operator==(const Product &other) const;
        bool operator!=(const Product &other) const;

    private:
        void swap(Product &other);

    private:
        char *name_;
        int quantity_;
        double price_;
    };

    Product::Product(const char *name, int quantity, double price)
    {
        name_ = new char[std::strlen(name) + 1];
        std::strcpy(name_, name);
        quantity_ = quantity;
        price_ = price;
    }

    std::ostream &operator<<(std::ostream &out, const Product &product)
    {
        out << product.name_ << " " << product.quantity_ << " " << product.price_;
        return out;
    }

    bool Product::operator==(const Product &other) const
    {
        return std::strcmp(name_, other.name_) == 0 && quantity_ == other.quantity_ && price_ == other.price_;
    }

    Product &Product::operator=(Product other)
    {
        swap(other);
        return *this;
    }

    void Product::swap(Product &other)
    {
        std::swap(name_, other.name_);
        std::swap(quantity_, other.quantity_);
        std::swap(price_, other.price_);
    }

    bool Product::operator!=(const Product &other) const
    {
        return !(*this == other);
    }

    Product::~Product()
    {
        delete[] name_;
    }

    Product::Product(const Product &other)
    {
        name_ = new char[std::strlen(other.name_) + 1];
        std::strcpy(name_, other.name_);
        quantity_ = other.quantity_;
        price_ = other.price_;
    }

}; // namespace product

namespace tests
{
    template <typename T>
    void test_my_vector(const T &a, const T &b)
    {
        containers::my_vector<T> v;

        assert(v.empty() && "vector is expected to be empty but it doesn't");

        v.push_back(a);

        assert(v.size() == 1 && "The size of array is not correct");
        assert(v.capacity() == 1 && "The actual capacity is wrong");
        assert(v[0] == a && "The element in position 0 is not corresponding to the expected one");

        v.push_back(a);
        assert(v.size() == 2 && "The size of array is not correct");
        assert(v.capacity() == 2 && "The actual capacity is wrong");
        assert(v[0] == a && v[1] == a && "The elements in positions 0 and 1 are not corresponding to the expected");

        v.push_back(b);
        assert(v.size() == 3 && "The size of array is not correct");
        assert(v.capacity() == 4 && "The actual capacity is wrong");
        assert(v[0] == a && v[1] == a && v[2] == b && "The elements in positions 0, 1 and 2 are not corresponding to the expected");

        assert(!v.empty() && "The empty function does not work fine");

        v.reserve(900);

        assert(v.capacity() == 1024 && v.size() == 3 && "Reservation seems to not work find");

        for (int i = 0; i < 1000; ++i)
        {
            v.push_back(b);
        }

        assert(v.capacity() == 1024 && v.size() == 1003 && "Vector does not work properly with large amount of data after push_back function");

        for (int i = 0; i < 1000; ++i)
        {
            v.pop_back();
        }

        assert(!v.empty() && v.size() == 3 && v.capacity() == 1024 && "Empty after pop_back() does not seem to work in a correct way");

        for (int i = 0; i < 1000; ++i)
        {
            v.push_back(a);
        }

        v.clear();

        assert(v.size() == 0 && v.capacity() == 1024 && "Simple clear() check");

        // operator= assert tests and copy constructor

        for (int i = 0; i < 1000; ++i)
        {
            v.push_back(b);
        }

        containers::my_vector<T> copy_v(v);

        assert(v.size() == copy_v.size() && v.capacity() == copy_v.capacity() && "Copy constructor size and capacity");

        for (size_t i = 0; i < copy_v.size(); ++i)
        {
            assert(v[i] == copy_v[i] && "Checking for elements equality after copying with the copy constructor");
        }

        v[0] = a;

        assert(v[0] != copy_v[0] && "The array seems to not be a deep copy");

        // operator= assert test

        copy_v = v;

        assert(v.size() == copy_v.size() && v.capacity() == copy_v.capacity() && "Operator= size and capacity");

        for (size_t i = 0; i < copy_v.size(); ++i)
        {
            assert(v[i] == copy_v[i] && "Checking for elements equality after copying with the copy constructor");
        }

        copy_v[0] = b;

        assert(v[0] != copy_v[0] && "The array seems to not be a deep copy");

        std::cout << "test_my_vector success" << std::endl;
    }

    template <typename T>
    void test_my_vector_default_constructible(const T &a, const T &b)
    {
        // testing constructor(size_t n)

        containers::my_vector<T> v(100);

        assert(v.size() == 100 && v.capacity() == 128 && "Constructor with argument of the initial size of array seems to work in an incorrect way");

        // resize assert test

        for (size_t i = 0; i < 100; ++i)
        {
            v.push_back(a);
        }

        v[0] = a;

        assert(v[0] == a && v.size() == 200 && v.capacity() == 256 && "Seems that push_back breaks the work of size and capacity");

        v.resize(101);

        assert(v.size() == 101 && v.capacity() == 256 && "Resize breaks size and capacity if resize arg is less then size");

        assert(v[100] == a && "Resize does not preserve the element value");

        std::cout << "test_my_vector_default_constructible success" << std::endl;

        // resize to lesser elements check

        v.resize(1);

        assert(v[0] == a && v.size() == 1 && !v.empty() && v.capacity() == 256 && "Resizing less elements seems to not work as expected");
    }
}

int main()
{
    containers::my_vector<int> v;
    v.push_back(2);
    const int n{3};
    v.push_back(n);
    std::cout << v << std::endl;

    tests::test_my_vector<int>(5, 10);

    tests::test_my_vector_default_constructible<int>(5, 10);

    tests::test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));

    return 0;
}
