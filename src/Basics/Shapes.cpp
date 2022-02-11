#include "Basics/Shapes.hpp"

#include <GL/glew.h>

void Shape::ChooseColor() const {
	glColor4f((GLfloat)m_col.r, (GLfloat)m_col.g, (GLfloat)m_col.b, (GLfloat)m_col.a);
}

void Point2::AddToGL() const { 
	glVertex2d(m_pt[0], m_pt[1]);
}

void Segment2::AddToGL() const {
	m_ptS.AddToGL();
	m_ptE.AddToGL();
}

void Circle2::AddToGL() const {
}
