clc                % Limpia la ventana de comandos
clear              % Borra todas las variables en el espacio de trabajo
close all          % Cierra todas las figuras abiertas

M = 4;             % Orden de la constelación (número de símbolos en la constelación)
m = log2(M);       % Bits por símbolo (log2(M))
nSimb = 2e5;       % Número de símbolos en la simulación
nBits = nSimb * m; % Número total de bits en la simulación
tAssign = 'gray';  % Tipo de asignación binaria ('gray', 'bin')
N = 11;            % Longitud de la secuencia DSSS
x1 = [+1 -1 +1 -1 +1 -1 +1 -1 +1 -1 +1]; % Secuencia DSSS para Usuario A
x2 = [-1 -1 -1 +1 +1 +1 -1 +1 +1 -1 +1]; % Secuencia DSSS para Usuario B
x3 = [-1 -1 -1 +1 +1 -1 +1 +1 +1 -1 +1]; % Otra secuencia DSSS para Usuario B (diferente de x2)
a = 9/10;          % Factor de atenuación para la secuencia DSSS
n = 0:1:50;
d = a.^n;          % Secuencia de atenuación exponencial
Kd = length(d) - 1; % Longitud de retardo para la convolución
Var = [0 1];       % Vector de dos niveles de varianza para el canal ruidoso

Pe_UsA = zeros(2, 3);  % Matriz para almacenar la probabilidad de error de símbolo para Usuario A
Pe_UsB = zeros(2, 3);  % Matriz para almacenar la probabilidad de error de símbolo para Usuario B
BER_UsA = zeros(2, 3); % Matriz para almacenar la tasa de error de bits para Usuario A
BER_UsB = zeros(2, 3); % Matriz para almacenar la tasa de error de bits para Usuario B
P_escalar = zeros(1, 3); % Vector para almacenar el producto escalar de las secuencias DSSS

X_UsA = [x1; x1; x2]; % Matriz de secuencias DSSS para Usuario A
X_UsB = [x2; x3; x3]; % Matriz de secuencias DSSS para Usuario B

B = randi([0 1], 1, nBits); % Genera una secuencia binaria aleatoria
Bsimb = zeros(m, nSimb);
Bsimb(:) = B;
Bdec = transpose(bin2dec(num2str(Bsimb')));
A = pammod(Bdec, M, 0, tAssign); % Modulación PAM de la secuencia decimal

% Bucle principal para iterar sobre las secuencias DSSS
for i = 1:3
    x_UsA = X_UsA(i, :);  % Selecciona la secuencia DSSS para Usuario A
    x_UsB = X_UsB(i, :);  % Selecciona la secuencia DSSS para Usuario B
    s_UsA = kron(A, x_UsA); % Repetición de la señal modulada por la secuencia DSSS para Usuario A
    s_UsB = kron(A, x_UsB); % Repetición de la señal modulada por la secuencia DSSS para Usuario B
    p_UsA = DSSS_p(x_UsA, d); % Procesamiento DSSS para Usuario A
    p_UsB = DSSS_p(x_UsB, d); % Procesamiento DSSS para Usuario B
    Pabs_UsA = abs(p_UsA);
    Pabs_UsB = abs(p_UsB);
    Pmax_UsA = max(Pabs_UsA);
    Pmax_UsB = max(Pabs_UsB);

    % Bucle para iterar sobre los dos niveles de varianza del canal ruidoso
    for k = 1:2
        v_A = conv([zeros(1, Kd), s_UsA], d);
        v_B = conv([zeros(1, Kd), s_UsB], d);
        v_A = v_A(Kd + 1: Kd + length(s_UsA));
        v_B = v_B(Kd + 1: Kd + length(s_UsB));
        v = v_A + v_B + sqrt(Var(k)) * randn(size(v_A)); % Adición de ruido blanco gaussiano

        xp_A = repmat(x_UsA, 1, length(A));
        xp_B = repmat(x_UsB, 1, length(A));
        aux_A = v .* conj(xp_A);
        aux_B = v .* conj(xp_B);
        aux_A = reshape(aux_A, N, length(A));
        aux_B = reshape(aux_B, N, length(A));
        q_A = sum(aux_A);
        qn_A = q_A / Pmax_UsA;
        q_B = sum(aux_B);
        qn_B = q_B / Pmax_UsB;

        Bdec_est_A = pamdemod(qn_A, M, 0, tAssign);
        Bdec_est_B = pamdemod(qn_B, M, 0, tAssign);
        A_est_A = pammod(Bdec_est_A, M, 0, tAssign);
        A_est_B = pammod(Bdec_est_B, M, 0, tAssign);
        B_est_A = transpose(dec2bin(Bdec_est_A) - '0');
        B_est_A = transpose(B_est_A(:));
        B_est_B = transpose(dec2bin(Bdec_est_B) - '0');
        B_est_B = transpose(B_est_B(:));

        % Cálculo de la probabilidad de error de símbolo y la tasa de error de bits
        Pe_UsA(k, i) = length(find(A_est_A ~= A)) / length(A);
        Pe_UsB(k, i) = length(find(A_est_B ~= A)) / length(A);
        BER_UsA(k, i) = length(find(B_est_A ~= B)) / length(B);
        BER_UsB(k, i) = length(find(B_est_B ~= B)) / length(B);

        % Cálculo del producto escalar entre las secuencias DSSS para Usuario A y B
        Suma = 0;
        for z = 1:N
            Suma = Suma + x_UsA(z) * x_UsB(z);
        end
        P_escalar(i) = Suma;
    end
end

% Muestra los resultados
P_escalar
Pe_UsA
Pe_UsB
BER_UsA
BER_UsB

