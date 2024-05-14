#include "AStar.hpp"
#include <algorithm>
#include <math.h>

using namespace std::placeholders;

AStar::Node::Node(Point coordinates_, Node* parent_) :
    coordinates(coordinates_),
    parent(parent_)
{
    G = H = 0;
}

AStar::uint AStar::Node::getScore()
{
    return G + H;
}

AStar::Generator::Generator(const uint32_t world_width, const uint32_t world_height) :
    direction({
        Point{ 0, 1 }, Point{ 1, 0 }, Point{ 0, -1 }, Point{ -1, 0 },
        Point{ -1, -1 }, Point{ 1, 1 }, Point{ -1, 1 }, Point{ 1, -1 }
        }),
    worldSize{ static_cast<int32_t>(world_width), static_cast<int32_t>(world_height) }
{
    setDiagonalMovement(false);
    setHeuristic(&Heuristic::manhattan);
}

void AStar::Generator::setWorldSize(Point worldSize_)
{
    worldSize = worldSize_;
}

void AStar::Generator::setDiagonalMovement(bool enable_)
{
    directions = (enable_ ? 8 : 4);
}

void AStar::Generator::setHeuristic(HeuristicFunction heuristic_)
{
    heuristic = std::bind(heuristic_, _1, _2);
}

void AStar::Generator::addCollision(Point coordinates_)
{
    walls.push_back(coordinates_);
}

void AStar::Generator::removeCollision(Point coordinates_)
{
    auto it = std::find(walls.begin(), walls.end(), coordinates_);
    if (it != walls.end()) {
        walls.erase(it);
    }
}

void AStar::Generator::clearCollisions()
{
    walls.clear();
}

std::optional<std::vector<Direction>> AStar::Generator::findPathDirections(const Point& source_, const Point& target_)
{
    std::vector<Direction> path_directions;
    const auto path_points = findPath(source_, target_);

    if (!path_points.has_value())
    {
        return std::nullopt;
    }

    for (size_t i = path_points->size() - 1; i >= 1 ; --i)
    {
        const Point movement_vector = path_points->at(i - 1) - path_points->at(i);
        path_directions.push_back(Point::get_direction_from_vector(movement_vector));
    }

    return path_directions;
}

std::optional<AStar::CoordinateList> AStar::Generator::findPath(const Point& source_, const Point& target_)
{
    Node* current = nullptr;
    NodeSet openSet, closedSet;
    openSet.reserve(100);
    closedSet.reserve(100);
    openSet.push_back(new Node(source_));

    while (!openSet.empty()) {
        auto current_it = openSet.begin();
        current = *current_it;

        for (auto it = openSet.begin(); it != openSet.end(); it++) {
            auto node = *it;
            if (node->getScore() <= current->getScore()) {
                current = node;
                current_it = it;
            }
        }

        if (current->coordinates == target_) {
            break;
        }

        closedSet.push_back(current);
        openSet.erase(current_it);

        for (uint i = 0; i < directions; ++i) {
            Point newCoordinates(current->coordinates + direction[i]);
            if (detectCollision(newCoordinates) ||
                findNodeOnList(closedSet, newCoordinates)) {
                continue;
            }

            uint totalCost = current->G + ((i < 4) ? 10 : 14);

            Node* successor = findNodeOnList(openSet, newCoordinates);
            if (successor == nullptr) {
                successor = new Node(newCoordinates, current);
                successor->G = totalCost;
                successor->H = heuristic(successor->coordinates, target_);
                openSet.push_back(successor);
            }
            else if (totalCost < successor->G) {
                successor->parent = current;
                successor->G = totalCost;
            }
        }
    }

    CoordinateList path;
    while (current != nullptr) {
        path.push_back(current->coordinates);
        current = current->parent;
    }

    releaseNodes(openSet);
    releaseNodes(closedSet);

    if (path.front() != target_)
    {
        return std::nullopt;
    }

    return path;
}

AStar::Node* AStar::Generator::findNodeOnList(NodeSet& nodes_, Point coordinates_)
{
    for (auto node : nodes_) {
        if (node->coordinates == coordinates_) {
            return node;
        }
    }
    return nullptr;
}

void AStar::Generator::releaseNodes(NodeSet& nodes_)
{
    for (auto it = nodes_.begin(); it != nodes_.end();) {
        delete* it;
        it = nodes_.erase(it);
    }
}

bool AStar::Generator::detectCollision(Point coordinates_)
{
    if (coordinates_.get_x() < 0 || coordinates_.get_x() >= worldSize.get_x() ||
        coordinates_.get_y() < 0 || coordinates_.get_y() >= worldSize.get_y() ||
        std::find(walls.begin(), walls.end(), coordinates_) != walls.end()) {
        return true;
    }
    return false;
}

Point AStar::Heuristic::getDelta(Point source_, Point target_)
{
    return Point{ abs(source_.get_x()  - target_.get_x()),  abs(source_.get_y() - target_.get_y()) };
}

AStar::uint AStar::Heuristic::manhattan(Point source_, Point target_)
{
    auto delta = std::move(getDelta(source_, target_));
    return static_cast<uint>(10 * (delta.get_x()  + delta.get_y()));
}

AStar::uint AStar::Heuristic::euclidean(Point source_, Point target_)
{
    auto delta = std::move(getDelta(source_, target_));
    return static_cast<uint>(10 * sqrt(pow(delta.get_x(), 2) + pow(delta.get_y(), 2)));
}

AStar::uint AStar::Heuristic::octagonal(Point source_, Point target_)
{
    auto delta = std::move(getDelta(source_, target_));
    return 10 * (delta.get_x()  + delta.get_y()) + (-6) * std::min(delta.get_x(), delta.get_y());
}
