#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <float.h>
#include <vector>
#include "Point.h"
#include "State.h"

class Agent
{
public:
	Agent();
	void gameLoop();

private:
	std::vector<Point> cities;
	template<class T>
	inline void shuffle_array(std::vector<T>& arr);

	void generate_seed_populations();
	const int city_count = 40;
	 
	sf::RenderWindow* window = nullptr;
	const int ITERATIONS = 10000;
	const int height = 800;
	const int width = 800;
	const int population_n = 200;

	State bestState;
	float bestFitness = FLT_MAX;
	State* population = nullptr;

	float getDist(sf::Vector2f a, sf::Vector2f b)
	{
		return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
	} 
	void GA();
	void calculateFitness(State & state);
	void normalizeFitness();
	void updateFitness();
	void nextGeneration();
	void mutate(std::vector<int> &order, float mutation_rate);

	State crossOver(const State &a, const State &b);

	State pickOne();

};


