#include "Edge.h"
#include "Node.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include<iostream>
#include <sstream>
using namespace std;
using namespace sf;

using namespace std;
using namespace sf;

Edge::Edge(Vector2f& pos1, Vector2f& pos2)
{
	line[0] = Vertex(pos1, Color::Black);
	line[1] = Vertex(pos2, Color::Black);

}
