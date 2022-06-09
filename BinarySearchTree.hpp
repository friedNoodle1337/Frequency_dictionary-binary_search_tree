#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <iostream>
#include <queue>

template < class K, class V >
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree< K, V >& other);
	BinarySearchTree(BinarySearchTree< K, V >&& other) noexcept;
	virtual ~BinarySearchTree();

	BinarySearchTree< K, V >& operator=(const BinarySearchTree< K, V >& other);
	BinarySearchTree< K, V >& operator=(BinarySearchTree< K, V >&& other) noexcept;
	bool operator==(const BinarySearchTree< K, V >& other);

	struct Node
	{
		K key_;
		V value_;
		Node* left_;
		Node* right_;
		Node* p_;

		Node(K key, V value, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr):
			key_(key), value_(value), left_(left), right_(right), p_(p) {}
	};

	Node* findKey(const K& key) const
	{
		return iterariveSearchNode(key);
	}

	bool searchKey(const K& key) const;
	bool insert(const K& key, const V& value);
	bool insert_or_assign(const K& key, const V& value);
	bool erase(const K& key);
	void inorderWalk() const;
	size_t size() const;
	void top(int pos);
	BinarySearchTree< V, K > remake();

private:
	Node* root_;
	int countPos;

	void swap(BinarySearchTree< K, V >& other)
	{
		std::swap(root_, other.root_);
		std::swap(countPos, other.countPos);
	}

	Node* iterariveSearchNode(const K& key) const
	{
		Node* current = root_;

		while (current != nullptr && current->key_ != key)
		{
			if (key > current->key_)
			{
				current = current->right_;
			}
			else
			{
				current = current->left_;
			}
		}

		return current;
	}

	bool insertNode(Node* newNode, bool insertOrAssign)
	{
		if (newNode == nullptr)
		{
			return false;
		}

		if (root_ == nullptr)
		{
			root_ = newNode;

			return true;
		}

		Node* current = root_;

		while (true)
		{
			if (newNode->key_ == current->key_)
			{
				if (insertOrAssign == true)
				{
					current->value_ = newNode->value_;

					return true;
				}
				else
				{
					return false;
				}
			}
			else if (newNode->key_ < current->key_)
			{
				if (current->left_ == nullptr)
				{
					current->left_ = newNode;
					newNode->p_ = current;

					return true;
				}
				current = current->left_;
			}
			else if (newNode->key_ > current->key_)
			{
				if (current->right_ == nullptr)
				{
					current->right_ = newNode;
					newNode->p_ = current;

					return true;
				}
				current = current->right_;
			}
		}
	}

	bool deleteNode(const K& key)
	{
		Node* current = iterariveSearchNode(key);
		if (current == nullptr)
		{
			return false;
		}
		Node* parentOfCurrent = current->p_;

		if (current->left_ == nullptr && current->right_ == nullptr)
		{
			if (current == root_)
			{
				delete current;
				root_ = nullptr;

				return true;
			}

			if (parentOfCurrent->left_ == current)
			{
				parentOfCurrent->left_ = nullptr;
			}
			else
			{
				parentOfCurrent->right_ = nullptr;
			}
			delete current;

			return true;
		}
		else if (current->left_ != nullptr && current->right_ != nullptr)
		{
			Node* min = current->right_;
			bool check = false;
			while (min->left_ != nullptr)
			{
				min = min->left_;
				check = true;
			}
			current->key_ = min->key_;
			current->value_ = min->value_;
			if (min->right_ != nullptr)
			{
				min->right_->p_ = min->p_;
			}
			if (check == true)
			{
				min->p_->left_ = min->right_;
			}
			else
			{
				min->p_->right_ = min->right_;
			}
			delete min;

			return true;
		}
		else if (current->left_ == nullptr)
		{
			current->right_->p_ = parentOfCurrent;
			if (parentOfCurrent->left_ == current)
			{
				parentOfCurrent->left_ = current->right_;
			}
			else
			{
				parentOfCurrent->right_ = current->right_;
			}
			delete current;

			return true;
		}
		else
		{
			current->left_->p_ = parentOfCurrent;
			if (parentOfCurrent->left_ == current)
			{
				parentOfCurrent->left_ = current->left_;
			}
			else
			{
				parentOfCurrent->right_ = current->left_;
			}
			delete current;

			return true;
		}
	}

	void inorderWalk(Node* node) const
	{
		if (node != nullptr)
		{
			inorderWalk(node->left_);
			std::cout << node->key_ << " " << node->value_ << " ";
			inorderWalk(node->right_);
		}
	}

	int getCount(Node* node) const
	{
		if (node == nullptr)
		{
			return 0;
		}

		return 1 + getCount(node->right_) + getCount(node->left_);
	}

	bool isSimilarTrees(Node* node1, Node* node2) const
	{
		if (node1 == node2 && node1 == nullptr)
		{
			return true;
		}
		else if ((node1 != node2 && node1 == nullptr) ||
			(node1 != node2 && node2 == nullptr))
		{
			return false;
		}
		else
		{
			return isSimilarTrees(node1->left_, node2->left_) &&
				node1->key_ == node2->key_ &&
				isSimilarTrees(node1->right_, node2->right_);
		}
	}

	void top(Node* node, int& pos) const
	{
		if (node == nullptr || pos > countPos)
		{
			return;
		}

		top(node->right_, pos);

		std::cout << pos << ". " << node->key_ << " " << node->value_ << "\n";
		++pos;

		top(node->left_, pos);
	}

	void reverseOrderWalkInsertOrAssign(Node* node, BinarySearchTree< V, K >& tree)
	{
		if (node != nullptr)
		{
			reverseOrderWalkInsertOrAssign(node->right_, tree);
			tree.insert_or_assign(node->value_, node->key_);
			reverseOrderWalkInsertOrAssign(node->left_, tree);
		}
	}
};

template < class K, class V >
BinarySearchTree< K, V >::BinarySearchTree():
	root_(nullptr), countPos(0)
{}

template < class K, class V >
BinarySearchTree< K, V >::BinarySearchTree(const BinarySearchTree< K, V >& other):
	root_(nullptr), countPos(other.countPos)
{
	if (other.root_ != nullptr)
	{
		std::queue< Node* > nodes;

		nodes.push(other.root_);
		if (other.root_->left_ != nullptr)
		{
			nodes.push(other.root_->left_);
		}
		if (other.root_->right_ != nullptr)
		{
			nodes.push(other.root_->right_);
		}

		Node* current = nodes.front();
		nodes.pop();
		while (nodes.empty() == false)
		{
			insert_or_assign(current->key_, current->value_);
			if (nodes.front()->left_ != nullptr)
			{
				nodes.push(nodes.front()->left_);
			}
			if (nodes.front()->right_ != nullptr)
			{
				nodes.push(nodes.front()->right_);
			}
			current = nodes.front();
			nodes.pop();
		}
		insert_or_assign(current->key_, current->value_);
	}
	else
	{
		root_ = other.root_;
	}
}

template < class K, class V >
BinarySearchTree< K, V >::BinarySearchTree(BinarySearchTree&& other) noexcept:
	root_(other.root_), countPos(other.countPos)
{
	other.root_ = nullptr;
	other.countPos = 0;
}

template < class K, class V >
BinarySearchTree< K, V >::~BinarySearchTree()
{
	Node* current = nullptr;
	Node* next = root_;

	while (next != nullptr)
	{
		if (next->left_ != nullptr)
		{
			current = next;
			next = next->left_;
		}
		else if (next->right_ != nullptr)
		{
			current = next;
			next = next->right_;
		}
		else
		{
			if (current != nullptr && current->right_ == next)
			{
				current->right_ = nullptr;
			}
			else if (current != nullptr)
			{
				current->left_ = nullptr;
			}
			delete next;
			next = current;
			if (current != nullptr)
			{
				current = current->p_;
			}
		}
	}
	root_ = nullptr;
	countPos = 0;
}

template < class K, class V>
BinarySearchTree< K, V >& BinarySearchTree< K, V >::operator=(const BinarySearchTree& other)
{
	if (this != &other)
	{
		this->~BinarySearchTree();
		BinarySearchTree< K, V > temp(other);
		root_ = temp.root_;
		temp.root_ = nullptr;
		countPos = temp.countPos;
	}

	return *this;
}

template < class K, class V >
BinarySearchTree< K, V >& BinarySearchTree< K, V >::operator=(BinarySearchTree&& other) noexcept
{
	if (this != &other)
	{
	  swap(other);
	}

	return *this;
}

template < class K, class V >
bool BinarySearchTree< K, V >::operator==(const BinarySearchTree< K, V >& other)
{
	return isSimilarTrees(root_, other.root_);
}

template < class K, class V >
bool BinarySearchTree< K, V >::searchKey(const K& key) const
{
	return iterariveSearchNode(key) != nullptr;
}

template < class K, class V >
bool BinarySearchTree< K, V >::insert(const K& key, const V& value)
{
	return insertNode(new Node(key, value), false);
}

template < class K, class V >
bool BinarySearchTree< K, V >::insert_or_assign(const K& key, const V& value)
{
	return insertNode(new Node(key, value), true);
}

template < class K, class V >
bool BinarySearchTree< K, V >::erase(const K& key)
{
	return deleteNode(key);
}

template < class K, class V >
void BinarySearchTree< K, V>::inorderWalk() const
{
	inorderWalk(root_);
	std::cout << "\n";
}

template < class K, class V >
size_t BinarySearchTree< K, V >::size() const
{
	return getCount(root_);
}

template < class K, class V >
void BinarySearchTree< K, V >::top(int pos)
{
	countPos = pos;
	pos = 1;
	top(root_, pos);
	countPos = 0;
}

template < class K, class V >
BinarySearchTree< V, K > BinarySearchTree< K, V >::remake()
{
	BinarySearchTree< V, K > temp;

	if (root_ != nullptr)
	{
		reverseOrderWalkInsertOrAssign(root_, temp);
	}

	return temp;
}

#endif
