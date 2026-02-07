close all
clear all
clc
dB =0:1:20; %vector de dB de 0 a 20 en saltos de 1
BER = zeros(1,length(dB));
SER = zeros(1,length(dB));

nSimb = 16; % Número de símbolos
combinaciones_de_bits = dec2bin(0:(2^4 - 1), 4) - '0'; % Patrón de bits
combinaciones_vector = reshape(combinaciones_de_bits.', 1, []);
nBits = length(combinaciones_vector); % Longitud total de bits


tAssig_gray = 'gray';
tAssig_sec='bin';
p=[1]; %Canal discreto equivalente
figure()
M = 4^2; %16 QAM                 
Es = 2*(M-1)/3;         %Energía de simbolo promedio
m = log2(M);            %Nº bits por simbolo
SNR_dB = dB+10*log10(m);
    
B = combinaciones_vector';
A_gray = qammod(B,M,tAssig_gray,'InputType','bit');%Modulación con asignación binaria de gray
A_sec = qammod(B,M,tAssig_sec,'InputType','bit');%Modulación con asignación binaria secuencial


% Desmodulación de A_gray y A_sec para obtener los bits
bits_gray = qamdemod(A_gray, M, tAssig_gray, 'OutputType', 'bit');
bits_sec = qamdemod(A_sec, M, tAssig_sec, 'OutputType', 'bit');

% Agrupar los bits en grupos de 4
bits_agrupados_gray = reshape(bits_gray, 4, []).';
bits_agrupados_sec = reshape(bits_sec, 4, []).';

% Crear una tabla para comparar los grupos de bits y su respectiva codificación
tabla_comparativa = table(bits_agrupados_gray,  A_gray, bits_agrupados_sec, A_sec);

% Asignar nombres a las columnas
tabla_comparativa.Properties.VariableNames = {'Bits_Gray', 'Codificacion_Gray','Bits_Sec', 'Codificacion_Sec'};

% Mostrar la tabla
disp(tabla_comparativa);





