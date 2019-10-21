#include "Basics.hpp"
#include "Graph.hpp"
#include "GLHelper.hpp"
#include<iostream>

int main() {

//	Graph G(5, {
//		{0, 1}, {0, 2}, {0, 3},
//		{0, 4}, {1, 2}, {1, 3}
//	});
	Graph G(4, { {0,1}, {0,2}, {0,3}, {1,2}, {1,3}, {2,3} });
	//Graph G(3, { {0,1}, {0,2} });
	//Graph G(2, {});
#ifdef _DEBUG
	G.Print();
#endif

	GLHelper gl(&G);
	while(gl.IsActive()) {
		gl.BeginLoop();
		G.Update();
		G.Draw();
		gl.EndLoop();
	}
	return 0;
}
