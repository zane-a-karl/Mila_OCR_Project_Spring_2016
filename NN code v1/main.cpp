/**
	Neural Net Simulator adapted from David Miller's 'Make a Neural Net Simulator in C++'
	video tutorial. Comments are my own and were added for clarification
*/

#include <vector>
#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <cmath>
#include "Net.h"
#include "Neuron.h"
#include "TrainingData.h"

int main() {
	
	TrainingData trainData("trainingData.txt");

    std::vector<unsigned> topology;
    trainData.getTopology(topology);

    Net myNet(topology);

    std::vector<double> inputVals, targetVals, resultVals;
    int trainingPass = 0;

    while (!trainData.isEof()) {
        ++trainingPass;
        std::cout << std::endl << "Pass " << trainingPass;

        // Check whether # of input values = # of nodes assigned in topology
        if (trainData.getNextInputs(inputVals) != topology[0]) {
            break;
        }
        showVectorVals(": Inputs:", inputVals);
        myNet.feedForward(inputVals);

        // Collect the net's actual output results
        myNet.getResults(resultVals);
        showVectorVals("Outputs:", resultVals);

        // Train the net 
        trainData.getTargetOutputs(targetVals);
        showVectorVals("Targets:", targetVals);
        assert(targetVals.size() == topology.back());

        myNet.backProp(targetVals);

        // Report how well the training is working
		// Averages over recent samples
        std::cout << "Net recent average error: "
                << myNet.getRecentAverageError() << std::endl;
	
    }

    std::cout << std::endl << "Done" << std::endl;

	system("PAUSE");
}