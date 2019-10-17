#include "Agent.h"



Agent::Agent()
{
	window = new sf::RenderWindow(sf::VideoMode(width, height), "GA");

	for (int i = 0; i < city_count; i++)
	{
		Point point;
		sf::Vector2f pos;
		pos.x = rand() % width;
		pos.y = rand() % height;
		point.setPos(pos);
		cities.push_back(point);
	}
}

void Agent::gameLoop()
{
	generate_seed_populations();


	while (window->isOpen())
	{
		for(int i = 0; i < ITERATIONS; i++)
			GA();

		sf::Event evnt;
		while (window->pollEvent(evnt))
		{
			switch (evnt.type)
			{
				case sf::Event::Closed:
					window->close();
					break;
			}
		}

		window->clear();

		float radius = 10;
		for (auto p : cities)
		{
			sf::CircleShape circle;
			circle.setRadius(radius);
			circle.setPosition(p.getPos());
			circle.setFillColor(sf::Color::White);
			window->draw(circle);
		}
		std::vector<sf::Vertex> city_points;
		for (int i = 0; i < bestState.points.size(); i++) {
			sf::Vertex city;
			city.position = sf::Vector2f(cities[bestState.points[i]].getPos().x + radius, cities[bestState.points[i]].getPos().y + radius);
			city_points.push_back(city);
			city.color = sf::Color::Red;
		}
		sf::Vertex city2;
		city2.position = sf::Vector2f(cities[bestState.points[0]].getPos().x + radius, cities[bestState.points[0]].getPos().y + radius);
		city_points.push_back(city2);

		window->draw(&city_points[0], city_points.size(), sf::LineStrip);
		window->display();

	}
}

template<class T>
inline void Agent::shuffle_array(std::vector<T>& arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		std::swap(arr[rand() % arr.size()], arr[rand() % arr.size()]);
	}
}


void Agent::generate_seed_populations()
{

	std::vector<int> order;
	for (int i = 0; i < cities.size(); i++)order.push_back(i);
	population = new State[population_n];
	for (int i = 0; i < population_n; i++)
	{
		shuffle_array(order);
		State state;
		state.points = order;
		population[i] = state;
	}

}

void Agent::GA()
{
	
	updateFitness();
	normalizeFitness();
	nextGeneration();
}

void Agent::calculateFitness(State & state)
{
	float dist = 0;
	for (int i = 0; i < state.points.size() - 1; i++)
	{
		dist += getDist(cities[state.points[i]].getPos(), cities[state.points[i + 1]].getPos());
	}
	dist += getDist(cities[state.points[0]].getPos(), cities[state.points[state.points.size() - 1]].getPos());
	state.fitness = 1.0f / dist;
}

void Agent::normalizeFitness()
{
	float sum = 0;

	for (int i = 0; i < population_n; i++)
	{
		sum += population[i].fitness; 
	}

	for (int i = 0; i < population_n; i++)
	{
		population[i].fitness = population[i].fitness / sum * 100;
	}
}
 
void Agent::updateFitness()
{
	for (int i = 0; i < population_n; i++)
	{
		calculateFitness(population[i]);
		if (1.0f / population[i].fitness < bestFitness)
		{
			bestFitness = 1.0f / population[i].fitness;
			bestState = population[i];
		}
	}
}

void Agent::nextGeneration()
{
	State *newPopulation = new State[population_n];

	for (int i = 0; i < population_n; i++)
	{
		State order = crossOver(pickOne(), pickOne());
	
		mutate(order.points, 8.0f);
		newPopulation[i] = order;
	}

	for (int i = 0; i < population_n; i++)
		population[i] = newPopulation[i];

	delete[]newPopulation;
}

void Agent::mutate(std::vector<int>& arr, float mutation_rate)
{
	if (rand() % 100 > mutation_rate) return;

	int index1 = rand() % arr.size();
	int index2 = index1 + 1 > arr.size() - 1 ? index1 - 1 : index1 + 1;
	std::swap(arr[index1], arr[index2]);

}

State Agent::crossOver(const State &a, const State &b)
{
	
	int start = rand() % a.points.size();
	int l = rand() % a.points.size() - start;

	std::vector<int> order;

	while (l > 0)
	{
		order.push_back(a.points[start] );
		start++;

		l--;
	}
	for (auto & p : b.points)
	{
		bool exist = false;
		for (auto &another : order)
		{
			if (another == p)
			{
				exist = true;
				break;
			}
		}

		if (!exist)
		{
			order.push_back(p);
		}
	}

	State newState;
	newState.fitness = 0;
	newState.points = order;
	return newState;
}

State Agent::pickOne()
{
	int index = 0;
	float r = rand() % 99 + 1;
	
	while (r > 0)
	{
		r = r - population[index].fitness;
		index++;
	}
	index--;

	return population[index];
}

