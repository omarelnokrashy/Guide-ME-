#include "Node.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include<iostream>
#include <sstream>


using namespace std;
using namespace sf;


Node::Node(string Text)
{

    if (!font.loadFromFile("Font/font.ttf"))
    {
        cerr << "Failed to load font file." << endl;
    }
    this->text = Text;
    shape.setRadius(40);
    shape.setFillColor(Color::White);
    shape.setOutlineColor(Color::Black);
    shape.setOutlineThickness(2);
    shape.setOrigin(shape.getRadius(),shape.getRadius());
    position = Vector2f((rand()% 500)+1200,(rand()% 300)+100);


    Vector2f Temp = static_cast<Vector2f>(position);
    shape.setPosition(Temp);

    // Label the node with its id
    label.setString(Text);
    label.setCharacterSize(20);
    label.setFillColor(Color::Black);
    label.setPosition(position.x - 35, position.y - 20);
    label.setFont(font);

}

void Node::Update_Position(Vector2f pos)
{
    position = pos;
}

