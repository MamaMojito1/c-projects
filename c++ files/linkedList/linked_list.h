//linkedList.h
#include <iostream>
#include <cstdlib>
#include <windows.h>
using namespace std;

template <class T = int>
class myLinkedList
{
    struct node
    {
        T data;
        node *next;
    } *head;
public:
    myLinkedList()
    {
        head = NULL;
    }
    ~myLinkedList()
    {
        node *temp = head;
        while(temp != NULL)
        {
            node *cur = temp->next;
            delete temp;
            temp = cur;
        }
    }
    void insertbegin(T d)
    {
        node *n = new node;
        n -> data = d;
        n -> next = head;
        head = n;
    }
    void insertend(T d)
    {
        node *n = new node;
        n -> data = d;
        n -> next == NULL;
        if(head == NULL)
            head = n;
        else {
            node *cur = head;
            while(cur -> next != NULL)
                cur = cur -> next;
            cur -> next = n;
        }
    }
    T deletebegin()
    {
        try {
            if(head == NULL)
                throw head;
        }
        catch(...)
        {
            cout << "The list is empty\n";
            exit(1);
        }
        node *cur = head;
        T d = cur -> data;
        head = head ->next;
        delete cur;
        return d;
    }
    T deleteend()
    {
        try {
            if(head == NULL)
                throw head;
        }
        catch(...)
        {
            cout << "The list is empty\n";
            exit(1);
        }
        node *cur = head, *prev;
        if(head->next == NULL)
            head == NULL;
        else
        {
            while(cur->next != NULL)
            {
                prev = cur;
                cur = cur->next;
            }
            prev->next = NULL;
        }
        T d = cur->data;
        delete cur;
        return d;
    }
    void display()
    {
        node *cur = head;
        if(head == NULL)
            cout << "The list is empty\n";
        while(cur != NULL)
        {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << "\n";
    }
};
