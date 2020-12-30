#pragma once
#include <map>
#include <vector>
#include <string>

template <class T>
class Pool {
    unsigned int m_capacity_;
    std::map<std::string, T> m_vol_;
    std::map<std::string, unsigned int> m_reference_count_;

public:
    Pool(unsigned int capacity = 100);
    virtual ~Pool();
    unsigned int size();
    bool is_full();
    std::vector<std::string> keys();
    bool add(std::string key, T value);
    bool release(std::string key);
};

#include "pool.cpp"
