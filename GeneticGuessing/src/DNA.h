#pragma once
#include <string>
#include <vector>
#include <random>

class DNA
{
public:
	DNA();
	void init(int size);
	void encode(const std::string& word);
	void encode(const DNA& parentA, const DNA& parentB);
	const std::vector<char>& getEncodedInformation() const;
	void mutate(float mutationRate);
	int evaluateFitness(const std::string& target) const;

private:
	std::vector<char> m_encodedInformation;
	std::random_device m_rd;
	std::mt19937 m_mt;
	
	//32-126 being the range of acceptable ascii symbols
	const int MIN_GENE = 32;
	const int MAX_GENE = 126;
};

