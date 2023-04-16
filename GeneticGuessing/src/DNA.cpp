#include "DNA.h"
#include <assert.h>

DNA::DNA() : m_mt(m_rd())
{
}

void DNA::init(int size)
{
	std::uniform_int_distribution<int> randomGene(MIN_GENE, MAX_GENE);		
	
	std::string result;
	for (int i = 0; i < size; ++i)
	{
		result += static_cast<char>(randomGene(m_mt));
	}
	encode(result);
}

void DNA::encode(const std::string& word)
{
	m_encodedInformation.clear();
    m_encodedInformation = std::vector<char>(word.begin(), word.end());
}

void DNA::encode(const DNA& parentA, const DNA& parentB)
{
	const std::vector<char>& word1 = parentA.getEncodedInformation();
	const std::vector<char>& word2 = parentB.getEncodedInformation();

	assert(word1.size() == word2.size());

	m_encodedInformation.clear();

	auto spliceIndex = static_cast<int>(word1.size() / 2);
	
	for (int i = 0; i < word1.size(); ++i)
	{
		if (i < spliceIndex)
		{
			m_encodedInformation.push_back(word1[i]);
		}
		else
		{
			m_encodedInformation.push_back(word2[i]);
		}
	}
}

const std::vector<char>& DNA::getEncodedInformation() const
{
    return m_encodedInformation;
}

void DNA::mutate(float mutationRate)
{
	std::uniform_real_distribution<float> willMutate(0.0f, 1.0f);
	std::uniform_int_distribution<int> randomMutation(MIN_GENE, MAX_GENE);

	for (auto& segment : m_encodedInformation)
	{
		if (willMutate(m_mt) <= mutationRate)
		{
			char mutation;
			do
			{
				mutation = static_cast<char>(randomMutation(m_mt));
			} while (mutation == segment);
			segment = mutation;
		}
	}
}

int DNA::evaluateFitness(const std::string& target) const
{
	assert(target.size() == m_encodedInformation.size());

	int fitness = 0;

	for (int i = 0; i < target.size(); ++i)
	{
		if (target[i] == m_encodedInformation[i])
		{
			fitness++;
		}
	}

	fitness = pow(fitness, 2);

	return fitness;
}
