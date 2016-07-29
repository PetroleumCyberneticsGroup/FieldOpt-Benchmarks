/******************************************************************************
 *
 *
 *
 * Created: 16.12.2015 2015 by einar
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

#ifndef ABSTRACTRUNNER_H
#define ABSTRACTRUNNER_H

#include "runtime_settings.h"
#include "Model/model.h"
#include "Optimization/optimizer.h"
#include "Optimization/case.h"
#include "Optimization/objective/objective.h"
#include "Simulation/simulator_interfaces/simulator.h"
#include "Utilities/settings/settings.h"
#include "bookkeeper.h"

namespace Runner {

class MainRunner;

/*!
 * \brief The AbstractRunner class is the abstract parent class for all runners. It should only be constructed by the MainRunner class.
 *
 * This class initializes the primary objects needed and provides some utility functions for logging.
 *
 * It also defines the purely virtual Execute() method which should be implemented by all concrete
 * runners.
 */
class AbstractRunner
{
    friend class MainRunner;
private:

    /*!
     * \brief Execute starts the actual optimization run and should not return until the optimization is done.
     */
    virtual void Execute() = 0;

protected:
    AbstractRunner(RuntimeSettings *runtime_settings);

    Bookkeeper *bookkeeper_;
    Model::Model *model_;
    Utilities::Settings::Settings *settings_;
    RuntimeSettings *runtime_settings_;
    Optimization::Case *base_case_;
    Optimization::Optimizer *optimizer_;
    Optimization::Objective::Objective *objective_function_;
    Simulation::SimulatorInterfaces::Simulator *simulator_;

    /*!
     * \brief setObjectiveFunctionSentinelValue Sets the objective function value to a sentinel value.
     *
     * Should be called when the case is invalid.
     *
     * If the ongoing run is maximization, the objective function value will be set to DBL_MIN; if
     * it is minimization, the value will be set to DBL_MAX.
     * \param c
     */
    void setObjectiveFunctionSentinelValue(Optimization::Case *c);

//    void printBaseCaseCompdat();

};

}

#endif // ABSTRACTRUNNER_H
