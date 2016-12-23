/********************************************************************************
Program-name: Josephus problem
This program simulates and solves the Josephus problem. Josephus Flavius was 
a famous historian of the first century at the time of the Second Temple 
destruction. During the war he got trapped in a cave with a group of 39 soldiers 
surrounded by Romans.  The legend has it that preferring suicide to capture, the 
people decided to form a circle and, proceeding clockwise around it, to kill every 
seventh (this number is input in my program) person until only one was left, who 
must then commit suicide.  Josephus, an accomplished mathematician, quickly found 
the safe spot in the circle (24th) to be the last to go.  But when the time came, 
instead of killing himself he joined the Roman side.  The problem rightfully 
raises the question of how someone might be able to quickly compute the correct 
place to stand.
In the beginning, you will be asked to enter the number of soldiers playing the 
Josephus game. Then, you will be asked to enter the soldiers’ name. Next, you will 
be asked which soldier is to be killed. Finally, the soldiers will be killed one 
by one until only a single alive soldier remains.

A QUEUE DATA STRUCTURE IS USED TO MAKE THE PROGRAM 
*********************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

/********************QueueNode Struct and Queue Class**************************/
struct QueueNode{
    string soldier_name;
    QueueNode *next;
};

typedef QueueNode* QueueNodePtr;

class Queue{
public:
    Queue();
    void add(string soldier_name);
    string remove();
    bool is_empty();
    QueueNodePtr get_front_ptr();
    QueueNodePtr get_back_ptr();
    void set_front_ptr(QueueNodePtr front_ptr);
    void set_back_ptr(QueueNodePtr back_ptr);
private:
    QueueNodePtr front;
    QueueNodePtr back;
};

Queue::Queue(){
    front = NULL;
    back = NULL;
}

void Queue::add(string soldier_name){
    QueueNodePtr temp_ptr = new QueueNode;
    temp_ptr->soldier_name = soldier_name;
    temp_ptr->next = NULL;
    
    if(is_empty()){
        front = temp_ptr;
        back = front;
    } else {
        back->next = temp_ptr;
        back = temp_ptr;
    }
}

string Queue::remove(){
    if(is_empty()){
        cout << "Error. Removing an item from an empty queue.\n";
        exit(1);
    }
    string soldier_name = front->soldier_name;
    QueueNodePtr discard = front;
    front = front->next;
    if(front == NULL){ //The only remaining node was removed
        back = NULL;
    }
    
    delete discard;
    
    return soldier_name;
}

bool Queue::is_empty(){
    if(front == NULL){
        return true;
    } else {
        return false;
    }
}

QueueNodePtr Queue::get_front_ptr(){
    return front;
}

QueueNodePtr Queue::get_back_ptr(){
    return back;
}

void Queue::set_front_ptr(QueueNodePtr front_ptr){
    front = front_ptr;
}

void Queue::set_back_ptr(QueueNodePtr back_ptr){
    back = back_ptr;
}
/******************************************************************************/

typedef string* StringPtr;
int ask_user_for_soldiers();
void ask_user_for_soldiers_names(StringPtr soldiers_names, int soldiers);
Queue put_in_queue(StringPtr soldiers_names, int soldiers);
void play_game(Queue a_queue, int soldiers);

int main(){
    int soldiers = ask_user_for_soldiers();
    StringPtr soldiers_names = new string[soldiers]; //Made 1D array
    ask_user_for_soldiers_names(soldiers_names, soldiers); //Kept all soldiers name in 1D array
    Queue a_queue = put_in_queue(soldiers_names, soldiers); 
    play_game(a_queue, soldiers);
    
    return 0;
}

int ask_user_for_soldiers(){
    while(true) {
        int soldiers;
        cout << "How many soldiers playing?: ";
        cin >> soldiers;
        if(soldiers > 0){
            cin.ignore(10000, '\n');
            return soldiers;
        } 
    }
}

void ask_user_for_soldiers_names(StringPtr soldiers_names, int soldiers){
    cout << "Type " << soldiers << " soldiers names: ";
    for(int i = 0; i < soldiers; i++){
        string soldier_name, i_to_string;
        stringstream ss;
        ss << i + 1;
        i_to_string = ss.str();
        cin >> soldier_name;
        soldier_name = soldier_name + " (" + i_to_string + ")";
        soldiers_names[i] = soldier_name;
    }
}

Queue put_in_queue(StringPtr soldiers_names, int soldiers){
    Queue a_queue;
    for(int i = 0; i < soldiers; i++){
        a_queue.add(soldiers_names[i]);
    }
    return a_queue;
}

void play_game(Queue a_queue, int soldiers){
    int kill_soldier_number, dead_soldiers = 0;
    cout << "Which soldier to kill? Every ";
    cin >> kill_soldier_number;
    
    cout << "\nEliminating order: " << endl;
    bool keep_going = true;
    while(keep_going){
        for(int i = 1; i < kill_soldier_number; i++){
            QueueNodePtr front_ptr = a_queue.get_front_ptr();
            QueueNodePtr back_ptr = a_queue.get_back_ptr();
            back_ptr->next = front_ptr;
            a_queue.set_front_ptr(front_ptr->next);
            front_ptr->next = NULL;
            a_queue.set_back_ptr(back_ptr->next);
        }
        
        string soldier_name = a_queue.remove();
        dead_soldiers++;
        cout << dead_soldiers << ". ";
        cout << soldier_name << endl;

        if (dead_soldiers == (soldiers - 1))
            keep_going = false;
    }
    
    QueueNodePtr front_ptr = a_queue.get_front_ptr();
    cout << "\nThe survivor is " << front_ptr->soldier_name;
}