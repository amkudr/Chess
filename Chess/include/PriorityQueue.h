#ifndef CHESS_PRIORITYQUEUE_H
#define CHESS_PRIORITYQUEUE_H

#include <memory>
#include <list>

using namespace std;

template<typename T>
class PriorityQueue {
    struct MyComparator {
        bool operator()(const shared_ptr<T> &a, const shared_ptr<T> &b) {
            return *a - *b;
        }
    };

    list<shared_ptr<T>> list;
    MyComparator comparator;

public:
    void push(shared_ptr<T> item);

    shared_ptr<T> poll();

    int getSize() const;
};

#endif //CHESS_PRIORITYQUEUE_H
