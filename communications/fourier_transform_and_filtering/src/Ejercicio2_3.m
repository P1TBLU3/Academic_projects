clc
clear all;
close all;

[x1, fs1] = wavread('audio2.wav');
P=22050;
Q=16000;

piano = resample(x1, Q, P);

t = (1:length(piano))/Q;

f0 = Q/4;
coseno= cos(2*pi*f0*t);

%Acabamos de generar un coseno a una frecuencia que es un cuarto de la
%frecuencia de muestreo de la señal leída

piano_desp = coseno'.*piano;

%Multiplicamos nuestra señal en el tiempo por el coseno en el tiempo.
%Sabemos de clase que lo que va a pasar es que el espectro de la señal se
%desplazará a la frecuencia del coseno (con la altura dividida entre dos).

N = 4096;
PIANO_DESP = fftshift(fft(piano_desp,N));
PIANO = fftshift(fft(piano,N));
ejef=linspace(-8000,8000,N);
%represento la TF de ambas señales (original en azul, arriba, y la otra en
%rojo, abajo), siempre en dB

subplot(2,1,2)
plot(ejef, 10*log10(abs(PIANO_DESP)), 'red');
subplot(2,1,1);
plot(ejef, 10*log10(abs(PIANO)));
soundsc(piano_desp);