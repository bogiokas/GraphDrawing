#pragma once
#include<functional>
#include "Basics/Basics.hpp"
#include "Basics/PtrUnorderedSet.hpp"

#include "Basics/Shapes.hpp"
#include "Graphs/Vertex.hpp"
#include "Graphs/Edge.hpp"
#include "Graphs/GraphEventHandler.hpp"

using VertexSet = PtrUnorderedSet<Vertex>;
using EdgeSet = PtrUnorderedSet<Edge>;

class Graph {
public:
	Graph(const std::vector<Label>& labels, const std::vector<std::array<Label, 2>>& labelPairs);
	template<class T> Graph(const std::vector<T>& names, const std::vector<std::array<T, 2>>& namePairs)
			: m_V(), m_E(), m_eventHandler(this) {
		Init(CreateLabels(names), CreateLabelPairs(namePairs));
	}
	Graph(Index n, const std::vector<std::array<Index, 2>>& rawLabelPairs);

	Graph(const std::vector<Label>& labels, const std::function<bool(Label, Label)> binRelation);
	template<class T> Graph(const std::vector<T>& names, const std::function<bool(const T&, const T&)> binRelation)
			: m_V(), m_E(), m_eventHandler(this) {
		std::vector<std::array<Label, 2>> labelPairs;
		for(const auto& name0 : names) {
			for(const auto& name1 : names) {
				if(binRelation(name0, name1))
					labelPairs.push_back({Label(name0), Label(name1)});
			}
		}
		Init(CreateLabels(names), labelPairs);
	}
	Graph(Index n, const std::function<bool(Index, Index)> binRelation);

	inline Index size() const { return m_V.size(); }
	inline GraphEventHandler& GetEventHandler() { return m_eventHandler; }

	double Density() {
		return 2 * m_E.size() / (size() * (size() - 1));
	}

	void Update();
	void Draw() const;

	bool IsVertex(const Label& label) const;
	bool IsEdge(const std::array<Label, 2>& labelPair) const;

	std::vector<Label> GetVertexLabels() const;
	std::vector<std::array<Label, 2>> GetEdgeLabels() const;

	Vertex* LocateVertexAt(const Point2& pt) const;
private:
	template<class T> std::vector<Label> CreateLabels(std::vector<T> names) {
		std::vector<Label> labels;
		labels.reserve(names.size());
		for(const auto& name : names)
			labels.emplace_back(name);
		return labels;
	}
	std::vector<Label> CreateLabels(Index n);
	template<class T> std::vector<std::array<Label, 2>> CreateLabelPairs(std::vector<std::array<T, 2>> namePairs) {
		std::vector<std::array<Label, 2>> labelPairs;
		labelPairs.reserve(namePairs.size());
		for(const auto& namePair : namePairs)
			labelPairs.push_back({Label(namePair[0]), Label(namePair[1])});
		return labelPairs;
	}

	void Init(const std::vector<Label>& labels, const std::vector<std::array<Label, 2>>& labelPairs);
	bool InsertVertex(const Label& label);
	bool InsertEdge(const std::array<Label, 2>& labelPair);

	std::optional<Vertex*> FindVertex(const Label& label) const;

	void ArrangeVerticesAtCircle(double r=0.5);
	void MakeVerticesRepelEachOther(double intensity);
	void MakeEdgesTryToKeepFixedDist(double dist, double intensity);
	void MakeVerticesBeRepelledFromBoundary(double intensity);
	void MakeVerticesBeDamped(double intensity);
	void LockVertexIfNeeded();
	void UpdateAllNodes();

	VertexSet m_V;
	EdgeSet m_E;
	GraphEventHandler m_eventHandler;
};

