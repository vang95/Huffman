#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <map>
#include <vector>
#include <string>
#include "priorityqueue.h"
#include "node.h"

typedef std::pair<char, std::string>    tPair;
typedef std::map<char, int>             tMap;
typedef std::map<char, int>::iterator   tMapIterator;
typedef std::vector<tPair>              tTable;
typedef PriorityQueue<huffman::Node *>  tPQueue;
typedef std::string                     tData;

using huffman::Node;

class Huffman
{
public:
    Huffman();                              // По умолчанию
    Huffman(const std::string & data);      // Установка строки для кодирования
    ~Huffman();                             // Будет отчищать за собой карту, используемую для вычисления кодов символов
public:
    void algorithm();                       // Совокупность методов, реализующий общий алгоритм.
    void setData(const std::string & data); // Установка строки для кодирования.
    void computeWeigth();                   // Вычисление весов символов в строке.
    void computeMap();                      // Создание карты для последующего построения таблицы кодов символов.
    void computeTableSymbolCode();          // Операция построения таблицы символ-кодов.
    void codingData();                      // Операция кодирования исходной строки в закодированную строку.
    void decondingData();                   // Операция декодирования закодированной строки.
private:
    void operationComputeMap();            // Операция построения дерева в методе comuterMap().
private:
    void freeMamory();                      // Отчистка памяти карты кодов символов.
private:                    // Данные, связанные с выявлением кодов символов
    tData       m_data;     // Данные строки, которая будет закодирована.
    tData        m_codeDate; // Закодированная информация в виде строки
    tMap        m_weigth;   // Карта весов.
    tPQueue     m_queue;    // Очередь с приоритетами, из которой ьудут браться два первый символов.
    tTable      m_table;    // Таблица весов - символов.
private:
    std::size_t m_sizeNode; // Количество ячеек в карте, которая характеризует коды символов.
    Node *      m_root;     // Голова карты, будет nullptr, пока в очередь не станет пуста.
    Node *      m_root_nil; // Псевдоголова карты
};

#endif // HUFFMAN_H
