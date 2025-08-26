#define _USE_MATH_DEFINES   // must come first
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <complex>
#include <numeric>

int main() {
    const float duration = 3.0f;  // seconds
    const std::vector<float> freq = { 1000.0f,6000.0f,12000.0f };     // Hz

    const float sampleRate = 60000; // 100 Hz
    const float Ts = 1.0f / sampleRate;
    const int numSamples = sampleRate * duration;

    std::vector<std::complex<float>> phasor1(numSamples);

    

    std::vector<float> interleaved(numSamples * 2); // holds both waves interleaved

    for (int n = 0; n < numSamples; ++n) {
        float t = n * Ts;
        std::complex<float> v = 0;
        for (std::size_t i = 0; i < freq.size(); ++i)
        {
            double angle = 2.0 * M_PI * freq[i] * t;

            phasor1[n] = std::exp(std::complex<double>(0.0, angle));

            v = v + phasor1[n];
        }

        

        double R_Phasor = std::real(v);
        double I_Phasor = std::imag(v);
        interleaved[2 * n] = R_Phasor; // I
        interleaved[2 * n + 1] = I_Phasor; // Q
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