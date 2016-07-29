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

#include "abstract_runner.h"
#include "Optimization/optimizers/compass_search.h"
#include "Optimization/objective/weightedsum.h"
#include "Simulation/simulator_interfaces/eclsimulator.h"
#include "Simulation/simulator_interfaces/adgprssimulator.h"

#include <limits>

#include "Utilities/file_handling/filehandling.h"
#include "Simulation/simulator_interfaces/driver_file_writers/adgprsdriverfilewriter.h"
#include "Simulation/simulator_interfaces/driver_file_writers/driver_parts/driverpart.h"
#include "Simulation/simulator_interfaces/driver_file_writers/driver_parts/ecl_driver_parts/compdat.h"

namespace Runner {

AbstractRunner::AbstractRunner(RuntimeSettings *runtime_settings)
{
    //Initialize settings
    std::cout << "Initializing settings..." << std::endl;
    runtime_settings_ = runtime_settings;
    settings_ = new Utilities::Settings::Settings(runtime_settings->driver_file(),
                                                  runtime_settings->output_dir());
    settings_->set_verbosity(runtime_settings_->verbose());

    // Override simulator driver and grid file paths if the have been passed as command line arguments
    if (runtime_settings->simulator_driver_path().length() > 0)
        settings_->simulator()->set_driver_file_path(runtime_settings->simulator_driver_path());
    if (runtime_settings->grid_file_path().length() > 0)
        settings_->model()->set_reservoir_grid_path(runtime_settings->grid_file_path());

    // Initialize model
    std::cout << "Initializing model..." << std::endl;
    model_ = new Model::Model(*settings_->model());

    // Initialize simulator
    std::cout << "Initializing simulator..." << std::endl;
    switch (settings_->simulator()->type()) {
    case ::Utilities::Settings::Simulator::SimulatorType::ECLIPSE:
        if (runtime_settings_->verbose()) std::cout << "Using ECL100 reservoir simulator." << std::endl;
        simulator_ = new Simulation::SimulatorInterfaces::ECLSimulator(settings_, model_);
        break;
    case ::Utilities::Settings::Simulator::SimulatorType::ADGPRS:
        if (runtime_settings_->verbose()) std::cout << "Using ADGPRS reservoir simulator." << std::endl;
        simulator_ = new Simulation::SimulatorInterfaces::AdgprsSimulator(settings_, model_);
        break;
    default:
        throw std::runtime_error("Unable to initialize runner: simulator set in driver file not recognized.");
    }

    // Evaluate the base case if not already done.
    if (!simulator_->results()->isAvailable()) {
        if (runtime_settings_->verbose()) std::cout << "Simulating base case." << std::endl;
        simulator_->Evaluate();
    }

    // Initialize objective function
    switch (settings_->optimizer()->type()) {
    case Utilities::Settings::Optimizer::ObjectiveType::WeightedSum:
        if (runtime_settings->verbose()) std::cout << "Using WeightedSum-type objective function." << std::endl;
        objective_function_ = new Optimization::Objective::WeightedSum(settings_->optimizer(), simulator_->results());
        break;
    default:
        throw std::runtime_error("Unable to initialize runner: objective function type not recognized.");
    }

    base_case_ = new Optimization::Case(model_->variables()->GetBinaryVariableValues(),
                                        model_->variables()->GetDiscreteVariableValues(),
                                        model_->variables()->GetContinousVariableValues());
    base_case_->set_objective_function_value(objective_function_->value());
    if (runtime_settings_->verbose()) std::cout << "Base case objective function value set to: " << base_case_->objective_function_value() << std::endl;




    // Print base case id to log_compdat file
    std::cout << "Printing out base case UUID" << std::endl;
    QString out_string = "--UUID (abstract_runner.cpp):\nUUID: " + base_case_->id().toString();
    QString file_path_out = "/home/bellout/git/PCG/FieldOpt/examples/test-ADGPRS-5SPOT_WPLC-A";
    Utilities::FileHandling::WriteLineToFile(out_string, file_path_out + "/log_compdat.out");

    // Print compdat to log_compdat file
//    Utilities::FileHandling::WriteLineToFile(compdat.GetPartString(),
//    "/home/bellout/git/PCG/FieldOpt/examples/test-ADGPRS-5SPOT_WPLC/log_compdat.out");




    // Initialize optimizer
    switch (settings_->optimizer()->type()) {
    case Utilities::Settings::Optimizer::OptimizerType::Compass:
        if (runtime_settings_->verbose()) std::cout << "Using CompassSearch optimization algorithm." << std::endl;
        optimizer_ = new Optimization::Optimizers::CompassSearch(settings_->optimizer(), base_case_, model_->variables());
        break;
    default:
        throw std::runtime_error("Unable to initialize runner: optimization algorithm set in driver file not recognized.");
        break;
    }

    bookkeeper_ = new Bookkeeper(settings_, optimizer_->case_handler());
}


//void AbstractRunner::printBaseCaseCompdat()
//{
//    namespace DriverParts {
    // Get compdat data from model
//    auto compdat = DriverParts::ECLDriverParts::Compdat(model_->wells());
//    }
//}



void AbstractRunner::setObjectiveFunctionSentinelValue(Optimization::Case *c)
{
    if (settings_->optimizer()->mode() == Utilities::Settings::Optimizer::OptimizerMode::Minimize)
        c->set_objective_function_value(std::numeric_limits<double>::max());
    if (settings_->optimizer()->mode() == Utilities::Settings::Optimizer::OptimizerMode::Maximize)
        c->set_objective_function_value(std::numeric_limits<double>::min());
}

}
