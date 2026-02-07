%
% DEMO para la modulación y demodulación de una señal de espectro
% ensanchado por secuencia directa
% -------------------------------------------------------------------------
% DEMO for the modulation and demodulation of a direct sequence spread
% spectrum modulation
%
%--------------------------------------------------------------------------
%
% LABORATORIO DE COMUNICACIONES DIGITALES   
%
%        Versión: 1.0
%  Realizado por: Marcelino Lázaro
%                 Departamento de Teoría de la Señal y Comunicaciones
%                 Universidad Carlos III de Madrid
%      Creación : noviembre 2022
% Actualización : noviembre 2022
%--------------------------------------------------------------------------

%--------------------------------------------------------------------------
% Parámetros generales de la simulación
% General parameters for the simulation
%--------------------------------------------------------------------------
M = 4;                  % Orden de la constelación (Constellation order)
m = log2(M);            % Bits por símbolo (Bits per symbol)
nSimb = 2e5;            % Number of symbols in the simulation
nBits = nSimb * m;      % Number of bits in the simulation
tAssign = 'gray';        % Type of binary assignement ('gray', 'bin')
%--------------------------------------------------------------------------
% Secuencia de ensanchado y factor de ensanchado
% Spreading sequence and spreading factor
%--------------------------------------------------------------------------
x=[+1,+1,+1,+1];
% x=[+1,-1,+1,-1];
N=length(x);
%--------------------------------------------------------------------------
% Modulador Digital PAM (Digital PAM Modulator)
%--------------------------------------------------------------------------
% Generación de bits (Generation of Bits) 
%--------------------------------------------------------------------------
B = randi([0 1],1,nBits);
% Separación de bits por símbolo (Bits per symbol)
Bsimb = zeros(m,nSimb);
Bsimb(:) = B;
% Representación decimal de los bits por símbolo
% Decimal representation of bits per symbol
Bdec = transpose(bin2dec(num2str(Bsimb')));
%--------------------------------------------------------------------------
% Codificación de bits en símbolos (Symbols encoded from bits)
%--------------------------------------------------------------------------
A = pammod(Bdec,M,0,tAssign); 
%--------------------------------------------------------------------------
% Diagrama de dispersión de los símbolos (Scattering diagram)
%--------------------------------------------------------------------------
scatterplot(A);title('Scatter Plot A[n]')
%--------------------------------------------------------------------------
% Canal discreto equivalente a tiempo de chip
% Equivalent discrete channel at chip rate
%--------------------------------------------------------------------------
d=[1 0.5 0.25 0.125 0.1 0.075 0.05 0.025];
%--------------------------------------------------------------------------
% Varianza de ruido (Noise variance)
%--------------------------------------------------------------------------
vNoise=0.1;
%--------------------------------------------------------------------------
% Samples at chip rate of the modulated signal
%--------------------------------------------------------------------------
 s=kron(A,x);
%--------------------------------------------------------------------------
% Transmission
%--------------------------------------------------------------------------
Kd=length(d)-1;
v=conv([zeros(1,Kd),s],d);
v=v(Kd+1:Kd+length(s));
v=v+sqrt(vNoise)*randn(size(v));
%--------------------------------------------------------------------------
% Demodulation
%--------------------------------------------------------------------------
% Periodical extention of the spreading sequence
xp=repmat(x,1,length(A));
aux=v.*conj(xp);
% Serial to parallel
aux=reshape(aux,N,length(A));
q=sum(aux);
%--------------------------------------------------------------------------
% Visualization
%--------------------------------------------------------------------------
figure(1),stem(0:9,A(1:10))
title('A[n]'),xlabel('n')
grid
figure(2),stem(0:10*N-1,s(1:10*N))
title('s[m]'),xlabel('n')
figure(3),stem(0:10*N-1,v(1:10*N))
title('v[m]'),xlabel('n')
grid
figure(4),stem(0:9,q(1:10))
title('q[n]'),xlabel('n')
grid

%--------------------------------------------------------------------------
% Canal discreto equivalente a tiempo de símbolo (teórico)
% Equivalent discrete channel at symbol rate (theoretical)
%--------------------------------------------------------------------------
p=DSSS_p(x,d);
disp(['x[n] : ',num2str(x)])
disp(['d[m] : ',num2str(d)])
disp(['p[n] : ',num2str(p)])
%--------------------------------------------------------------------------
% Normalización de la obsevación
% Normalization of the observation
%--------------------------------------------------------------------------
qn=q/p(1);
figure(5), plot(real(qn),imag(qn),'o')
title('Diagrama de dispersión / Scattering diagram')
%--------------------------------------------------------------------------
% Decisiones (estimas) y decodificación
% Decision (estimation) and decoding
Bdec_est = pamdemod(qn,M,0,tAssign);
A_est = pammod(Bdec_est,M,0,tAssign);

B_est = transpose(dec2bin(Bdec_est) -'0');
B_est = transpose(B_est(:));
%--------------------------------------------------------------------------
% Prestaciones / Performance
%--------------------------------------------------------------------------
Pe=length(find(A_est~=A))/length(A);
BER=length(find(B_est~=B))/length(B);
disp(['Pe : ',num2str(Pe)])
disp(['BER : ',num2str(BER)])
