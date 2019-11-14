#pragma once
#include "Basics/Basics.hpp"

class LabelBase;
template<class Name> class Label;

class LabelBuilder {
public:
	template<class Name> static std::unique_ptr<LabelBase> CreateLabel(const Name& name);
	template<class Name> static std::unique_ptr<LabelBase> CloneLabelAndAddInfo(Label<Name> label, Index info) {
		return std::move(CreateLabel(std::make_pair(label.GetName(), info)));
		//return std::make_unique<Label<std::pair<Name, Index>>>(std::make_pair(label.GetName(), info));
	}
};

