#include "huffman.h"

template<> void PriorityQueue<huffman::Node *>::show() const;
template<> void PriorityQueue<huffman::Node *>::priorityPush(PriorityQueue<huffman::Node *>::Node * node);

Huffman::Huffman()
    : m_sizeNode(0), m_root(nullptr), m_root_nil(nullptr)
{
    m_root_nil = new Node;
}

Huffman::Huffman(const std::string & data)
    : m_data(data), m_sizeNode(0), m_root(nullptr), m_root_nil(nullptr)
{
    m_root_nil = new Node;
}

Huffman::~Huffman()
{
//    Huffman::freeMamory();
}

void Huffman::setData(const std::string & data)
{
    m_data = data;
}

void Huffman::computeWeigth()
{
    m_weigth.clear();
    for(std::size_t i = 0; i < m_data.length(); ++i)
        ++m_weigth[m_data[i]];
}

void Huffman::computeMap()
{
    tMapIterator itr;
    for(itr = m_weigth.begin(); itr != m_weigth.end(); itr++){
        Node * node = new Node(itr->first, itr->second);
        std::cout << *node << std::endl;
        m_queue.push(node);
    }
    Huffman::operationComputeMap();
}

void Huffman::operationComputeMap()
{
    m_sizeNode = m_queue.size();
    while(!m_queue.is_empty()){
        if(m_queue.size() == 1){
            Node * node = m_queue.top();
            m_root = node;
            m_queue.pop();
        }
        else{
            Node * nodeFirst = m_queue.top();
            m_queue.pop();
            Node * nodeSecond= m_queue.top();
            m_queue.pop();
            Node * nodeSumm = new Node(nodeFirst->weigth() + nodeSecond->weigth(), nodeFirst, nodeSecond);
            m_queue.push(nodeSumm);
            ++m_sizeNode;
        }
    }
}

void Huffman::computeTableSymbolCode()
{
    Node * ptr = m_root;
    Node * ptrPerent = nullptr;
    std::string code;
    while(Huffman::m_sizeNode != 0){
        if(ptr->left() != nullptr){
            ptrPerent = ptr;
            ptr = ptr->left();
            code += "0";
        }
        else if(ptr->rigth() != nullptr){
            ptrPerent = ptr;
            ptr = ptr->rigth();
            code += "1";
        }
        else if(ptr->is_value()){
            // Запись символа - кода в таблицу
            tPair pair;
            pair.first = ptr->value();
            pair.second = code;
            m_table.push_back(pair);
            code.clear(); // Отчистка кода буфера
            if(ptrPerent != nullptr && ptrPerent->left() == ptr)
                ptrPerent->setLeft(nullptr);
            else if(ptrPerent != nullptr)
                ptrPerent->setRigth(nullptr);
            delete ptr;
            --m_sizeNode;
            ptr = m_root;
            ptrPerent = nullptr;
        }
        else{                   // Удаляем пустую ячейку, у которой нет детей-значений
            code.clear();
            if(ptrPerent != nullptr && ptrPerent->left() == ptr)
                ptrPerent->setLeft(nullptr);
            else if(ptrPerent != nullptr)
                ptrPerent->setRigth(nullptr);
            delete ptr;
            --m_sizeNode;
            ptr = m_root;
            ptrPerent = nullptr;
        }

    }
    std::cout << ">> show table: " << std::endl;
    for(std::size_t i = 0; i < m_table.size(); ++i)
        std::cout << m_table[i].first << " : " << m_table[i].second << std::endl;
}

void Huffman::codingData()
{
    std::cout << ">> Condinf data: " << std::endl;
    std::cout << "In data: " << m_data << std::endl;
    std::size_t counter = 0;
    char symbolOut = 0;
    for(std::size_t i = 0; i < m_data.length(); ++i){
        char symbol = m_data[i];
        std::string code;
        // нахождение кода определенного символа
        for(std::size_t j = 0; j < m_table.size(); ++j){
            if(symbol == m_table[j].first)
               code = m_table[j].second;
        }
        // Преоброзование кода в символ и запись его в конечную строку
        for(std::size_t k = 0; k < code.length(); ++k){
            int codeInt = (code[k] == '0' ? 0 : 1);
            symbolOut = symbolOut | (codeInt << (7 - counter));
            ++counter;
            std::cout << "cCh = " << code[k] << std::endl;
            if(counter == 8){
                std::cout << "FLAG" << std::endl;
                std::string temp(" ");
                temp[0] = symbolOut;
                m_codeDate += temp;
                counter = 0;
                symbolOut = 0;
            }
            else if(i == m_data.length() - 1 && k == code.length() - 1){
                std::cout << "FLAG" << std::endl;
                std::string temp(" ");
                temp[0] = symbolOut;
                m_codeDate += temp;
                counter = 0;
                symbolOut = 0;
            }
        }
    }
    std::cout << ">> Result code data = " << m_codeDate << std::endl;
}

void Huffman::decondingData()
{
    std::cout << ">> Decoding data: " << std::endl;
    std::string data;
    char symbolOut;
    std::string code;
    std::size_t counter = 0;
    int i = 0;
    char byte = m_codeDate[i++];
    while(true){

        bool buff = byte & (1 << (7 - counter));
        code += (buff == 0 ? "0" : "1");
        std::cout << code << std::endl;
        for(std::size_t j = 0; j < m_table.size(); ++j){
            if(m_table[j].second == code){
                std::cout << "code = " << code << " ch = " << m_table[j].first << std::endl;
                char temp[2];
                temp[0] = m_table[j].first;
                temp[1] = '\0';
                data += temp;
                code.clear();
            }
        }
        ++counter;
        if(counter == 8){
            if(i == m_codeDate.length())
                break;
            counter = 0;
            byte = m_codeDate[i++];
        }
    }
    std::cout << "result data = " << data << std::endl;
}

void Huffman::algorithm()
{
    Huffman::computeWeigth();
    Huffman::computeMap();
    Huffman::computeTableSymbolCode();
    Huffman::codingData();
    Huffman::decondingData();
}
