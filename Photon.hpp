#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

class Photon
{
public:
	Photon(double angle_p, double energy_p);
	~Photon() = default;

	void horizontal_refl(void);
	void vertical_refl(void);
	void diagonal_refl(void);
	void stuck(void);
	Photon* half_stuck(void);

	double get_angle(void) { return v_angle; };
	double get_energy(void) { return energy; };
	bool is_dead(void) { return end_of_life; };
	int x, y;

private:
	double v_angle; 
	double energy;

	bool end_of_life = false;

};