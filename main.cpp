#include <iostream>
#include <string>
#include "Simulation.hpp"

int main(void)
{
	int steps_cnt, ph_neighbours_cnt;
	std::string txt_path = "matrix.txt";

	std::cout << "Enter the amount of steps to simulate: ";
	std::cin >> steps_cnt;
	std::cout << "Enter the amount of nearest photons to calculate node intensity: ";
	std::cin >> ph_neighbours_cnt;
	
	Simulation simulation(steps_cnt, ph_neighbours_cnt, txt_path);
	simulation.simulate();
	simulation.print_results();

	return 0;
}