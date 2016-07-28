/******************************************************************************
 *
 * reservoir.cpp
 *
 * Created: 22.09.2015 2015 by einar
 *
 * This file is part of the FieldOpt project.
 *
 * Copyright (C) 2015-2015 Einar J.M. Baumann <einar.baumann@ntnu.no>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *****************************************************************************/

#include "reservoir.h"
#include "reservoir_exceptions.h"
#include "grid/eclgrid.h"
#include <iostream>

namespace Model {
namespace Reservoir {

Reservoir::Reservoir(Utilities::Settings::Model::Reservoir reservoir_settings)
{
    if (reservoir_settings.path.length() == 0)
        throw std::runtime_error("The path to a reservoir grid file must be "
                                 "specified in the FieldOpt driver file, or "
                                 "be passed as a command line parameter.");

    if (reservoir_settings.type ==
            ::Utilities::Settings::Model::ReservoirGridSourceType::ECLIPSE){

        std::cout << "Reservoir::defining Grid object...(start)" << std::endl;
        grid_ = new Grid::ECLGrid(reservoir_settings.path);
    }
    else throw ReservoirTypeNotRecognizedException();
}

}
}
