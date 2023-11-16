#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <thread>
#include <chrono>


// wave a, b

const float waveLengthA = 0.8f;
const float waveLengthB = 1.2f;

const float maxHeightA = 0.5f;
const float maxHeightB = 0.4f;

// position
float pa = 0.0f;
float pb = 1.0f;
// velocity
float va = 1.5f;
float vb = -1.0f;

const size_t kBufferSize = 80;
std::vector<float> heightField(kBufferSize);

const size_t FPS = 60;
const float TIMESTEP = 1.0f / FPS;

const std::string kGrayScaleTable = " .:-=+*#%@";

void updateWave(const float timeStep, float *p, float *velocity)
{

	(*p) += timeStep * (*velocity);

	// boundary condition
	if ((*p) > 1.0f) {
		(*velocity) *= -1.0f;
		(*p) = 1.0f + timeStep * (*velocity);
	}
	else if ((*p) < 0.0f) {
		(*velocity) *= -1.0f;
		(*p) = timeStep * (*velocity);
	}

}

void sampleWaveToHeightField(
	const float position,
	const float waveLength,
	const float maxHeight
)
{
	const float quarterWaveLength = 0.25f * waveLength;
	const int start = static_cast<int>((position - quarterWaveLength) * kBufferSize);
    const int end = static_cast<int>((position + quarterWaveLength) * kBufferSize);

	for ( int i = start; i < end; i++ )
	{
		int iNew = i;
        if (i < 0) {
            iNew = -i - 1;
        } else if (i >= static_cast<int>(kBufferSize)) {
            iNew = 2 * kBufferSize - i - 1;
        }

        float distance = fabs((i + 0.5f) / kBufferSize - position);

		float height = maxHeight * 0.5f
            * (cos(std::min(distance * (float)M_PI / quarterWaveLength, (float)M_PI)) + 1.0f);

        heightField[iNew] += height;

	}

}

void draw()
{
    std::string buffer(kBufferSize, ' ');

	// Convert height field to grayscale
	for (size_t i = 0; i < kBufferSize; ++i)
	{
		float height = heightField[i];
		size_t tableIndex = 
			std::min(static_cast<size_t>(floor(kGrayScaleTable.length() * height)),
            kGrayScaleTable.length() - 1);
		
		buffer[i] = kGrayScaleTable[tableIndex];
	}

	// Clear old prints
    for (size_t i = 0; i < kBufferSize; ++i) {
        printf("\b");
    }

	// Draw new buffer
    printf("%s", buffer.c_str());
    fflush(stdout);
}

int main() {

    const size_t numStep = 1000;


    for (size_t i = 0; i < numStep; i++) 
	{
		updateWave(TIMESTEP, &pa, &va);
		updateWave(TIMESTEP, &pb, &vb);

		for (float &height : heightField) {
			height = 0.0f;
		}

		sampleWaveToHeightField(pa, waveLengthA, maxHeightA);
		sampleWaveToHeightField(pb, waveLengthB, maxHeightB);

		draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));

    }

    printf("\n");
    fflush(stdout);


    return 0;
}