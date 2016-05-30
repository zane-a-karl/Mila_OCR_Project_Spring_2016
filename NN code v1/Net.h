/**
	Neural Net Simulator adapted from David Miller's 'Make a Neural Net Simulator in C++'
	video tutorial. Comments are my own and were added for clarification
*/

#ifndef NET_H
#define NET_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <cmath>
#include "Neuron.h"

class Neuron;

//create alias for std::vector<Neuron> type
typedef std::vector<Neuron> Layer;

class Net {
public:
	Net(const std::vector<unsigned> &topology);
	void feedForward(const std::vector<double> &inputVals);
	void backProp(const std::vector<double> &targetVals);
	void getResults(std::vector<double> &resultVals) const;
	double getRecentAverageError() const { return m_recentAverageError; }
private:
	std::vector<Layer> m_layers; //m_layers[layerNum][neuronNum]
	double m_error;
	double m_recentAverageError;
	static double m_recentAverageSmoothingFactor;
};

double Net::m_recentAverageSmoothingFactor = 100.0; //Number of training samples to average over

/**
	Constructor
	@param topology		size of this vector = # of layers in the net
*/
Net::Net(const std::vector<unsigned> &topology) {
	unsigned numLayers = topology.size();

	for(unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
		m_layers.push_back(Layer()); // Push back an std::vector<Neuron>
		unsigned numOutputs = layerNum == topology.size()-1 ? 0 : topology[layerNum + 1];
		// Now that we have a layer, fill it with neurons and add a bias neuron in each layer
		for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
			m_layers.back().push_back(Neuron(numOutputs, neuronNum));
			std::cout << "Made a Neuron!" << std::endl;
		}
		// Set the bias neuron's weight to 1
		m_layers.back().back().setOutputVal(1.0);
	}
}

/**
	Forward propagation - send inputs through the neural net to generate the 
	output activations
*/
void Net::feedForward(const std::vector<double> &inputVals) {
		// Make sure # inputs matches # neurons that were created
		assert(inputVals.size() == m_layers[0].size() - 1);

		// Add input values to each neuron
		for(unsigned i = 0; i < inputVals.size(); ++i) {
			m_layers[0][i].setOutputVal(inputVals[i]);
		}

		// Forward propagation
		for(unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) {
			Layer &prevLayer = m_layers[layerNum - 1];
			for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n) {
				m_layers[layerNum][n].feedForward(prevLayer); 
			}
		}
}

/**
	Backward propagation - go back through the neural net using the target values
	to generate delta, difference between target output and actual output
*/
void Net::backProp(const std::vector<double> &targetVals) {
		// Calculate overall net error - root mean square error
		Layer &outputLayer = m_layers.back();
		m_error = 0.0; 

		for(unsigned n = 0; n < outputLayer.size() - 1; ++n) {
			double delta = targetVals[n] - outputLayer[n].getOutputVal();
			m_error += delta * delta;
		}
		// m_error is now the sum of the squares of the error

		m_error /= outputLayer.size() - 1; //divide by number of values summed
		m_error = sqrt(m_error); //take sqrt to get root mean square

		// Use this to output a value to help us know how well the NN is being trained
		m_recentAverageError = 
			(m_recentAverageError * m_recentAverageSmoothingFactor + m_error)
			/ (m_recentAverageSmoothingFactor + 1.0);

		// Output of layer gradients
		for(unsigned n = 0; n < outputLayer.size() - 1; ++n) {
			outputLayer[n].calcOutputGradients(targetVals[n]);
		}

		// Hidden layers
		for(unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum) {
			Layer &hiddenLayer = m_layers[layerNum];
			Layer &nextLayer = m_layers[layerNum + 1];

			for(unsigned n = 0; n < hiddenLayer.size(); ++n) {
				hiddenLayer[n].calcHiddenGradients(nextLayer);
			}
		}

		// Update connection weights for the layers from output to first hidden layer
		for(unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum) {
			Layer &layer = m_layers[layerNum];
			Layer &prevLayer = m_layers[layerNum - 1];

			for(unsigned n = 0; n < layer.size() - 1; ++n) {
				layer[n].updateInputWeights(prevLayer);
			}
		}
}

/**
	Add the results of training to a vector
	@param resultVals	vector to add result values to
*/
void Net::getResults(std::vector<double> &resultVals) const {
		resultVals.clear();

		for(unsigned n = 0; n < m_layers.back().size() - 1; ++n) {
			resultVals.push_back(m_layers.back()[n].getOutputVal());
		}
}



#endif

