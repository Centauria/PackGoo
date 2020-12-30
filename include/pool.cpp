#include "pool.h"

template <class T>
Pool<T>::Pool(const unsigned int capacity) {
    m_capacity_ = capacity;
}

template <class T>
Pool<T>::~Pool() {

}

template <class T>
unsigned int Pool<T>::size() {
    return m_vol_.size();
}

template <class T>
bool Pool<T>::is_full() {
    return size() == m_capacity_;
}

template <class T>
std::vector<std::string> Pool<T>::keys() {
    std::vector<std::string> ks;
    for (auto const& k : m_vol_) {
        ks.push_back(k.first);
    }
    return ks;
}

template <class T>
bool Pool<T>::add(std::string key, T value) {
    if (!is_full()) {
        m_vol_[key] = value;
        m_reference_count_[key] = 1;
    }
    return true;
}

template <class T>
bool Pool<T>::release(std::string key) {
    delete m_vol_[key];
    return true;
}
