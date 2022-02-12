#pragma once
#include "Basics/Basics.hpp"

#include "Basics/Shapes.hpp"
#include "Force.hpp"

class Node {
public:
	Node()
		: m_pos(), m_vel(), m_acc(), m_mass(1.0), m_r(0.05) {}
	Node(const Point2& pos)
		: m_pos(pos), m_vel(), m_acc(), m_mass(1.0), m_r(0.05) {}
	Node(const Point2& pos, const Point2& vel)
		: m_pos(pos), m_vel(vel), m_acc(), m_mass(1.0), m_r(0.05)  {}
	void Update();
	void StayStill();
	void RestrictVelocity(double cap);
	void RestrictInsideBoundary();
	void ApplyForce(const Force& force);
	const Point2& GetPos() const { return m_pos; }
	const Point2& GetVel() const { return m_vel; }
	const Point2& GetAcc() const { return m_acc; }
	double GetMass() const { return m_mass; }
	void SetPos(const Point2& pt);
	bool Contains(const Point2& pt) const {
		return m_pos.DistQ(pt) < m_r * m_r;
	}
private:
	static double constexpr timestep = 0.3;
	Point2 m_pos;
	Point2 m_vel;
	Point2 m_acc;
	double m_mass;
	double m_r;
};

