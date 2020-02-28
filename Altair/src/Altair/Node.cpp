#include "Node.h"
#include <cmath>

namespace Altair {

double Node::absoluteLength() {
	return sqrt(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2));
}

}