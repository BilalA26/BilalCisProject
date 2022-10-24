# BilalCisProject

#pragma once
#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int nextPrime(int n);
int hash1(const string& key);
int hash1(int key);

template <typename HashedObj>
class HashTable
{
public:

    explicit HashTable(int size = 101) : array(nextPrime(size))
    {
        makeEmpty();
    }

    bool contains(const HashedObj& x) const
    {
        return isActive(findPos(x));
    }

    void makeEmpty()
    {
        currentSize = 0;
        for (int i = 0; i < array.size(); i++)
            array[i].info = EMPTY;

        numberOfObjectsInTable = 0;
    }

    bool insert(const HashedObj& x)
     {
        int currentPos = findPosInsert(x);
        if (isActive(currentPos))
        {
            return false;
        }
        array[currentPos] = HashEntry(x, ACTIVE);
        numberOfObjectsInTable++;
        if (++currentSize > array.size() / 2)
            rehash();

        return true;
    }

    bool remove(const HashedObj& x)
    {
        int currentPos = findPos(x);
        if (!isActive(currentPos))
            return false;

        array[currentPos].info = DELETED;
        numberOfObjectsInTable--;
        return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

    double getCollisionLengthAverage()
    {
        double sum = 0;
        double size = collisionAverage.size();
        for (int i = 0; i < collisionAverage.size(); ++i)
        {
            sum += collisionAverage[i];
        }
        return sum / size;
    }

    int getLongestCollision()
    {
        auto biggest = (collisionAverage.begin(), collisionAverage.end());
        return *biggest;
    }

    int getTotalCollisions()
    {
        int number = 0;
        for (int i = 0; i < collisionAverage.size(); ++i)
        {
            if (collisionAverage[i] > 1)
            {
                number++;
            }
        }
        return number;
    }

    double getLoadFactor()
    {
        double temp = array.size();
        return numberOfObjectsInTable / temp;
    }

    int getArraySize()
    {
        return array.size();
    }

    int getNumberOfObjectsInTable()
    {
        return numberOfObjectsInTable;
    }

private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY)
            : element(e), info(i) {}

    };

    vector<HashEntry> array;
    int currentSize;
    bool isActive(int currentPos) const
    {
        return array[currentPos].info == ACTIVE;
    }

    int findPosInsert(const HashedObj& x)
    {
        int offset = 1;
        int currentPos = myhash(x);

        collisionCount = 1;
        while (array[currentPos].info != EMPTY &&
            array[currentPos].element != x)
        {
            if (collisionCount == 1)
            {
                numberOfCollisionInsertions++;
            }
            collisionCount++;
            currentPos += offset;
            offset += 2;
            if (currentPos >= array.size())
                currentPos -= array.size();
        }
        if (collisionCount > longestCollision)
        {
            longestCollision = collisionCount;
        }
        collisionAverage.push_back(collisionCount);
        return currentPos;
    }

    int findPos(const HashedObj& x) const
    {
        int offset = 1;
        int currentPos = myhash(x);

        while (array[currentPos].info != EMPTY &&
            array[currentPos].element != x)
        {

            currentPos += offset;
            offset += 2;
            if (currentPos >= array.size())
                currentPos -= array.size();
        }
        return currentPos;
    }

    void rehash()
    {

        if (collisionCount > longestCollision)
        {
            longestCollision = collisionCount;
        }
        collisionCount = 0;
        numberOfCollisionInsertions = 0;
        vector<HashEntry> oldArray = array;

        array.resize(nextPrime(2 * oldArray.size()));
        for (int j = 0; j < array.size(); j++)
            array[j].info = EMPTY;

        currentSize = 0;
        for (int i = 0; i < oldArray.size(); i++)
            if (oldArray[i].info == ACTIVE)
                insert(oldArray[i].element);
    }

    int myhash(const HashedObj& x) const
    {
        int hashVal = hash1(x);

        hashVal %= array.size();
        if (hashVal < 0)
            hashVal += array.size();

        return hashVal;
    }

    int longestCollision = 0;
    int numberOfObjectsInTable = 0;
    int collisionCount = 1;
    int numberOfCollisionInsertions = 0;
    vector<int> collisionAverage;
};
#endif
