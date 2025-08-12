#pragma once

struct Point{
    float x;
    float y;

    //minimal use case for angle (rads), for placing balls at the end of cannon, didnt know where else to place them
    float angle;

    bool operator ==(const Point &other) const{
        return x == other.x && y ==other.y;
    }
};