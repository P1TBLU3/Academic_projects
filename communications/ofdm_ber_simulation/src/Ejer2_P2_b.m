clc
clear all
close all

T=1;                    % Tiempo de símbolo / Symbol length
N=16;                    % Número de portadoras / Number of carriers
M = 16;                 % Orden de la constelación (Constellation order)
m = log2(M);            % Bits por símbolo (Bits per symbol)
nBlocks=1e5;            % Número de bloques / Number of blocks
nSymb = nBlocks*N;      % Number of symbols in the simulation
nBits = nSymb * m;      % Number of bits in the simulation
tAssign = 'gray';       % Type of binary assignement ('gray', 'bin')

a=9/10;
n = 0:1:5;
d= a.^n;
varNoise=[0 4];

for i = 1:2
    if i ==1
        disp('Probabilidades de error Para V = 0') 
    else
         disp('Probabilidades de error para V = 4')
    end
    
    for j = 1:10
        C=j;
        % Generación de bits (Generation of Bits) 
        B = randi([0 1],nBits,1);
        % Codificación de bits en símbolos (Symbols encoded from bits)
        A = qammod(B,M,tAssign,'InputType','bit'); 
        %B=genera_bits(Nbits);
        %A=codifica_gray_qam(B,M);
        % Conversión serie a paralelo / Serial to parallel conversion
        Ak=reshape(A,N,nBlocks);
        sb=N/sqrt(T)*ifft(Ak,N,1);
        sb=[sb(end-C+1:end,:);sb];
        % Conversión paralelo a serie / Parallel to serial conversion
        s=reshape(sb,1,nSymb+C*nBlocks);

        Kd=length(d)-1;
        v=conv([zeros(1,Kd),s],d);
        v=v(Kd+1:Kd+length(s));
        v=v+sqrt(varNoise(i)/2)*randn(size(v))+1j*sqrt(varNoise(i)/2)*randn(size(v));

        vp=reshape(v,N+C,nBlocks);
        qk=1/sqrt(T)*fft(vp(C+1:end,:),N,1);
        p=OFDM_p(d,N,C);
        Pe=zeros(1,N);
        if j==1
            disp('Probabilidades de error / Error probabilities')
        end
                for k=1:N
                pk=p{k,k};
                qn=qk(k,:)/pk(1);
                Bke = qamdemod(qn,M,tAssign,'OutputType','bit');
                Ake = qammod(Bke,M,tAssign,'InputType','bit'); 
                Pe(k)=length(find(Ake~=Ak(k,:)))/length(Ake);
                
                if  i == 2 && j==5 %Prefijo cíclico óptimo c=5
                    %Prob error para cada portadora k
                    disp(['  Pe (k=',num2str(k-1),') = ',num2str(Pe(k))])
                end

            end
        disp(['Pe (mean) = ',num2str(mean(Pe))])
        
    end
end
