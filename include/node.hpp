#ifndef _PATHFINDER_NODE_HPP_
#define _PATHFINDER_NODE_HPP_

#include <raylib.h>
#include <memory>


enum State { NONE, START, END, PATH, EMPTY, WALL };

class Node {
public:
    Node(Rectangle rect, int x, int y);

    void setRect(Rectangle rect);

    float getDistance(Node* other) const;

    State getState() const;
    bool isVisited() const;
    void setState(State newState, bool visited = false);

    unsigned int getX() const;
    unsigned int getY() const;

    float getGCost() const;
    void setGCost(float gCost);

    float getHCost() const;
    void setHCost(float hCost);
    void setHCost(Node* endNode);

    float getFCost() const;

    Node* getParent() const;
    void setParent(Node* newParent);

    void draw() const;

private:
    Vector2 _center;
    Rectangle _rect;
    int _x, _y;
    
    State _state;
    bool _isVisited;

    float _gCost;
    float _hCost;
    float _fCost;

    Node* _parent;

    std::unique_ptr<Color> _color;
};


#endif