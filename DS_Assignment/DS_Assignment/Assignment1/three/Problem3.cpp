#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* next;
    Node(int value);
};

class SortedLinkedList
{
private:
    Node* head;
public:
    SortedLinkedList();

    void insert(int value);
    void remove(int index);
    //ovarloaded
    friend ostream& operator<<(ostream& os,const SortedLinkedList& list);
    int operator[](int index);

    ~SortedLinkedList();
};


Node::Node(int value) {
    data = value;
    next = nullptr;
}


SortedLinkedList::SortedLinkedList()
{
    head = nullptr; 
}

void SortedLinkedList::insert(int value) {
    Node* newNode = new Node(value);
    
    if (head == nullptr || value < head->data) { // Insert at the beginning
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* ptr = head;
    while (ptr->next != nullptr && ptr->next->data < value) {
        ptr = ptr->next;
    }

    newNode->next = ptr->next;
    ptr->next = newNode;
}

void SortedLinkedList::remove(int index)
{
    
    if (index == 0) { // Remove the first node
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* ptr = head;
    Node* prev = nullptr;

    for (int i = 0; i < index; i++) {
        prev = ptr;
        ptr = ptr->next;
        if (ptr == nullptr) { 
            return;
        }
    }

    prev->next= ptr->next; 
    delete ptr; 

}

ostream& operator<<(ostream& os, const SortedLinkedList& list) {
    Node* ptr = list.head;
    while (ptr != nullptr) {
        os << ptr->data << " -> ";
        ptr = ptr->next;
    }
    os << "NULL";
    return os;
}

int SortedLinkedList::operator[](int index)
{
    Node *ptr=head;
    for(int i=0;i<index;i++)
    {
        if(ptr==nullptr){
            throw out_of_range("Index out of range");
        }

        ptr = ptr->next;
    }
    
    return ptr->data;
}

SortedLinkedList::~SortedLinkedList() {
    Node* ptr = head;
    while (ptr != nullptr) {
        Node* temp = ptr;
        ptr = ptr->next;
        delete temp;
    }
}



int main(){
    SortedLinkedList L;
    L.insert(5); 
    L.insert(8);
    L.insert(7);
    L.insert(6); 
    L.insert(6); 
    cout << L<<endl; // Output: [5, 6, 6, 7, 8]

    L.remove(0); 
    cout << L<<endl; // Output: [6, 6, 7, 8]

    L.remove(100); // No change 
    cout << L<<endl; // Output: [6, 6, 7, 8]

    L.remove(2); 
    cout << L<<endl; // Output: [6, 6, 8]

    L.remove(2); 
    cout << L; // Output: [6, 6]    
}