/**
	Neural Net Simulator adapted from David Miller's 'Make a Neural Net Simulator in C++'
	video tutorial. Comments are my own and were added for clarification
*/

#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

struct Connection {
	double weight;
	// for any given weight, we want change in weight: error * input
	double deltaWeight;
};

class Neuron;

typedef std::vector<Neuron> Layer;

class Neuron {
public:
	Neuron(unsigned numOutputs, unsigned myIndex);
	void setOutputVal(double val) { m_outputVal = val; }
	double getOutputVal() const { return m_outputVal; }
	void feedForward(const Layer &prevLayer);
	void calcOutputGradients(double targetVal); 
	void calcHiddenGradients(const Layer &nextLayer);
	void updateInputWeights(Layer &prevLayer);
private:
	static double eta; 
	static double alpha;
	static double transferFunction(double x) {
		// hyperbolic tangent - range [-1,1]
		return tanh(x);
	}
	static double transferFunctionDerivative(double x) {
		// hyperbolic tangent derivative
		return 1.0 - x*x;
	}
	double sumDOW(const Layer & nextLayer) const;
	static double randomWeight() { return rand()/double(RAND_MAX); }
	double m_outputVal;
	std::vector<Connection> m_outputWeights;
	unsigned m_myIndex;
	double m_gradient;
};


double Neuron::eta = 0.15;    // overall net learning rate, [0.0..1.0]
double Neuron::alpha = 0.5;   // momentum, multiplier of last deltaWeight, [0.0..1.0]

Neuron::Neuron(unsigned numOutputs, unsigned myIndex) {
	for(unsigned c = 0; c < numOutputs; ++c) {
		m_outputWeights.push_back(Connection()); 
		m_outputWeights.back().weight = randomWeight();
	}
	m_myIndex = myIndex;
}

void Neuron::calcOutputGradients(double targetVal) {
		double delta = targetVal - m_outputVal;
		m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::calcHiddenGradients(const Layer &nextLayer)
{
    double dow = sumDOW(nextLayer);
    m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::updateInputWeights(Layer &prevLayer) {
	for(unsigned n = 0; n < prevLayer.size(); ++n) {
			Neuron &neuron = prevLayer[n];


			double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

			double newDeltaWeight = 
				eta
				* neuron.getOutputVal()
				* m_gradient
				+ alpha
				* oldDeltaWeight;
			neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
			neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
		}
}

void Neuron::feedForward(const Layer &prevLayer) {
	double sum = 0.0;
		//loop thorugh all nodes in prev layer - inputs * connection weights
		for(unsigned n = 0; n < prevLayer.size(); ++n) {
			sum += prevLayer[n].getOutputVal() *
				prevLayer[n].m_outputWeights[m_myIndex].weight;
		}

		m_outputVal = Neuron::transferFunction(sum);
}

double Neuron::sumDOW(const Layer & nextLayer) const {
	double sum = 0.0;

		for(unsigned n = 0; n < nextLayer.size() - 1; ++n) {
			sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
		}
		return sum;
}

#endif 