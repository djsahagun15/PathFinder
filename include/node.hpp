#ifndef __PATHFINDER_NODE_HPP__
#define __PATHFINDER_NODE_HPP__


class Node {
public:
    Node(int x, int y);

    void draw() const;

private:
    int _x, _y;
};


#endif