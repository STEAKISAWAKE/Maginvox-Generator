

#include "FastNoise.h"

#include <cmath>
#include <cassert>
#include <algorithm>
#include <array>

struct Vec3
{
	float x, y, z;
};


extern "C" {
	__declspec(dllexport) float generate(float x, float y, float z, int& material);
	__declspec(dllexport) struct Vec3 gradient(float x, float y, float z);
}

float clip(float n, float lower, float upper) {
	return max(lower, min(n, upper));
}

float generate(float x, float y, float z, int& material)
{
	float value;

	FastNoise noise;

	noise.SetNoiseType(FastNoise::Perlin);

	float noiseValue;

	noise.SetSeed(1337);

	noise.SetFrequency(0.03f);

	noiseValue = noise.GetNoise(x, y, z);

	noiseValue = noiseValue * 10.0f;

	noiseValue = noiseValue - y;
	
	FastNoise colorNoise;
	colorNoise.SetNoiseType(FastNoise::WhiteNoise);
	float color =  colorNoise.GetWhiteNoise(x, y);

	value = noiseValue;
	material = color;
	return value;
}

void normalize(Vec3& v)
{
	float l = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	assert(l > 0);
	v.x /= l;
	v.y /= l;
	v.z /= l;
}

struct Vec3 gradient(float x, float y, float z)
{
	const float epsilon = 0.0001;

	int nomat = 0;

	Vec3 result;

	float dx = generate(x + epsilon, y, z, nomat) - generate(x - epsilon, y, z, nomat);
	float dy = generate(x, y + epsilon, z, nomat) - generate(x, y - epsilon, z, nomat);
	float dz = generate(x, y, z + epsilon, nomat) - generate(x, y, z - epsilon, nomat);

	result.x = dx;
	result.y = dy; 
	result.z = dz;

	normalize(result);
	return result;
}