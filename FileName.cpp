
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include<iostream>
#include <sstream>
#include "Node.h"
#include "Edge.h"

using namespace std;
using namespace sf;

Mouse mouse;
Font font;
Texture TArea, Confirm_Button;

vector<Edge> Edges;
vector<Node> Nodes;
vector <pair <Node, Node> > Graph;


void Draw_Edge(vector <pair <Node, Node> > Temp1, vector <Edge>& Temp2)
{
    Temp2.clear();
    for (auto itr = Temp1.begin(); itr != Temp1.end(); itr++)
    {
        Node node = itr->first;
        Node node2 = itr->second;

        Vector2f pos1 = node.position;
        Vector2f pos2 = node2.position;

        Edge* edge = new Edge(pos1, pos2);
        Temp2.push_back(*edge);
    }
}

int main() {
    RenderWindow window(VideoMode(1920, 1080), "Graph Editor");
    // window.setFramerateLimit(60);

    int counter = 0;

    Clock cursorClock;
    Time cursorTimer;
    bool cursorVisible = false;

    font.loadFromFile("Font/font.ttf");

    TArea.loadFromFile("Textures/TextArea.png");
    Sprite TextArea;
    TextArea.setTexture(TArea);
    TextArea.setPosition(50, 100);

    Confirm_Button.loadFromFile("Textures/Confirm.png");
    Sprite Confirm;
    Confirm.setTexture(Confirm_Button);
    Confirm.setPosition(50, 600);

    string text = "";
    Text Source;

    Source.setFont(font);
    Source.setCharacterSize(30);
    Source.setString("");
    Source.setFillColor(Color::Black);
    Source.setPosition(55, 120);

    Sprite TextArea2;
    TextArea2.setTexture(TArea);
    TextArea2.setPosition(50, 300);

    string text2 = "";
    Text Destination;

    Destination.setFont(font);
    Destination.setCharacterSize(30);
    Destination.setString("");
    Destination.setFillColor(Color::Black);
    Destination.setPosition(55, 320);

    Node* Giza = new Node("Giza");
    Node* Aswan = new Node("Aswan");
    Node* Cairo = new Node("Cairo");

    Nodes.push_back(*Giza);
    Nodes.push_back(*Aswan);
    Nodes.push_back(*Cairo);

    pair< Node, Node>* IntialNodes = NULL;
    IntialNodes->first = *Giza;
    IntialNodes->second = *Aswan;
    Graph.push_back(*IntialNodes);

    IntialNodes->first = *Cairo;
    IntialNodes->second = *Aswan;
    Graph.push_back(*IntialNodes);

    IntialNodes->first = *Cairo;
    IntialNodes->second = *Giza;
    Graph.push_back(*IntialNodes);

    Draw_Edge(Graph, Edges);

    bool isDraggingEdge = false;
    Vector2i edgeStartPos;
    Vector2i edgeEndPos;

    while (window.isOpen()) {
        RectangleShape mouseshadow(Vector2f(15, 15));
        RectangleShape cursor(Vector2f(5, 0));
        cursor.setFillColor(Color::Black);

        mouseshadow.setPosition(mouse.getPosition().x, mouse.getPosition().y - 40);
        mouseshadow.setFillColor(Color::Black);

        Event event;
        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }

            if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(TextArea.getGlobalBounds()))
            {
                counter = 1;
            }
            if (event.type == Event::TextEntered && event.type != Keyboard::Enter && counter == 1)
            {
                text += static_cast<char>(event.text.unicode);
                Source.setString(text);
            }

            if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(TextArea2.getGlobalBounds()))
            {
                counter = 2;
            }
            if (event.type == Event::TextEntered && event.type != Keyboard::Enter && counter == 2)
            {
                text2 += static_cast<char>(event.text.unicode);
                Destination.setString(text2);
            }

            //Node old position and new position

            if (event.type == sf::Event::MouseButtonPressed)
            {
                for (size_t i = 0; i < Nodes.size(); ++i)
                {
                    bool nodeClicked = false;
                    int clickedNodeIndex = -1;

                    if (Mouse::isButtonPressed(Mouse::Right) && mouseshadow.getGlobalBounds().intersects(Nodes[i].shape.getGlobalBounds()))
                    {
                        Vector2i mousePos1 = Mouse::getPosition(window);
                        nodeClicked = false;
                        clickedNodeIndex = -1;
                    }

                    if (mouseshadow.getGlobalBounds().intersects(Nodes[i].shape.getGlobalBounds()))
                    {
                        nodeClicked = true;
                        clickedNodeIndex = i;
                        break;
                    }
                    if (event.type == Event::MouseButtonReleased)
                    {
                        Vector2i mousePos2 = Mouse::getPosition(window);

                        Vector2f Temp = static_cast<Vector2f>(mousePos2);

                        Nodes[clickedNodeIndex].Update_Position(Temp);

                        Draw_Edge(Graph, Edges);
                    }

                }

            }
            if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(Confirm.getGlobalBounds()))
            {
                bool Source_Unique = true, Destination_Unique = true;
                Node* Test = NULL;
                Node* Test2 = NULL;

                for (auto itr = Nodes.begin(); itr != Nodes.end(); itr++)
                {
                    if (itr->text == text && Source_Unique == true)
                    {
                        Source_Unique = false;
                        Test = &(*itr);
                    }
                    if (itr->text == text2 && Destination_Unique == true)
                    {
                        Destination_Unique = false;
                        Test2 = &(*itr);
                    }

                }
                if (Source_Unique == true && Destination_Unique == true)
                {
                    Node* Source = new Node(text);
                    Node* Destination = new Node(text2);

                    Nodes.push_back(*Source);
                    Nodes.push_back(*Destination);

                    pair <Node, Node>* Temp = NULL;
                    Temp->first = *Source;
                    Temp->second = *Destination;

                    Graph.push_back(*Temp);

                }
                else if (Source_Unique == true && Destination_Unique == false)
                {
                    Node* Source = new Node(text);
                    Nodes.push_back(*Source);

                    pair <Node, Node>* Temp = NULL;
                    Temp->first = *Source;
                    Temp->second = *Test2;

                    Graph.push_back(*Temp);

                }
                else if (Destination_Unique == true && Source_Unique == false)
                {
                    Node* Destination = new Node(text2);
                    Nodes.push_back(*Destination);

                    pair <Node, Node>* Temp = NULL;
                    Temp->first = *Test;
                    Temp->second = *Destination;

                    Graph.push_back(*Temp);
                }
                else if (Destination_Unique == false && Source_Unique == false)
                {
                    pair <Node, Node>* Temp = NULL;
                    Temp->first = *Test;
                    Temp->second = *Test2;

                    Graph.push_back(*Temp);
                }

                Draw_Edge(Graph, Edges);

                text = "";
                text2 = "";
                Source.setString(text);
                Destination.setString(text2);
            }

            if (cursorClock.getElapsedTime().asMilliseconds() >= 500)
            {
                cursorVisible = !cursorVisible;
                cursorClock.restart();
            }
            //Delete

            if (Keyboard::isKeyPressed(Keyboard::Backspace) && text.size() > 0 && Keyboard::isKeyPressed(Keyboard::BackSpace) && counter == 1)
            {
                text.resize(text.size() - 1);
                Source.setString(text);
            }
            if (Keyboard::isKeyPressed(Keyboard::Backspace) && text2.size() > 0 && Keyboard::isKeyPressed(Keyboard::BackSpace) && counter == 2)
            {
                text2.resize(text2.size() - 1);
                Destination.setString(text2);
            }
            if (cursorClock.getElapsedTime().asMilliseconds() >= 500)
            {
                cursorVisible = !cursorVisible;
                cursorClock.restart();
            }

            if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(TextArea.getGlobalBounds()))
            {
                cursorVisible = true;
            }

            if (cursorVisible == true && counter == 1)
            {
                cursor.setSize(Vector2f(2, TextArea.getLocalBounds().height * 0.52));
                cursor.setPosition(Source.getPosition().x + Source.getLocalBounds().width + 5, Source.getPosition().y + 6);
            }

            if (Mouse::isButtonPressed(Mouse::Left) && mouseshadow.getGlobalBounds().intersects(TextArea2.getGlobalBounds()))
            {
                cursorVisible = true;
            }

            if (cursorVisible == true && counter == 2)
            {
                cursor.setSize(Vector2f(2, TextArea2.getLocalBounds().height * 0.52));
                cursor.setPosition(Destination.getPosition().x + Destination.getLocalBounds().width + 5, Destination.getPosition().y + 6);
            }
            //end of events
        }

        //begin of drawing

        window.clear(Color::Blue);


        for (auto itr = Edges.begin(); itr != Edges.end(); itr++)
        {
            window.draw(itr->line, 2, Lines);
        }


        for (auto itr = Nodes.begin(); itr != Nodes.end(); itr++)
        {
            window.draw(itr->shape);
            window.draw(itr->label);
        }
        window.draw(TextArea);
        window.draw(TextArea2);
        window.draw(Source);
        window.draw(Destination);
        window.draw(mouseshadow);
        window.draw(Confirm);
        window.draw(cursor);
        window.display();
    }

    return 0;
}
