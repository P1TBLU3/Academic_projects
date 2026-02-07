function p=OFDM_p(d,N,C,T);
%
% p=OFDM_p(d,N,C,T);
%
% Función que calcula los canales discretos equivalentes a tiempo de símbolo
% p_ki[n] en una modulación OFDM a partir del canal discreto equivalente a 
% tiempo T/(N+C) d[m].
%
% Function that obtains the equivalent discrete channels at symbol rate 
% p_ki[n] in a OFDM from the equivalent discrete channel at T/(N+C) d[m].
%
% d: canal d[m] / channel d[m] (1 x (Kd+1))
% N: número de portadoras / number of carriers
% C: nº de muestras del prefijo cíclico / # of samples of the cyclic prefix
%    (C=0 by default)
% T: tiempo de símbolo OFDM / duration of OFDM symbol 
%    (T=1 by default)
%
% p: canales discretos equivalentes / equivalent discrete channels
%    NxN cell array 
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
% Actualización : noviembre 2018
%--------------------------------------------------------------------------

if nargin<3, C=0;end
if nargin<4, T=1;end

Kd=length(d)-1;
Nn=ceil(Kd/N);

p=cell(N,N);

for k=0:N-1
    for t=0:N-1
        paux=zeros(1,Nn+1);
        for n=0:Nn
            for m=-C:N-1
                for l=0:N-1
                    if ( (n*(N+C)+l-m)>=0 )& ( (n*(N+C)+l-m)<=Kd )
                        paux(n+1)=paux(n+1)+1/T*exp(j*2*pi*t*m/N)*exp(-j*2*pi*k*l/N)*d(n*(N+C)+l-m+1);
                    end
                end
            end
            if abs(paux(n+1))<1e-10, paux(n+1)=0;end
        end
        v=find(abs(paux)>0);
        if length(v)>0
            paux=paux(1:v(end));
        else
            paux=0;
        end
        p{k+1,t+1}=paux;
    end
end