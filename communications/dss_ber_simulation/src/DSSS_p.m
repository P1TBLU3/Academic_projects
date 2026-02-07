function p=DSSS_p(x,d);
%
% p=DSSS_p(x,d) 
%
% Función que calcula el canal discreto equivalente a tiempo de símbolo
% p[n] en una modulación de espectro ensanchado por secuencia directa a
% partir de la secuencia de ensanchado x[m] y del canal discreto 
% equivalente a tiempo de chip d[m].
%
% Function that obtains the equivalent discrete channel at symbol rate p[n]
% in a direct sequence spread spectrum modulation from the spreading
% sequence x[m] and the equivalent discrete channel at chip rate d[m].
%
% x: secuencia de ensanchado / spreading sequence (1 x N) 
% d: canal d[m] / channel d[m] (1 x (Kd+1))
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

Kd=length(d)-1;
N=length(x);
Nn=ceil(Kd/N);

p=zeros(1,Nn+1);
for n=0:Nn
    for m=0:N-1
        for l=0:N-1
            %disp(['n=',num2str(n),' m=',num2str(m),' l=',num2str(l)])
            if ( (n*N+l-m)>=0 )& ( (n*N+l-m)<=Kd )
                p(n+1)=p(n+1)+x(m+1)*conj(x(l+1))*d(n*N+l-m+1);
            end
        end
    end
end