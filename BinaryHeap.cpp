/**
 * @file BinaryHeap.cpp
 * @author Yadong Qu
 * @brief
 * @version 0.1
 * @date 2022-07-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <vector>
#include <optional>
struct BinaryHeap
{
    std::vector<int> data;

    void insert(int key)
    {
        data.push_back(key);
        heapify_up(data.size() - 1);
    }

    std::optional<int> pop()
    {
        if (data.size() == 0)
        {
            return std::nullopt;
        }
        auto result = std::optional<int>(data[0]);
        if (data.size() == 1)
        {
            data.pop_back();
            return result;
        }
        data[0] = data[data.size() - 1];
        data.pop_back();
        heapify_down(0);
        return result;
    }

    std::optional<size_t> parent(size_t index)
    {
        return index == 0
                   ? std::nullopt
                   : std::optional<size_t>((index - 1) / 2);
    }

    std::optional<size_t> left(size_t index)
    {
        size_t l = index * 2 + 1;
        return l >= data.size() ? std::nullopt : std::optional<size_t>(l);
    }

    std::optional<size_t> right(size_t index)
    {
        size_t r = index * 2 + 2;
        return r >= data.size() ? std::nullopt : std::optional<size_t>(r);
    }

    void
    heapify_up(size_t index)
    {
        while (index > 0 && data[parent(index).value()] > data[index])
        {
            std::swap(data[index], data[parent(index).value()]);
            index = parent(index).value();
        }
    }

    void heapify_down(size_t index)
    {
        auto l = left(index);
        auto r = right(index);
        size_t smallest = index;
        if (l.has_value() && data[l.value()] < data[smallest])
        {
            smallest = l.value();
        }

        if (r.has_value() && data[r.value()] < data[smallest])
        {
            smallest = r.value();
        }

        if (smallest != index)
        {
            std::swap(data[index], data[smallest]);
            heapify_down(smallest);
        }
    }
};

int main()
{
    BinaryHeap heap;
    heap.insert(8);
    heap.insert(3);
    heap.insert(1);
    heap.insert(9);
    std::cout << (heap.pop().value() == 1) << std::endl;
    std::cout << (heap.pop().value() == 3) << std::endl;
    std::cout << (heap.pop().value() == 8) << std::endl;
    std::cout << (heap.pop().value() == 9) << std::endl;
}