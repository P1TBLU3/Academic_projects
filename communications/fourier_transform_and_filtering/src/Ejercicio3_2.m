clc
clear all;
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

%Volvemos a generar la señal mezcla, como antes, así como su transformada.



M=1024;
b = fir1(M, 0.2,'low');
B1 = fftshift(fft(b,M));
db = 10*log10(abs(B1));
f = linspace(-512,512,M);
mezcla_filtrada = filter(b, 1, mezcla);
MEZCLA_FILTRADA = fftshift(fft(mezcla_filtrada,M));
f1 = linspace(-pi,pi,length(MEZCLA_FILTRADA));
db1 = 10*log10(abs(MEZCLA_FILTRADA));
plot(f1, db1);
soundsc(mezcla_filtrada);


%Lo que hemos hecho es pasar la señal mezcla a través del filtro paso bajo
%de antes. Lógicamente, el filtro elimina casi por completo la señal
%piano_desp, quedándonos solo voz, que es lo que se aprecia en el dibujo


%NOTA: Al dibujar en escala logarítmica, parece que realmente queda algo de
%la señal piano_desp... Pero, si nos fijamos, su amplitud es 20 dB menor
%que la de la señal de voz. Eso se traduce en un tamaño 10 a la 20 partido
%de 10 veces más pequeño (100 veces más pequeño).