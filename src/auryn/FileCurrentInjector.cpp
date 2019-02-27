/* 
* Copyright 2014-2018 Friedemann Zenke
*
* This file is part of Auryn, a simulation package for plastic
* spiking neural networks.
* 
* Auryn is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Auryn is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Auryn.  If not, see <http://www.gnu.org/licenses/>.
*
* If you are using Auryn or parts of it for your work please cite:
* Zenke, F. and Gerstner, W., 2014. Limits to high-speed simulations 
* of spiking neural networks using general-purpose computers. 
* Front Neuroinform 8, 76. doi: 10.3389/fninf.2014.00076
*/

#include "FileCurrentInjector.h"

using namespace auryn;

FileCurrentInjector::FileCurrentInjector(NeuronGroup * target, std::string neuron_state_name, AurynFloat initial_current ) : Device( )
{
	auryn::sys->register_device(this);
	dst = target;

	set_target_state(neuron_state_name);
	currents = new AurynVectorFloat(dst->get_vector_size()); 

	currents->set_all( initial_current );
	alpha = auryn_timestep;
}



void FileCurrentInjector::free( ) 
{
	delete currents;
}


FileCurrentInjector::~FileCurrentInjector()
{
	free();
}

void FileCurrentInjector::execute()
{
	if ( dst->evolve_locally() ) {
		target_vector->saxpy(alpha, currents);
	}
}

void FileCurrentInjector::set_current(NeuronID i, AurynFloat current) {
	currents->set(i, current);
}

void FileCurrentInjector::set_all_currents(AurynFloat current) {
	currents->set_all(current);
}

void FileCurrentInjector::set_target_state(std::string state_name) {
	target_vector = dst->get_state_vector(state_name);
}

