#include <iostream>
#include <stdlib.h>
#include <portaudio.h>

static void checkError(PaError err) {
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main() {
    PaError err;
    err = Pa_Initialize();
    checkError(err);

    int numDevices = Pa_GetDeviceCount();
    std::cout << "\nNumber of devices: " << numDevices << std::endl;
    if (numDevices < 0) {
        std::cout << "Error getting device count" << std::endl;
        exit(EXIT_FAILURE);
    } else if (numDevices == 0) {
        std::cout << "No devices found" << std::endl;
        exit(EXIT_FAILURE);
    }

    const PaDeviceInfo* deviceInfo;
    for (int i = 0; i < numDevices; i++) {
        deviceInfo = Pa_GetDeviceInfo(i);
        std::cout << "\nDevice " << i << ":\n";
        std::cout << "Name: " << deviceInfo->name << std::endl;
        std::cout << "Max input channels: " << deviceInfo->maxInputChannels << std::endl;
        std::cout << "Max output channels: " << deviceInfo->maxOutputChannels << std::endl;
        std::cout << "Default sample rate: " << deviceInfo->defaultSampleRate << std::endl;
    }

    err = Pa_Terminate();
    checkError(err);

    return EXIT_SUCCESS;
}