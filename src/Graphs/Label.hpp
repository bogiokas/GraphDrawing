#pragma once
#include "Basics/Basics.hpp"

class Label {
public:
	template<class T> Label(const T& name) : m_pName(new Name<T>(name)) {}
	Label(const Label& other) : m_pName(other.m_pName->copy()) {}
	void operator=(const Label& other) { m_pName.reset(other.m_pName->copy()); }
	size_t Hash() const { return m_pName->Hash(); }
	bool operator==(const Label& other) const { return *m_pName == *other.m_pName; }
private:
	struct NameBase {
	public:
		virtual size_t Hash() const = 0;
		virtual bool operator==(const NameBase&  other) const = 0;
		virtual NameBase* copy() const = 0;
		virtual ~NameBase() = default;
//		virtual std::unique_ptr<LabelBase> cloneAndAddExtraInfo(const Index& info) const = 0;
	};

	template<class T> struct Name : NameBase {
	public:
		Name(T name) : m_name(std::move(name)) {}
		size_t Hash() const override {
			return std::hash<T>()(m_name);
		}
		bool operator==(const NameBase& other) const override {
			const auto otherCasted = dynamic_cast<const Name<T>*>(&other);
			if(otherCasted == nullptr) return false;
			return m_name == otherCasted->m_name;
		}
		NameBase* copy() const override {
			return new Name<T>(m_name);
		}
//		std::unique_ptr<LabelBase> cloneAndAddExtraInfo(const Index& info) const override {
//			return std::move(LabelBuilder::CloneLabelAndAddInfo(*this, info));
//		}
	private:
		T m_name;
	};

	std::unique_ptr<NameBase> m_pName;
};

