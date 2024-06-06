#include "screen.h"
#include <cmath> // For std::cos, std::sin, std::sqrt, std::atan2
#include <vector>

struct vec3
{
	float x, y, z;
};

struct connection
{
	int a, b;
};

void rotate(vec3& point, float x = 1, float y = 1, float z = 1)
{
	float rad = 0;

	// Rotation around the x-axis
	rad = x;
	{
		float newY = std::cos(rad) * point.y - std::sin(rad) * point.z;
		float newZ = std::sin(rad) * point.y + std::cos(rad) * point.z;
		point.y = newY;
		point.z = newZ;
	}

	// Rotation around the y-axis
	rad = y;
	{
		float newX = std::cos(rad) * point.x + std::sin(rad) * point.z;
		float newZ = -std::sin(rad) * point.x + std::cos(rad) * point.z;
		point.x = newX;
		point.z = newZ;
	}

	// Rotation around the z-axis
	rad = z;
	{
		float newX = std::cos(rad) * point.x - std::sin(rad) * point.y;
		float newY = std::sin(rad) * point.x + std::cos(rad) * point.y;
		point.x = newX;
		point.y = newY;
	}
}

void line(Screen& screen, float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;

	float length = std::sqrt(dx * dx + dy * dy);
	if (length == 0)
	{
		screen.pixel(x1, y1);
		return;
	}

	float angle = std::atan2(dy, dx);

	for (float i = 0; i < length; i++)
	{
		screen.pixel(x1 + std::cos(angle) * i,
			y1 + std::sin(angle) * i);
	}
}

int main(int argc, char* argv[])
{
	Screen screen;

	std::vector<vec3> points{
		{100, 100, 100},
		{200, 100, 100},
		{200, 200, 100},
		{100, 200, 100},

		{100, 100, 200},
		{200, 100, 200},
		{200, 200, 200},
		{100, 200, 200}
	};

	std::vector<connection> connections
	{
		{0, 4},
		{1, 5},
		{2, 6},
		{3, 7},

		{0, 1},
		{1, 2},
		{2, 3},
		{3, 0},

		{4, 5},
		{5, 6},
		{6, 7},
		{7, 4}
	};

	// Calculate centroid
	vec3 c{ 0, 0, 0 };
	for (auto& p : points)
	{
		c.x += p.x;
		c.y += p.y;
		c.z += p.z;
	}

	c.x /= points.size();
	c.y /= points.size();
	c.z /= points.size();

	bool running = true;
	while (running)
	{
		for (auto& p : points)
		{
			p.x -= c.x;
			p.y -= c.y;
			p.z -= c.z;
			rotate(p, 0.02f, 0.01f, 0.04f);
			p.x += c.x;
			p.y += c.y;
			p.z += c.z;
			screen.pixel(p.x, p.y);
		}

		for (auto& conn : connections)
		{
			line(screen, points[conn.a].x,
				points[conn.a].y,
				points[conn.b].x,
				points[conn.b].y);
		}

		screen.show();
		screen.clear();

		// Handle input and check for exit condition
		running = screen.input();
		SDL_Delay(30);
	}

	return 0;
}
