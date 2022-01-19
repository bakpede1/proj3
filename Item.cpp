#include "Item.h"

// Name: Item (default constructor)
// Desc: Sets default values of a new Item (an item is a node in a linked list)
Item::Item(){
    m_name = "";
    m_time = 0;
    m_next = nullptr;
}

// Name: Item (overloaded constructor)
// Desc: Sets values of a new Item (an item is a node in a linked list)
Item::Item(string name, int time){
    SetName(name);
    SetTime(time);
    m_next = nullptr;
}

// Name: GetName
// Desc: Returns the name of the item
string Item::GetName(){
    return m_name;
}

// Name: GetTime
// Desc: Returns the time of the item
int Item::GetTime(){
    return m_time;
}

// Name: GetNext
// Desc: Returns the pointer to the next item
Item* Item::GetNext(){
    return m_next;
}

// Name: SetName
// Desc: Sets the name of the item
void Item::SetName(string name){
    m_name = name;
}
// Name: SetTime
// Desc: Sets the time of the item
void Item::SetTime(int time){
    m_time = time;
}

// Name: SetNext
// Desc: Sets the next item
void Item::SetNext(Item* newItem){
    m_next = newItem;
}
