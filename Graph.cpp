#include "Graph.hpp"
#include "DrawHelper.hpp"

#include<iostream>

Vertex::Vertex(Index i, Index n)
	: name(i), node(Point2(0.5*cos(2*M_PI*i/n), 0.5*sin(2*M_PI*i/n))), isMouseLocked(false) {}

void Vertex::Print() const {
	std::cout<<name<<" ";
}

void Vertex::RestrictInsideBoundary() {
	node.RestrictInsideBoundary();
}

void Vertex::RepelledFrom(const Vertex& other, double intensity) {
	node.ApplyForce(Force::CalcForceToRepel(node, other.GetNode()) * intensity);
}

void Vertex::RepelledFromBoundary(double intensity) {
	node.ApplyForce(Force::CalcForceToRepelFromBoundary(node) * intensity);
}

void Vertex::AttractedTo(const Vertex& other, double intensity) {
	node.ApplyForce(Force::CalcForceToKeepAtDist(node, other.GetNode(), 0.2) * intensity);
}

void Vertex::Update() {
	if(!isMouseLocked) node.Update();
	else node.StayStill();
}

void Vertex::SetNodePos(const Point2& pt) {
	//assert(isMouseLocked);
	node.SetPos(pt);
}

void Edge::Print() const {
	std::cout<<"{";
	vertices[0]->Print();
	vertices[1]->Print();
	std::cout<<"} ";
}

Graph::Graph(Index n, const std::vector<std::array<Index, 2>>& vPairs) : V(n), eventHandler(this) {
	for(Index i = 0; i<n ; ++i) V[i] = std::make_unique<Vertex>(i, n);
	E.reserve(vPairs.size());
	for(const auto& vPair : vPairs) {
		E.push_back(std::make_unique<Edge>(V[vPair[0]].get(), V[vPair[1]].get()));
	}
}

void Graph::Print() const {
	std::cout<<"Graph:"<<std::endl;
	for(const auto& v : V) v->Print();
	for(const auto& e : E) e->Print();
	std::cout<<std::endl;
}

void Graph::Update() {
	double intensityRepel = 0.1;
	double intensityAttract = 0.2;
	for(auto& v0 : V) {
		for(const auto& v1 : V) {
			if(*v0 != *v1) v0->RepelledFrom(*v1, intensityRepel);
		}
	}
	for(const auto& e : E) {
		const auto& vertices = e->GetVertices();
		vertices[0]->AttractedTo(*vertices[1], intensityAttract);
		vertices[1]->AttractedTo(*vertices[0], intensityAttract);
	}
	for(const auto& v : V) v->Update();
}

void Graph::Draw() const {
	DrawHelper::Draw(E);
	DrawHelper::Draw(V);
}

Vertex* Graph::LocateVertexAt(const Point2& pt) const {
	for(const auto& v : V) {
		if(v->GetNode().Contains(pt)) return v.get();
	}
	return nullptr;
}

const std::vector<std::array<Index, 2>> Graph::GetEdgeNames() const {
	std::vector<std::array<Index, 2>> edgeNames;
	edgeNames.reserve(E.size());
	for(const auto& e : E)
		edgeNames.push_back(e->GetName());
	return edgeNames;
}

