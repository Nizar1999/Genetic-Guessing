#include "pch.h"
#include "DNA.h"
#include "Population.h"

TEST(GeneticGuessing, encode_word) {
	DNA dna;
	std::string word = "word";

	dna.encode(word);

	EXPECT_EQ(4, dna.getEncodedInformation().size());
	EXPECT_EQ(std::vector<char>(begin(word), end(word)), dna.getEncodedInformation());
}

TEST(GeneticGuessing, mutate_dna)
{
	DNA dna;
	std::string word = "word";

	dna.encode(word);
	dna.mutate(1.0f);

	EXPECT_EQ(4, dna.getEncodedInformation().size());
	EXPECT_NE(std::vector<char>(begin(word), end(word)), dna.getEncodedInformation());
}

TEST(GeneticGuessing, crossover_dna)
{
	DNA parentA;
	DNA parentB;

	std::string word1 = "toma";
	std::string word2 = "pled";

	parentA.encode(word1);
	parentB.encode(word2);

	DNA child;
	child.encode(parentA, parentB);

	EXPECT_EQ(std::vector<char>({'t', 'o', 'e', 'd'}), child.getEncodedInformation());
}

TEST(GeneticGuessing, crossover_then_mutate_dna)
{
	DNA parentA;
	DNA parentB;

	std::string word1 = "toma";
	std::string word2 = "pled";

	parentA.encode(word1);
	parentB.encode(word2);

	DNA child;
	child.encode(parentA, parentB);
	child.mutate(1.0f);

	EXPECT_NE(std::vector<char>({'t', 'o', 'e', 'd'}), child.getEncodedInformation());
}

TEST(GeneticGuessing, evaluate_fitness_to_zero_of_target)
{
	DNA dna;
	std::string word = "fitness";
	dna.encode(word);

	EXPECT_EQ(0, dna.evaluateFitness("ssesift"));
}

TEST(GeneticGuessing, evaluate_fitness_to_half_of_target)
{
	DNA dna;
	std::string word = "fitness";
	dna.encode(word);

	EXPECT_EQ(9, dna.evaluateFitness("fitsift"));
}

TEST(GeneticGuessing, evaluate_fitness_to_all_of_target)
{
	DNA dna;
	std::string word = "fitness";
	dna.encode(word);

	EXPECT_EQ(49, dna.evaluateFitness("fitness"));
}

TEST(GeneticGuessing, dna_init)
{
	DNA dna;
	dna.init(5);
	EXPECT_EQ(5, dna.getEncodedInformation().size());
}

TEST(GeneticGuessing, population_generation)
{
	std::string word = "tigers";
	Population pop(word);

	EXPECT_EQ(300, pop.getPopulation().size());
	for (auto& dna : pop.getPopulation())
	{
		EXPECT_EQ(word.size(), dna->getEncodedInformation().size());
	}
}

TEST(GeneticGuessing, population_select_parent)
{
	std::string word = "tigers";
	Population pop(word);

	pop.evaluateFitness();
	const DNA& parent = pop.selectPossibleParent();
	EXPECT_TRUE(pop.m_maxFitness >= parent.evaluateFitness(word));
}
