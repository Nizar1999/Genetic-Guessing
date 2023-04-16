#pragma once
#include "DNA.h"
#include <memory>
#include <random>

class Population
{
public:
	Population(const std::string& target);
	void mutate();
	DNA& selectPossibleParent();
	void evaluateFitness();
	void breedNewPopulation();
	const std::vector<std::unique_ptr<DNA>>& getPopulation() const;

	int m_maxFitness = 0;
	int m_currentGeneration = 1;
	std::string bestDNA;

private:
	std::vector<std::unique_ptr<DNA>> m_population;
	const float m_mutationRate = 0.01f;
	const int m_populationCount = 300;
	const std::string m_target;

	std::random_device m_rd;
	std::mt19937 m_mt;
};

