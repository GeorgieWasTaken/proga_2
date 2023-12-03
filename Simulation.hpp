#pragma once
#define _USE_MATH_DEFINES
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <random>
#include <iomanip> 

#include "Photon.hpp"
#include "Node.hpp"
#include "Quadtree.hpp"

class Simulation
{
public:
	Simulation(int steps_cnt_p, int ph_neighbours_cnt_p, std::string file_path);
	~Simulation() = default;

	void print_results(void);
	void simulate(void);

private:
	int height = 0, width = 0;
	std::vector<std::vector<Node>> area;
	int steps_cnt, ph_neighbours_cnt;
	std::vector<Photon*> photons;
	std::vector<Node*> photon_sources;

	std::uniform_real_distribution<double> rand_angle;
	std::uniform_real_distribution<double> rand_energy;
	std::default_random_engine re;

	int read_from_file(std::string file_path);
	void simulation_step(void);
	void calculate_intensity(void);
	bool bound_check(int x, int y);

};
