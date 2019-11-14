#include "Basics/Basics.hpp"
#include "Graphs/Graph.hpp"
#include "Graphs/GraphBuilder.hpp"
#include "GLHelper/GLHelper.hpp"

int main() {
	//auto pG = GraphBuilder::Dual(*GraphBuilder::DisjointUnion(*GraphBuilder::Cycle(3),*GraphBuilder::Cross(3)));
	auto pG = GraphBuilder::Complete(10);
	//auto pG = GraphBuilder::Dual(*GraphBuilder::Cycle(26));
	//auto pG = GraphBuilder::Dual(*GraphBuilder::Union(*GraphBuilder::Cycle(3),*GraphBuilder::Cross(3)));
	//able to init up to K_{37} w/o exploding
	//auto pG = GraphBuilder::Cross(4);
	//auto pG = GraphBuilder::Dual(*GraphBuilder::Cycle(26));
	//auto pG = GraphBuilder::Union(*GraphBuilder::Cross(4), *GraphBuilder::Cross(4));
	//auto pG = GraphBuilder::BipartiteComplete(3,3);
	//auto pG = GraphBuilder::Cube(3);

	GLHelper gl(pG.get());
	while(gl.IsActive()) {
		gl.BeginLoop();
		pG->Update();
		pG->Draw();
		gl.EndLoop();
	}
	return 0;
}
