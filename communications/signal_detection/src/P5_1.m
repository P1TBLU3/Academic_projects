close all
clear all
clc

M = 16;
m = log2(M);
Es = 2*(M-1)/3;

nSimb = 1*10^6;
nBits = nSimb*m;

a = 1;  
b = 1/16; 
dB = 15;
SNR_dB = dB+10*log10(m);

N0 = (Es/m)/(10^(dB/10));
tAssig = 'gray';
B = randi([0 1],nBits,1);
A = qammod(B,M,tAssig,'InputType','bit'); 



p1=[1];                      %Sin ISI
p = [-b/2, b, a, b, -b/2];  % Respuesta al impulso del canal con ISI
d = [0, 1, 2, 3, 4];  % Valores de retardo de decisión
BER = zeros(1, length(d));  % Almacena la BER
PES = zeros(1, length(d));  % Almacena la Probabilidad de Error de Símbolo

BER_ideal=0;
PES_ideal=0;
o_ideal = conv(A,p1);
o_ideal = o_ideal(1:nSimb);
q_ideal = awgn(o_ideal,SNR_dB,10*log10(Es));
Be_ideal = qamdemod(q_ideal,M,tAssig,'OutputType','bit');
BER_ideal = sum(B~=Be_ideal)/nBits;

% Cálculo de la PES
S_ideal = qammod(Be_ideal,M,tAssig,'InputType','bit');
PES_ideal = sum(A~=S_ideal)/nSimb;

for i = 1:length(d)
    o = conv(A,p);
    o = o(1+d(i):nSimb+d(i));
    q = awgn(o,SNR_dB,10*log10(Es));
    % Cálculo de la BER
    Be = qamdemod(q,M,tAssig,'OutputType','bit');
    BER(1,i) = sum(B~=Be)/nBits;
    
    % Cálculo de la PES
    S = qammod(Be,M,tAssig,'InputType','bit');
    PES(1,i) = sum(A~=S)/nSimb;
end

display(BER_ideal)
display(PES_ideal)
    
% Gráficas de BER y Probabilidad de Error de Símbolo vs. Retardo de Decisión
figure;
subplot(2, 1, 1);
plot(d, BER, 'o', 'LineWidth', 2);
title('BER vs. Retardo de Decisión');
xlabel('Retardo de Decisión (d)');
ylabel('BER');

subplot(2, 1, 2);
plot(d, PES, 'o', 'LineWidth', 2);
title('Probabilidad de Error de Símbolo vs. Retardo de Decisión');
xlabel('Retardo de Decisión (d)');
ylabel('Probabilidad de Error de Símbolo');