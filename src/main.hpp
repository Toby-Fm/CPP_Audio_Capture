#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <portaudio.h>

// Funktion zur Überprüfung von PortAudio-Fehlern
static void checkError(PaError err) {
    // Wenn ein Fehler auftritt, wird eine Fehlermeldung ausgegeben und das Programm beendet
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        exit(EXIT_FAILURE);
    }
}
// Funktion zur Bestimmung des Maximums von zwei Zahlen
static inline float max(float a, float b) {
    return a > b ? a : b;
}

static int patestCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {
    // Konvertierung des Eingabepuffers in ein float-Array
    float* in = (float*)inputBuffer;
    // OutputBuffer wird nicht verwendet
    (void)outputBuffer;

    // Größe der Anzeige
    int disSize = 100;
    std::cout << "\r";

    // Leeren des Ausgabepuffers
    fflush(stdout);

    // Initialisierung der Lautstärkevariablen für den linken und rechten Kanal
    float vol_left = 0;
    float vol_right = 0;

    // Durchlaufen des Eingabepuffers und Bestimmung der maximalen Lautstärke für den linken und rechten Kanal
    for (unsigned long i = 0; i < framesPerBuffer * 2; i += 2) {
        vol_left = max(vol_left, std::abs(in[i]));
        vol_right = max(vol_right, std::abs(in[i + 1]));
    }

    // Erzeugung der Lautstärkeanzeige
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