#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

class Binary_tree
{
private:
	class Node
	{
	public:
		int info;
		Node* left=nullptr;
		Node* right=nullptr;
		Node* parent=nullptr;
	};

	Node* top;
	Node* bottom;
	int number_of_elements;
	std::vector<int>PreOrder_vector;
	std::vector<int>InOrder_vector;
	std::vector<int>PostOrder_vector;
	int size;

public:

	Binary_tree()
	{
		size = 0;
		top = nullptr;
		number_of_elements = 0;
	}

	~Binary_tree()
	{
		std::queue<Node*>coada_de_noduri;
		Node* parinte = top;
		coada_de_noduri.push(parinte);
		while (coada_de_noduri.size() != 0)
		{
			parinte = coada_de_noduri.front();
			coada_de_noduri.pop();
			if (parinte->left != nullptr)
			{
				coada_de_noduri.push(parinte->left);
			}
			if (parinte->right != nullptr)
			{
				coada_de_noduri.push(parinte->right);
			}
			delete parinte;
		}
	}

	void generare_copii_si_adaugare_in_coada(Node*& parinte, int childrean, std::queue<Node*>&coada_de_noduri)
	{
		if (childrean == -1 || childrean ==2)
		{
			Node* new_child_left = new Node;
			new_child_left->parent = parinte;
			parinte->left = new_child_left;
			coada_de_noduri.push(new_child_left);
			if (childrean == 2)
			{
				Node* new_child_right = new Node;
				new_child_right->parent = parinte;
				parinte->right = new_child_right;
				coada_de_noduri.push(new_child_right);
			}
		}
		else if (childrean == 1)
		{
			Node* new_child_right = new Node;
			new_child_right->parent = parinte;
			parinte->right = new_child_right;
			coada_de_noduri.push(new_child_right);
		}
	}

	void reading_elements_using_width_traversal(std::string file="input.in")
	{
		int element, childrean;
		std::queue<Node*>coada_de_noduri;
		std::ifstream fin;
		fin.open(file);
		fin >> element >> childrean;
		Node* parinte = new Node;
		parinte->info = element;
		number_of_elements++;
		top = parinte;
		generare_copii_si_adaugare_in_coada(parinte, childrean, coada_de_noduri);
		while (!fin.eof() && coada_de_noduri.size()!=0)
		{
			fin >> element >> childrean;
			parinte = coada_de_noduri.front();
			parinte->info = element;
			number_of_elements++;
			bottom = parinte;
			coada_de_noduri.pop();
			generare_copii_si_adaugare_in_coada(parinte, childrean, coada_de_noduri);
		}

		fin.close();
	}

	void print2DUtil(Node* root, int space, int COUNT=10)
	{
		if (root == NULL)
			return;

		space += COUNT;

		print2DUtil(root->right, space);

		std::cout << std::endl;
		for (int i = COUNT; i < space; i++)
			std::cout << " ";
		std::cout << root->info<< "\n";

		print2DUtil(root->left, space);
	}

	void print2D()
	{
		print2DUtil(top, 0);
	}

	struct comparator
	{
		bool operator()(const std::pair<Node*, int>a, const std::pair<Node*, int> b)
		{
			return a.second > b.second;
		}
	};

	void adding_childreans_in_priority_queue(std::priority_queue<std::pair<Node*, int>, std::vector<std::pair<Node*, int>>, comparator>& p_queue, Node* parinte, int indice_directie)
	{
		if (parinte->left != nullptr)
		{
			p_queue.push(std::make_pair(parinte->left, indice_directie));
		}
		if (parinte->right != nullptr)
		{
			p_queue.push(std::make_pair(parinte->right, indice_directie));
		}
	}

	void print_leaves_from_left_to_right()
	{
		int indice_directie;
		std::priority_queue<std::pair<Node*, int>, std::vector<std::pair<Node*, int>>, comparator>p_queue;
		Node* parinte = top;
		if (parinte->left != nullptr)
		{
			p_queue.push(std::make_pair(parinte->left, -1));
		}
		if (parinte->right != nullptr)
		{
			p_queue.push(std::make_pair(parinte->right, 1));
		}

		while (p_queue.size() != 0)
		{
			parinte = p_queue.top().first;
			indice_directie = p_queue.top().second;
			p_queue.pop();
			if (parinte->left == nullptr && parinte->right == nullptr)
			{
				std::cout << parinte->info<<" ";
			}
			adding_childreans_in_priority_queue(p_queue, parinte, indice_directie);
		}

	}

	bool check_if_two_trees_are_identical(Binary_tree tree)
	{
		std::vector<int>PostOrder_tree1 = getPostOrder();
		std::vector<int>InOrder_tree1 = getInOrder();
		std::vector<int>PostOrder_tree2 = tree.getPostOrder();
		std::vector<int>InOrder_tree2 = tree.getInOrder();

		if (PostOrder_tree1.size() != PostOrder_tree2.size() || InOrder_tree1.size() != InOrder_tree1.size())
		{
			return false;
		}

		for (int i = 0; i < PostOrder_tree1.size(); i++)
		{
			if (PostOrder_tree1[i] != PostOrder_tree2[i])
			{
				return false;
			}
		}

		for (int i = 0; i < InOrder_tree1.size(); i++)
		{
			if (InOrder_tree1[i] != InOrder_tree2[i])
			{
				return false;
			}
		}

		return true;
	}

	int getHeight(Node* node)
	{
		int height=0, max_height=0;
		std::queue<std::pair<Node*, int>>coada_de_noduri;
		Node* parinte=node;
		coada_de_noduri.push(std::make_pair(parinte, height));		
		while (coada_de_noduri.size() != 0)
		{
			parinte = coada_de_noduri.front().first;
			height = coada_de_noduri.front().second;
			if (max_height < height)
			{
				max_height = height;
			}
			coada_de_noduri.pop();
			if (parinte->left != nullptr)
			{
				coada_de_noduri.push(std::make_pair(parinte->left, height+1));
			}

			if (parinte->right != nullptr)
			{
				coada_de_noduri.push(std::make_pair(parinte->right, height+1));
			}
		}
		return max_height;
	}

	int getNodeDepth(Node* node)
	{
		int counter = 0;
		while (node!= nullptr)
		{
			counter++;
			node = node->parent;
		}
		if (counter == 0)
		{
			return 0;
		}
		return counter - 1;
	}

	bool isTreeComplete()
	{
		std::queue<Node*>coada_de_noduri;
		bool isPenultimateLevel = false;
		bool isLastLevel = false;
		Node* cross_tree;
		Node* first_node_that_hurt_the_tree=nullptr;
		coada_de_noduri.push(top);


		while (coada_de_noduri.size() != 0)
		{
			cross_tree = coada_de_noduri.front();
			coada_de_noduri.pop();
			if (first_node_that_hurt_the_tree==cross_tree)
			{
				isLastLevel = true;
			}

			if (cross_tree->left != nullptr && isLastLevel == false)
			{
				coada_de_noduri.push(cross_tree->left);
			}
			else if (cross_tree->left == nullptr && isLastLevel == true && cross_tree!=first_node_that_hurt_the_tree)
			{
				return false;
			}
			else if(first_node_that_hurt_the_tree == nullptr)
			{
				first_node_that_hurt_the_tree = cross_tree->right;
				isPenultimateLevel=true;
			}

			if (cross_tree->right != nullptr && isLastLevel==false)
			{
				coada_de_noduri.push(cross_tree->right);
			}
			else if (cross_tree->right == nullptr && isLastLevel == true && cross_tree != first_node_that_hurt_the_tree)
			{
				return false;
			}
			else if(first_node_that_hurt_the_tree==nullptr)
			{
				isPenultimateLevel = true;
				first_node_that_hurt_the_tree = cross_tree->left;
			}

		}
		return true;
	}

	void showPreOrder(Node* node, bool show=true)
	{
		PreOrder_vector.clear();
		if (node == nullptr)
		{
			return;
		}
		if (show == true)
		{
			std::cout << node->info<<" ";
		}
		PreOrder_vector.push_back(node->info);

		showPreOrder(node->left, show);
		showPreOrder(node->right, show);
	}

	std::vector<int> getPreOrder()
	{
		if (number_of_elements!=PreOrder_vector.size())
		{
			showPreOrder(top, false);
		}
		return PreOrder_vector;
	}

	void showInOrder(Node* node, bool show = true)
	{
		if (node == nullptr)
		{
			return;
		}

		showInOrder(node->left, show);

		if (show == true)
		{
			std::cout << node->info << " ";
		}
		InOrder_vector.push_back(node->info);

		showInOrder(node->right, show);
	}

	std::vector<int> getInOrder()
	{
		if (number_of_elements != InOrder_vector.size())
		{
			showInOrder(top, false);
		}
		return InOrder_vector;
	}

	void showPostOrder(Node* node, bool show = true)
	{
		if (node == nullptr)
		{
			return;
		}
	
		showPostOrder(node->left, show);
		showPostOrder(node->right, show);

		if (show == true)
		{
			std::cout << node->info << " ";
		}
		PostOrder_vector.push_back(node->info);
	}

	std::vector<int> getPostOrder()
	{
		if (number_of_elements != PostOrder_vector.size())
		{
			showPostOrder(top, false);
		}
		return PostOrder_vector;
	}

	Node* getTop()
	{
		return top;
	}

	Node* getBottom()
	{
		return bottom;
	}

	Node* getParent(Node* node)
	{
		return node->parent;
	}

	Node* getLeftChild(Node* node)
	{
		return node->left;
	}

	Node* getRightChild(Node* node)
	{
		return node->right;
	}
	
};

int main()
{
	Binary_tree b;
	b.reading_elements_using_width_traversal();

	return 0;
}