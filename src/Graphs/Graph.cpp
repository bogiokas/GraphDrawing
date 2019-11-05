#include "Graph.hpp"
#include "Output/DrawHelper.hpp"
#include "Physics/ForceBuilder.hpp"
#include "Label.hpp"

Graph::Graph(const std::vector<constLabel>& labels, const std::vector<std::array<constLabel, 2>>& labelPairs)
		: m_V(), m_E(), m_eventHandler(this) {
	m_V.reserve(labels.size());
	for(const auto& label : labels)
		assert(InsertVertex(label));
	ArrangeVerticesAtCircle();
	m_E.reserve(labelPairs.size());
	for(const auto& labelPair : labelPairs)
		assert(InsertEdge(labelPair));
}

template<class Name> Graph::Graph(const std::vector<Name>& rawLabels, const std::vector<std::array<Name, 2>>& rawLabelPairs)
		: m_V(), m_E(), m_eventHandler(this) {
	m_V.reserve(rawLabels.size());
	for(const auto& rawLabel : rawLabels) {
		auto oLabel = Label<Name>(rawLabel);
		assert(InsertVertex(&oLabel));
	}
	ArrangeVerticesAtCircle();
	m_E.reserve(rawLabelPairs.size());
	for(const auto& rawLabelPair : rawLabelPairs) {
		auto oLabel0 = Label<Name>(rawLabelPair[0]);
		auto oLabel1 = Label<Name>(rawLabelPair[1]);
		assert(InsertEdge({ &oLabel0, &oLabel1 }));
	}
}

Graph::Graph(Index n, const std::vector<std::array<Index, 2>>& rawLabelPairs)
		: m_V(), m_E(), m_eventHandler(this) {
	m_V.reserve(n);
	for(Index i=0; i<n; i++) {
		auto oLabel = Label<Index>(i);
		assert(InsertVertex(&oLabel));
	}
	ArrangeVerticesAtCircle();
	m_E.reserve(rawLabelPairs.size());
	for(const auto& rawLabelPair : rawLabelPairs) {
		auto oLabel0 = Label<Index>(rawLabelPair[0]);
		auto oLabel1 = Label<Index>(rawLabelPair[1]);
		assert(InsertEdge({ &oLabel0, &oLabel1 }));
	}
}

Graph::Graph(const std::vector<constLabel>& labels, const std::function<bool(constLabel, constLabel)> binRelation)
		: m_V(), m_E(), m_eventHandler(this) {
	m_V.reserve(labels.size());
	for(const auto& label : labels)
		assert(InsertVertex(label));
	ArrangeVerticesAtCircle();
	for(const auto& label0 : labels) {
		for(const auto& label1 : labels) {
			if(binRelation(label0, label1))
				assert(InsertEdge({ label0, label1 }));
		}
	}
}

template<class Name> Graph::Graph(const std::vector<Name>& rawLabels, const std::function<bool(const Name&, const Name&)> rawBinRelation)
		: m_V(), m_E(), m_eventHandler(this) {
	m_V.reserve(rawLabels.size());
	for(const auto& rawLabel : rawLabels) {
		auto oLabel = Label<Name>(rawLabel);
		assert(InsertVertex(&oLabel));
	}
	ArrangeVerticesAtCircle();
	for(const auto& rawLabel0 : rawLabels) {
		for(const auto& rawLabel1 : rawLabels) {
			if(rawBinRelation(rawLabel0, rawLabel1)) {
				auto oLabel0 = Label<Name>(rawLabel0);
				auto oLabel1 = Label<Name>(rawLabel1);
				assert(InsertEdge({ &oLabel0, &oLabel1 }));
			}
		}
	}
}


Graph::Graph(Index n, const std::function<bool(Index, Index)> rawBinRelation)
		: m_V(), m_E(), m_eventHandler(this) {
	m_V.reserve(n);
	for(Index i=0; i<n; i++) {
		auto oLabel = Label<Index>(i);
		assert(InsertVertex(&oLabel));
	}
	ArrangeVerticesAtCircle();
	for(Index i=0; i<n; i++) {
		for(Index j=0; j<n; j++) {
			if(rawBinRelation(i, j)) {
				auto oLabel0 = Label<Index>(i);
				auto oLabel1 = Label<Index>(j);
				assert(InsertEdge({ &oLabel0, &oLabel1 }));
			}
		}
	}
}

bool Graph::InsertVertex(constLabel label) {
	return m_V.insert(std::make_unique<Vertex>(std::move(label->clone()))).second;
}

bool Graph::InsertEdge(const std::array<constLabel, 2>& labelPair) {
	auto v0 = FindVertex(labelPair[0]);
	if(!v0.has_value()) return false;
	auto v1 = FindVertex(labelPair[1]);
	if(!v1.has_value()) return false;
	return m_E.insert(std::make_unique<Edge>(*v0, *v1)).second;
}

std::optional<Vertex*> Graph::FindVertex(constLabel label) const {
	auto it = std::find_if(m_V.begin(), m_V.end(), [label](const auto& v) { return v->GetLabel()->IsEqual(label); });
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

bool Graph::IsVertex(constLabel label) {
	auto it = std::find_if(m_V.begin(), m_V.end(), [label](const auto& pV) { return pV->GetLabel()->IsEqual(label); });
	return it != m_V.end();
}

bool Graph::IsEdge(const std::array<constLabel, 2> labelPair) {
	if(!IsVertex(labelPair[0]) || !IsVertex(labelPair[1])) return false;
	auto it = std::find_if(m_E.begin(), m_E.end(), [labelPair](const auto& pE) {
			auto labels = pE->GetLabels();
			return labels[0] == labelPair[0] && labels[1] == labelPair[1];
	});
	return it != m_E.end();
}

Vertex* Graph::LocateVertexAt(const Point2& pt) const {
	for(const auto& v : m_V) {
		if(v->GetNode().Contains(pt)) return v.get();
	}
	return nullptr;
}


const std::vector<constLabel> Graph::GetVertexLabels() const {
	std::vector<constLabel> labels;
	labels.reserve(size());
	for(const auto& v : m_V)
		labels.push_back(v->GetLabel());
	return labels;
}
const std::vector<std::array<constLabel, 2>> Graph::GetEdgeLabels() const {

	std::vector<std::array<constLabel, 2>> labelPairs;
	labelPairs.reserve(m_E.size());
	for(const auto& e : m_E)
		labelPairs.push_back(e->GetLabels());
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

