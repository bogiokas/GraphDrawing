#include "Basics.hpp"
#include "Graph.hpp"
#include "GraphBuilder.hpp"
#include "GLHelper.hpp"

int main() {
	auto pG = GraphBuilder::Cross(4);

	GLHelper gl(pG.get());
	while(gl.IsActive()) {
		gl.BeginLoop();
		pG->Update();
		pG->Draw();
		gl.EndLoop();
	}
	return 0;
}
