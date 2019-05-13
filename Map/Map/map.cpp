#include "stdafx.h"
#include "map.h"
#include "Iterator.h"
#include <stdexcept>


template <typename T, typename G >
map<T, G>::map()
{
	root = nullptr;
	size = 0;
}

template <typename T, typename G >
map<T, G>::~map()
{
	clear();
	
}

template <typename T, typename G >
void map<T, G>::remove(T key)
{
	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}

	node *current;
	current = root;
	node *successor = nullptr;
	node *temp = nullptr;
	int found = 0;
	while (current != nullptr && found == 0)
	{
		if (current->key == key)
			found = 1;
		if (found == 0)
		{
			if (current->key < key)
				current = current->next_right;
			else
				current = current->next_left;
		}
	}
	if (found == 0)
	{
		throw out_of_range("no this element");
	}
	else
	{
		if (current->next_left == nullptr || current->next_right == nullptr)
			successor = current;
		else
			successor = get_successor(current);
		if (successor->next_left != nullptr)
			temp = successor->next_left;
		else
		{
			if (successor->next_right != nullptr)
				temp = successor->next_right;
			else
				temp = nullptr;
		}
		if (temp != nullptr)
			temp->parent = successor->parent;
		if (successor->parent == nullptr)
			root = temp;
		else
		{
			if (successor == successor->parent->next_left)
				successor->parent->next_left = temp;
			else
				successor->parent->next_right = temp;
		}
		if (successor != current)
		{
			current->color = successor->color;
			current->key = successor->key;
			current->data = successor->data;
		}
		if (successor->color == 0)
			delfix(temp);
	}
	size--;
}

template <typename T, typename G >
void map<T, G>::get_keys()
{

	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}
	auto it = create_bft_iterator();
	for (; it != nullptr; it++)
		cout << it.current_key() << endl;
	cout << '\n';
}


template <typename T, typename G >
void map<T, G>::get_value()
{
	if (this->root == nullptr)
	{
		throw out_of_range("error");
	}
	auto it = create_bft_iterator();
	for (; it != nullptr; it++)
	{
		cout << *it << '-' << it.current_key() << ' ' << it.current_color();
		cout << endl;
	}
	cout << '\n';


}

template <typename T, typename G >
void map<T, G>::clear()
{
	while (size > 0)
		remove(root->key);
}



template <typename T, typename G >
typename map<T, G>::node * map<T, G>::get_successor(node *current) 
{
	node *successor = nullptr;
	if (current->next_left != nullptr)
	{
		successor = current->next_left;
		while (successor->next_right != nullptr)
			successor = successor->next_right;
	}
	else
	{
		successor = current->next_right;
		while (successor->next_left != nullptr)
			successor = successor->next_left;
	}
	return successor;
}


template <typename T, typename G >
void map<T, G>::insert(T key, G value) {

	node *temp, *prev;
	node *current = new node(key, value);
	temp = root;
	prev = nullptr;
	if (root == nullptr)
	{
		root = current;
		current->parent = nullptr;
	}
	else
	{
		while (temp != nullptr)
		{
			prev = temp;
			if (temp->key < current->key)
				temp = temp->next_right;
			else
				temp = temp->next_left;
		}
		current->parent = prev;
		if (prev->key < current->key)
			prev->next_right = current;
		else
			prev->next_left = current;
	}

	insertfix(current);
	size++;
}

template<typename T, typename G>
void map<T, G>::delfix(node *fixable) //balancing tree 
{

	node *sibling;
	while (fixable != root && fixable->color == 0)
	{
		if (fixable->parent->next_left == fixable)
		{
			sibling = fixable->parent->next_right;
			if (sibling->color == 1)
				//sibling red->change the colors necessary elements; use left rotation
			{
				sibling->color = 0;
				fixable->parent->color = 1;
				leftrotate(fixable->parent);
				sibling = fixable->parent->next_right;
			}
			if (sibling->next_right->color == 0 && sibling->next_left->color == 0) // change sibling it to red
			{
				sibling->color = 1;
				fixable = fixable->parent;
			}
			else
			{
				if (sibling->next_right->color == 0) //use right rotatoin; change colors
				{
					sibling->next_left->color = 0;
					sibling->color = 1;
					rightrotate(sibling);
					sibling = fixable->parent->next_right;
				}
				sibling->color = fixable->parent->color;
				fixable->parent->color = 0;
				sibling->next_right->color = 0;
				leftrotate(fixable->parent);
				fixable = root;
			}
		}
		else
		{
			sibling = fixable->parent->next_left;
			if (sibling->color == 1)
			{
				sibling->color = 0;
				fixable->parent->color = 1;
				rightrotate(fixable->parent);
				sibling = fixable->parent->next_left;
			}
			if (sibling->next_left->color == 0 && sibling->next_right->color == 0)
			{
				sibling->color = 1;
				fixable = fixable->parent;
			}
			else
			{
				if (sibling->next_left->color == 0)
				{
					sibling->next_right->color = 0;
					sibling->color = 1;
					leftrotate(sibling);
					sibling = fixable->parent->next_left;
				}
				sibling->color = fixable->parent->color;
				fixable->parent->color = 0;
				sibling->next_left->color = 0;
				rightrotate(fixable->parent);
				fixable = root;
			}
		}
		fixable->color = 0;
		root->color = 0;
	}
}

template <typename T, typename G >
void map<T, G>::insertfix(node *current) { //balancing tree
	node *uncle;
	//0 - black
	//1 - red
	//The current node  at the root of the tree.
	if (root == current)
	{
		current->color = 0;
		return;
	}
	while (current->parent != nullptr && current->parent->color == 1)
	{
		node *grandparent = current->parent->parent; // get grandparent of the current node
		if (grandparent->next_left == current->parent) // grandparents and uncle are red->change color uncle and left grandparent
		{
			if (grandparent->next_right != nullptr)
			{
				uncle = grandparent->next_right;
				if (uncle->color == 1)
				{
					current->parent->color = 0;
					uncle->color = 0;
					grandparent->color = 1;
					current = grandparent;
				}
			}
			else
			{
				if (current->parent->next_right == current) //parent is red, uncle is black, current node is right descendant; use rotation
															
				{
					current = current->parent;
					leftrotate(current);
				}
				current->parent->color = 0;
				grandparent->color = 1;
				rightrotate(grandparent);
			}
		}
		else
		{
			if (grandparent->next_left != nullptr)//parents and uncle are red->change color in to black and color of left grandparent change to red 
			{
				uncle = grandparent->next_left;
				if (uncle->color == 1)
				{
					current->parent->color = 0;
					uncle->color = 0;
					grandparent->color = 1;
					current = grandparent;
				}
			}
			else
			{
				if (current->parent->next_left == current) //parent is red, uncle is black, the current node is the left descendant; use rotation
				{
					current = current->parent;
					rightrotate(current);
				}
				current->parent->color = 0;
				grandparent->color = 1;
				leftrotate(grandparent);
			}
		}
		root->color = 0;
	}

}

template <typename T, typename G >
void map<T, G>::leftrotate(node *current)
{
	if (current->next_right == nullptr)
		return;
	else
	{
		node *child = current->next_right;
		if (child->next_left != nullptr)
		{
			current->next_right = child->next_left;
			child->next_left->parent = current;
		}
		else
			current->next_right = nullptr;
		if (current->parent != nullptr)
			child->parent = current->parent;
		if (current->parent == nullptr)
			root = child;
		else
		{
			if (current == current->parent->next_left)
				current->parent->next_left = child;
			else
				current->parent->next_right = child;
		}
		child->next_left = current;
		current->parent = child;
	}
}

template <typename T, typename G >
void map<T, G>::rightrotate(node *current)
{
	if (current->next_left == nullptr)
		return;
	else
	{
		node *child = current->next_left;
		if (child->next_right != nullptr)
		{
			current->next_left = child->next_right;
			child->next_right->parent = current;
		}
		else
			current->next_left = nullptr;
		if (current->parent != nullptr)
			child->parent = current->parent;
		if (current->parent == nullptr)
			root = child;
		else
		{
			if (current == current->parent->next_left)
				current->parent->next_left = child;
			else
				current->parent->next_right = child;
		}
		child->next_right = current;
		current->parent = child;
	}
}
