#define _USE_MATH_DEFINES   // must come first
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

int main() {
    const float duration = 3.0f;  // seconds
    const float intercept = -6000.0f;     // Hz
    const float slope = (-2 * intercept) / duration;     // Hz
    const float sampleRate = 60000; // 100 Hz
    const float Ts = 1.0f / sampleRate;
    const int numSamples = sampleRate * duration;

    std::vector<float> wave1(numSamples);
    std::vector<float> wave2(numSamples);

    std::vector<float> interleaved(numSamples * 2); // holds both waves interleaved

    for (int n = 0; n < numSamples; ++n) {
        float t = n * Ts;
        wave1[n] = std::sin(2.0f * M_PI * (.5 * slope * pow(t, 2) + intercept * t)); // I
        wave2[n] = std::cos(2.0f * M_PI * (.5 * slope * pow(t, 2) + intercept * t)); // Q

        interleaved[2 * n] = wave1[n]; // I
        interleaved[2 * n + 1] = wave2[n]; // Q
    }

    // Write to binary file (float32, interleaved I/Q)
    std::ofstream outFile("interleaved.bin", std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(interleaved.data()),
        interleaved.size() * sizeof(float));
    outFile.close();

    std::cout << "Wrote " << interleaved.size() << " float samples ("
        << interleaved.size() * sizeof(float) << " bytes) to interleaved.bin\n";

    return 0;
}