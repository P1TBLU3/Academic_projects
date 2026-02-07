clc
clear all;
close all
N=1024;

%Generamos un filtro paso bajo de longitud 1024 (en el tiempo) y le hacemos
%la TF para ver que "pinta" tiene en frecuencia. Como siempre, lo mostramos
%en dB

b = fir1(N, 0.2,'low');
B1 = fftshift(fft(b,N));
db = 10*log10(abs(B1));
f = linspace(-pi,pi,N);

%Nota importante: ahora hemos generado el fitro en el tiempo como señal
%discreta. No tenemos, por tanto, la frecuencia de muestreo de la teórica
%señal continua que, tras ser muestreada, nos daría ese filtro. De ahí que
%EL DIBUJO SEA EN OMEGA MAYÚSCULA, PUESTO QUE NO HAY OTRO CAMINO PARA
%HACERLO.

plot(f, db);

%Hemos generado un filtro ideal (altura 1, por tanto). De ahí que el valor
%máximo en el dibujo sea precisamente 0 dB = 1. Como era de esperar, el
%filtro no ha quedado verdaderamente ideal, sino que hay una transición
%entre la parte que "pasa" (centro) y la que es rechazada (lados). Eso se
%debe a que UN FILTRO IDEAL EN FRECUENCIA, COMO LOS QUE SOLEMOS UTILIZAR EN
%CLASE, NECESITARÍA DE INFINITOS PUNTOS EN EL TIEMPO: NOSOTROS HEMOS USADO
%1024, ASÍ QUE SU TF NO QUEDA EXACTAMENTE LA ESPERADA.