#include "polygon.h"


Polygon::Polygon(const std::vector<Point>& m){
    for(auto i : m) this->getVertices.push_back(i);
}

int Polygon::verticesCount() const{
    return (getVertices.size());
}

bool Polygon::isConvex() const{
    bool convex = true;
    for(int i = 0; i < getVertices.size(); i++){
        convex *= isConvexv(Vector(getVertices[i], getVertices[(i+1) % getVertices.size()]),
        Vector(getVertices[i], getVertices[(i+2) % getVertices.size()]));
        
    }
    return convex;
};

double Polygon::perimeter() const{
    double ans = 0;
    for(int i = 0; i < getVertices.size(); i++){
        ans += Vector(getVertices[i], getVertices[(i+1)&getVertices.size()]).lengh();
    }
    return ans;
};

double Polygon::area() const{
    double ans = 0;
    for(int i = 0; i < getVertices.size(); i++){
        int d = (i+1)%getVertices.size();
        ans += (getVertices[i].x * getVertices[d].y - getVertices[d].x * getVertices[i].y);
    }
    ans/=2;
    if (ans<0) ans*=-1.0;
    return ans;
}

bool Polygon::operator==(const Shape& another) const{
    const auto* another2 = dynamic_cast<const Polygon*>(&another);
    if (this->verticesCount() != another2->verticesCount()) return false;
    bool ans = 0;
    for(int i = 0; i < getVertices.size(); i++){
        if (another2->getVertices[0] == this->getVertices[i]){
            int h = 0;
            ans = 1;
            for(int j = i; j < i+getVertices.size(); j++){
                if (getVertices[j%getVertices.size()] != another2->getVertices[h]){
                    ans = 0;
                }
                h++;
            }
            if (ans) break;
            ans = 1;
            h = 0;
            for(int j = i; j >= 0; j--){
                if (getVertices[j%getVertices.size()] != another2->getVertices[h]){
                    ans = 0;
                }
                h++;
            }
            for(int j = getVertices.size()-1; j > getVertices.size() - i; j--){
                if (getVertices[j%getVertices.size()] != another2->getVertices[h]){
                    ans = 0;
                }
                h++;
            }
        }
    }
    return ans;   
}

bool Polygon::isCongruentTo(const Shape& another) const{
    const auto* another2 = dynamic_cast<const Polygon*>(&another);
    if (this->verticesCount() != another2->verticesCount()) return false;
    bool ans = 0;
    for(int i = 0; i < getVertices.size(); i++){
        if (another2->getVertices[0] == this->getVertices[i]){
            int h = 0;
            ans = 1;
            for(int j = i; j < i+getVertices.size(); j++){
                if (getVertices[j%getVertices.size()] != another2->getVertices[h]){
                    ans = 0;
                }
                h++;
            }
            if (ans) break;
            ans = 1;
            h = 0;
            for(int j = i; j >= 0; j--){
                if (getVertices[j%getVertices.size()] != another2->getVertices[h]){
                    ans = 0;
                }
                h++;
            }
            for(int j = getVertices.size()-1; j > getVertices.size() - i; j--){
                if (getVertices[j%getVertices.size()] != another2->getVertices[h]){
                    ans = 0;
                }
                h++;
            }
        }
    }
    return ans;   
}

bool Polygon::isSimilarTo(const Shape& another) const{
    const auto* another2 = dynamic_cast<const Polygon*>(&another);
    if (this->verticesCount() != another2->verticesCount()) return false;
    bool ans = 1;
    double dif = Vector(getVertices[getVertices.size()-1], getVertices[0]).lengh() /
     Vector(another2->getVertices[getVertices.size()-1], another2->getVertices[0]).lengh();
    for(int i = 0; i < getVertices.size()-1; i++){
        if (Vector(getVertices[i], getVertices[i+1]).lengh() /
     Vector(another2->getVertices[i], another2->getVertices[i+1]).lengh() != dif) ans = 0;
    }
    return ans;   
}

bool Polygon::containsPoint(const Point& another) const{
    int convex = 0;
    for(int i = 0; i < getVertices.size(); i++){
        int d = (i+1) % getVertices.size();
        if ((getVertices[i].x > another.x) || (getVertices[d].x > another.x) &&
        (((getVertices[i].y > another.y) || (getVertices[d].y < another.y)) ||
        ((getVertices[i].y < another.y) || (getVertices[d].y > another.y)))){
            convex++;
        }
    }
    return convex;
}

Shape& Polygon::rotate(const Point& center, const double& angle){
    const auto* another2 = dynamic_cast<const Polygon*>(this);
    double rad = angle * pi / 180.0;
    for(int i = 0; i < getVertices.size(); i++){
        Vector g2;
        Vector g = Vector(getVertices[i], center);
        g2.x = g.x*cos(rad) - g.y*sin(rad);
        g2.y = g.x*sin(rad) + g.y*cos(rad);
        getVertices[i].x=g2.x;
        getVertices[i].y=g2.y;
    }
    return *this;
}

Shape& Polygon::reflex(const Point& center) {
    this->rotate(center, 180);
    return *this;
}

Shape& Polygon::reflex(const Line& axis){
    for (int i = 0; i < getVertices.size(); i++) {
		Point proj = axis.getProjection(getVertices[i]);
		getVertices[i] += (proj - getVertices[i]) * 2;
	}
	return *this;
}

Shape& Polygon::scale(const Point& center, const double& coefficient){
    for (int i = 0; i < getVertices.size(); i++) {
		getVertices[i] = (getVertices[i] - center) * coefficient;
	}
	return *this;
}