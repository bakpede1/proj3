#include "Schedule.h"

// Name: Schedule() - Default Constructor
// Desc: Used to build a new Schedule
Schedule::Schedule(){
    m_name = "Default";
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

// Name: Schedule(string) - Overloaded Constructor
// Desc: Used to build a new Schedule with the schedule name passed
Schedule::Schedule(string name){
    m_name = name;
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}
// Name: ~Schedule() - Destructor
// Desc: Used to destruct a strand of Schedule
Schedule::~Schedule(){
    Item *curr = m_head;

    // traverses LL to delete every node
    while(curr != nullptr) {
        m_head = curr;
        curr = curr->GetNext();
        delete m_head;
    }

    // resets all of the static linked list pointers
    m_head = nullptr; // sets the pointer to point at nothing
    m_tail = nullptr; // sets the pointer to point at nothing
    m_size = 0; // sets the size of the linked list to 0

}

// Name: InsertSorted
// Desc: Inserts a new item into the schedule. Inserts it from earliest time (0) to highest time (2359) ascending
//       Does NOT insert at correct location when reversed
void Schedule::InsertSorted(Item* newItem){
    // creation of curr node
    Item *curr = m_head;

    // sets newItem m_next to nullptr
    newItem->SetNext(nullptr);

    // makes newItem equal to m_head
    // if it's the first item in a schedule
    if(m_head == nullptr){
        m_head = newItem;
        m_head->SetNext(nullptr);
        m_tail = newItem;

        // inserts the newItem in the front of the LL
        // if m_head's time is greater than newItem's time
    }else if(m_head->GetTime() >= newItem->GetTime()){
        newItem->SetNext(m_head);
        m_head = newItem;

    }else{
        // traverses LL till it reaches the point in the LL
        // that's right before insert location
        while(curr->GetNext()!= nullptr
        && curr->GetNext()->GetTime() < newItem->GetTime()){
            curr = curr->GetNext();
        }
        // sets newItem's next to curr node's next
        // and curr node's next to newItem
        newItem->SetNext(curr->GetNext());
        curr->SetNext(newItem);
    }

    m_size++;
}

// Name: GetName()
string Schedule::GetName(){
    return m_name;
}

// Name: GetSize()
int Schedule::GetSize(){
    return m_size;
}

// Name: ReverseSchedule
void Schedule::ReverseSchedule(){
    // if there is no LL (or size is 1),
    // no need to reverse
    if(m_head == nullptr || m_size == 1){
        return;
    }

    // creation of curr, prev, and next nodes
    Item *curr = m_head;
    Item *prev = nullptr;
    Item *next = nullptr;

    // reverses LL till end node is reached
    while(curr != nullptr){
        next = curr->GetNext();
        curr->SetNext(prev);
        prev = curr;
        curr = next;
    }
    m_head = prev;
}

// Name: GetData
// Desc: Returns the time at a specific location in the Schedule
Item* Schedule::GetData(int nodeNum) {
    // creation of curr node to traverse LL
    Item *curr = m_head;
    int n = 0;

    // loops till nodeNum is reached
    while(curr != nullptr && n < nodeNum){
        curr = curr->GetNext();
        n++;
    }

    // returns item
    if(curr){
        return curr;
    }

    return nullptr;
}

// Name: operator<<
// Desc: Allows you to cout a Schedule object
ostream &operator<< (ostream &output, Schedule &mySchedule){
    // creation of curr node to traverse LL
    Item *curr = mySchedule.m_head;

    // returns a message if the schedule is empty
    if(curr == nullptr){
        output << "The schedule is empty" << endl;
        return output;

    }else{
        // loops till end of LL
        while(curr != nullptr){
            output << *curr << endl;
            curr = curr->GetNext();
        }
    }
    return output;
}
