#pragma once
#include "Photon.hpp"
#include <set>

struct Node
{
	int type; // 0 - empty, 1 - K(wall), 2 - R(photon source)
	double intensity = 0;
	int x, y; //coordinates
	std::set<Photon*> photons;
};