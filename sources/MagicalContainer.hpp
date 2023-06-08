#pragma once
#include <stdio.h>
#include <vector>

using namespace std;
namespace ariel
{
    class MagicalContainer
    {
    private:
        vector<int> elements;
        std::vector< int*> primes;


    public:
        MagicalContainer();
        ~MagicalContainer() ;
        MagicalContainer(const MagicalContainer&) = delete;             // Delete copy constructor
       MagicalContainer& operator=(const MagicalContainer&) = delete;  // Delete copy assignment operator
          MagicalContainer(MagicalContainer&&) = delete;                  // Delete move constructor
        MagicalContainer& operator=(MagicalContainer&&) = delete;       // Delete move assignment op
        void addElement(int element);
        void removeElement(int element);
        int size();
        bool isPrime(int num) const;


        class AscendingIterator
        {
        private:
            const MagicalContainer *container;
            size_t index;

        public:
            AscendingIterator();
            AscendingIterator(const AscendingIterator &other);
            AscendingIterator(const MagicalContainer &mgcContainer);
            ~AscendingIterator();
            AscendingIterator(AscendingIterator&& other) = default;  // Move constructor
            AscendingIterator& operator=(AscendingIterator&& other)= default;  // Move assignment operator
            AscendingIterator &operator=(const AscendingIterator &other);
            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;
            bool operator>(const AscendingIterator &other) const;
            int operator*();
            AscendingIterator& operator++();
            AscendingIterator begin();
            AscendingIterator end();
        };

        class SideCrossIterator
        {
        private:
            const MagicalContainer *container;
            size_t index;

        public:
            SideCrossIterator();
            SideCrossIterator(const SideCrossIterator &other);
            SideCrossIterator(const MagicalContainer &mgcContainer);
            ~SideCrossIterator();
            SideCrossIterator &operator=(const SideCrossIterator &other);
             SideCrossIterator(SideCrossIterator&& other) = default;  // Move constructor
            SideCrossIterator& operator=(SideCrossIterator&& other)= default;  // Move assignment operator
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;
            int operator*();
            SideCrossIterator& operator++();
            SideCrossIterator begin();
            SideCrossIterator end();
        };

        class PrimeIterator
        {
        private:
            const MagicalContainer *container;
            size_t index;

        public:
            PrimeIterator();
            PrimeIterator(const PrimeIterator &other);
            PrimeIterator(const MagicalContainer &mgcContainer);
            ~PrimeIterator();
            PrimeIterator &operator=(const PrimeIterator &other);
             PrimeIterator(PrimeIterator&& other) = default;  // Move constructor
            PrimeIterator& operator=(PrimeIterator&& other)= default;  // Move assignment operator
            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;
            bool operator>(const PrimeIterator &other) const;
            int operator*();
            PrimeIterator& operator++();
            PrimeIterator begin();
            PrimeIterator end();
        };
    };

}