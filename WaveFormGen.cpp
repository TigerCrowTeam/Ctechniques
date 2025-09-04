#define _USE_MATH_DEFINES   // must come first
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <complex>
#include "../noise/noise.h"
#include "../chirp1/chirp.h"
#include "../Wave01/wave.h"
#include "../Phasor1/phasor.h"
#include "../WaveformGen/sweptnoise.h"

int main() {
    float duration;
    float sampleRate;
    std::string choice;
    std::cout<< "what would you like to do? (type one of these options: wave,chirp,phasor,noise)" << std::endl;
    std::cin >> choice;
    std::cout << "whats the duration" << std::endl;
    std::cin >> duration;
    std::cout << "whats the samplerate" << std::endl;
    std::cin >> sampleRate;
    if (choice == "wave")
    {
        wave(duration, sampleRate);
    }
    else if(choice == "chirp"){
        chirp(duration, sampleRate);
        }

    else if(choice == "phasor"){
        phasor(duration, sampleRate);
    }
    else if (choice == "noise") {
        noise(duration, sampleRate);
        std::cout << "noise completed" << std::endl;
    }

    else if (choice == "sweptnoise") {
        float freq_inc;
        std::cout << "what's the freq inc" << std::endl;
        std::cin >> freq_inc;
        SweptNoise(duration, sampleRate,freq_inc);
        std::cout << "sweptnoise completed" << std::endl;
    }
    else { std::cout << "womp womp" << std::endl; };

}