close all
clear all
clc
M = 16;                       
m = log2(M);            
nSimb = 1e6;            
nBits = nSimb * m;      
tAssig = 'gray'; 
Es = 2*(M-1)/3;   
dB = 40;
SNR_dB = dB*10*log10(m);
a =  [1/16 1/8 1/4];
Kp = 2;

B = randi([0 1],nBits,1);
A = qammod(B,M,tAssig,'InputType','bit'); 
scatterplot(A);title('Scatter Plot A[n]')


for i=1:3
    p = [1,a(i),a(i)/4];
    o = conv(A,p);
    o = o(1:nSimb);
    q = awgn(o,SNR_dB,10*log10(Es));
    scatterplot(q);
    title('Scatter Plot q[n]')

    
    Be = qamdemod(q,M,tAssig,'OutputType','bit');
end