#include "Basics/Basics.hpp"
#include "Graphs/Graph.hpp"
#include "Graphs/GraphBuilder.hpp"
#include "GLHelper/GLHelper.hpp"

#include<iostream>
int main() {
	//auto pG = GraphBuilder::Dual(*GraphBuilder::DisjointUnion(*GraphBuilder::Cycle(3),*GraphBuilder::Cross(3)));
	auto pG = GraphBuilder::Complete(10);

	GLHelper gl(pG.get());
	while(gl.IsActive()) {
		gl.BeginLoop();
		pG->Update();
		pG->Draw();
		gl.EndLoop();
	}
	return 0;
}
