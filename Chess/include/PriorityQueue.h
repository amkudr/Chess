#ifndef CHESS_PRIORITYQUEUE_H
#define CHESS_PRIORITYQUEUE_H

#include <memory>
#include <list>

using namespace std;

template<typename T>
class PriorityQueue {
    struct MyComparator {
        bool operator()(const shared_ptr<T> &a, const shared_ptr<T> &b) {
            return *b < *a;
        }
    };

    list<shared_ptr<T>> list;
    MyComparator comparator;

public:
    PriorityQueue() = default;
    void push(shared_ptr<T> item);

    shared_ptr<T> poll();

    int getSize() const;

    void clear() {
        list.clear();
    }
};

template<typename T>
shared_ptr<T> PriorityQueue<T>::poll() {
    if (list.empty()) {
        return nullptr;
    }
    shared_ptr<T> item = list.front();
    list.pop_front();
    return item;
}

template<typename T>
void PriorityQueue<T>::push(shared_ptr<T> item) {
    auto it = list.begin();
    while (it != list.end() && comparator(*it, item)) {
        it++;
    }
    list.insert(it, item);
//    if (list.size() > 5) {
//        list.pop_back();
//    }
}
template<typename T>
int PriorityQueue<T>::getSize() const {
    return list.size();
}



#endif //CHESS_PRIORITYQUEUE_H
