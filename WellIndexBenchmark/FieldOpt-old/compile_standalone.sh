echo Starting: "/usr/bin/make" clean

cd ERTWrapper/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/ERTWrapper/ERTWrapper.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile clean

rm -f eclgridreader.o eclsummaryreader.o
rm -f *~ core *.core

cd ..

cd Utilities/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/Utilities/Utilities.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile clean


rm -f optimizer.o simulator.o model.o settings.o filehandling.o execution.o
rm -f *~ core *.core

cd ..

cd WellIndexCalculator/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/WellIndexCalculator/WellIndexCalculator.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile clean

rm -f cell.o grid.o ijkcoordinate.o xyzcoordinate.o eclgrid.o geometryfunctions.o line.o squareplane.o well_constraint_projections.o wellindexcalculator.o
rm -f *~ core *.core

cd ..

cd Model/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/Model/Model.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile clean

rm -f model.o well.o reservoir.o cell.o grid.o ijkcoordinate.o xyzcoordinate.o completion.o perforation.o trajectory.o wellspline.o eclgrid.o control.o wellblock.o binary_property.o variable_property_container.o variable_property_handler.o continous_property.o discrete_property.o

rm -f *~ core *.core

cd ..

cd AdgprsResultsReader/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/AdgprsResultsReader/AdgprsResultsReader.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile clean

rm -f json_summary_reader.o adgprs_results_reader.o
rm -f *~ core *.core

cd ..

cd Simulation/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/Simulation/Simulation.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile clean

rm -f simulator.o ecldriverfilewriter.o eclsimulator.o adgprssimulator.o driverpart.o welspecs.o ecldriverpart.o compdat.o wellcontrols.o grid_section.o runspec_section.o props_section.o solution_section.o summary_section.o schedule_section.o eclresults.o adgprsresults.o adgprsdriverfilewriter.o wellstre.o adgprs_wellcontrols.o

rm -f *~ core *.core

cd Optimization/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/Optimization/Optimization.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile clean

rm -f objective.o weightedsum.o case.o case_handler.o constraint.o box_constraint.o constraint_handler.o optimizer.o compass_search.o well_spline_length.o interwell_distance.o well_spline_constraint.o combined_spline_length_interwell_distance.o

rm -f *~ core *.core

cd Runner/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/Runner/Runner.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile clean

rm -f main.o runtime_settings.o main_runner.o abstract_runner.o serial_runner.o logger.o bookkeeper.o
rm -f *~ core *.core

cd ..

echo Starting: "/usr/lib/x86_64-linux-gnu/qt5/bin/qmake"

# /usr/lib/x86_64-linux-gnu/qt5/bin/qmake
/usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/FieldOpt-old.pro \
-r -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug


echo Starting: "/usr/bin/make"

cd ERTWrapper/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/ERTWrapper/ERTWrapper.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile

cd ..

cd Utilities/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/Utilities/Utilities.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile

cd ..

cd WellIndexCalculator/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/WellIndexCalculator/WellIndexCalculator.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile

cd ..

cd Model/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/Model/Model.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile

cd ..

cd AdgprsResultsReader/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/AdgprsResultsReader/AdgprsResultsReader.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile

cd ..

cd Simulation/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/Simulation/Simulation.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile

cd ..

cd Optimization/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake 
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/Optimization/Optimization.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile

cd ..

cd Runner/ && ( test -e Makefile || /usr/lib/x86_64-linux-gnu/qt5/bin/qmake \
	/home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/Runner/Runner.pro \
	-spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o Makefile ) && /usr/bin/make -f Makefile

cd ..

mkdir -p -p /home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/build-FieldOpt-old/AdgprsSummaryConverter ; 
mkdir -p -p /home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/build-FieldOpt-old/execution_scripts ; 
cp -f /home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/Simulation/execution_scripts/*.sh /home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/build-FieldOpt-old/execution_scripts ; 
cp -f /home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/FieldOpt-old/AdgprsSummaryConverter/*.py /home/bellout/git/PCG/FieldOpt-Benchmarks/WellIndexBenchmark/build-FieldOpt-old/AdgprsSummaryConverter/
