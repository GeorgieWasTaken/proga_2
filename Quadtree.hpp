#pragma once
#include "Photon.hpp"
#include "Node.hpp"
#include <vector>

struct Qt_node
{
	Qt_node* branch[4];
	Qt_node* up_connection;
	bool is_leaf;
	int upper_bound, lower_bound, right_bound, left_bound;
	std::vector<Photon*> photons;
};

class Quadtree
{
public:
	Quadtree(int height, int width, std::vector<std::vector<Node>> area_p);
	~Quadtree() = default;

private:
	Qt_node* root;
	std::vector<std::vector<Node>> area;

	void qt_node_separation(Qt_node& node);

};