#include "Graphs/LabelBuilder.hpp"

template<class Name> std::unique_ptr<LabelBase> LabelBuilder::CreateLabel(const Name& name) {

	std::unique_ptr<LabelBase> newLabel = std::make_unique<Label<Name>>(name);
	return std::move(newLabel);
}

template std::unique_ptr<LabelBase> LabelBuilder::CreateLabel<Index>(const Index& name);
template std::unique_ptr<LabelBase> LabelBuilder::CreateLabel<std::pair<Index, Index>>(const std::pair<Index, Index>& name);

