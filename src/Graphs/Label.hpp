#pragma once
#include "Basics.hpp"

class LabelBase {
public:
	virtual bool operator==(const LabelBase& other) const = 0;
};

template<class Name> class Label : public LabelBase {
public:
	Label<Name>(const Name& name) : m_name(name) {}
	Label<Name>(const Label<Name>& other) = default;
	const Name& GetName() const {
		return m_name;
	}
	bool operator==(const LabelBase& other) const override {
		const auto otherLabel = dynamic_cast<const Label<Name>*>(&other);
		if(otherLabel == nullptr) return false;
		return m_name == otherLabel->GetName();
	}
private:
	Name m_name;
};

template class Label<Index>;

