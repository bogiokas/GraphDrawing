#include "Graph.hpp"
#include "Output/DrawHelper.hpp"
#include "Physics/ForceBuilder.hpp"
#include "Label.hpp"

Graph::Graph(std::vector<std::unique_ptr<LabelBase>> V, std::vector<std::array<LabelBase*, 2>> E) : m_V(), m_E(), m_eventHandler(this) {
	Init(std::move(V), std::move(E));
}

Graph::Graph(Index n, const std::vector<std::array<Index, 2>>& indexPairs) : m_V(), m_E(), m_eventHandler(this) {
	std::vector<std::unique_ptr<LabelBase>> V(n);
	for(Index i = 0; i < n; ++i)
		V[i] = std::make_unique<Label<Index>>(i);
	Index m = indexPairs.size();
	std::vector<std::array<LabelBase*, 2>> E(m);
	for(Index i = 0; i < m; ++i)
		E[i] = std::array<LabelBase*, 2>({ V[indexPairs[i][0]].get(), V[indexPairs[i][1]].get() });
			//E[i] = { V[indexPairs[i][0]].get(), V[indexPairs[i][1]].get() };
	Init(std::move(V), std::move(E));
}

void Graph::Init(std::vector<std::unique_ptr<LabelBase>> V, std::vector<std::array<LabelBase*, 2>> E) {
	m_V.reserve(V.size());
	for(auto& pLabel : V)
		assert(InsertVertex(std::move(pLabel)));
	m_E.reserve(E.size());
	for(const auto& labelPair : E)
		assert(InsertEdge(labelPair[0], labelPair[1]));
	ArrangeVerticesAtCircle();
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

bool Graph::InsertVertex(std::unique_ptr<LabelBase> pLabel) {
	return m_V.insert(std::make_unique<Vertex>(std::move(pLabel))).second;
}
bool Graph::InsertEdge(LabelBase* pLabel0, LabelBase* pLabel1) {
	auto it0 = std::find_if(m_V.begin(), m_V.end(), [pLabel0](const auto& pV) { return pV->GetLabel() == pLabel0; });
	if(it0 == m_V.end()) return false;
	auto it1 = std::find_if(m_V.begin(), m_V.end(), [pLabel1](const auto& pV) { return pV->GetLabel() == pLabel1; });
	if(it1 == m_V.end()) return false;
	m_E.insert(std::make_unique<Edge>(it0->get(), it1->get()));
	return true;
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

void Graph::ArrangeVerticesAtCircle(const double r) {
	Index n = size();
	Index i = 0;
	for(const auto& v : m_V) {
		const Point2& pt = Point2(r, 2*M_PI*i/n, CoordsSetting::Polar);
		v->FixNodeToPosition(pt);
		i++;
	}
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

