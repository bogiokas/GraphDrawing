#pragma once
#include "Basics/Basics.hpp"

class Shape {
public:
	Shape(const Color& col) : m_col(col) {}
	void Draw() const {
		ChooseColor();
		AddToGL();
	}
	void ChooseColor() const;
	virtual void AddToGL() const = 0;
	virtual ~Shape() {};
private:
	Color m_col;
};

enum class CoordsSetting { Cartesian, Polar };
class Point2 : public Shape {
public:
	Point2(const Color& col = BLUE)
		: Shape(col), m_pt{0.0, 0.0} {}
	Point2(double s, double t, CoordsSetting setting = CoordsSetting::Cartesian, const Color& col = BLUE)
		: Shape(col), m_pt{0.0, 0.0} {
			if(setting == CoordsSetting::Cartesian) m_pt = {s, t};
			else if(setting == CoordsSetting::Polar) m_pt = {s*cos(t), s*sin(t)};
			else assert(false);
		}
	static Point2 Zero() { return Point2(0.0, 0.0); }
	static Point2 X() { return Point2(1.0, 0.0); }
	static Point2 Y() { return Point2(0.0, 1.0); }
	void operator+=(const Point2& other) {
		m_pt[0] += other.GetPt()[0];
		m_pt[1] += other.GetPt()[1];
	}
	void operator-=(const Point2& other) {
		m_pt[0] -= other.GetPt()[0];
		m_pt[1] -= other.GetPt()[1];
	}
	void operator*=(double r) {
		m_pt[0] *= r;
		m_pt[1] *= r;
	}
	void operator/=(double r) {
		m_pt[0] /= r;
		m_pt[1] /= r;
	}
	Point2 operator+(const Point2& other) const {
		return Point2(m_pt[0]+other.GetPt()[0], m_pt[1]+other.GetPt()[1]);
	}
	Point2 operator-(const Point2& other) const {
		return Point2(m_pt[0] - other.GetPt()[0], m_pt[1] - other.GetPt()[1]);
	}
	Point2 operator-() const {
		return Point2(-m_pt[0], -m_pt[1]);
	}
	Point2 operator*(double r) const {
		return Point2(m_pt[0]*r, m_pt[1]*r);
	}
	Point2 operator/(double r) const {
		return Point2(m_pt[0]/r, m_pt[1]/r);
	}
	double operator[](Index i) const {
		return m_pt[i];
	}
	double& operator[](Index i) {
		return m_pt[i];
	}
	double NormQ() const {
		return m_pt[0]*m_pt[0] + m_pt[1]*m_pt[1];
	}
	double Norm() const {
		return std::sqrt(NormQ());
	}
	void Normalize() {
		double normQ = NormQ();
		if(normQ > EPSQ) *this/=std::sqrt(normQ);
		else *this = Zero();
	}
	double DistQ(const Point2& other) const {
		return (other-*this).NormQ();
	}
	const std::array<double, 2>& GetPt() const {
		return m_pt;
	}
	virtual void AddToGL() const override;
private:
	std::array<double, 2> m_pt;
};

class Segment2 : public Shape {
public:
	Segment2(const Point2& ptS, const Point2& ptE, const Color& col = RED)
		: Shape(col), m_ptS(ptS), m_ptE(ptE) {}
	virtual void AddToGL() const override;
private:
	Point2 m_ptS, m_ptE;
};

class Circle2 : public Shape {
public:
	Circle2(const Point2& pt, double r, const Color& col)
		: Shape(col), m_pt(pt), m_r(r) {}
	virtual void AddToGL() const override;
private:
	Point2 m_pt;
	double m_r;
};
