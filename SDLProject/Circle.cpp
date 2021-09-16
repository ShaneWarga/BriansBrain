#include "Circle.h"


Circle::Circle(std::unique_ptr<Vector2> initialPosition, int initRadius, bool fill) {
	position = std::move(initialPosition);
	radius = initRadius;
    filled = fill;
    objectColor = std::unique_ptr<ColorData>(new ColorData());
}

void Circle::Render() {
    const int diameter = (radius * 2);
    points.clear();
    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    SDL_SetRenderDrawColor(mRenderer, objectColor.get()->RED, objectColor.get()->GREEN, objectColor.get()->BLUE, objectColor.get()->ALPHA);

    while (x >= y)
    {
        points.push_back(std::pair<double, double>(position.get()->x + x, position.get()->y - y));
        points.push_back(std::pair<double, double>(position.get()->x + x, position.get()->y + y));
        points.push_back(std::pair<double, double>(position.get()->x - x, position.get()->y - y));
        points.push_back(std::pair<double, double>(position.get()->x - x, position.get()->y + y));
        points.push_back(std::pair<double, double>(position.get()->x + y, position.get()->y - x));
        points.push_back(std::pair<double, double>(position.get()->x + y, position.get()->y + x));
        points.push_back(std::pair<double, double>(position.get()->x - y, position.get()->y - x));
        points.push_back(std::pair<double, double>(position.get()->x - y, position.get()->y + x));

        if (!filled) {
            for (auto point : points) {
                SDL_RenderDrawPoint(mRenderer, point.first, point.second);
            }
        }
        else {
            //  Each of the following renders an octant of the circle
            for (auto point : points) {
                    SDL_RenderDrawLine(mRenderer, position->x, position->y, point.first, point.second);
            }
        }
        
        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }

}

void Circle::Update() {
    return;
}