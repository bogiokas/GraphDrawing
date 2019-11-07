#pragma once
#include "Basics/Basics.hpp"

class LabelBase;
using constLabel = const LabelBase*;

class LabelBase {
public:
	virtual size_t Hash() const = 0;
	virtual bool IsEqual(constLabel other) const = 0;
	virtual std::unique_ptr<LabelBase> clone() const = 0;
	virtual ~LabelBase() = default;
};

template<class Name> class Label : public LabelBase {
public:
	Label<Name>(const Name& name) : m_name(name) {}
	Label<Name>(const Label<Name>& other) = default;
	const Name& GetName() const {
		return m_name;
	}
	size_t Hash() const override {
		return std::hash<Name>()(m_name);
	}
	bool IsEqual(constLabel other) const override {
		const auto otherCasted = dynamic_cast<const Label<Name>*>(other);
		if(otherCasted == nullptr) return false;
		return m_name == otherCasted->GetName();
	}
	std::unique_ptr<LabelBase> clone() const override {
		return std::make_unique<Label<Name>>(m_name);
	}
	~Label<Name>() override = default;
private:
	Name m_name;
};

template class Label<Index>;

