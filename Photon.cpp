#include "Photon.hpp"

Photon::Photon(double angle_p, double energy_p) : v_angle(angle_p), energy(energy_p)
{
	;
}

void Photon::horizontal_refl(void)
{
	v_angle = 2 * M_PI - v_angle;
}

void Photon::vertical_refl(void)
{
	v_angle = M_PI - v_angle;
	if (v_angle < 0)
	{
		v_angle += 2 * M_PI;
	}
}

void Photon::diagonal_refl(void)
{
	v_angle += M_PI;
	if (v_angle > 2 * M_PI)
	{
		v_angle -= 2 * M_PI;
	}
}

void Photon::stuck(void)
{
	end_of_life = true;
}

Photon* Photon::half_stuck(void)
{
	energy = energy / 2;
	Photon* new_ph = new Photon(v_angle, energy);
	new_ph->x = x;
	new_ph->y = y;
	new_ph->end_of_life = true;
	return new_ph;
}
