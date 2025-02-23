#include "node.h"

void Node::printNode(void(*func)(ADT data))
{
    func(data);
}

