#include "main.hpp"

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512

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

    int device = 0;

    PaStreamParameters inputParameters;
    PaStreamParameters outputParameters;

    memset(&inputParameters, 0, sizeof(inputParameters));
    inputParameters.channelCount = 2;
    inputParameters.device = device;
    inputParameters.hostApiSpecificStreamInfo = NULL;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(device)->defaultLowInputLatency;

    memset(&outputParameters, 0, sizeof(outputParameters));
    outputParameters.channelCount = 2;
    outputParameters.device = device;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(device)->defaultLowInputLatency;

    PaStream* stream;
    err = Pa_OpenStream(
        &stream,
        &inputParameters,
        &outputParameters,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paNoFlag,
        patestCallback,
        NULL
    );
    checkError(err);

    err = Pa_StartStream(stream);
    checkError(err);

    Pa_Sleep(10 * 1000);

    err = Pa_StopStream(stream);
    checkError(err);

    err = Pa_CloseStream(stream);
    checkError(err);

    err = Pa_Terminate();
    checkError(err);

    return EXIT_SUCCESS;
}