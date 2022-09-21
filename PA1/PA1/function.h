#ifndef MY_FUNCTION
#define MY_FUNCTION


template <typename T>
struct node
{
	T command;
	T description;
	node* next;
};

template <class T>
class linkedlist
{
private:
	node<T>* head;
public:
	void addCommand(T c, T d);
	bool searchCommand(T s);
	node<T>* getCommand(int index);
	void removeCommand(T c);
};

#endif