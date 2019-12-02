

#include "FastNoise.h"

extern "C" {
	__declspec(dllexport) float generate(float x, float y, float z, int* material);
}

float generate(float x, float y, float z, int* material)
{
	float value;

	FastNoise noise;

	noise.SetNoiseType(FastNoise::Perlin);

	float noiseValue;

	noise.SetSeed(1337);

	noise.SetFrequency(0.1f);

	noiseValue = noise.GetNoise(x, y, z);

	noiseValue = noiseValue * 10.0f;

	noiseValue = noiseValue - y;



	value = noiseValue;
	material = 0;
	return value;
}