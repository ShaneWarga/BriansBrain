#pragma once
#include "GameObject.h"
#include <vector>

class Circle : public GameObject
{
private:
	int radius;
	bool filled;
	std::vector<std::pair<double, double>> points;
public:
	Circle(std::unique_ptr<Vector2> initialPosition, int initRadius, bool fill);
	void Render() override;
	void Update() override;
};

