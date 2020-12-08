#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include <utility> // std::pair
#include "ortools/linear_solver/linear_solver.h"
#include "include/json.hpp"
using JSON = nlohmann::json;

typedef std::vector<std::pair<std::string, std::vector<float>>> DATA;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


float getDataFromJSON(int progID, std::string parameter)
{
	std::string path = "bin/";
	path.append("program_");
	path.append(std::to_string(progID));
	path.append(".json");

	float result = 0;

	//Read json file from disk
    std::string line;
    std::ifstream r_file(path.c_str());
    std::getline(r_file, line);
    r_file.close();

	//Append data and create string
    JSON old_content = JSON::parse(line);

	result = old_content[0][parameter];

	return result;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void updateProgramsJSON(int progID, float dataToUpdate, std::string parameter)
{
	std::cout << "FOR: " << parameter << '\n';

	std::string path = "bin/";
	path.append("program_");
	path.append(std::to_string(progID));
	path.append(".json");

	//Read json file from disk
    std::string line;
    std::ifstream r_file(path.c_str());    
    std::getline(r_file, line);
    r_file.close();

	//Append data and create string
    JSON old_content = JSON::parse(line);

	std::cout << old_content[0] << '\n';
	old_content[0][parameter] = dataToUpdate;
	std::cout << old_content[0] << '\n';

	std::string data_w = old_content.dump();
    //Write in disk
	std::ofstream resources_file(path.c_str());
	resources_file << data_w << std::endl;
	resources_file.close();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


std::vector<int> optAssignResources(float core_require, float core_available, int progID)
{
	int priority_level = 1; // Current priority level
	const int MAX_PRIORITY_LEVEL = 3; // Max priority level to achieve

	std::vector<int> result; // Result vector

	// Cores Upper bound definition
	float x_UB = (core_require > core_available) ? core_available : core_require;

	// Priorities results
	float x_result_1, y_result_1, x_result_2, y_result_2, x_result_3, y_result_3;
	x_result_1 = y_result_1 = x_result_2 = y_result_2 = x_result_3 = y_result_3 = 0;

	// deviation variables results
	float dneg_3_result, dpos_3_result, dneg_2_result, dpos_2_result, dpos_1_result, dneg_1_result;
	dneg_3_result = dpos_3_result = dneg_2_result = dpos_2_result = dpos_1_result = dneg_1_result = 0;

	// Functions coefficients, factors and goals
	// F1
	float x_coef_1 = 1/core_available;
	float y_coef_1 = -1/(core_available*5);
	float goal1 = core_require/core_available;
	// F2
	float x_coef_2 = 1/(core_available*2);
	float y_coef_2 = 1/10;
	float goal2 = core_require/core_available;
	// F3
	float lambda = 1;
	float x_coef_3 = 1;
	float y_coef_3 = 1;

	float goal3_1 = 0;
	float goal3 = 0;
	// Deviation variables coefficients
	float dneg_3_coef, dpos_3_coef, dneg_2_coef, dpos_2_coef, dpos_1_coef, dneg_1_coef;
	dneg_3_coef = dpos_3_coef = dneg_2_coef = dpos_2_coef = dpos_1_coef = dneg_1_coef = 1;

	while(priority_level <= MAX_PRIORITY_LEVEL) {
		if(priority_level == 3)
		{
			// Create the linear solver with the GLOP backend
			operations_research::MPSolver solver("Solver_f1", operations_research::MPSolver::GLOP_LINEAR_PROGRAMMING);

			// Create the objective function
			operations_research::MPObjective* const objective = solver.MutableObjective();

			// Infinity representation constant
			const double infinity = solver.infinity();

			// Create the desition variables with their respective constraints
			operations_research::MPVariable* const x = solver.MakeNumVar(0.0, x_UB, "x"); // Cores
			operations_research::MPVariable* const y = solver.MakeNumVar(1.0, 5.0, "y"); // Mem priority
			operations_research::MPVariable* const dneg_1 = solver.MakeNumVar(0.0, infinity, "dneg_1"); // Negative deviation variable f1
			operations_research::MPVariable* const dpos_1 = solver.MakeNumVar(0.0, infinity, "dpos_1"); // Positive deviation variable f1
			operations_research::MPVariable* const dneg_2 = solver.MakeNumVar(dneg_2_result, dneg_2_result, "dneg_2"); // Negative deviation variable f2
			operations_research::MPVariable* const dpos_2 = solver.MakeNumVar(0.0, infinity, "dpos_2"); // Positive deviation variable f2
			operations_research::MPVariable* const dneg_3 = solver.MakeNumVar(0.0, infinity, "dneg_3"); // Negative deviation variable f3
			operations_research::MPVariable* const dpos_3 = solver.MakeNumVar(dpos_3_result, dpos_3_result, "dpos_3"); // Positive deviation variable f3

			// Funcion restriction
			operations_research::MPConstraint* const ct1 = solver.MakeRowConstraint(goal1, goal1, "ct1");
			ct1->SetCoefficient(x, x_coef_1);
			ct1->SetCoefficient(y, y_coef_1);
			ct1->SetCoefficient(dneg_1, dneg_1_coef);
			ct1->SetCoefficient(dpos_1, -dpos_1_coef);

			operations_research::MPConstraint* const ct2 = solver.MakeRowConstraint(goal2, goal2, "ct2");
			ct2->SetCoefficient(x, x_coef_2);
			ct2->SetCoefficient(y, y_coef_2);
			ct2->SetCoefficient(dneg_2, dneg_2_coef);
			ct2->SetCoefficient(dpos_2, -dpos_2_coef);

			operations_research::MPConstraint* const ct3 = solver.MakeRowConstraint(goal3, goal3, "ct3");
			ct3->SetCoefficient(x, x_coef_3);
			ct3->SetCoefficient(y, y_coef_3);
			ct3->SetCoefficient(dneg_3, dneg_3_coef);
			ct3->SetCoefficient(dpos_3, -dpos_3_coef);

			// Objective function
			objective->SetCoefficient(dpos_1, dpos_1_coef);
			objective->SetCoefficient(x, 0);
			objective->SetCoefficient(y, 0);
			objective->SetCoefficient(dneg_1, 0);
			objective->SetMinimization();

			// Solve
			solver.Solve();

			// Assign result values
			y_result_1 = y->solution_value();
			x_result_1 = x->solution_value();
			dpos_1_result = dpos_1->solution_value();

			// Update total execution time
			float total_time = getDataFromJSON(progID, "TotalExecTime");
			float new_time = total_time + x_coef_1*x_result_1 + y_coef_1*y_result_1;
			updateProgramsJSON(progID, new_time, "TotalExecTime");
		}
			
		else if (priority_level == 2)
		{
			// Create the linear solver with the GLOP backend
			operations_research::MPSolver solver("Solver_f2", operations_research::MPSolver::GLOP_LINEAR_PROGRAMMING);

			// Create the objective function
			operations_research::MPObjective* const objective = solver.MutableObjective();

			// Infinity representation constant
			const double infinity = solver.infinity();

			// Create the desition variables with their respective constraints
			operations_research::MPVariable* const x = solver.MakeNumVar(0.0, x_UB, "x"); // Cores
			operations_research::MPVariable* const y = solver.MakeNumVar(1.0, 5.0, "y"); // Mem priority
			operations_research::MPVariable* const dneg_2 = solver.MakeNumVar(0.0, infinity, "dneg_2"); // Negative eviation variable f2
			operations_research::MPVariable* const dpos_2 = solver.MakeNumVar(0.0, infinity, "dpos_2"); // Positive deviation variable f2
			operations_research::MPVariable* const dneg_3 = solver.MakeNumVar(0.0, infinity, "dneg_3"); // Negative deviation variable f3
			operations_research::MPVariable* const dpos_3 = solver.MakeNumVar(dpos_3_result, dpos_3_result, "dpos_3"); // Positive deviation variable f3

			//float result_f3 = (x_coef_3)*(x_result_3) + (y_coef_3)*(y_result_3);

			// Funcion restriction
			operations_research::MPConstraint* const ct1 = solver.MakeRowConstraint(goal2, goal2, "ct1");
			ct1->SetCoefficient(x, x_coef_2);
			ct1->SetCoefficient(y, y_coef_2);
			ct1->SetCoefficient(dneg_2, dneg_2_coef);
			ct1->SetCoefficient(dpos_2, -dpos_2_coef);

			operations_research::MPConstraint* const ct2 = solver.MakeRowConstraint(goal3, goal3, "ct2");
			ct2->SetCoefficient(x, x_coef_3);
			ct2->SetCoefficient(y, y_coef_3);
			ct2->SetCoefficient(dneg_3, dneg_3_coef);
			ct2->SetCoefficient(dpos_3, -dpos_3_coef);

			// Objective function
			objective->SetCoefficient(dneg_2, dneg_2_coef);
			objective->SetCoefficient(x, 0);
			objective->SetCoefficient(y, 0);
			objective->SetCoefficient(dpos_2, 0);
			objective->SetMinimization();

			// Solve
			solver.Solve();

			// Assign result values
			y_result_2 = y->solution_value();
			x_result_2 = x->solution_value();
			dneg_2_result = dneg_2->solution_value();
		}
		else if(priority_level == 1)
		{
			// Create the linear solver with the GLOP backend
			operations_research::MPSolver solver("Solver_f3", operations_research::MPSolver::GLOP_LINEAR_PROGRAMMING);

			// Create the objective function
			operations_research::MPObjective* const objective = solver.MutableObjective();

			// Infinity representation constant
			const double infinity = solver.infinity();

			// Create the desition variables with their respective constraints
			operations_research::MPVariable* const x = solver.MakeNumVar(0.0, x_UB, "x"); // Cores
			operations_research::MPVariable* const y = solver.MakeNumVar(1.0, 5.0, "y"); // Mem priority
			operations_research::MPVariable* const dneg_3 = solver.MakeNumVar(0.0, infinity, "dneg_3"); // Negative deviation variable f3
			operations_research::MPVariable* const dpos_3 = solver.MakeNumVar(0.0, infinity, "dpos_3"); // Positive deviation variable f3
			
			lambda = getDataFromJSON(progID, "lambda");
			goal3_1 = ( lambda == 0 ? 0 : ( (core_available/core_require) >= 5 ? 5 : std::floor(core_available/core_require) ) ); // Computational resources from mem priority term
			goal3 = std::round(core_require*lambda) + goal3_1;

			// Funcion restriction
			operations_research::MPConstraint* const ct1 = solver.MakeRowConstraint(goal3, goal3, "ct1");
			ct1->SetCoefficient(x, x_coef_3);
			ct1->SetCoefficient(y, y_coef_3);
			ct1->SetCoefficient(dneg_3, dneg_3_coef);
			ct1->SetCoefficient(dpos_3, -dpos_3_coef);

			// Objective function
			objective->SetCoefficient(dpos_3, dpos_3_coef);
			objective->SetCoefficient(x, 0);
			objective->SetCoefficient(y, 0);
			objective->SetCoefficient(dneg_3, 0);
			objective->SetMinimization();

			// Solve
			solver.Solve();

			// Assign result values
			y_result_3 = y->solution_value();
			x_result_3 = x->solution_value();
			dpos_3_result = dpos_3->solution_value();

			// Update lambda factor
			float total_time = getDataFromJSON(progID, "TotalExecTime");
			float new_lambda = lambda - (0.002*total_time);
			float l = (new_lambda >= 0) ? new_lambda : 0;
			updateProgramsJSON(progID, l, "lambda");
		}

		priority_level += 1;
	}

	// Build result vector
	int x_result_1_int = (int) std::ceil(x_result_1);
	int y_result_1_int = (int) std::ceil(y_result_1);

	result.push_back(x_result_1_int);
	result.push_back(y_result_1_int);

	return result;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void write_csv_files(DATA dataset_cores, DATA dataset_priority)
{
	// Creating CSV file stream
	std::ofstream csv_cores("csv_cores__l0.002.csv");
	std::ofstream csv_priorities("csv_priorities_l0.002.csv");

	// Send columns names to the stream
	for(int j = 0; j < dataset_cores.size(); ++j) {
		csv_cores << dataset_cores.at(j).first;
		csv_priorities << dataset_priority.at(j).first;

		if(j != dataset_cores.size() - 1) {
			csv_cores << ";";
			csv_priorities << ";";
		}
	}
	csv_cores << "\n";
	csv_priorities << "\n";

	// Send data names to the stream
	for(int i = 0; i < dataset_cores.at(0).second.size(); i++) {
		for(int j = 0; j < dataset_cores.size(); j++) {
			csv_cores << dataset_cores.at(j).second.at(i);
			csv_priorities << dataset_priority.at(j).second.at(i);

			if(j != dataset_cores.size() - 1) {
				csv_cores << ";";
				csv_priorities << ";";
			}
		}
		csv_cores << "\n";
		csv_priorities << "\n";
	}

	// Close the files
	csv_cores.close();
	csv_priorities.close();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	// Parameters to edit
	int iterations = 1;                     // Ccurrent iteration
	const int MAX_ITERATIONS = 50;		    // Max number of iterations
	const float ca = 25;				    // Cores available value

	// Variables
	float cr = 1;						    // Cores require value
	std::vector<float> cores_assigned;	    // Cores assigned vector
	std::vector<float> cores_require;	    // Cores available vector
	std::vector<float> priorities_assigned; // Priorities asigned vector

	while(iterations <= MAX_ITERATIONS) {
		// Calling the optimization function
		std::vector<int> result = optAssignResources(cr, ca, 0);

		// Filling vectors
		cores_assigned.push_back(result[0]);
		priorities_assigned.push_back(result[1]);
		cores_require.push_back(cr);

		cr++;							    // Increase core require

		iterations++;                       // Increase iteration
	}

	// Build vector for creating CSV file
	DATA dataset_cores = {{"core require", cores_require}, {"core assigned", cores_assigned}};
	DATA dataset_priority = {{"core require", cores_require}, {"priority assigned", priorities_assigned}};

	// Write CSV files
	write_csv_files(dataset_cores, dataset_priority);

	return 0;
}