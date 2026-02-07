clc
clear all;
close all
[x1, fs1] = wavread('audio2.wav');

%Sólo es repetir el ejercicio anterior para otra señal. Al leerla, vemos
%que la frecuencia de muestreo es la misma, así que todo va igual (mismos P
%y Q).

P=22050;
Q=16000;
piano = resample(x1, P, Q);
soundsc(piano);

N=4096;
X1=fftshift(fft(piano,N));
f=linspace(-8000,8000,N);
db=10*log10(abs(X1));
plot(f,db);

