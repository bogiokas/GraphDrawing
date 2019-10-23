#include "Physics.hpp"
#include "DrawHelper.hpp"

void Physics::Update() {
	m_vel += m_acc * timestep;
	m_pos += m_vel * timestep;
	m_acc = Point2::Zero();
	RestrictInsideBoundary();
}

void Physics::StayStill() {
	m_vel = Point2::Zero();
	m_acc = Point2::Zero();
}

void Physics::SetPos(const Point2& pt) {
	Point2 prevPos = m_pos;
	m_pos = pt;
	m_vel = (m_pos-prevPos)/timestep;
	RestrictInsideBoundary();
}
void Physics::RestrictInsideBoundary() {
	bool restrict = false;
	if(m_pos[0] >= 1.0) {
		m_pos[0] = 1.0 - 5*EPS;
		restrict = true;
	}
	else if(m_pos[0] <= -1.0) {
		m_pos[0] = -1.0 + 5*EPS;
		restrict = true;
	}
	if(m_pos[1] >= 1.0) {
		m_pos[1] = 1.0 - 5*EPS;
		restrict = true;
	}
	else if(m_pos[1] <= -1.0) {
		m_pos[1] = -1.0 + 5*EPS;
		restrict = true;
	}
	if(restrict) {
		m_vel = Point2::Zero();
		m_acc = Point2::Zero();
	}
}

void Physics::ApplyForce(const Point2& force) {
	m_acc += force/m_mass;
}

Point2 Force::CalcForceToAttract(const Physics& nodeFrom, const Physics& nodeTo) {
	double forceMagnitude = CalcGravitationalForceMagnitude(nodeFrom, nodeTo);
	Point2 direction = nodeTo.GetPos() - nodeFrom.GetPos();
	direction.Normalize();
	return direction * forceMagnitude;
}

Point2 Force::CalcForceToRepel(const Physics& nodeFrom, const Physics& nodeTo) {
	double forceMagnitude = CalcGravitationalForceMagnitude(nodeFrom, nodeTo);
	Point2 direction = nodeFrom.GetPos() - nodeTo.GetPos();
	direction.Normalize();
	return direction * forceMagnitude;
}

Point2 Force::CalcForceToRepelFromBoundary(const Physics& nodeFrom) {
	const auto& pos = nodeFrom.GetPos();
	Physics projRight = Physics(Point2(1.0, pos[1]));
	double forceMagnitudeRight = CalcGravitationalForceMagnitude(nodeFrom, projRight);
	Physics projLeft = Physics(Point2(-1.0, pos[1]));
	double forceMagnitudeLeft = CalcGravitationalForceMagnitude(nodeFrom, projLeft);
	Physics projUp = Physics(Point2(pos[0], 1.0));
	double forceMagnitudeUp = CalcGravitationalForceMagnitude(nodeFrom, projUp);
	Physics projDown = Physics(Point2(pos[0], -1.0));
	double forceMagnitudeDown = CalcGravitationalForceMagnitude(nodeFrom, projDown);
	return Point2::Xinv() * forceMagnitudeRight +
		Point2::X() * forceMagnitudeLeft +
		Point2::Yinv() * forceMagnitudeUp +
		Point2::Y() * forceMagnitudeDown;
}

Point2 Force::CalcForceToKeepAtDist(const Physics& nodeFrom, const Physics& nodeTo, double dist) {
	double d = (nodeFrom.GetPos() - nodeTo.GetPos()).Norm();
	double frac = (d - dist)/d;
	const auto fracPos = nodeFrom.GetPos()*(1-frac) + nodeTo.GetPos()*frac;
	const auto nodeTarget = Physics(fracPos, nodeTo.GetVel());
	return CalcDampedHarmonicOscilationForce(nodeFrom, nodeTarget);
}

double Force::CalcGravitationalForceMagnitude(const Physics& node0, const Physics& node1) {
	constexpr double gConst = 0.005;
	double distQ = (node0.GetPos() - node1.GetPos()).NormQ();
	return gConst * node0.GetMass()  * node1.GetMass() / distQ;
}

Point2 Force::CalcDampedHarmonicOscilationForce(const Physics& node0, const Physics& node1) {
	return CalcHarmonicOscilationForce(node0, node1) + CalcDampingForce(node0, node1);
}

Point2 Force::CalcHarmonicOscilationForce(const Physics& node0, const Physics& node1) {
	constexpr double kConst = 0.01;
	Point2 relativePos = node1.GetPos() - node0.GetPos();
	return relativePos * kConst;
}

Point2 Force::CalcDampingForce(const Physics& node0, const Physics& node1) {
	constexpr double cConst = 0.1; // limit: 2sqrt(m*k) = 0.2
	Point2 relativeVel = node1.GetVel() - node0.GetVel();
	return relativeVel * cConst;
}

