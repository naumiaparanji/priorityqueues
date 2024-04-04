#include <string>
#include <iostream>
using namespace std;
class Linkedlist{
private:
struct node{
int priority;
string instruction;
node *next;
node() : priority(-1), instruction(""), next(nullptr){}
node(int x, string s) : priority(x), instruction(s), next(nullptr){}

node(int x, string s, node *n) : priority(x), instruction(s), next(n){}
};
node *head;
public:
Linkedlist() : head(nullptr){}
string getHead(){
  return head->instruction;
}
int getSize();
bool isEmpty(){
  return (head == nullptr);
}

void insertTail(int);
void insertPosition(int pr, string in){
  if (head == nullptr || pr < head->priority){
    head = new node(pr, in, head);
    return;
  }
  node *prev = nullptr;
  node *curr = head;
  while(curr != nullptr && pr > curr->priority){
    prev = curr;
    curr = curr->next;
  }
  node *temp = new node(pr, in, curr);
  prev->next = temp;
}
void removeHead(){
  if(head == nullptr){
    return;
  }
  node *deleteNode = head;
  head = head->next;
  delete deleteNode;
}
void print(){
  node *curr = head;
  while(curr != nullptr){
    cout << curr->instruction << " " << curr->priority << endl;
    curr = curr->next;
  }
}
};