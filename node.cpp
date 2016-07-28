#include "node.h"

namespace huffman
{
    Node::Node()
        : m_left(nullptr), m_rigth(nullptr), m_value(nullptr), m_weigth(0)
    {
    }

    Node::Node(int weigth, Node *left, Node *rigth)
        : m_left(left), m_rigth(rigth), m_value(nullptr), m_weigth(weigth)
    {
    }

    Node::Node(char value, int weigth, Node *left, Node *rigth)
        : m_left(left), m_rigth(rigth), m_weigth(weigth)
    {
        m_value = new char;
        *m_value = value;
    }

    Node::~Node()
    {
        if(Node::is_value())
            delete m_value;
    }

    void Node::setLeft(Node * node)
    {
        m_left = node;
    }

    void Node::setRigth(Node * node)
    {
        m_rigth = node;
    }

    void Node::setWeigth(int weigth)
    {
        m_weigth = weigth;
    }

    void Node::setValue(char value)
    {
        if(!Node::is_value())
            m_value = new char;
        *m_value = value;
    }

    bool Node::is_value() const
    {
        if(m_value == nullptr)
            return false;
        return true;
    }

    char Node::value() const
    {
        return *m_value;
    }

    int Node::weigth() const
    {
        return m_weigth;
    }

    Node * Node::left() const
    {
        return m_left;
    }

    Node * Node::rigth() const
    {
        return m_rigth;
    }

    Node & Node::operator = (const Node & node)
    {
        if(this == &node)
            return *this;
        m_left = node.left();
        m_rigth = node.rigth();
        m_weigth = node.weigth();
        delete m_value;
        if(node.is_value()){
            m_value = new char;
            *m_value = node.value();
        }
        else
            m_value = nullptr;
        return *this;
    }

    std::ostream & operator << (std::ostream & os, const Node & node)
    {
        os << node.weigth() << " : ";
        if(node.is_value())
            std::cout << node.value();
        else
            std::cout << "Null";
        return os;
    }
}
