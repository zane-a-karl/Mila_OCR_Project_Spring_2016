/**
	Class that handles the data files that will be used in the neural net
*/

#ifndef TRAININGDATA_H
#define TRAININGDATA_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

class TrainingData
{
public:
    TrainingData(const std::string filename);
    bool isEof() { return m_trainingDataFile.eof(); }
    void getTopology(std::vector<unsigned> &topology);
    unsigned getNextInputs(std::vector<double> &inputVals);
    unsigned getTargetOutputs(std::vector<double> &targetOutputVals);

private:
    std::ifstream m_trainingDataFile;
};

/**
	Constructor
	Create an object associated with a text data file and open the file
*/
TrainingData::TrainingData(const std::string filename)
{
    m_trainingDataFile.open(filename.c_str());
}

/**
	Get the number of layers and number of neurons per layer for the neural net 
	and store the values in a vector
	@param topology		vector to fill with topology values
*/
void TrainingData::getTopology(std::vector<unsigned> &topology)
{
    std::string line;
    std::string label;

	//topology information will be in first line of data file
    getline(m_trainingDataFile, line);
    std::stringstream ss(line);
    ss >> label;
    if (this->isEof() || label.compare("topology:") != 0) {
        abort();
    }

    while (!ss.eof()) {
        unsigned n;
        ss >> n;
        topology.push_back(n);
    }
    return;
}

/**
	Get inputs from the data file to use in neural net
	@param inputVals	vector of unsigned ints to hold the input values
	@return				the size of the vector once all inputs have been added
*/
unsigned TrainingData::getNextInputs(std::vector<double> &inputVals)
{

    inputVals.clear();

    std::string line;
    getline(m_trainingDataFile, line);
    std::stringstream ss(line);

    std::string label;
    ss >> label;
    if (label.compare("in:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            inputVals.push_back(oneValue);
        }
    }

    return inputVals.size();
}

/**
	Get target output values from the data file
	@param targetOutputVals	vector of unsigned ints to hold output values
	@return					size of the vector once all output values have been added
*/
unsigned TrainingData::getTargetOutputs(std::vector<double> &targetOutputVals)
{
    targetOutputVals.clear();

    std::string line;
    getline(m_trainingDataFile, line);
    std::stringstream ss(line);

    std::string label;
    ss>> label;
    if (label.compare("out:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            targetOutputVals.push_back(oneValue);
        }
    }

    return targetOutputVals.size();
}

/**
	Print the contents of a vector to the console
	@param label	any label given for the output
	@param v		vector holding the values to be printed
*/
void showVectorVals(std::string label, std::vector<double> &v)
{
    std::cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }

    std::cout << std::endl;
}

#endif