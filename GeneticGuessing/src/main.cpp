#include "Population.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "main.h"

void printResults(Population& pop)
{
	system("cls");
	std::cout << "Generation: " << pop.m_currentGeneration << std::endl
		<< "Best DNA: " << pop.bestDNA << std::endl
		<< "Best Fitness: " << pop.m_maxFitness << std::endl << std::endl;

	for (auto& dna : pop.getPopulation())
	{
		auto& ss = dna->getEncodedInformation();
		std::string ds = std::string(ss.begin(), ss.end());
		std::cout << ds << std::endl;
	}

	pop.evaluateFitness();
	pop.breedNewPopulation();
}

int main()
{
	std::string secret;
	std::cout << "Secret: ";
	std::getline(std::cin, secret);

	Population pop(secret);

	while (pop.m_currentGeneration < 1000 && pop.bestDNA != secret)
	{
		printResults(pop);
		pop.evaluateFitness();
		pop.breedNewPopulation();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	printResults(pop);
	return 0;
}