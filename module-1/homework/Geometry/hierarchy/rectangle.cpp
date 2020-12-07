#include "rectangle.h"

Rectangle::Rectangle(Point a, Point b, double& ratio) {
<<<<<<< HEAD
    if (a.y < b.y) {
        std::swap(a.x, b.x);
        std::swap(a.y, b.y);
    }
    if (a.x > b.x) {
        this->vertices.push_back(a);
        this->vertices.push_back(Point(b.x, a.y));
        this->vertices.push_back(b);
        this->vertices.push_back(Point(a.x, b.y));
    }
    else {
        this->vertices.push_back(a);
        this->vertices.push_back(Point(a.x, b.y));
        this->vertices.push_back(b);
        this->vertices.push_back(Point(b.x, a.y));
    }
    this->k = ratio;
}
Rectangle::Rectangle() {
    for (int i = 0; i < 2; i++) {
        this->vertices.push_back(Point(0, 0));
    }
}
Point Rectangle::center() {
    Point result;
    for (int i = 1; i <= 3; i++) {
        if (this->vertices[0].y == this->vertices[i].y) {
            result.x = fabs(this->vertices[0].x == this->vertices[i].x) / 2.0;
        }
        if (this->vertices[0].x == this->vertices[i].x) {
            result.y = fabs(this->vertices[0].y == this->vertices[i].y) / 2.0;
        }
    }
    return result;
}
std::pair<Line, Line> Rectangle::diagonals() {
    std::pair<Line, Line> result;
    int count_changes = 0;
    for (int i = 0; i < 4 && count_changes != 2; i++) {
        for (int j = i + 1; j < 4 && count_changes != 2; j++) {
            bool eqv_x = (this->vertices[i].x != this->vertices[j].x);
            bool eqv_y = (this->vertices[i].y != this->vertices[j].y);
            if (eqv_x && eqv_y) {
                result.first.first_point = this->vertices[i];
                result.first.second_point = this->vertices[j];
                count_changes++;
            }
        }
    }
    return result;
=======
	if (a.y < b.y) {
		std::swap(a.x, b.x);
		std::swap(a.y, b.y);
	}
	if (a.x > b.x) {
		this->vertices.push_back(a);
		this->vertices.push_back(Point(b.x, a.y));
		this->vertices.push_back(b);
		this->vertices.push_back(Point(a.x, b.y));
	}
	else {
		this->vertices.push_back(a);
		this->vertices.push_back(Point(a.x, b.y));
		this->vertices.push_back(b);
		this->vertices.push_back(Point(b.x, a.y));
	}
	this->k = ratio;
}
Rectangle::Rectangle() {
	for (int i = 0; i < 2; i++) {
		this->vertices.push_back(Point(0, 0));
	}
}
Point Rectangle::center()
{
	Point result;
	for (int i = 1; i <= 3; i++) {
		if (this->vertices[0].y == this->vertices[i].y) {
			result.x = fabs(this->vertices[0].x == this->vertices[i].x) / 2.0;
		}
		if (this->vertices[0].x == this->vertices[i].x) {
			result.y = fabs(this->vertices[0].y == this->vertices[i].y) / 2.0;
		}
	}
	return result;
}
std::pair<Line, Line> Rectangle::diagonals()
{
	std::pair<Line, Line> result;
	int count_changes = 0;
	for (int i = 0; i < 4 && count_changes != 2; i++) {
		for (int j = i + 1; j < 4 && count_changes != 2; j++) {
			if (this->vertices[i].x != this->vertices[j].x && this->vertices[i].y != this->vertices[j].y)
			{
				result.first.first_point = this->vertices[i];
				result.first.second_point = this->vertices[j];
				count_changes++;
			}
		}
	}
	return result;
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
}
