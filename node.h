#ifndef NODE_H
#define NODE_H

#include <iostream>

namespace huffman
{
    class Node
    {
    public:
        Node();
        Node(int weigth, Node * left = nullptr, Node * rigth = nullptr);
        Node(char value, int weigth, Node * left = nullptr, Node * rigth = nullptr);
        ~Node();
    public:
        void setWeigth(int weigth);
        void setValue(char value);
        void setLeft(Node * node);
        void setRigth(Node * node);
        int weigth() const;
        bool is_value() const;
        char value() const;
        Node * left() const;
        Node * rigth() const;
    public:
        friend std::ostream & operator << (std::ostream & os, const Node & node);
        Node & operator = (const Node & node);
    private:
        Node *  m_left;
        Node *  m_rigth;
        char *  m_value;
        int     m_weigth;
    };
}

#endif // NODE_H
