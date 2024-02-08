# CPP_Audio_Capture
Dieses Projekt ist ein "Audio-Monitor", der in C++ geschrieben ist. Es nutzt die `PortAudio-Bibliothek`, um Audioeingaben von verschiedenen Quellen zu überwachen. Es kann sowohl Mikrofoneingaben als auch Audioausgaben von Anwendungen wie Spotify überwachen. Die Lautstärke der Audioeingaben wird in Echtzeit visualisiert, wobei die Amplitude der Audiosignale steigt und fällt.

![Audio test](/img/image-1.png)
![Audio test](/img/image.png)
![Audio test](/img/image-4.png)

---

## Voraussetzungen

- Ein `C++-Compiler` *(z.B. g++)*
- Die `PortAudio-Bibliothek`
- `Linux` *(getestet auf Debian 12)*

---

## Installation

1. Stelle sicher dass du den g++ compiler installiert hast. Wenn nicht, installiere ihn mit dem folgenden Befehl:
```shell
/* Debian / Ubuntu */

~$ sudo apt-get install g++ -y
~$ g++ --version
```


2. Clone das Repository und wechsle in das Verzeichnis:
```shell
~$ git clone https://github.com/Toby-Fm/CPP_Audio_Capture.git && cd CPP_Audio_Capture
```


3. Um die Abhängigkeiten zu installieren, führe den folgenden Befehl aus:
```shell
~$ make install-deps
```
---

## Ausführung
Um das Projekt zu kompilieren und auszuführen, führe den folgenden Befehl aus:
```shell
~$ make
```
```shell 
~$ ./make
```