close all
clear all
clc
M = 16;             %16QAM
m = log2(M);        %BITS/SIMB
Es = 2*(M-1)/3;     %ENERGIA PROMEDIO DE SIMBOLO
dB = 12;            
N0 = (Es/m)/(10^(dB/10));   
p=[1];              %Canal discreto equivalente
tAssig = 'gray';
nSimb = 1*10^6;
fase = -180:5:180;  %vector con todos los defases en saltos de 5º
BER = zeros(1,length(fase));
nBits = nSimb*m;
SNR_dB = dB+10*log10(m);
B = randi([0 1],nBits,1);
A = qammod(B,M,tAssig,'InputType','bit'); 
    
for i = 1:length(fase)
    o = conv(A,p)*exp(j*(fase(i)*pi/180));
    o = o(1:nSimb);
    q = awgn(o,SNR_dB,10*log10(Es));
    Be = qamdemod(q,M,tAssig,'OutputType','bit');
    BER(1,i) = sum(B~=Be)/nBits;
end 
figure()
semilogy(fase,BER)
