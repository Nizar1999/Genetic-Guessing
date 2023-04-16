#include "Population.h"

Population::Population(const std::string& target) : m_target(target), m_mt(m_rd())
{	
	for (int i = 0; i < m_populationCount; ++i)
	{
		auto dna = std::make_unique<DNA>();
		dna->init(static_cast<int>(target.size()));
		m_population.push_back(std::move(dna));
	}
}

const std::vector<std::unique_ptr<DNA>>& Population::getPopulation() const
{
	return m_population;
}

void Population::mutate() 
{
	for (auto& dna : m_population)
	{
		dna->mutate(m_mutationRate);
	}
}

DNA& Population::selectPossibleParent() 
{

	std::uniform_int_distribution<int> indices(0, m_populationCount-1);
	while (true)
	{
		int index = indices(m_mt);
		DNA& parent = *m_population[index];


		std::uniform_int_distribution<int> fitness(0, m_maxFitness);
		int randomFitness = fitness(m_mt);

		if (randomFitness <= parent.evaluateFitness(m_target))
		{
			return parent;
		}
	}

}

void Population::evaluateFitness()
{
	for (const auto& dna : m_population)
	{
		int fitness = dna->evaluateFitness(m_target);
		if (m_maxFitness < fitness)
		{
			auto& ss = dna->getEncodedInformation();
			bestDNA = std::string(ss.begin(), ss.end());
			m_maxFitness = fitness;
		}
	}
}

void Population::breedNewPopulation()
{
	std::vector<std::unique_ptr<DNA>> newPopulation;
	for (int i = 0; i < m_populationCount; ++i)
	{
		const DNA& parentA = selectPossibleParent();
		const DNA& parentB = selectPossibleParent();

		auto child = std::make_unique<DNA>();
		child->encode(parentA, parentB); //crossover function
		child->mutate(m_mutationRate);
		newPopulation.push_back(std::move(child));
	}

	m_population.clear();
	for (int i = 0; i < m_populationCount; ++i)
	{
		m_population.push_back(std::move(newPopulation[i]));
	}
	++m_currentGeneration;
}
