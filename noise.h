#pragma once
#define noise_h
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>
#include <complex>
#include <random>
#include <fstream>
#include <numeric>
#include <cctype>
#include <typeinfo>
#include <limits.h>


    std::vector<float> noise(float duration, float sample_rate){
    const float num_points = sample_rate * duration;

    bool typex = false;
    float freqshift = 0;
    float amount;
    float v; // is the bandwidth
    std::vector<float> amplitude(num_points, 0.0);
    std::string shift;
    std::cout << "do you want to shift" << std::endl;
    std::cin >> shift;

    for (char& c : shift) {
        c = std::tolower(c);
    }

    std::cout << "how large do you want your bandwidth to be " << std::endl;
    std::cin >> v;
    while (true) {
        if (v != 0) {

            if (shift == "yes" or shift == "y")
            {
                typex = true;
                std::cout << "how much do you want to shift it by" << std::endl;
               std::cin >> freqshift;
                break;
            }
            else {
                amount = 0;
                break;
            }      
        }
        else if (v == 0) {
            break;
        }
        else {
            std::cout << "please use a number" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }       
    }

   if (fmod(v, 2) == 0) {
        std::fill(amplitude.begin(), amplitude.begin() + ((v / 2) + 1), 1);
        std::fill(amplitude.begin() + (sample_rate - (v / 2)), amplitude.begin() + sample_rate, 1);

    }


    std::vector<float> num(num_points);
    std::iota(num.begin(), num.end(), 0);


    std::random_device rd;            // seed
    std::mt19937 gen(rd());           // engine
    std::uniform_real_distribution<float> dist(0.0, 2 * M_PI);
    std::vector<float> phase(num_points);
    std::vector<float> freqs(num_points);
    for (int i = 0; i < num_points; i++) {
        phase[i] = dist(gen);
        freqs[i] = i / duration;

    }



    //# Time vector
    //t = np.linspace(0, duration, num_points, endpoint = False)
    std::vector<float> t(num_points);
    float step = duration / num_points;  // step size

    for (int i = 0; i < num_points; i++) {
        t[i] = i * step;  // goes from 0 up to duration - step
    }

    std::vector<std::complex<float>>x(num_points, 0);
    std::vector<float> interleaved(num_points * 2); // holds both waves interleaved

    for (int f = 0; f < num_points; f++)
    {
        std::vector<std::complex<float>> y(num_points);
        for (int n = 0; n < num_points; n++)
        {
            //# Cosine wave

            float angle = (2 * M_PI * freqs[f] * t[n] + phase[f]);
            float angle2 = (2 * M_PI * freqshift * t[n]);
            


            std::complex<float> z = std::exp(std::complex<float>(0.0, angle+angle2));
            y[n] = amplitude[f] * z;


        }
        for (int l = 0; l < num_points; l++)
        {
            std::complex<float> q = x[l] + y[l];
            x[l] = q;
        }

    }

    for (int p = 0; p < num_points; p++) {
        interleaved[2 * p] = x[p].real(); // I
        interleaved[2 * p + 1] = x[p].imag(); // Q
    }
    // Write to binary file (float32, interleaved I/Q)
    std::ofstream outFile("interleaved.bin", std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(interleaved.data()),
        interleaved.size() * sizeof(float));
    outFile.close();

    std::cout << "Wrote " << interleaved.size() << " float samples ("
        << interleaved.size() * sizeof(float) << " bytes) to interleaved.bin\n";

    return interleaved;

}


