close all
clear all
clc
M = 16;                 % Orden de la constelación (Constellation order)
m = log2(M);            % Bits por símbolo (Bits per symbol)
nSimb = 1e6;            % Number of symbols in the simulation
nBits = nSimb * m;      % Number of bits in the simulation
tAssig = 'gray';        % Type of binary assignement ('gray', 'bin')
Es = 2*(M-1)/3;         % Energía media por símbolo (Mean Energy per Symbol)
dB = [5 10 15 20];      % Relación señal a ruido en dB (S/N in dB)
p=[1];                  % Canal discreto equivalente (Equivalent discrete channel)
N0 = (Es/m)./(10.^(dB/10))           % De la formula de la señal ruido, despejas y pasas a w
SNR_dB = dB+10*log10(m)
B = randi([0 1],nBits,1);
% Codificación de bits en símbolos (Symbols encoded from bits)
A = qammod(B,M,tAssig,'InputType','bit'); 
% Diagrama de dispersión de los símbolos (Scattering diagram)
scatterplot(A);title('Scatter Plot A[n]')
% Transmisión a través del canal (Transmission through channel)
o = conv(A,p);
o = o(1:nSimb);

for i=1:4
    
    % Ruido Aditivo Blanco Gausiano (Additive White Gaussian Noise)
    q = awgn(o,SNR_dB(i),10*log10(Es));
    scatterplot(q);
    title('Scatter Plot q[n]')

    % Demodulación a nivel de bit (Bit-level demodulation)
    Be = qamdemod(q,M,tAssig,'OutputType','bit');
end 