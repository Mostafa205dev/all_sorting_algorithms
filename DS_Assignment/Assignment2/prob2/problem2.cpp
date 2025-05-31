#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct contact_info
{
	string name;
	string phone;
	string email;
};

class AVL_node
{
public:
	int key;
	contact_info value;
	AVL_node *left;
	AVL_node *right;
	int height;

	AVL_node(int key, contact_info value)
		: key(key), value(value), left(nullptr), right(nullptr), height(1) {}

	void print()
	{
		cout << "ID: " << key << endl;
		cout << "Name: " << value.name << endl;
		cout << "Phone: " << value.phone << endl;
		cout << "Email: " << value.email << endl;
	}
	int right_height()
	{
		if (right)
		{
			return right->height;
		}
		else
		{
			return 0;
		}
	}

	int left_height()
	{
		if (left)
		{
			return left->height;
		}
		else
		{
			return 0;
		}
	}

	void update_height()
	{
		height = 1 + max(left_height(), right_height());
	}

	void print_tree(std::string prefix = "", bool is_left = true) const
	{
		if (right)
		{
			right->print_tree(prefix + (is_left ? "│   " : "    "), false);
		}
		std::cout << prefix << (is_left ? "└── " : "┌── ") << key << " (h=" << height << ")" << std::endl;
		if (left)
		{
			left->print_tree(prefix + (is_left ? "    " : "│   "), true);
		}
	}
};

class AVL_tree
{
private:
	AVL_node *insert_node(AVL_node *cur, AVL_node *ins)
	{
		if (cur == nullptr)
		{
			cur = ins;
		}
		else
		{

			if (ins->key < cur->key)
			{
				cur->left = insert_node(cur->left, ins);
			}
			else
			{
				cur->right = insert_node(cur->right, ins);
			}
		}

		cur->update_height();

		int balance = get_balance(cur);

		if (balance > 1 && ins->key < cur->left->key)
		{
			return right_rotation(cur);
		}
		if (balance < -1 && ins->key > cur->right->key)
		{
			return left_rotation(cur);
		}
		// Left Right Case
		if (balance > 1 && ins->key > cur->left->key)
		{
			cur->left = left_rotation(cur->left);
			return right_rotation(cur);
		}

		// Right Left Case
		if (balance < -1 && ins->key < cur->right->key)
		{
			cur->right = right_rotation(cur->right);
			return left_rotation(cur);
		}
		return cur;
	}

	void in_order_travel(AVL_node *node)
	{

		if (!node)
			return;
		in_order_travel(node->left);
		node->print();
		cout << endl;
		in_order_travel(node->right);
	}

	void pre_order_travel(AVL_node *node)
	{
		if (!node)
			return;

		node->print();
		cout << endl;
		pre_order_travel(node->left);
		pre_order_travel(node->right);
	}

	void post_order_travel(AVL_node *node)
	{

		if (!node)
			return;

		pre_order_travel(node->left);
		pre_order_travel(node->right);
		node->print();
		cout << endl;
	}

	AVL_node *search(AVL_node *node, int key)
	{
		if (!node)
		{
			return nullptr;
		}
		if (key == node->key)
		{
			return node;
		}
		if (key > node->key)
		{
			return search(node->right, key);
		}
		else
		{
			return search(node->left, key);
		}
	}

	AVL_node *delete_node(AVL_node *y, int key)
	{
		if (!y)
			return nullptr;

		if (key > y->key)
		{
			y->right = delete_node(y->right, key);
		}
		else if (key < y->key)
		{
			y->left = delete_node(y->left, key);
		}
		else
		{
			// Node to be deleted found
			if (!y->left || !y->right)
			{
				AVL_node *temp = y->left ? y->left : y->right;
				delete y;
				return temp;
			}
			else
			{
				// Node with two children
				AVL_node *temp = get_smallest(y->right);
				y->key = temp->key;
				y->value = temp->value;
				y->right = delete_node(y->right, temp->key);
			}
		}

		y->update_height();
		int balance = get_balance(y);

		// Left Left Case
		if (balance > 1 && get_balance(y->left) >= 0)
			return right_rotation(y);

		// Left Right Case
		if (balance > 1 && get_balance(y->left) < 0)
		{
			y->left = left_rotation(y->left);
			return right_rotation(y);
		}

		// Right Right Case
		if (balance < -1 && get_balance(y->right) <= 0)
			return left_rotation(y);

		// Right Left Case
		if (balance < -1 && get_balance(y->right) > 0)
		{
			y->right = right_rotation(y->right);
			return left_rotation(y);
		}

		return y;
	}

public:
	AVL_node *root;
	AVL_tree()
	{
		root = nullptr;
	};

	void delete_node(int key)
	{
		root = delete_node(root, key);
	}

	AVL_node *get_smallest(AVL_node *y)
	{
		if (!y->left)
		{
			return y;
		}
		return get_smallest(y->left);
	}

	AVL_node *get_biggest(AVL_node *y)
	{
		if (!y->right)
		{
			return y;
		}
		return get_biggest(y->right);
	}
	AVL_node *right_rotation(AVL_node *y)
	{

		if (!y || !y->left)
			return y;
		AVL_node *x = y->left;
		AVL_node *T2 = x->right;

		y->left = T2;
		x->right = y;

		y->update_height();
		x->update_height();

		return x;
	};
	AVL_node *left_rotation(AVL_node *y)
	{
		if (!y || !y->right)
			return y;
		AVL_node *x = y->right;
		AVL_node *T2 = x->left;

		y->right = T2;
		x->left = y;

		y->update_height();
		x->update_height();

		return x;
	};
	int get_balance(AVL_node *n)
	{
		if (!n)
		{
			return 0;
		}
		return height(n->left) - height(n->right);
	}

	int height(AVL_node *n)
	{
		if (!n)
		{
			return 0;
		}
		return n->height;
	}

	void in_order_traversal()
	{
		in_order_travel(root);
	}
	void insert(int key, contact_info val)
	{
		root = insert_node(root, new AVL_node(key, val));
	};

	AVL_node *search(int key)
	{
		return search(root, key);
	}

	void print_tree()
	{
		root->print_tree();
	}
};

int main()
{
	AVL_tree tree;

	int choice;

	fstream inputFile("testp2.txt", ios::in);
	while (!inputFile.eof())
	{

		if (!inputFile)
		{
			cerr << "Error: Could not open input.txt\n";
			break;
		}

		inputFile >> choice;

		switch (choice)
		{
		case 1:
		{
			int id;
			string name;
			string phone;
			string email;

			inputFile >> id;
			inputFile.ignore(); // Skip newline or space
			getline(inputFile, name);
			getline(inputFile, phone);
			getline(inputFile, email);

			auto node = tree.search(id);

			if (node)
			{
				cout << "Contact with id " << id << " already exists" << endl;
			}
			else
			{

				tree.insert(id, {name, phone, email});

				cout << "Added Contact:" << endl;
				cout << "ID: " << id << endl;
				cout << "Name: " << name << endl;
				cout << "Phone: " << phone << endl;
				cout << "Email: " << email << endl;
			}
			break;
		}
		case 2:
		{
			int id;
			inputFile >> id;

			auto node = tree.search(id);

			if (node)
			{
				cout << "Found contact\n";
				node->print();
			}
			else
			{
				cout << "No contact found with Id" << id << endl;
			}

			break;
		}
		case 3:
		{
			int id;
			inputFile >> id;

			auto node = tree.search(id);

			if (node)
			{
				cout << "Deleted contact with id " << id << " with name " << node->value.name << endl;
			}
			else
			{
				cout << "No contact found with Id " << id << endl;
			}
			break;
		}
		case 4:
			if (tree.root)
			{
				cout << "List of contacts:\n";
				tree.in_order_traversal();
			}
			else
			{
				cout << "No Contacts registred\n";
			}
			break;
		case 5:
			tree.print_tree();
			break;
		default:
			cout << "Invalid option. Please enter a number between 1 and 5.\n";
		}

		cout << endl;
	}
	inputFile.close();

	return 0;
}
