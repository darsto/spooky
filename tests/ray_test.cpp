//
// Created by dar on 12/18/15.
//

#include <core/Ray.h>
#include "gtest/gtest.h"

struct RayTest : testing::Test {
    Ray *ray;

    RayTest() { }

    virtual ~RayTest() {
        delete this->ray;
    }
};

struct project_data {
    double x;
    double y;
    double angle;
    double maxDist;
    std::function<bool(int, int)> doesCollide;

    double final_x;
    double final_y;
    double final_dist;
    bool final_wall_type;

    friend std::ostream &operator<<(std::ostream &os, const project_data &obj) {
        os << " x: " << obj.x;
        os << " y: " << obj.y;
        os << " angle: " << obj.angle;
        os << " finalX: " << obj.final_x;
        os << " finalY: " << obj.final_y;
        os << " finalDist: " << obj.final_dist;
        return os;
    }

    project_data copy() {
        return project_data {x, y, angle, maxDist, doesCollide, final_x, final_y, final_dist, final_wall_type};
    }
};

struct RayProjectTest : RayTest, testing::WithParamInterface<project_data> {
    RayProjectTest() {
        auto par = GetParam();
        this->ray = projectRay(par.x, par.y, par.angle, par.maxDist, par.doesCollide);
    }
};

TEST_P(RayProjectTest, projectRayTest) {
    auto par = GetParam();
    EXPECT_EQ(par.final_x, (int) (this->ray->getCompX() * 100) / 100.0);
    EXPECT_EQ(par.final_y, (int) (this->ray->getCompY() * 100) / 100.0);
    EXPECT_EQ(par.final_dist, (int) (this->ray->getDistance() * 100) / 100.0);
    EXPECT_EQ(par.final_wall_type, this->ray->getBreakingWallType());
}

std::vector<project_data> projectRayTestValues() {
    std::vector<project_data> vector;
    project_data data[3];

    char map_bl[] =
        {'X', 'X', 'X', 'X', 'X', ' ',
         'X', ' ', ' ', 'X', 'X', ' ',
         'X', ' ', ' ', 'X', ' ', ' ',
         'X', ' ', 'X', 'X', ' ', 'X',
         'X', 'X', 'X', ' ', ' ', 'X',
         'X', 'X', 'X', 'X', ' ', 'X'};

    auto doesCollide = [=](int x, int y) {
        return x < 0 || x >= 6 || y < 0 || y >= 6 || map_bl[y * 6 + x] == 'X';
    };

    data[0].doesCollide = data[1].doesCollide = data[2].doesCollide = doesCollide;

    data[0].x = 1.5;
    data[0].y = 1.5;
    data[0].angle = 0;
    data[0].maxDist = 5;
    data[0].final_x = 1.5;
    data[0].final_y = 0;
    data[0].final_dist = 1.5;
    data[0].final_wall_type = BREAKING_WALL_VERTICAL;
    vector.push_back(data[0]);

    data[1].x = 1.5;
    data[1].y = 1.5;
    data[1].angle = 0;
    data[1].maxDist = 5;
    data[1].angle = M_PI_2 * 3;
    data[1].final_x = 0;
    data[1].final_y = 2.5;
    data[1].final_dist = 2.5;
    data[1].final_wall_type = BREAKING_WALL_HORIZONTAL;
    vector.push_back(data[1]);

    data[2].x = 4;
    data[2].y = 3;
    data[2].angle = M_PI_4;
    data[2].maxDist = 5;
    data[2].final_x = 2;
    data[2].final_y = -1.99;
    data[2].final_dist = 2.82;
    data[2].final_wall_type = BREAKING_WALL_VERTICAL;
    vector.push_back(data[2]);

    return vector;
}

INSTANTIATE_TEST_CASE_P(Default, RayProjectTest, testing::ValuesIn(projectRayTestValues()));