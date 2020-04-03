#include<iostream>

using namespace std;

template<class type>
struct Node
{
    Node<type> *next;
    Node<type> *back;
    type data;
};

template<class type>
class MyList
{
private:
    Node <type>* head;
    Node <type>* dummyNode;
public:
    class iterator
    {
    private:
        Node <type>* i = NULL;
        MyList l;
    public:
        Node<type>*& getIteratorNode()
        {
            return i;
        }
        MyList& getIteratorObject()
        {
            return l;
        }
        void operator++(int)
        {
            if (i == l.dummyNode || i->next == NULL)
            {
                throw "error";
            }
            else
            {
                i = i->next;
            }
        }
        void operator--(int)
        {
            if (l.head == l.dummyNode || l.head == i || i->back == NULL)
            {
                throw "error";
            }
            else
            {
                i = i->back;
            }
        }
        type& operator *()
        {
            return (i->data);
        }
        bool operator ==(const iterator& m)
        {
            if (m.i == i)
                return true;
            return false;
        }
    };

    MyList()
    {
        dummyNode = new Node<type>();
        dummyNode->data = 0;
        dummyNode->next = NULL;
        dummyNode->back = NULL;
        head = dummyNode;
    }
    MyList(type value, int initial_size)
    {
        head = new Node<type>();
        dummyNode = new Node<type>();
        dummyNode->data = 0;
        Node <type>*cur = head;
        head->data = value;
        head->back = NULL;
        for (int i = 1; i<initial_size; i++)
        {
            Node<type> *newNode = new Node<type>();
            newNode->data = value;
            newNode->back = cur;
            cur->next = newNode;
            cur = newNode;
        }
        cur->next = dummyNode;
        dummyNode->back = cur;
        dummyNode->next = NULL;
    }
private :
    void push_back(type x)
    {
        Node<type> * new_node = new Node<type>();
        new_node->data = x;
        if(head == dummyNode)
        {
            new_node->next = dummyNode;
            new_node->back = NULL;
            dummyNode->back = new_node;
            head = new_node;
        }
        else
        {
            new_node->next = dummyNode;
            new_node->back = dummyNode->back;
            dummyNode->back->next = new_node;
            dummyNode->back = new_node;
        }
    }
public :
    void insert(int x, iterator& position)
    {
        Node<type> *new_node = new Node<type>();
        new_node->data = x;
        if (position.getIteratorNode() != head)
        {
            new_node->next = position.getIteratorNode();
            new_node->back = position.getIteratorNode()->back;
            position.getIteratorNode()->back->next = new_node;
            position.getIteratorNode()->back = new_node;
            position.getIteratorNode()=new_node;
            return;
        }
        else
        {
            new_node->next = head;
            head->back = new_node;
            new_node->back = NULL;
            head = new_node;
            position.getIteratorObject().head = head;
            position.getIteratorNode() = new_node;
            return;
        }
    }
    iterator& erase(iterator &position)
    {
        Node<type>* cur = position.getIteratorNode();
        if (position.getIteratorNode() != head && position.getIteratorNode() != dummyNode)
        {
            position.getIteratorNode()->back->next = position.getIteratorNode()->next;
            position.getIteratorNode()->next->back = position.getIteratorNode()->back;
            position.getIteratorNode() = cur->next;
            delete cur;
            return position;
        }
        else if (position.getIteratorNode() == head)
        {
            head = head->next;
            head->back = NULL;
            position.getIteratorNode() = head;
            delete cur;
            return position;
        }
        else
        {
            cout << "you cant delete node after the last node\n";
            return position;
        }
    }
    iterator begin()
    {
        iterator b;
        b.getIteratorObject().head = head;
        b.getIteratorNode() = head;
        return b;
    }
    iterator end()
    {
        iterator it;
        it.getIteratorObject().dummyNode = dummyNode;
        it.getIteratorNode() = dummyNode;
        return it;
    }
    int size()
    {
        Node<type>* current = head;
        int i = 0;
        while (current != dummyNode)
        {
            i++;
            current = current->next;
        }
        return i;
    }
    MyList<type>& operator = (MyList<type>* another_list)
    {
        Node<type> * cur = another_list->head;
        for(int i = 0 ; cur->next!=NULL ; i++)
        {
            push_back(cur->data);
            cur = cur->next;
        }
        return *this;
    }

};

int main()
{
    MyList<int> list(2,3);

    MyList<int> list1;
    MyList<int>::iterator it = list.begin();

    cout<<*it<<endl;//2

    list.insert(3,it);//3 2 2 2
    try
    {
        it++;   //2
    }
    catch(const char* x)
    {
        cout<<x<<endl;
    }
    cout<<*it<<endl;//2
    try
    {
        it--;   //3
    }
    catch(const char* x)
    {
        cout<<x<<endl;
    }
    cout<<*it<<endl;//3
    list.insert(5,it);// 5 3 2 2 2
    list.insert(9,it);// 9 5 3 2 2 2
    MyList<int> m;
    m = list;
    MyList<int>::iterator it2 = m.begin();
    cout<<*it2<<endl;//9
    cout<< list.size()<<endl;//6
    list.erase(it);//5 3 2 2 2
    cout<< list.size()<<endl;//5
    cout<<*it<<endl;//5
    MyList<int>::iterator k =list.begin();
    it=list.end();//2
    cout<<(it==k)<<endl;//0
    try
    {
        it++;   // exception
    }
    catch(const char* x)
    {
        cout<<x<<endl;
    }
    it=list.begin();//5
    cout<<(it==k)<<endl;//1
    try
    {
        it--;   // excption
    }
    catch(const char* x)
    {
        cout<<x<<endl;
    }
    return 0;
}
