#include "PriorityQueue.h"

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
}
template<typename T>
int PriorityQueue<T>::getSize() const {
    return list.size();
}

