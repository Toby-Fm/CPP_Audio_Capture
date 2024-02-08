#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <portaudio.h>

static void checkError(PaError err) {
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        exit(EXIT_FAILURE);
    }
}

static inline float max(float a, float b) {
    return a > b ? a : b;
}

static int patestCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {
    float* in = (float*)inputBuffer;
    (void)outputBuffer;

    int disSize = 100;
    std::cout << "\r";

    fflush(stdout);

    float vol_left = 0;
    float vol_right = 0;

    for (unsigned long i = 0; i < framesPerBuffer * 2; i += 2) {
        vol_left = max(vol_left, std::abs(in[i]));
        vol_right = max(vol_right, std::abs(in[i + 1]));
    }

    for (int i = 0; i < disSize; i++) {
        float barProportion = i / (float)disSize;
        if (barProportion <= vol_left && barProportion <= vol_right) {
            std::cout << "█";
        } else if (barProportion <= vol_left) {
            std::cout << "█";
        } else if (barProportion <= vol_right) {
            std::cout << "█";
        } else {
            std::cout << " ";
        }
    }

    return 0;
}