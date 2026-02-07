close all
clear all
clc
dB =0:1:20; %vector de dB de 0 a 20 en saltos de 1
BER = zeros(1,length(dB));
SER = zeros(1,length(dB));
nSimb = 1*10^6;
tAssig = 'bin';
p=[1]; %Canal discreto equivalente
figure()
for i = 1:3
    M = 4^i; %4,16 y 64 QAM                 
    Es = 2*(M-1)/3;         %Energía de simbolo promedio
    m = log2(M);            %Nº bits por simbolo
    nBits = nSimb*m;
    SNR_dB = dB+10*log10(m);
    
    B = randi([0 1],nBits,1);
    A = qammod(B,M,tAssig,'InputType','bit'); 

    o = conv(A,p);
    o = o(1:nSimb);
    for j = 1:length(dB)
        
        q = awgn(o,SNR_dB(1, j),10*log10(Es));
        Be = qamdemod(q,M,tAssig,'OutputType','bit');
        BER(1,j) = sum(B~=Be)/nBits;
    end    
    semilogy(dB,BER)
    hold on
end
title('Comparación BER vs N0/Eb (secuencial)')
xlabel('N0/Eb') 
ylabel('BER') 
legend({'M = 4','M = 16','M = 64'},'Location','northeast')

o

