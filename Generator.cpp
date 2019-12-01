

#include "FastNoise.h"

extern "C" {
	__declspec(dllexport) float generate(float x, float y, float z);
}

float generate(float x, float y, float z)
{
	float value;

	FastNoise noise;

	noise.SetNoiseType(FastNoise::Perlin);

	float noiseValue;

	noise.SetSeed(1337);

	noise.SetFrequency(0.1f);

	noiseValue = noise.GetNoise(x, y, z);

	noiseValue = noiseValue - y;

	value = noiseValue;

	return value;
}