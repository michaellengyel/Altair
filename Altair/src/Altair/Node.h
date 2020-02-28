//TODO: Remove example class
#pragma once

namespace Altair {

class Node {
public:

	// Constructor
	Node(int x, int y, int z) : m_x(x), m_y(y), m_z(z) {}

	// Destructor
	~Node() {}

	// Member function declaration
	double absoluteLength();

	int getx() { return m_x; }
	int gety() { return m_y; }
	int getz() { return m_z; }

	void setx(int x) { m_x = x; }
	void sety(int y) { m_y = y; }
	void setz(int z) { m_z = z; }

private:
	int m_x, m_y, m_z;
};

}