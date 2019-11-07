#pragma once
#include "Basics.hpp"

template<class T> struct Unique_Ptr_Hash {
public:
	bool operator()(const std::unique_ptr<T>& ptr) const { return ptr->Hash(); }
};

template<class T> struct Unique_Ptr_Eq {
public:
	bool operator()(const std::unique_ptr<T>& ptr1, const std::unique_ptr<T>& ptr2) const { return *ptr1 == *ptr2; }
};

template<class T> using PtrUnorderedSet = std::unordered_set<std::unique_ptr<T>, Unique_Ptr_Hash<T>, Unique_Ptr_Eq<T>>;

namespace std {
	template<class T1, class T2> struct hash<std::pair<T1, T2>> {
		size_t operator()(std::pair<T1, T2> p) {
			return std::hash<T1>()(p.first) ^ std::hash<T2>()(p.second);
		}
	};
}

