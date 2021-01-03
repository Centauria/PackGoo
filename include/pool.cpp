#include "pool.h"

template <typename T>
Pool<T>::Pool(const unsigned int capacity) {
    m_capacity_ = capacity;
}

template <typename T>
Pool<T>::~Pool() {

}

template <typename T>
unsigned int Pool<T>::size() {
    return m_vol_.size();
}

template <typename T>
bool Pool<T>::is_full() {
    return size() == m_capacity_;
}

template <typename T>
std::vector<std::string> Pool<T>::keys() {
    std::vector<std::string> ks;
    for (auto const& k : m_vol_) {
        ks.push_back(k.first);
    }
    return ks;
}

template <typename T>
bool Pool<T>::add(std::string key, T value) {
    if (!is_full()) {
        m_vol_[key] = value;
        m_reference_count_[key] = 1;
    }
    return true;
}

template <typename T>
bool Pool<T>::release(std::string key) {
    delete m_vol_[key];
    return true;
}
