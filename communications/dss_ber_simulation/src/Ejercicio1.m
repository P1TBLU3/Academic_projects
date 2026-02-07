clc               % Limpia la ventana de comandos
clear             % Borra todas las variables en el espacio de trabajo
close all         % Cierra todas las figuras abiertas

M = 4;            % Orden de la constelación (número de símbolos en la constelación)
m = log2(M);      % Bits por símbolo (log2(M))
nSimb = 2e5;      % Número de símbolos en la simulación
nBits = nSimb * m; % Número total de bits en la simulación
tAssign = 'gray'; % Tipo de asignación binaria ('gray', 'bin')
N = 11;           % Longitud de la secuencia DSSS
x = zeros(4, 11);
x(1, :) = ones(1, N); % Secuencia DSSS para x0
x(2, :) = [+1 -1 +1 -1 +1 -1 +1 -1 +1 -1 +1]; % Secuencia DSSS para x1
x(3, :) = [-1 -1 -1 +1 +1 +1 -1 +1 +1 -1 +1]; % Secuencia DSSS para x2
x(4, :) = [-1 -1 -1 +1 +1 -1 +1 +1 +1 -1 +1]; % Secuencia DSSS para x3
a = 9/10;
n = 0:1:50;
d = a.^n;          % Secuencia de atenuación exponencial
Energia_d = sum(d.^2);

Var = [0 1];
Energia_pn = zeros(1, 4);
Dpico = zeros(1, 4);
YISI = zeros(1, 4);
Pe = zeros(2, 4);
BER = zeros(2, 4);
c = zeros(1, 21);
tiempo = 0:1:20;
figure()

% Bucle principal para iterar sobre las secuencias DSSS
for i = 1:4
    xi = x(i, :);  % Selecciona la secuencia DSSS
    c = xcorr(xi); % Calcula la autocorrelación de la secuencia
    B = randi([0 1], 1, nBits); % Genera una secuencia binaria aleatoria
    Bsimb = zeros(m, nSimb);
    Bsimb(:) = B;
    Bdec = transpose(bin2dec(num2str(Bsimb')));
    A = pammod(Bdec, M, 0, tAssign); % Modulación PAM de la secuencia decimal
    s = kron(A, xi); % Repetición de la señal modulada por la secuencia DSSS
    p = DSSS_p(xi, d); % Procesamiento DSSS
    Energia_pn(i) = sum(p.^2);
    Pabs = abs(p);
    Pmax = max(Pabs);
    
    Dpico(i) = sum(Pabs(Pabs ~= Pmax)) / Pmax ;  
    ISI(i) = Dpico(i) * max(abs(A));

    % Bucle para iterar sobre los dos niveles de varianza del canal ruidoso
    for k = 1:2
        Kd = length(d) - 1;
        v = conv([zeros(1, Kd), s], d);
        v = v(Kd + 1: Kd + length(s));
        v = v + sqrt(Var(k)) * randn(size(v));

        xp = repmat(xi, 1, length(A));
        aux = v .* conj(xp);
        aux = reshape(aux, N, length(A));
        q = sum(aux);
        qn = q / Pmax;

        Bdec_est = pamdemod(qn, M, 0, tAssign);
        A_est = pammod(Bdec_est, M, 0, tAssign);

        B_est = transpose(dec2bin(Bdec_est) - '0');
        B_est = transpose(B_est(:));

        Pe(k, i) = length(find(A_est ~= A)) / length(A);
        BER(k, i) = length(find(B_est ~= B)) / length(B);

        % Gráficos de autocorrelación
        subplot(2, 2, i)
        plot(tiempo, c)
        xlabel('Tiempo'), ylabel('Autocorrelacion')
    end
end

Energia_pn
Dpico
ISI
Pe
BER
