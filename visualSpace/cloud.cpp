#include <vector>
#include "point.cpp"

class pointCloud{
public:
    pointCloud(int size = 0){
        points.reserve(size);
    }

    std::vector<Point> getPoints(){
        return points;
    }

    int totalPoints(){
        return points.size();
    }

    bool addPoint(Point newPoint){
        try{
            points.push_back(newPoint);
            return true;
        } catch (int errorCdoe){
            return false;
        }
    }

    bool resetPoints(){
        try{
            points.clear();
        } catch (int errorcode){
            return false;
        }
    }

private:    
    std::vector<Point> points;
};