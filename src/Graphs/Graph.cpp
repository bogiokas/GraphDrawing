#include "Graph.hpp"
#include "DrawHelper.hpp"
#include "Physics/ForceBuilder.hpp"
#include "Label.hpp"

//Graph::Graph(const std::vector<std::unique_ptr<LabelBase>> V,
//	const std::vector<std::array<std::unique_ptr<LabelBase>, 2>> E)
//	: m_V(V.size()), m_E(), m_eventHandler(this) {
//}

Graph::Graph(Index n, const std::vector<std::array<Index, 2>>& E) 
	: m_V(n), m_E(), m_eventHandler(this) {
	constexpr double initD = 0.5;
	for(Index i = 0; i<n ; ++i) {
		auto pLabel = std::make_unique<Label<Index>>(i);
		m_V[i] = std::make_unique<Vertex>(std::move(pLabel));
		const Point2& pt = Point2(initD*cos(2*M_PI*i/n),initD*sin(2*M_PI*i/n));
		m_V[i]->FixNodeToPosition(pt);
	}
	m_E.reserve(E.size());
	for(const auto& e : E) {
		m_E.push_back(std::make_unique<Edge>(m_V[e[0]].get(), m_V[e[1]].get()));
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
	DrawHelper::Draw(m_E);
	DrawHelper::Draw(m_V);
}

Vertex* Graph::LocateVertexAt(const Point2& pt) const {
	for(const auto& v : m_V) {
		if(v->GetNode().Contains(pt)) return v.get();
	}
	return nullptr;
}

const std::vector<std::array<const LabelBase*, 2>> Graph::GetEdgeLabels() const {
	std::vector<std::array<const LabelBase*, 2>> edgeLabels;
	edgeLabels.reserve(m_E.size());
	for(const auto& e : m_E)
		edgeLabels.push_back(e->GetLabels());
	return edgeLabels;
}

void Graph::MakeVerticesRepelEachOther(double intensity) {
	for(auto& v0 : m_V) {
		for(const auto& v1 : m_V) {
			if(*v0 != *v1) {
				v0->ApplyForceToNode(ForceBuilder::RepulsionForce(v0->GetNode(), v1->GetNode()), intensity);
			}
		}
	}
}

void Graph::MakeEdgesTryToKeepFixedDist(double dist, double intensity) {
	for(const auto& e : m_E) {
		const auto& vertices = e->GetVertices();
		const auto& v0 = vertices[0];
		const auto& v1 = vertices[1];
		v0->ApplyForceToNode(ForceBuilder::KeepAtDistForce(v0->GetNode(), v1->GetNode(), dist), intensity);
		v1->ApplyForceToNode(ForceBuilder::KeepAtDistForce(v1->GetNode(), v0->GetNode(), dist), intensity);
	}
}

void Graph::LockVertexIfNeeded() {
	if(auto lock = m_eventHandler.GetLock(); lock.has_value()) {
		auto [pV, pt] = *lock;
		pV->FixNodeToPosition(pt);
	}
}

void Graph::UpdateAllNodes() {
	for(auto& v : m_V) {
		v->UpdateNode();
	}
}

