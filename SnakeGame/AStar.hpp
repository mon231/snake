/*
    Copyright (c) 2015, Damian Barczynski <daan.net@wp.eu>
    Following tool is licensed under the terms and conditions of the ISC license.
    For more information visit https://opensource.org/licenses/ISC.
*/

#pragma once
#include "Point.hpp"

#include <set>
#include <vector>
#include <optional>
#include <functional>

namespace AStar
{
    using uint = unsigned int;
    using HeuristicFunction = std::function<uint(Point, Point)>;
    using CoordinateList = std::vector<Point>;

    struct Node
    {
        uint G, H;
        Point coordinates;
        Node* parent;

        Node(Point coord_, Node* parent_ = nullptr);
        uint getScore();
    };

    using NodeSet = std::vector<Node*>;

    class Generator
    {
        bool detectCollision(Point coordinates_);
        Node* findNodeOnList(NodeSet& nodes_, Point coordinates_);
        void releaseNodes(NodeSet& nodes_);

    public:
        Generator(uint32_t world_width, uint32_t world_height);
        void setWorldSize(Point worldSize_);
        void setDiagonalMovement(bool enable_);
        void setHeuristic(HeuristicFunction heuristic_);
        std::optional<CoordinateList> findPath(const Point& source_, const Point& target_);
        std::optional<std::vector<Direction>> findPathDirections(const Point& source_, const Point& target_);
        void addCollision(Point coordinates_);
        void removeCollision(Point coordinates_);
        void clearCollisions();

    private:
        HeuristicFunction heuristic;
        CoordinateList direction, walls;
        Point worldSize;
        uint directions;
    };

    class Heuristic
    {
        static Point getDelta(Point source_, Point target_);

    public:
        static uint manhattan(Point source_, Point target_);
        static uint euclidean(Point source_, Point target_);
        static uint octagonal(Point source_, Point target_);
    };
}
