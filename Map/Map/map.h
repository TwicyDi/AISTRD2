#pragma once
#include <iostream>
#include "Iterator.h"

using namespace std;


template <class item> class queue
{
	item *Queue; int head, tail, size_, Max;
public:
	queue(int maxQ) : head(0), tail(0), Max(maxQ), size_(0), Queue(new item[maxQ + 1]) {}
	~queue();
	bool empty() const { return (head % Max) == tail; }
	int size() const { return size_; }
	void push(item & item) { Queue[tail++] = item; tail %= Max; ++size_; }
	item front() const { return Queue[head % Max]; }
	void pop() { head++; head %= Max; --size_; }
};

template <class item>
queue<item>::~queue()
{
	free(Queue);
}

template <typename T, typename G >
class map 
{
private:

	class node
	{

	public:
		node(T key, G data, node * next1 = nullptr, node * next2 = nullptr) {
			this->data = data;
			this->next_left = next1;
			this->next_right = next2;
			this->key = key;
			this->parent = nullptr;
			this->color = 1;

		};
		bool color;
		T key;
		G data;
		node * next_right, *next_left, *parent;
		~node();

	};

	void delfix(node*);
	void insertfix(node *t);
	void leftrotate(node *);
	void rightrotate(node *);
	node *get_successor(node *current);
	node * root;
	size_t size;

public:
	map();
	~map();
	class TreeIterator : public Iterator<T, G> {
	protected:
		node *current;
		TreeIterator(node* root) : current(root) { }

	public:
		bool operator==(const nullptr_t) const override { return current == nullptr; }
		bool operator!=(const nullptr_t) const override { return !operator==(nullptr); }
		G operator*() const override { return current->data; }
		T current_key() { return current->key; }
		bool current_color() { return current->color; }

	};

	
	class BftIterator : public TreeIterator { //wide tree traversal
	private:
		queue<node*> nodes;
	public:
		BftIterator(node *root, size_t size) : TreeIterator(root), nodes(size) {}
		void operator++(T) override;
	};
	
	void remove(T);
	G find(T);

	void get_keys();
	void get_value();
	void clear();
	void insert(T, G);


	BftIterator create_bft_iterator() { return BftIterator(root, size); }
};



template<typename T, typename G>
void map<T, G>::BftIterator::operator++(T)
{
	if (this->current->next_left != nullptr)
		nodes.push(this->current->next_left);
	if (this->current->next_right != nullptr)
		nodes.push(this->current->next_right);
	if (nodes.size() > 0) {
		this->current = nodes.front();
		nodes.pop();
	}
	else
		this->current = nullptr;
}
