#include "MagicalContainer.hpp"
#include <stdexcept>
using namespace ariel;

// ***************************************//
// MagicalContainer                       //
// ***************************************//

MagicalContainer::MagicalContainer() {}

MagicalContainer::~MagicalContainer()
{
    for (int* prime : primes)
    {
        delete prime;
    }
    primes.clear();
}




void MagicalContainer::addElement(int element)
{
    auto elementsIter = lower_bound(elements.begin(), elements.end(), element);
    elements.insert(elementsIter, element);

    // Check if the added element is a prime number
    if (isPrime(element)) {
        auto primeElement = new int(element);
        auto primesIter = lower_bound(primes.begin(), primes.end(), primeElement,
                                      [](const int* a, const int* b) {
                                          return *a < *b;
                                      });
        primes.insert(primesIter, primeElement);
    }

    std::sort(primes.begin(), primes.end(), [](const int* a, const int* b) {
        return *a < *b;
    });
}





void MagicalContainer::removeElement(int element)
{
    auto it = std::find(elements.begin(), elements.end(), element);
    if (it != elements.end())
    {
        elements.erase(it);
    }
    else
    {
        throw std::runtime_error("The element is not in the container");
    }
}


int MagicalContainer::size()
{
    return elements.size();
}
bool MagicalContainer::isPrime(int num) const
{
    if (num < 2)
    {
        return false;
    }
    for (int i = 2; i * i <= num; ++i)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}



// ***************************************//
// AscendingIterator                      //
// ***************************************//
MagicalContainer::AscendingIterator::AscendingIterator()
    : container(nullptr), index(0) {
    // Default constructor
}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
    : container(other.container), index(other.index) {
    // Copy constructor
}

MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer& other)
    : container(&other), index(0) {
    // Constructor that takes a MagicalContainer parameter
}

MagicalContainer::AscendingIterator::~AscendingIterator() {
    // Destructor
}


MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other)
{
    if (container != other.container)
    {
        throw std::runtime_error("Assigning iterators from different containers is not allowed");
    }
    if (this != &other)
    {
        container = other.container;
        index = other.index;
    }
    return *this;
}


bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
    // Equality comparison operator
    if (container == other.container) {
        return index == other.index;
    }
    return false;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
    // Inequality comparison operator
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
    // Less-than comparison operator
    if (container == other.container) {
        return index < other.index;
    }
    throw std::runtime_error("Comparison of iterators from different containers is not allowed");
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
    // Greater-than comparison operator
    if (container == other.container) {
        return index > other.index;
    }
    throw std::runtime_error("Comparison of iterators from different containers is not allowed");
}

int MagicalContainer::AscendingIterator::operator*() {
    // Dereference operator
    if (container) {
        return container->elements[index];
    }
    throw std::runtime_error("Iterator is not associated with a container");
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++()
{
    if (container && index < container->elements.size())
    {
        ++index;
        return *this;
    }
    throw std::runtime_error("Iterator is already at the end or not associated with a container");
}


MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    // begin() function
    if (container) {
        AscendingIterator it(*this);
        it.index = 0;
        return it;
    }
    throw std::runtime_error("Iterator is not associated with a container");
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    // end() function
    if (container) {
        AscendingIterator it(*this);
        it.index = container->elements.size();
        return it;
    }
    throw std::runtime_error("Iterator is not associated with a container");
}

MagicalContainer::SideCrossIterator::SideCrossIterator() : container(nullptr), index(0) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
    : container(other.container), index(other.index) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &other)
    : container(&other), index(0) {}

MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other)
{
    if (container != other.container)
    {
        throw std::runtime_error("You are trying to assign iterators from different containers");
    }
    if (this != &other)
    {
        index = other.index;
    }
    return *this;
}


bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
{
    return container == other.container && index == other.index;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
{
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
{
    return index < other.index;
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
{
    return index > other.index;
}

int MagicalContainer::SideCrossIterator::operator*()
{
    if (container && index < container->elements.size())
    {
        return container->elements[index];
    }
    throw std::runtime_error("Iterator is not associated with a container or reached the end");
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++()
{
    if (index == container->elements.size())
    {
        throw std::runtime_error("You are in the last element");
    }
    if (index == (container->elements.size() / 2))
    {
        index = container->elements.size();
        return *this;
    }

    if (index < (container->elements.size() / 2))
    {
        index = container->elements.size() - index - 1;
        return *this;
    }
    else if (index > (container->elements.size() / 2))
    {
        index = container->elements.size() - index;
        return *this;
    }

    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    SideCrossIterator iter(*this);
    iter.index = 0;
    return iter;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    SideCrossIterator iter(*this);
    iter.index = container->elements.size();
    return iter;
}

// ***************************************//
// PrimeIterator                          //
// ***************************************//

MagicalContainer::PrimeIterator::PrimeIterator()
    : container(nullptr), index(0) {}

ariel::MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
    : container(other.container), index(other.index) {}

MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &Container)
    : container(&Container), index(0) {}

MagicalContainer::PrimeIterator::~PrimeIterator() {}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    if (this->container != other.container)
    {
        throw runtime_error("You try to pointing at different containers");
    }

    if (this != &other)
    {
        container = other.container;
        index = other.index;
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
{
    return (container == other.container) && (index == other.index);
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
{
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
{
    return (container == other.container) && (index < other.index);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
{
    return (container == other.container) && (index > other.index);
}

int MagicalContainer::PrimeIterator::operator*()
{
    if (container && index < container->primes.size())
    {
        return *this->container->primes[index];
    }
    throw std::runtime_error("Iterator is not associated with a container or reached the end");
}


MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++()
{
    if (index == this->end().index)
    {
        throw std::runtime_error("You are in the last element");
    }
    ++index;
    return *this;
}


MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    if (container && !container->primes.empty())
    {
        PrimeIterator iter(*this);
        iter.index = 0;
        while (iter.index < container->primes.size() && !container->isPrime(*container->primes[iter.index]))
        {
            ++iter.index;
        }
        return iter;
    }
    throw std::runtime_error("Iterator is not associated with a container or no primes found");
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
   
        PrimeIterator iter(*this);
        iter.index = container->primes.size();
        return iter;
    
   throw std::runtime_error("Iterator is not associated with a container or no primes found");
}
