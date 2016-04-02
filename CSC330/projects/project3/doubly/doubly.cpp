#include "doubly.h"

/*Progress Report- Change edit the insert and delete funtion to 
 * be an unsorted version. 
 * (Check)Create a copy constructor and a destructor.
 * Refer to the Project 3 sheet for checklist details... */ 

//Error with overload function header
template<class x>
ostream& operator<<<x>(ostream& osObject, const doubly<x>& nodez)
{
  osObject << nodez->info; 
}

//Error with overload function header
template<class x>
istream& operator>><x>(istream isObject, const doubly<x>& nodez)
{
  x stuff; 
  isObject >> stuff; 
  nodez.insert(stuff); 
}

//constructor 
template <class x>
doubly<x>::doubly()
{
  first = NULL; 
  last = NULL;
  length = 0;
}

template <class x>
doubly<x>::doubly(const doubly<x>& other)
{
  Dnode<x> *newNode; 
  Dnode<x> *otherPoint; 
  
  if (first != NULL) //if list is not empty, clear it
    clear(); 
    
  if (other.first == NULL) //if other list is empty 
   {
     first = NULL; 
     last = NULL; 
     length = 0; 
   }
   else 
   {
     otherPoint = other.first; //set other pointer 
     length = other.length; // set length

     first = new Dnode<x>; //create new node
     first->info = otherPoint->info; //copy info 
     first->bck = NULL; 
     first->nxt = NULL; 
     last = first;  
     otherPoint = otherPoint->nxt; //set pointer to next node(maybe)  

     while (otherPoint != NULL)
     {
       newNode = new Dnode<x>; //create new node
       newNode->info = otherPoint->info; //copy info 
       newNode->nxt = NULL; //set new node next null 
       last->nxt = newNode;//point last next to newnode 
       newNode->bck = last; //pont new node back to last node 
       last = newNode; //make newnode the last 
       otherPoint = otherPoint->link; //point to next node(maybe)
     }
   }
}

template <class x>
doubly<x>::~doubly()
{
  Dnode<x> *temp;

  while (first != NULL)
  {
    temp = first; 
    first = first->nxt;
    first->bck = NULL; 
    delete temp; 
  }

  last = NULL;
  length = 0; 
}

template <class x>
bool doubly<x>::isEmpty() const
{
  return (first == NULL); 
}

template <class x>
void doubly<x>::clear()
{
  Dnode<x> *temp; //destructo pointer

  while(first != NULL)
  {
    temp = first;
    first = first -> nxt;
    delete temp; 
  }

  last = NULL; 
  length = 0; 
}

template <class x>
void doubly<x>::initialize()
{
  clear(); 
}


template <class x>
int doubly<x>::getLength() const
{
  return length;
}

template <class x>
void doubly<x>::print() const
{
  Dnode<x> *current; //traverse pointer 

  current = first;

  while (current != NULL)
  {
    cout << current->info << " "; 
    current = current->nxt;
  }
}

template <class x>
void doubly<x>::reversePrint() const
{
  Dnode<x> *current; 

  current = last; 

  while (current != NULL)
  {
    cout << current->info << " "; 
    current = current->back; 
  }
}

/*template <class x>
bool doubly<x>::search(const x& item) const//delete this const and see what happens
{
  bool found = false; 
  Dnode<x> *current; 

  current = first;

  while (current != NULL && !found)
    if (current->info >= item)
      found = true; 
    else 
      current = current->nxt; 

    if (found)
      found = (current->info == item); 

    return; 
}*/


template <class x>
x doubly<x>::getFirst() const 
{
  assert(first != NULL); 

  return first->info; 
}

template <class x>
x doubly<x>::getLast() const
{
  assert(last != NULL);

  return last->info; 
}

//This function will have to be edited so that it does not insert nodes PRE SORTED
template <class x>
void doubly<x>::insert(const x& item)
{
  Dnode<x> *current; //traverse pointer
  Dnode<x> *shadow; //pointer before current
  Dnode<x> *newNode; //node creator 
  bool found; 

  newNode = new Dnode<x>;
  newNode->nxt = NULL; 
  newNode->bck = NULL;  
  newNode->info = item; 

  if (first == NULL) //if there is an empty list 
  {
    first = newNode; 
    last = newNode;
    length++; 
  }
  else
  {
    found = false; 
    current = first;

    while (current != NULL && !found)//while not empty ^ item not found 
      if (current->info >= item)
        found = true; 
      else
      {
        shadow = current; 
        current = current->nxt; 
      }

      if (current == first) //for new node before first
      {
        first->bck = newNode; 
        newNode->nxt = first; 
        first = newNode; 
        length++; 
      }
      else 
      {
        if (current != NULL) //insert in between
        {
          shadow->nxt = newNode; 
          newNode->bck = shadow; 
          newNode->nxt = current; 
          current->bck = newNode; 
        }
        else //add node to the end 
        {
          shadow->nxt = newNode; 
          newNode->bck = shadow;
          last = newNode;
        }

        length++; 
      }
  }
}

//revise this function to not operate on a PRE SORTED list
template <class x>
void doubly<x>::deleteNode(const x& item)
{
  Dnode<x> *current; //traverse pointer 
  Dnode<x> *shadow; 
  bool found; 

  if (first == NULL)
    cout << "Cannot delete from an empty list." << endl; 
  else if (first->info == item) //delete first node
  {
    current = first; 
    first = first->nxt; 

    if (first != NULL)
      first->bck = NULL; 
    else 
      last = NULL; 

      length--; 

      delete current; 
  }
  else 
  {
    found = false;
    current = first;

    while (current != NULL && !found)
      if (current->info >= item)
        found = true;
      else 
        current = current->nxt; 

    if (current == NULL)
      cout << "The item you want deleted does not exist." << endl;
    else if (current->info == item) //equality checkpoint
    {
      shadow = current->bck; 
      shadow->nxt = current->nxt; 

      if (current->nxt != NULL)
        current->nxt->bck = shadow; 

      if (current == last)
        last = shadow;

      length--; 
      delete current;
    }
    else 
      cout << "The item to be deleted is not in list." << endl;
  }
}

int main(){ return 0;}
