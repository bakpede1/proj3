#include "Manager.h"

// Name: Manager (constructor)
// Desc: Creates a Manager to manage schedules
Manager::Manager(string fileName){
    m_fileName = fileName;
    MainMenu();
}

// Name:  Manager (destructor)
// Desc: Deallocates all dynamic aspects of a Manager
Manager::~Manager(){
    cout << "Schedules removed from memory" << endl;
    cout << "Deleting Schedules" << endl;
    for (unsigned int i = 0; i < m_schedules.size(); i++) {
        // deallocate dynamic memory for each schedule
        delete m_schedules[i];
        m_schedules[i] = nullptr; // cleanup
    }
}

// Name:  DisplaySchedules
// Desc: Displays each schedule in m_schedules
void Manager::DisplaySchedules(){
    // loops through m_schedules to output each schedule's data
    for (unsigned int i = 0; i < m_schedules.size(); i++) {
        cout << "Schedule for " << m_schedules[i]->GetName() << endl;
        cout << m_schedules[i]->GetSize() << " activities scheduled" << endl;
        cout << *m_schedules[i];
    }
}

// Name:  ReadFile
// Desc: Reads in a file that has the schedule name then semicolon the starting time then a semicolon
//       then the name of the activity.
//       Input files are an indeterminate length. There are an indeterminate number of schedules in
//       an input file. There are an indeterminate number of items in each file.
//       The vector can hold many schedules.
void Manager::ReadFile() {
    string name;
    string time;
    string task;
    int itemCount = 0;

    ifstream inputStream(m_fileName);

    // loops till end of file is reached
    while(getline(inputStream,name, ';'),
            getline(inputStream,time, ';'),
            getline(inputStream, task, '\n')){

        Item *newItem;
        int index;
        newItem = new Item(task, stoi(time));

        index = FindSchedule(name);

        // adds a new item to a schedule
        // if it already exists
        if(index != -1){
            m_schedules[index]->InsertSorted(newItem);
            itemCount++;
        }

        // adds a new schedule to m_schedules
        // (with one item in it)
        else{
            Schedule *newS;
            newS = new Schedule(name);
            newS->InsertSorted(newItem);
            m_schedules.push_back(newS);
            itemCount++;
            newS = nullptr; // cleanup
        }

        newItem = nullptr; // cleanup
    }


    cout << "Opened File" << endl;
    cout << itemCount
    << " nodes loaded across "
    << int(m_schedules.size()) << " schedules." << endl;

    inputStream.close();

}


// Name: InsertNewItem
// Desc: Asks the user which schedule they would like to insert into (uses FindSchedule)
//       If new schedule, inserts a new schedule and indicates a new schedule was created
//       Prompts user for time and name of item then inserts item into schedule
void Manager::InsertNewItem(){
    string name;
    string time;
    string activity;
    Schedule *newS;
    Item *newItem;

    cout << "What is the name of the schedule you would like to insert into? ";
    getline(cin, name);

    cout << "What is the start time of the activity? ";
    getline(cin,time);

    cout << "What is the name of the activity? ";
    getline(cin, activity);

    int index = FindSchedule(name);
    newItem = new Item(activity, stoi(time));

    // adds a new item to an existing schedule
    if(index != -1){
        m_schedules[index]->InsertSorted(newItem);
    } else {
        // adds a new schedule to m_schedules
        // (with one item in it)
        newS = new Schedule(name);
        newS->InsertSorted(newItem);
        m_schedules.push_back(newS);
        newS = nullptr;
    }
    newItem = nullptr;
}

// Name: FindSchedule
// Desc: Returns the index of the schedule from m_schedules else -1
int Manager::FindSchedule(string schedName){
    // loops through schedules until a schedule is found
    // with a name equivalent to schedName
    for (unsigned int i = 0; i < m_schedules.size(); i++) {
        if(m_schedules[i]->GetName() == schedName){
            return i;
        }
    }
    // if name is not found
    return -1;
}

// Name:  MainMenu
// Desc: Displays the main menu and manages exiting
void Manager::MainMenu(){
    int selection = 0;
    ReadFile();

    // loops until user selection is 4
    while(selection != 4){
        cout << "What would you like to do?:" << endl;
        cout << "1. Display Schedules" << endl;
        cout << "2. Reverse Schedules" << endl;
        cout << "3. Insert New Item" << endl;
        cout << "4. Exit" << endl;

        cin >> selection;

        // validates user selection
        while(selection < 1 || selection > 4){
            cin >> selection;
        }

        // cleans up remaining newline char
        if (cin.peek() == '\n'){
            cin.ignore(256, '\n');
        }

        // runs functions based on user selection
        if(selection == 1){
            DisplaySchedules();

        } else if(selection == 2){
            ReverseSchedule();

        } else if(selection == 3){
            InsertNewItem();
        }

    }
}

// Name: ReverseSchedule
// Desc: User chooses a schedule and the schedule is reversed
//       If only one schedule in m_schedules, automatically reverses it without prompting the user
void Manager::ReverseSchedule(){
    int schRevChoice;

    // reverses the first schedule
    // (when size of m_schedules is 1)
    if (int(m_schedules.size()) == 1) {
        m_schedules[0]->ReverseSchedule();
        cout << "Done reversing Schedule 1" << endl;

    } else{
        cout << "Which schedule to reverse?" << endl;
        cout << "Choose 1 - " << int(m_schedules.size()) << endl;
        cin >> schRevChoice;

        // validates user choice
        while(schRevChoice < 1 || schRevChoice > int(m_schedules.size())) {
            cout << "Choose 1 - " << int(m_schedules.size()) << endl;
            cin >> schRevChoice;
        }

        // loop until choice is found
        for (unsigned int i = 0; i < m_schedules.size(); i++){
            int num = int(i) + 1;
            if(num == schRevChoice ){
                m_schedules[i]->ReverseSchedule();
            }
        }
        cout << "Done reversing Schedule " << schRevChoice << endl;

    }
}