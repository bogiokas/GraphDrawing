#include "Graph.hpp"
#include "DrawHelper.hpp"

#include<iostream>

Vertex::Vertex(Index i, Index n)
	: name(i), node(Point2(0.5*cos(2*M_PI*i/n), 0.5*sin(2*M_PI*i/n))) {}

void Vertex::FixNodeToPosition(const Point2& pt) {
	node.StayStill();
	node.SetPos(pt);
}
void Vertex::ApplyForceToNode(const Point2& force, double intensity) {
	node.ApplyForce(force * intensity);
}
void Vertex::UpdateNode() {
	node.Update();
}

Graph::Graph(Index n, const std::vector<std::array<Index, 2>>& vPairs) : V(n), E(), eventHandler(this) {
	for(Index i = 0; i<n ; ++i) V[i] = std::make_unique<Vertex>(i, n);
	E.reserve(vPairs.size());
	for(const auto& vPair : vPairs) {
		E.push_back(std::make_unique<Edge>(V[vPair[0]].get(), V[vPair[1]].get()));
	}
}

void Graph::Update() {
	double intensityRepel = 0.1;
	double intensityAttract = 0.2;
	MakeVerticesRepelEachOther(intensityRepel);
	MakeEdgesTryToKeepFixedDist(0.2, intensityAttract);
	LockVertexIfNeeded();
	UpdateAllNodes();
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

void Graph::MakeVerticesRepelEachOther(double intensity) {
	for(auto& v0 : V) {
		for(const auto& v1 : V) {
			if(*v0 != *v1) {
				v0->ApplyForceToNode(Force::CalcForceToRepel(v0->GetNode(), v1->GetNode()), intensity);
			}
		}
	}
}

void Graph::MakeEdgesTryToKeepFixedDist(double dist, double intensity) {
	for(const auto& e : E) {
		const auto& vertices = e->GetVertices();
		const auto& v0 = vertices[0];
		const auto& v1 = vertices[1];
		v0->ApplyForceToNode(Force::CalcForceToKeepAtDist(v0->GetNode(), v1->GetNode(), dist), intensity);
		v1->ApplyForceToNode(Force::CalcForceToKeepAtDist(v1->GetNode(), v0->GetNode(), dist), intensity);
	}
}

void Graph::LockVertexIfNeeded() {
	if(auto lock = eventHandler.GetLock(); lock.has_value()) {
		auto [pV, pt] = *lock;
		pV->FixNodeToPosition(pt);
	}
}

void Graph::UpdateAllNodes() {
	for(auto& v : V) {
		v->UpdateNode();
	}
}

