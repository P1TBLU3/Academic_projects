clc
clear all;
close all;
%Como siempre, cerramos todas las ventanas previas y limpiamos las
%variables usadas hasta ahora.

[x1, fs1] = wavread('audio1.wav');

%leemos el archivo de audio y lo convertirmos en una secuencia de valores
%x y, además, guardamos la frecuencia de muestreo que se usó en fs1

%ahora vamos a cambiar la frecuencia de muestreo de la señal, como he mos
%visto en clase, utilizando un comando que introduce un diezmado con un
%factor P y una interpolación con un factor Q sobre la señal de entrada x1

%Como se desea que la resultante sea de 16KHz y fs1 es de valor 22050, si
%colocamos directamente las siguientes líneas, garantizamos tener el mismo
%resultado que si, directamente, se hubiera muestreado a 16KHz (obviamente,
%podríamos simplificar esos factores para obtener otros más simples, pero
%no merece ni la pena).

P=22050;
Q=16000;
voz = resample(x1, Q, P);
soundsc(voz);


%A continuación hacemos la FFT de 4096 puntos de la señal voz
N=4096;
X1=fftshift(fft(voz,N));
f=linspace(-8000,8000,N);

%Arriba hemos tomado4096 puntos equiespaciados entre los -8 y +8 KHz. A
%continuación pasamos a dB

db=10*log10(abs(X1));
plot(f,db);

