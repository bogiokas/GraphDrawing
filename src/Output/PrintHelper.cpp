#include "Output/PrintHelper.hpp"

#include<iostream>


void PrintHelper::PrintLine() {
	std::cout<<std::endl;
}

template<> void PrintHelper::Print(const Point2& point) {
	const auto& pt = point.GetPt();
	std::cout<<"("<<pt[0]<<", "<<pt[1]<<")"<<std::flush;
}

template<> void PrintHelper::Print(const Node& node) {
	std::cout<<"Pos: ";
	Print(node.GetPos());
	std::cout<<", Vel: ";
	Print(node.GetVel());
	std::cout<<", Acc: ";
	Print(node.GetAcc());
	std::cout<<", Mass: "<<node.GetMass()<<std::endl;
}
