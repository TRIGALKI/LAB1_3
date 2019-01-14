#include "ingrident.h"
#include "actioningrident.h"
#include "queue.h"
#include <cassert>
#include <iostream>
#include <string>
#include "vseotec.h"
using namespace std;

Queue::Iterator::Iterator():
    node(nullptr)
{
}

Queue::Iterator::Iterator(Iterator& existing):
    node(existing.node)
{
}

Queue::Iterator::Iterator(IngridentNode* existing):
    node(existing)
{
}
Queue::Iterator::~Iterator()
{
}
Vseotec* Queue::Iterator::operator*()
{
    return node->object;
}

Queue::Iterator& Queue::Iterator::operator++()
{
    node = node->next;
    return *this;
}
Queue::Iterator& Queue::Iterator::operator++(int)
{
    node = node->next;
    return *this;
}

bool Queue::Iterator::operator == (Iterator const &right) const
{
    return this->node == right.node;
}

bool Queue::Iterator::operator != (Iterator const &right) const
{
    return !(this->node == right.node);
}

Queue::Queue()://пустая очередь
    head(nullptr),
    tail(nullptr),
    _length(0)
    //size(5)
{

}

/*Queue::Queue(const Queue &existing)://копируем очередь
    head(nullptr),
    tail(nullptr)
    //size(existing.size)
{
    IngridentNode *newNode, *existingNode = existing.head;
    Vseotec* tempIngrident;
    _length = 0;
    if(existing._length)
    {
        if (tempIngrident->whichClass())
        {
        tempIngrident = new (Vseotec*)((existingNode->object));
        newNode = new IngridentNode;
        newNode->object = tempIngrident;
        existingNode = existingNode->next;
        _length++;
        head = newNode;
        tail = head;
        tail->next = nullptr;
        while(existingNode)
        {
            tempIngrident = new Vseotec(*(existingNode->object));
            tail = new IngridentNode;
            newNode->next = tail;
            tail->next = nullptr;
            tail->object = tempIngrident;
            existingNode = existingNode->next;
            newNode = tail;
            _length++;
        }
    }

}
*/
Queue::~Queue()
{
    while(head)
    {
        tail = head->next;
        delete head;
        head = tail;
    }

}


void Queue::addNode(Ingrident & existing)
{
    IngridentNode* curr = new IngridentNode;
    curr->object = new Ingrident(existing);
    curr->next = nullptr;
    if (_length == 0)
    {
        head = curr;
        tail = head;
    }
    else
    {
       tail->next = curr;
       tail = curr;
    }
    _length++;
}
void Queue::addNode(ActionIngrident & existing)
{
    IngridentNode* curr = new IngridentNode;
    curr->object = new ActionIngrident(existing);
    curr->next=nullptr;
    if (_length==0)
    {
        head = curr;
        tail = head;
    }
    else
    {
       tail->next = curr;
       tail = curr;
    }
    _length++;
}
Vseotec* Queue::deleteNode()
{
 Vseotec* curr;
 curr = (head->object);
 head = head->next;
 _length--;
 if(_length == 0)
 {
    tail=nullptr;
 }
 return curr;
}


void Queue::deleteQueue()
{
    while(head)
    {
        tail = head->next;
        delete head;
        head = tail;
    }
    head = tail = nullptr;
    _length = 0;
}

int Queue::getLength()
{
    return _length;
}

Queue::Iterator Queue::begin()
{
    Iterator temp(head);
    return temp;
}

Queue::Iterator Queue::end() const
{
    Iterator temp(tail);
    return temp;
}

IngridentNode* Queue::getHead() const
{
    return head;
}

IngridentNode* Queue::getTail() const
{
    return tail;
}

bool Queue::isEqual(Queue &existingList)
{
    Queue::Iterator firstIterator, secondIterator;
    if( this->getLength() != existingList.getLength())
    {
        //std::cerr << "Lengths of recepts does not match!" << std::endl;
        return false;
    }
    bool answer = true;
    for(firstIterator = this->begin(), secondIterator = existingList.begin();
        firstIterator != nullptr; firstIterator++, secondIterator++)
    {
        if ((*firstIterator)->whichClass() == (*secondIterator)->whichClass())
        {
        if((*firstIterator)->isUnequal(*(*secondIterator)))
        {
            answer = false;
        }
        }
        else
        {
            answer = false;
        }
    }
    return answer;
}
void Queue::writeInFile(std::string fileName)
{
    Queue::Iterator iterator;
    string name,value,type,action;
    int number,len;
    float dur;
    ofstream file(fileName, std::ios::out | std::ios::binary);
    len = this->getLength();
    file.write(reinterpret_cast<char*>(&len),sizeof(len));
    for(iterator = this->begin(); iterator != nullptr; iterator++)
    {
        if ((*iterator)->whichClass() == true)
        {
            const Ingrident *p = static_cast<const Ingrident*>(*iterator);
            type = "Ing";
            name = p->getName();
            value = p->getValue();
            number = p->getNumber();
            size_t sizeName = name.size()+1;
            size_t sizeValue = value.size()+1;
            size_t sizeType = type.size()+1;
            file.write(reinterpret_cast<char*>(&sizeType),sizeof(sizeType));
            file.write(type.c_str(),sizeType);
            file.write(reinterpret_cast<char*>(&sizeName),sizeof(sizeName));
            file.write(name.c_str(), sizeName);
            file.write(reinterpret_cast<char*>(&sizeValue),sizeof(sizeValue));
            file.write(value.c_str(), sizeValue);
            file.write(reinterpret_cast<char*>(&number), sizeof (number));
        }
        else
        {
             const ActionIngrident *a = static_cast<const ActionIngrident*>(*iterator);
            type = "Act";
            action = a->getAction();
            dur = a->getDur();
            size_t sizeAction = action.size()+1;
            size_t sizeType = type.size()+1;
            file.write(reinterpret_cast<char*>(&sizeType),sizeof(sizeType));
            file.write(type.c_str(),sizeType);
            file.write(reinterpret_cast<char*>(&sizeAction),sizeof(sizeAction));
            file.write(action.c_str(), sizeAction);
            file.write(reinterpret_cast<char*>(&dur), sizeof (dur));
        }
    }
    file.close();
}
void Queue::readFromFile(std::string fileName)
{
    string name,value,action,type;
    int number ,len,s;
    float dur;
    ifstream file(fileName,std::ios::out | std::ios::binary);
    size_t size1,size2,size0;
    s=0;
    file.read(reinterpret_cast<char*>(&len),sizeof(len));
    while (s!=len)
    {
        file.read(reinterpret_cast<char*>(&size0),sizeof(size0));
        char buff_0[size0];
        file.read(reinterpret_cast<char*>(&buff_0), size0);
        type = string(buff_0);
        if (type == "Ing")
        {
            file.read(reinterpret_cast<char*>(&size1),sizeof(size1));
            char buff[size1];
            file.read(reinterpret_cast<char*>(&buff), size1);
            file.read(reinterpret_cast<char*>(&size2),sizeof(size2));
            char buff1[size2];
            file.read(reinterpret_cast<char*>(&buff1), size2);
            file.read(reinterpret_cast<char*>(&number), sizeof (number));
            name = string(buff);
            value = string(buff1);
            Ingrident NewIngrident(name,value,number);
            this->addNode(NewIngrident);
            s++;
        }
        else
        {
            file.read(reinterpret_cast<char*>(&size1),sizeof(size1));
            char buff[size1];
            file.read(reinterpret_cast<char*>(&buff), size1);
            file.read(reinterpret_cast<char*>(&dur), sizeof (dur));
            action = string(buff);
            ActionIngrident NewActionIngrident(action,dur);
            this->addNode(NewActionIngrident);
            s++;
        }
    }
    file.close();
}


