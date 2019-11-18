#include "Graphs/Graph.hpp"
#include "Output/DrawHelper.hpp"
#include "Physics/ForceBuilder.hpp"
#include "Graphs/Label.hpp"

Graph::Graph(const std::vector<Label>& labels, const std::vector<std::array<Label, 2>>& labelPairs) : m_V(), m_E(), m_eventHandler(this) {
	Init(labels, labelPairs);
}

Graph::Graph(Index n, const std::vector<std::array<Index, 2>>& namePairs) : m_V(), m_E(), m_eventHandler(this) {
	Init(CreateLabels(n), CreateLabelPairs(namePairs));
}

Graph::Graph(const std::vector<Label>& labels, const std::function<bool(Label, Label)> binRelation) : m_V(), m_E(), m_eventHandler(this) {
	std::vector<std::array<Label, 2>> labelPairs;
	for(const auto& label0 : labels) {
		for(const auto& label1 : labels) {
			if(binRelation(label0, label1))
				labelPairs.push_back({label0, label1});
		}
	}
	Init(labels, labelPairs);
}

Graph::Graph(Index n, const std::function<bool(Index, Index)> binRelation) : m_V(), m_E(), m_eventHandler(this) {
	std::vector<std::array<Label, 2>> labelPairs;
	for(Index i=0; i<n; i++) {
		for(Index j=0; j<n; j++) {
			if(binRelation(i, j))
				labelPairs.push_back({Label(i), Label(j)});
		}
	}
	Init(CreateLabels(n), labelPairs);
}

std::vector<Label> Graph::CreateLabels(Index n) {
	std::vector<Label> labels;
	labels.reserve(n);
	for(Index i=0; i<n; i++)
		labels.emplace_back(i);
	return labels;
}

void Graph::Init(const std::vector<Label>& labels, const std::vector<std::array<Label, 2>>& labelPairs) {
	m_V.reserve(labels.size());
	for(const auto& label : labels)
		assert(InsertVertex(label));
	ArrangeVerticesAtCircle();
	m_E.reserve(labelPairs.size());
	for(const auto& labelPair : labelPairs)
		assert(InsertEdge(labelPair));
}


bool Graph::InsertVertex(const Label& label) {
	m_V.insert(std::make_unique<Vertex>(label));
	return true;
}

bool Graph::InsertEdge(const std::array<Label, 2>& labelPair) {
	auto v0 = FindVertex(labelPair[0]);
	if(!v0.has_value()) return false;
	auto v1 = FindVertex(labelPair[1]);
	if(!v1.has_value()) return false;
	m_E.insert(std::make_unique<Edge>(*v0, *v1));
	return true;
}

std::optional<Vertex*> Graph::FindVertex(const Label& label) const {
	auto it = std::find_if(m_V.begin(), m_V.end(), [&label](const auto& v) { return v->GetLabel() == label; });
	if(it == m_V.end())
		return std::nullopt;
	return it->get();
}

void Graph::Update() {
	double intensityRepel = 0.01;
	double idealDistance = 0.5 * Density() + 0.2;
	double intensityFixedDistance = 1.0;
	double intensityBoundaryRepel = 0.05;
	double intensityDamping = 0.1;
	MakeVerticesRepelEachOther(intensityRepel);
	MakeEdgesTryToKeepFixedDist(idealDistance, intensityFixedDistance);
	MakeVerticesBeRepelledFromBoundary(intensityBoundaryRepel);
	MakeVerticesBeDamped(intensityDamping);
	LockVertexIfNeeded();
	UpdateAllNodes();
}

void Graph::Draw() const {
	DrawHelper::Draw(m_E);
	DrawHelper::Draw(m_V);
}

bool Graph::IsVertex(const Label& label) const {
	const auto& pV = FindVertex(label);
	return pV.has_value();
}

bool Graph::IsEdge(const std::array<Label, 2>& labelPair) const {
	if(!IsVertex(labelPair[0]) || !IsVertex(labelPair[1])) return false;
	auto v0 = std::make_unique<Vertex>(labelPair[0]);
	auto v1 = std::make_unique<Vertex>(labelPair[1]);
	auto e = std::make_unique<Edge>(v0.get(), v1.get());
	auto it = std::find_if(m_E.begin(), m_E.end(), [&e](const auto& f) { return Unique_Ptr_Eq<Edge>()(e, f); });
	return it != m_E.end();
}

Vertex* Graph::LocateVertexAt(const Point2& pt) const {
	for(const auto& v : m_V) {
		if(v->GetNode().Contains(pt)) return v.get();
	}
	return nullptr;
}


std::vector<Label> Graph::GetVertexLabels() const {
	std::vector<Label> labels;
	labels.reserve(m_V.size());
	for(const auto& v : m_V)
		labels.emplace_back(v->GetLabel());
	return labels;
}
std::vector<std::array<Label, 2>> Graph::GetEdgeLabels() const {
	std::vector<std::array<Label, 2>> labelPairs;
	labelPairs.reserve(m_E.size());
	for(const auto& e : m_E)
		labelPairs.emplace_back(e->GetLabels());
	return labelPairs;
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

void Graph::MakeVerticesBeRepelledFromBoundary(double intensity) {
	for (auto& v : m_V) {
		v->ApplyForceToNode(ForceBuilder::RepulsionFromBoundaryForce(v->GetNode()), intensity);
	}
}

void Graph::MakeVerticesBeDamped(double intensity) {
	for (auto& v : m_V) {
		v->ApplyForceToNode(ForceBuilder::DampingForce(v->GetNode()), intensity);
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

