#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include "node.h"



template<class T>
class PriorityQueue
{
private:
    class Node;
public:
    PriorityQueue();
    ~PriorityQueue();
public:
    void    push(const T & value);
    void    pop();
    void    clear();
public:
    void show() const;

    std::size_t size() const;
    bool        is_empty() const;
    T &         top();
    T &         back();
private:
    void priorityPush(Node * node);
private:
    void freeMemory();
private:
    std::size_t m_size;
    Node *      m_data;
    Node *      m_top;
    Node *      m_back;
private:
    class Node
    {
    public:
        Node(const T & value);
    public:
        void setValue(const T & value);
        void setPerent(Node * node);
        void setNext(Node * node);
        T &   value();
        Node * perent() const
        { return m_perent; }
        Node * next() const
        { return m_next; }
    public:
        bool operator < (const Node & node) const
        { return m_value < node.value(); }
        bool operator > (const Node & node) const
        { return m_value > node.value(); }\
        bool operator == (const Node & node) const
        { return m_value == node.value(); }
    private:
        T m_value;
        Node * m_perent;
        Node * m_next;
    };
};

template<class T>
PriorityQueue<T>::Node::Node(const T &value)
    : m_value(value), m_perent(nullptr), m_next(nullptr)
{}

template<class T>
void PriorityQueue<T>::Node::setValue(const T &value)
{
    m_value = value;
}

template<class T>
void PriorityQueue<T>::Node::setPerent(PriorityQueue<T>::Node *node)
{
    m_perent = node;
}

template<class T>
void PriorityQueue<T>::Node::setNext(PriorityQueue<T>::Node *node)
{
    m_next = node;
}

template<class T>
T & PriorityQueue<T>::Node::value()
{
    return m_value;
}

template<class T>
PriorityQueue<T>::PriorityQueue()
    : m_size(0), m_data(nullptr), m_top(nullptr), m_back(nullptr)
{
}

template<class T>
PriorityQueue<T>::~PriorityQueue()
{
    PriorityQueue::freeMemory();
}

template<class T>
void PriorityQueue<T>::show() const
{
    std::cout << "show: " << std::endl;
    if(PriorityQueue::is_empty()){
        std::cout << "Queue is null" << std::endl;
        return;
    }
    Node * ptr = m_top;
    while(ptr != nullptr){
        std::cout << ptr->value() << std::endl;
        ptr =ptr->next();
    }
    std::cout << std::endl;
}

template<>
void PriorityQueue<huffman::Node *>::show() const
{
    std::cout << "show: " << std::endl;
    if(PriorityQueue::is_empty()){
        std::cout << "Queue is null" << std::endl;
        return;
    }
    Node * ptr = m_top;
    while(ptr != nullptr){
        std::cout << *ptr->value() << std::endl;
        ptr = ptr->next();
    }
    std::cout << std::endl;
}


template<class T>
std::size_t PriorityQueue<T>::size() const
{
    return m_size;
}

template<class T>
bool PriorityQueue<T>::is_empty() const
{
    if(m_size == 0)
        return true;
    return false;
}

template<class T>
T & PriorityQueue<T>::top()
{
    return m_top->value();
}

template<class T>
T & PriorityQueue<T>::back()
{
    return m_back->value();
}

template<class T>
void PriorityQueue<T>::priorityPush(PriorityQueue<T>::Node * node)
{
    Node * ptr = m_top;
    for(std::size_t i = 0; i < m_size; ++i){
        if(node->value() > ptr->value())
            ptr = ptr->next();
        else if(node->value() <=  ptr->value()){
            node->setPerent(ptr->perent());
            if(ptr->perent() != nullptr)
                ptr->perent()->setNext(node);
            node->setNext(ptr);
            ptr->setPerent(node);
            if(ptr == m_back && ptr == m_top)
                m_top = node;
            else if(ptr == m_top)
                m_top = node;
            else if(ptr == m_back)
                m_back = node;
            return;
        }
    }
    m_back->setNext(node);
    node->setPerent(m_back);
    m_back = node;
}

template<>
void PriorityQueue<huffman::Node *>::priorityPush(PriorityQueue<huffman::Node *>::Node * node)
{
    Node * ptr = m_top;
    for(std::size_t i = 0; i < m_size; ++i){
        if(node->value()->weigth() > ptr->value()->weigth()){
            ptr = ptr->next();
        }
        else if(node->value()->weigth() <=  ptr->value()->weigth()){
            node->setPerent(ptr->perent());
            if(ptr->perent() != nullptr)
                ptr->perent()->setNext(node);
            node->setNext(ptr);
            ptr->setPerent(node);
            if(ptr == m_back && ptr == m_top)
                m_top = node;
            else if(ptr == m_top)
                m_top = node;
            return;
        }
    }
    m_back->setNext(node);
    node->setPerent(m_back);
    m_back = node;
}

template<class T>
void PriorityQueue<T>::push(const T &value)
{
    Node * node = new Node(value);
    if(PriorityQueue::is_empty())
        m_top = m_back = node;
    else
        PriorityQueue::priorityPush(node);
    ++m_size;
}

template<class T>
void PriorityQueue<T>::pop()
{
    if(PriorityQueue::is_empty())
        return;
    Node * temp = m_top;
    if(m_size == 1){
        m_top = m_back = nullptr;
    }else{
        m_top = m_top->next();
        m_top->setPerent(nullptr);
    }
    delete temp;
    --m_size;
}

template<class T>
void PriorityQueue<T>::freeMemory()
{
    while(!PriorityQueue::is_empty())
        PriorityQueue::pop();
}

template<class T>
void PriorityQueue<T>::clear()
{
    if(PriorityQueue::is_empty())
        return false;
    PriorityQueue::freeMemory();
}

#endif // PRIORITYQUEUE_H
