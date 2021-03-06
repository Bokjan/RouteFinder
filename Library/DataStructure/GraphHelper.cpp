#include "GraphHelper.hpp"

using std::string;

inline static float abs(float x)
{
	return x > 0 ? x : -x;
}

bf::GraphHelper::GraphHelper(void)
{
	// A estimated value
	routes.reserve(this->MAX_ROUTES);
	vertices.reserve(this->MAX_VERTICES);
}

void bf::GraphHelper::AddVertex(const string &ident, float latitude, float longitude)
{
	if (FindVertexId(ident, latitude) != -1)
		return;
	vertices.emplace_back(Vertex(vid, Coordinate(latitude, longitude), ident));
	vmap.insert(std::make_pair(ident, vid++));
}

int bf::GraphHelper::FindVertexId(const string &ident, float latitude)
{
	constexpr float epsilon = 1e0;
	const auto range = vmap.equal_range(ident);
	for (auto it = range.first; it != range.second; ++it)
		if (abs(vertices[it->second].coord.latitude - latitude) < epsilon)
			return it->second;
	return -1;
}

int bf::GraphHelper::FindVertexId(const std::string &ident)
{
	auto f = vmap.find(ident);
	return f == vmap.end() ? -1 : f->second;
}

string bf::GraphHelper::GetRouteString(int index)
{
	return routes[index];
}

string bf::GraphHelper::GetVertexString(int index)
{
	return vertices[index].name;
}

void bf::GraphHelper::AddRouteString(const std::string &route)
{
	routes.emplace_back(route);
	rmap.insert(std::make_pair(route, (int) (routes.size() - 1)));
}

const std::vector<bf::Vertex> &bf::GraphHelper::GetVertices(void)
{
	return vertices;
}

int bf::GraphHelper::GetRouteIndex(const std::string &route)
{
	auto f = rmap.find(route);
	return f == rmap.end() ? -1 : f->second;
}

std::pair<std::multimap<string, int>::iterator, std::multimap<string, int>::iterator>
bf::GraphHelper::GetVertexRange(const std::string &ident)
{
	return vmap.equal_range(ident);
}
