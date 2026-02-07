clc
clear all;
close all;

[x1, fs1] = wavread('audio2.wav');
[x2, fs2] = wavread('audio1.wav');

P=22050;
Q=16000;

voz = resample(x2, Q, P);
piano = resample(x1, Q, P);

t = (1:length(piano))/Q;
f0 = Q/4;
coseno= cos(2*pi*f0*t);
piano_desp = coseno'.*piano;
N = 4096;
mezcla = piano_desp + voz;

MEZCLA = fftshift(fft(mezcla,N));
ejef=linspace(-8000,8000,N);

%Representamos ahora la TF de la suma de ambas señales (señal mezcla), como
%siempre en dB

plot(ejef,10*log10(abs(MEZCLA)));

soundsc(mezcla);