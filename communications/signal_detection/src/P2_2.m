close all
clear all
clc

M = 16;     % Orden de la constelación (Constellation order)                     
m = log2(M);     % Bits por símbolo (Bits per symbol)       
nSimb = 1e6;      % Numero de bits en la simulacion      
nBits = nSimb * m;   % Numero de simbolos en la simulacion   
tAssig = 'gray';      % Tipo de asignación de constelación  
dB = 40;          % Relación señal-ruido en decibelios (SNR)

Es = 2*(M-1)/3;   
SNR_dB = dB*10*log10(m);
a =  [1/16 1/8 1/4];
Kp = 1;

B = randi([0 1],nBits,1);
A = qammod(B,M,tAssig,'InputType','bit'); 
scatterplot(A);title('Scatter Plot A[n]')


for i=1:3
    p = [1,a(i)];
    o = conv(A,p);
    o = o(1:nSimb);
    q = awgn(o,SNR_dB,10*log10(Es));
    scatterplot(q);
    title('Scatter Plot q[n]')

    
    Be = qamdemod(q,M,tAssig,'OutputType','bit');
end 