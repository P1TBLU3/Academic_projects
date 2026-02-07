%
% DEMO para la modulación y demodulación de una señal de espectro
% ensanchado por secuencia directa
% -------------------------------------------------------------------------
% DEMO for the modulation and demodulation of a OFDM modulation
%
%--------------------------------------------------------------------------
%
% LABORATORIO DE COMUNICACIONES DIGITALES   
%
%        Versión: 1.0
%  Realizado por: Marcelino Lázaro
%                 Departamento de Teoría de la Señal y Comunicaciones
%                 Universidad Carlos III de Madrid
%      Creación : noviembre 2018
% Actualización : noviembre 2022
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% Parámetros generales de la simulación
% General parameters for the simulation
%--------------------------------------------------------------------------
T=1;            % Tiempo de símbolo / Symbol length
N=4;            % Número de portadoras / Number of carriers
M = 16;                 % Orden de la constelación (Constellation order)
m = log2(M);            % Bits por símbolo (Bits per symbol)
nBlocks=1e5;            % Número de bloques / Number of blocks
nSymb = nBlocks*N;      % Number of symbols in the simulation
nBits = nSymb * m;      % Number of bits in the simulation
tAssign = 'gray';       % Type of binary assignement ('gray', 'bin')

d=[1];

varNoise=0;
%--------------------------------------------------------------------------
% Modulation
%--------------------------------------------------------------------------
% Generación de bits (Generation of Bits) 
B = randi([0 1],nBits,1);
% Codificación de bits en símbolos (Symbols encoded from bits)
A = qammod(B,M,tAssign,'InputType','bit'); 
%B=genera_bits(Nbits);
%A=codifica_gray_qam(B,M);
% Conversión serie a paralelo / Serial to parallel conversion
Ak=reshape(A,N,nBlocks);
sb=N/sqrt(T)*ifft(Ak,N,1);
% Conversión paralelo a serie / Parallel to serial conversion
s=reshape(sb,1,nSymb);
%--------------------------------------------------------------------------
% Transmission
%--------------------------------------------------------------------------
Kd=length(d)-1;
v=conv([zeros(1,Kd),s],d);
v=v(Kd+1:Kd+length(s));
v=v+sqrt(varNoise/2)*randn(size(v))+j*sqrt(varNoise/2)*randn(size(v));
%--------------------------------------------------------------------------
% Demodulation
%--------------------------------------------------------------------------
% Serial to parallel
vp=reshape(v,N,nBlocks);
qk=1/sqrt(T)*fft(vp,N,1);
%--------------------------------------------------------------------------
% Visualization
%--------------------------------------------------------------------------
p=OFDM_p(d,N);
Pe=zeros(1,N);
disp('Probabilidades de error / Error probabilities')
for k=1:N
    pk=p{k,k};
    qn=qk(k,:)/pk(1);
    Bke = qamdemod(qn,M,tAssign,'OutputType','bit');
    Ake = qammod(Bke,M,tAssign,'InputType','bit'); 
    %Ake=decisor_qam(qn,M);
    Pe(k)=length(find(Ake~=Ak(k,:)))/length(Ake);
    disp(['  Pe (k=',num2str(k-1),') = ',num2str(Pe(k))])
end
disp(['Pe (mean) = ',num2str(mean(Pe))])
