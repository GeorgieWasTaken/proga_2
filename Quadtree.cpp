#include "Quadtree.hpp"

double calculate_distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

Quadtree::Quadtree(int height, int width, std::vector<std::vector<Node>> area_p) : area(area_p)
{
	root = new Qt_node;
	root->left_bound = 0;
	root->upper_bound = 0;
	root->right_bound = width;
	root->lower_bound = height;
	root->up_connection = nullptr;

	qt_node_separation(*root);
}

void Quadtree::qt_node_separation(Qt_node& node)
{
	int horizontal_sep = node.lower_bound / 2 + node.upper_bound, vertical_sep = node.right_bound / 2 + node.left_bound;
	if (horizontal_sep >= node.lower_bound || horizontal_sep <= node.upper_bound || vertical_sep >= node.right_bound || vertical_sep <= node.left_bound)
	{
		node.is_leaf = true;
		for (int i = node.upper_bound; i < node.lower_bound; i++)
		{
			for (int j = node.left_bound; j < node.right_bound; j++)
			{
				for (Photon* photon : area[i][j].photons)
				{
					node.photons.push_back(photon);
				}
			}
		}
		return;
	}

	node.is_leaf = false;
	for (int i = 0; i < 4; i++)
	{
		node.branch[i] = new Qt_node;
		node.branch[i]->up_connection = &node;
	}

	node.branch[0]->left_bound = vertical_sep;
	node.branch[0]->right_bound = node.right_bound;
	node.branch[0]->upper_bound = node.upper_bound;
	node.branch[0]->lower_bound = horizontal_sep;

	node.branch[1]->left_bound = node.left_bound;
	node.branch[1]->right_bound = vertical_sep;
	node.branch[1]->upper_bound = node.upper_bound;
	node.branch[1]->lower_bound = horizontal_sep;

	node.branch[2]->left_bound = node.left_bound;
	node.branch[2]->right_bound = vertical_sep;
	node.branch[2]->upper_bound = horizontal_sep;
	node.branch[2]->lower_bound = node.lower_bound;

	node.branch[3]->left_bound = vertical_sep;
	node.branch[3]->right_bound = node.right_bound;
	node.branch[3]->upper_bound = horizontal_sep;
	node.branch[3]->lower_bound = node.lower_bound;

	for (int i = 0; i < 4; i++)
	{
		qt_node_separation(*node.branch[i]);
	}

	node.photons.insert(node.photons.end(), node.branch[0]->photons.begin(), node.branch[0]->photons.end());
	node.photons.insert(node.photons.end(), node.branch[1]->photons.begin(), node.branch[1]->photons.end());
	node.photons.insert(node.photons.end(), node.branch[2]->photons.begin(), node.branch[2]->photons.end());
	node.photons.insert(node.photons.end(), node.branch[3]->photons.begin(), node.branch[3]->photons.end());
}