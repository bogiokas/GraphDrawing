#pragma once
#include "Basics.hpp"
#include "Shapes.hpp"

class Physics {
public:
	Physics(const Point2& pos)
		: m_pos(pos), m_vel(), m_acc(), m_mass(1.0), m_r(0.05) {}
	Physics(const Point2& pos, const Point2& vel)
		: m_pos(pos), m_vel(vel), m_acc(), m_mass(1.0), m_r(0.05)  {}
	void Update();
	void StayStill();
	void RestrictInsideBoundary();
	void ApplyForce(const Point2& force);
	const Point2& GetPos() const { return m_pos; }
	const Point2& GetVel() const { return m_vel; }
	const Point2& GetAcc() const { return m_acc; }
	double GetMass() const { return m_mass; }
	void SetPos(const Point2& pt);
	bool Contains(const Point2& pt) const {
		return m_pos.DistQ(pt) < m_r * m_r;
	}
private:
	static double constexpr timestep = 1.0;
	Point2 m_pos;
	Point2 m_vel;
	Point2 m_acc;
	double m_mass;
	double m_r;
};

class Force {
public:
	static Point2 CalcForceToAttract(const Physics& nodeFrom, const Physics& nodeTo);
	static Point2 CalcForceToRepel(const Physics& nodeFrom, const Physics& nodeTo);
	static Point2 CalcForceToRepelFromBoundary(const Physics& nodeFrom);
	static Point2 CalcForceToKeepAtDist(const Physics& nodeFrom, const Physics& nodeTo, double dist);
private:
	static double CalcGravitationalForceMagnitude(const Physics& node0, const Physics& node1);
	static Point2 CalcDampedHarmonicOscilationForce(const Physics& node0, const Physics& node1);
	static Point2 CalcHarmonicOscilationForce(const Physics& node0, const Physics& node1);
	static Point2 CalcDampingForce(const Physics& node0, const Physics& node1);
};
