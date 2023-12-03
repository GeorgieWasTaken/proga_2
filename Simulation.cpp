#include "Simulation.hpp"

Simulation::Simulation(int steps_cnt_p, int ph_neighbours_cnt_p, std::string file_path) : steps_cnt(steps_cnt_p), ph_neighbours_cnt(ph_neighbours_cnt_p)
{
	read_from_file(file_path);
	rand_angle = std::uniform_real_distribution<double>(0.0, 2 * M_PI);
	rand_energy = std::uniform_real_distribution<double>(1, 10);
}

int Simulation::read_from_file(std::string file_path)
{
	srand(time(NULL));

	std::fstream file(file_path);
	std::string str;

	int i = 0;
	Node mem;
	width = 0;
	while (true)
	{
		str = "";
		file >> str;
		if (str.empty())
			break;
		if (width == 0)
			width = str.size();
		else if (str.size() != width)
			return -1; //incorrect shape of area
		
		area.push_back(std::vector<Node>());
		for (int j = 0; j < str.size(); j++)
		{
			mem.y = i;
			mem.x = j;
			switch (str[j])
			{
			case '.':
				mem.type = 0;
				break;
			case 'K':
				mem.type = 1;
				break;
			case 'R':
				mem.type = 2;
				break;
			default:
				return -2; //incorrect value
				break;
			}
			
			area[i].push_back(mem);
		}
		i++;
	}
	height = i;

	for (int k = 0; k < height; k++)
	{
		for (int j = 0; j < width; j++)
		{
			if (area[k][j].type == 2)
			{
				photon_sources.push_back(&area[k][j]);
			}
		}
	}

	return 0;
}

bool Simulation::bound_check(int x, int y)
{
	return x < 0 || y < 0 || x >= width || y >= height || area[y][x].type == 1;
}

void Simulation::simulation_step(void)
{
	//new photons generation
	for (Node* src : photon_sources)
	{
		for (int i = 0; i < rand() % 4 + 1; i++)
		{
			photons.push_back(new Photon(rand_angle(re), rand_energy(re)));
			src->photons.insert(photons.back());
			photons.back()->x = src->x;
			photons.back()->y = src->y;
		}
	}

	//photons travel
	int dest_x, dest_y, mem_x, mem_y;
	Photon* photon;
	for (int i = 0; i < photons.size(); i++)
	{
		photon = photons[i];
		if (photon->is_dead())
			continue;

		dest_x = photon->x;
		dest_y = photon->y;
		area[photon->y][photon->x].photons.erase(photon);

		for (int distance = 0;; distance++)
		{
			mem_x = dest_x;
			mem_y = dest_y;
			
			//lookahead
			dest_x = (int)(round(cos(photon->get_angle()) * distance)) + photon->x;
			dest_y = (int)(round(sin(photon->get_angle()) * distance)) + photon->y;

			//reflection (3 variants) / travel
			if (bound_check(dest_x, dest_y))
			{
				photon->x = mem_x;
				photon->y = mem_y;
				area[photon->y][photon->x].photons.insert(photon);
				
				switch (rand() % 3)
				{
				case 0:
					//full reflection
					if ((dest_x != mem_x && dest_y == mem_y) || (dest_x != mem_x && dest_y != mem_y && bound_check(dest_x, mem_y)))
					{
						photon->vertical_refl();
					}
					else if ((dest_x == mem_x && dest_y != mem_y) || (dest_x != mem_x && dest_y != mem_y && bound_check(mem_x, dest_y)))
					{
						photon->horizontal_refl();
					}
					else
					{
						photon->diagonal_refl();
					}
					break;
				case 1:
					//half reflection
					photons.push_back(photon->half_stuck());
					area[photon->y][photon->x].photons.insert(photons.back());
					if ((dest_x != mem_x && dest_y == mem_y) || (dest_x != mem_x && dest_y != mem_y && bound_check(dest_x, mem_y)))
					{
						photon->vertical_refl();
					}
					else if ((dest_x == mem_x && dest_y != mem_y) || (dest_x != mem_x && dest_y != mem_y && bound_check(mem_x, dest_y)))
					{
						photon->horizontal_refl();
					}
					else
					{
						photon->diagonal_refl();
					}
					break;
				case 2:
					//stuck on a place
					photon->stuck();
					break;
				}
				break;
			}
		}
	}
}

void Simulation::calculate_intensity(void)
{
	Quadtree quadtree(height, width, area);
	std::vector<Photon*> k_nearest;

	for (int i = 0; i < area.size(); i++)
	{
		for (int j = 0; j < area[i].size(); j++)
		{
			//quadtree
			//<I> = sum(Ik)/max(rk)		
		}
	}
}



void Simulation::simulate(void)
{
	for (int i = 0; i < steps_cnt; i++)
	{
		simulation_step();
	}
	calculate_intensity();
}

void Simulation::print_results(void)
{
	for (std::vector<Node> line : area)
	{
		for (Node node : line)
		{
			if (node.type == 1)
			{
				std::cout << std::setw(15) << "K";
				continue;
			}
			std::cout << std::setw(15) << node.intensity;
		}
		std::cout << std::endl;
	}
}
