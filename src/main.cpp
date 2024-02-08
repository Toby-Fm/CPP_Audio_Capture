#include "main.hpp"

// Definieren der Sample-Rate und der Anzahl der Frames pro Buffer
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512

int main() {
    PaError err;
    // Initialisierung von PortAudio
    err = Pa_Initialize();
    checkError(err);

    // Abrufen der Anzahl der verfügbaren Geräte
    int numDevices = Pa_GetDeviceCount();
    std::cout << "\nNumber of devices: " << numDevices << std::endl;
    // Überprüfen, ob Geräte vorhanden sind
    if (numDevices < 0) {
        std::cout << "Error getting device count" << std::endl;
        exit(EXIT_FAILURE);
    } else if (numDevices == 0) {
        std::cout << "No devices found" << std::endl;
        exit(EXIT_FAILURE);
    }

    const PaDeviceInfo* deviceInfo;
    // Durchlaufen aller Geräte und Ausgabe der Informationen
    for (int i = 0; i < numDevices; i++) {
        deviceInfo = Pa_GetDeviceInfo(i);
        std::cout << "\nDevice " << i << ":\n";
        std::cout << "Name: " << deviceInfo->name << std::endl;
        std::cout << "Max input channels: " << deviceInfo->maxInputChannels << std::endl;
        std::cout << "Max output channels: " << deviceInfo->maxOutputChannels << std::endl;
        std::cout << "Default sample rate: " << deviceInfo->defaultSampleRate << std::endl;
    }

    // Auswahl des zu verwendenden Geräts
    int device = 0;

    PaStreamParameters inputParameters;
    PaStreamParameters outputParameters;

    // Initialisierung der Eingabe- und Ausgabeparameter
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

    // Erstellen eines Streams
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

    // Starten des Streams
    err = Pa_StartStream(stream);
    checkError(err);

    // Der Stream läuft für 10 Sekunden
    Pa_Sleep(10 * 1000);

    // Stoppen des Streams
    err = Pa_StopStream(stream);
    checkError(err);

    // Schließen des Streams
    err = Pa_CloseStream(stream);
    checkError(err);

    // Beenden von PortAudio
    err = Pa_Terminate();
    checkError(err);

    return EXIT_SUCCESS;
}