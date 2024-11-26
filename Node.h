#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include<iostream>
#include <sstream>
#include <string>
using namespace std;
using namespace sf;

class Node
{
    int id;
    Font font;
public:

    Node(string Text);
    Vector2f position;
    Text label;
    CircleShape shape;
    string text;
    void Update_Position(Vector2f pos);
};

