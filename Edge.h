#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include<iostream>
#include <sstream>
#include <string>
using namespace std;
using namespace sf;

class Edge
{
	//vertex as it has 2 points (x,y)
public:
	Vertex line[2];

public:
	Edge(Vector2f& pos1, Vector2f& pos2);
};

