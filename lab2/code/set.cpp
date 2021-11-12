#include "set.h"
#include "node.h"

int Set::Node::count_nodes = 0;  // initialize total number of existing nodes to zero

/*****************************************************
 * Implementation of the member functions             *
 ******************************************************/

// Used for debug purposes
// Return number of existing nodes  -- static member function
int Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

// Default constructor
Set::Set() : counter{0} { //Assignments, O(1)
    // IMPLEMENTED before Lab1 HA
    //Create two dummy nodes, one head and one tail
    head = new Node();
    tail = new Node();
    
    head->next = tail;
    tail->prev = head;
}

// Conversion constructor
Set::Set(int n) //Insert at tail, O(1)
: Set{}  // create an empty list
{
    // IMPLEMENTED before Lab1 HA
    //Takes in an integer n and creates a set with ONE node with the value of n,
    //    counter = 1;
    
    _insert(tail, n);
    
}

// Constructor to create a Set from a sorted vector v
Set::Set(const std::vector<int>& v) //O(n)
: Set{}  // create an empty list
{
    // IMPLEMENTED before Lab1 HA
    //Goes trough the vector and stores all it's values in a set
    //    counter = v.size();
    
    for (long unsigned i = 0; i < v.size(); i++) { //Loop with i<v.size() and i++, O(n)
        _insert(tail, v[i]); //Insert at tail, O(1)
    }
    
}

// Make the set empty
void Set::make_empty() { //O(n)
    // IMPLEMENT before Lab1 HA
    //Goes trough the set with a temp-pointer and delete each node until the head-next points to the tail
    //    counter = 0;
    
    Node* temp = head->next;
    
    while (temp != tail) { //Go trough the set O(n)
        Node* p = temp;
        temp = temp->next;
        _remove(p); //delete the first node in set, O(1)
    }
    
    //Point to eachother as the default empty set
    head->next = tail;
    tail->prev = head;
}

Set::~Set() {//O(n)
    // Member function make_empty() can be used to implement the destructor
    // IMPLEMENTED before Lab1 HA
    make_empty(); //O(n)
    _remove(head); //O(1)
    _remove(tail); //O(n)
}

// Copy constructor
Set::Set(const Set& source)//O(n)
: Set{}  // create an empty list
{
    // IMPLEMENTED before Lab1 HA
    //Create a pointer that goes trough source
    //    counter = source.counter;
    Node* p = source.head->next;
    
    while (p != source.tail) { //O(n), As long as set source has values, then insert each value from source with a pointer into a new set
        _insert(tail, p->value); //insert last, O(1)
        p = p->next;
    }
}

// Copy-and-swap assignment operator
Set& Set::operator=(Set source) { //O(n)
    // IMPLEMENTED before Lab1 HA
    counter = source.counter; //Copy constructor, O(n)
    
    std::swap(head, source.head); //O(1) acoording to cpluspluc.com
    std::swap(tail, source.tail); //O(1) acoording to cpluspluc.com
    
    return *this;
}

// Test set membership
bool Set::is_member(int val) const { //O(n)
    // IMPLEMENTED before Lab1 HA
    
    Node* p = head->next;
    
    while ((p != nullptr) && (p->value != val))  //O(n), As long as p is not a nullptr and does not have the same value as val, check the next one
    {
        p = p->next;
    }
    
    if (p == nullptr) { //If p is nullptr (is this neccessary?) //O(1)
        return false;
    }
    
    else { //Else is member
        return true;
    }
    
    return false;  // remove this line
}

// Test whether a set is empty
bool Set::is_empty() const {
    return (counter == 0);
}


// Return number of elements in the set
size_t Set::cardinality() const {
    return counter;
}


// Modify *this such that it becomes the union of *this with Set S
// Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S) { //O(n1+n2)
    // IMPLEMENT
    //Create a pointer that goes trough source
    Node* p1 = S.head->next;
    Node* p2 = head->next;
    
    while (p1 != S.tail && p2 != tail) { //O(n1+n2) // As long as set S has values
        if (p1->value < p2->value) { //if S's value is smaller then of *this, insert in *this and go on in S
            _insert(p2, p1->value); //O(1)
            p1 = p1->next;
            
        }
        else if (p1->value > p2->value) { //if S's value is bigger than *this go on in *this
            p2 = p2->next;
        }
        
        else { //if p1->value and p1->value is ==
            p1 = p1->next;
            p2 = p2->next;
            
        }
        
    }
    
    while (p1->next != nullptr) { //O(n1) add the rest of S's values into the end at *this
        _insert(p2, p1->value); //O(1)
        p1 = p1->next;
        p2 = p2->next;
    }
    
    return *this;
}

// Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S) { //O(n1+n2)
    // IMPLEMENT
    //Create a pointer that goes trough S
    Node* p1 = S.head->next;
    Node* p2 = head->next;
    
    while (p1 != S.tail && p2 != tail) { //O(n1+n2) As long as set S and *this has values
        if (p1->value > p2->value) { //if S's value is bigger than *this
            p2 = p2->next;
            
        }
        else if (p1->value < p2->value) { //if S's value is smaller than *this value, value does not exist in *this, (sorted)
            p1 = p1->next;
        }
        
        else { //If they are equal remove it from *this
            p1 = p1->next;
            p2 = p2->next;
            _remove(p2->prev);
        }
    }
    
    return *this;
}

// Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S) {//O(n1+n2)
    
    Node* p1 = S.head->next;
    Node* p2 = head->next;
    
    while (p1 != S.tail && p2 != tail) { //O(n1+n2) As long as set S and *this has values
        
        if (p1->value > p2->value) { //if S's value is bigger than *this value, remove the value from *this
            p2 = p2->next;
            _remove(p2->prev);
        }
        
        else if (p1->value < p2->value) { //if S's value is smaller than *this value, value does not exist in *this, (sorted)
            p1 = p1->next;
        }
        
        else { // if the values are ==
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    
    while (p2->next != nullptr) { //O(n2) remove the rest in *this
        p2 = p2->next;
        _remove(p2->prev);
    }
    
    return *this;
    
}

// Overloaded stream insertion operator<<
std::ostream& operator<<(std::ostream& os, const Set& b) {
    if (b.is_empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* temp{b.head->next};
        
        os << "{ ";
        while (temp != b.tail) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
    return os;
}

/* ******************************************** *
 * Private Member Functions -- Implementation   *
 * ******************************************** */

//helper function to the friend operator function <=
bool Set::subSet(const Set& S2) const { //O(n)
    
    Node* p1 = S2.head->next; //pointer to S2s head->next
    Node* p2 = head->next; //pointer to "this" head->next
    
    if (S2.counter < counter) //If the wanted subset (S1) has more nodes than S2, return false
    {
        return false;
    }
    
    while (p2 != tail && p1 != S2.tail) //As long as both sets has nodes to go trough
    {
        if (p2->value < p1->value) //If *this value is smaller than S2, return false (Sorted order)
        {
            return false;
        }
        else if (p2->value > p1->value) //If *this value are bigger than S2, continue to the next node in S2
        {
            p1 = p1->next;
        }
        else //Continue in both sets
        {
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    
    return true;
    
}

// Insert a new Node storing val after the Node pointed by p
void Set::_insert(Node* p, int val) { //O(1)
    // IMPLEMENTED
    Node* newNode = new Node(val, p, p->prev); // Create new node with the value val, the pointer to right and the pointer to left
    p->prev = p->prev->next = newNode; //re-point the next nodes prev pointer and the previous nodes next pointer to the new node
    counter++;
    
}


// Remove the Node pointed by p
void Set::_remove(Node* p) { //O(1)
    // IMPLEMENTED
    if (p->next) //if p has a next, repoint p->next->prev to the one node before p (removing from the beginning)
        p->next->prev = p->prev;
    
    if(p->prev) //if p has a prev, repoint p->prev->next to the one node after p (removing from the end)
        p->prev->next = p->next;
    
    delete p;
    counter--;
}


