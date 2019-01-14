#ifndef QUEUE_H
#define QUEUE_H
#include "ingrident.h"
#include "actioningrident.h"
#include <cassert>
#include <fstream>
#include "vseotec.h"
using namespace std;
struct IngridentNode{
    Vseotec* object;
    IngridentNode *next;
};
class Queue
{
private:
   // Ingrident *queuePtr;
    //const int size;  // максимальное количество элементов в очереди
     IngridentNode *head,       // начало очереди
        *tail;         // конец очереди
    int _length;      // счетчик элементов
public:
    class Iterator
    {
    public:
        friend Queue;
        Iterator();
        Iterator(Iterator&);
        Iterator(IngridentNode*);
        ~Iterator();
        Iterator& operator ++();
        Iterator& operator++(int);
        bool operator == (Iterator const &) const;
        bool operator != (Iterator const &) const;
        Vseotec* operator *();
    private:
        IngridentNode *node;
    };
    friend Iterator;
    Queue();          // конструктор по умолчанию
    /*Queue(const Queue &);*/ // конструктор копирования
    ~Queue();// деструктор
    void addNode(Ingrident& existing);
    void addNode(ActionIngrident& existing);// добавить элемент в очередь
    Vseotec* deleteNode();
    IngridentNode* getHead() const;
    IngridentNode* getTail() const;
    void deleteQueue();
    Iterator begin();
    Iterator end() const;
    int getLength();
    bool isEqual(Queue &existingList);
    void writeInFile(std::string fileName);
    void readFromFile(std::string fileName);
};

#endif  //QUEUE_H
