import java.util.Scanner;
import java.lang.Math;

public class FINAL_PABLO_MARIO {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		char[][] tablero = new char[3][3];
		boolean check = false, disponible, repeat = false;
		String pos = "", respuesta, jugador1 = "", jugador2 = "", fichas = "X0ABCDEFGHIJKLMNOPQRSTUVWYZ+*-@1", aux = "";
		char ficha1 = ' ', ficha2 = ' ';
		int empates = 0, victoriaJugador1 = 0, victoriaJugador2 = 0;
		do {
			System.out.println("Bienvenido a las 3 en raya, elija un modo de juego");
			System.out
					.println("Inserte 1 para el modo jugador contra la IA y 2 para modo  jugador contra jugador local");
			respuesta = input.nextLine();
			if (respuesta.equals("1") || respuesta.equals("2")) {
				check = true;
			} else {
				System.out.println("Por favor, elija una respuesta v�lida.");
			}
		} while (check == false);
		if (respuesta.equals("2")) {
			System.out.println("Escriba un nombre para el Jugador_1");
			do {
				check = true;
				jugador1 = input.nextLine();
				check = jugador1.length() > 0;
				if (!check) {
					System.out.println("El nombre introducido es demasiado corto");
				}
			} while (check == false);
			System.out.println(fichas + "\nElije tu ficha:");
			do {
				aux = input.nextLine();
				ficha1 = aux.charAt(0);
				check = (fichas.contains("" + ficha1));
				if (!check) {
					System.out.println("Elija una respuesta v�lida");
				}
			} while (check == false);
			System.out.println("Escriba un nombre para el Jugador_2");
			do {
				check = true;
				fichas = fichas.substring(0, fichas.indexOf(ficha1)) + fichas.substring(fichas.indexOf(ficha1) + 1);
				jugador2 = input.nextLine();
				check = jugador2.length() > 0;
				if (!check) {
					System.out.println("El nombre introducido es demasiado corto");
				}
			} while (check == false);
			System.out.println(fichas + "\n Elije tu ficha:");
			do {
				check = true;
				aux = input.nextLine();
				ficha2 = aux.charAt(0);
				check = (fichas.contains("" + ficha2));
				if (!check) {
					System.out.println("Escoge una ficha disponible");
				}
			} while (check == false);
			do {
				if (repeat == true) {
					System.out.println("Victorias de " + jugador1 + ": " + victoriaJugador1 + "\n Victorias de "
							+ jugador2 + ": " + victoriaJugador2 + "Empates: " + empates);
				}
				for (int i = 0; i < tablero.length; i++) {
					for (int j = 0; j < tablero.length; j++) {
						tablero[i][j] = ' ';
					}
				}
				int turno = 0;
				boolean victoria = false;
				display(tablero);
				for (int i = 1; i < 10; i++) {
					System.out.println("Fichas introducidas: " + (i - 1));
					if (i % 2 == 1) {
						System.out.println("Turno de " + jugador1 + ":");
						System.out.println("Elija una casilla:");
						do {
							disponible = true;
							pos = input.nextLine();
							disponible = valido(pos, tablero);
							if (disponible == false)
								System.out.println(
										"Seleccione una casilla disponible por favor y recuerde usar el formato (N�,N�).");
						} while (disponible == false);
						eleccion(tablero, ficha1, pos);
					} else if (i % 2 == 0) {
						System.out.println("Turno de " + jugador2 + ":");
						System.out.println("Elija una casilla:");
						do {
							disponible = true;
							pos = input.nextLine();
							disponible = valido(pos, tablero);
							if (disponible == false)
								System.out.println(
										"Seleccione una casilla disponible por favor y recuerde usar el formato (N�,N�).");
						} while (disponible == false);
						eleccion(tablero, ficha2, pos);
					}
					display(tablero);
					victoria = condicionVictoria(tablero, ficha1, ficha2);
					if (victoria) {
						break;
					}
					turno = i;
				}
				if (victoria == false) {
					empates++;
					System.out.println("�Habeis empatado!");
				} else if (turno % 2 == 0) {
					System.out.println("�La victoria es para " + jugador1 + "!");
					victoriaJugador1++;
				} else {
					System.out.println("�La victoria es para " + jugador2 + "!");
					victoriaJugador2++;
				}
				System.out.println("�Quer�is jugar la revancha?");
				boolean valorValido = false;
				do {
					System.out.println("(S) para la jugar revancha. \n(N) si no quieres seguir jugando.");
					aux = input.nextLine();
					if (aux.equals("N") || aux.equals("S")) {
						valorValido = true;
					} else {
						valorValido = false;
					}
					if (!valorValido) {
						System.out.println("Introduzca una respuesta v�lida:");
					}
				} while (!valorValido);
				if (aux.equals("S")) {
					repeat = true;
				} else {
					repeat = false;
				}
			} while (repeat == true);

		} else {
			ficha2 = '0';
			System.out.println("Escriba un nombre para el Jugador_1:");
			do {
				jugador1 = input.nextLine();
				check = true;
				check = jugador1.length() > 0;
				if (!check) {
					System.out.println("El nombre introducido es demasiado corto.");
				}
			} while (!check);
			fichas = "XABCDEFGHIJKLMNOPQRSTUVWYZ+*-@1";
			System.out.println(fichas + "\n Elije tu ficha:");
			do {
				aux = input.nextLine();
				check = true;
				ficha1 = aux.charAt(0);
				check = (fichas.contains("" + ficha1));
				if (!check) {
					System.out.println("Escoge una ficha disponible.");
				}
			} while (check == false);
			do {
				if (repeat == true) {
					System.out.println("Empates: " + empates);
					System.out.println("Victorias de " + jugador1 + ": " + victoriaJugador1 + "\nVictorias de la IA: "
							+ victoriaJugador2);
				}
				for (int i = 0; i < tablero.length; i++) {
					for (int j = 0; j < tablero.length; j++) {
						tablero[i][j] = ' ';
					}
				}
				boolean victoria = false;
				display(tablero);
				int turno = 0;
				for (int i = 1; i < 10; i++) {
					System.out.println("Fichas introducidas: " + (i - 1));
					if (i % 2 == 1) {
						System.out.println("Turno de " + jugador1);
						System.out.println("Seleccione una casilla:");
						do {
							disponible = true;
							pos = input.nextLine();
							disponible = valido(pos, tablero);
							if (!disponible)
								System.out.println("Elija una casilla disponible por favor.");
						} while (!disponible);
						eleccion(tablero, ficha1, pos);
					} else if (i % 2 == 0) {
						do {
							disponible = true;
							pos = "(" + random() + "," + random() + ")";
							disponible = valido(pos, tablero);
							;
						} while (!disponible);
						eleccion(tablero, ficha2, pos);
					}
					display(tablero);
					victoria = condicionVictoria(tablero, ficha1, ficha2);
					if (victoria) {
						break;
					}
					turno = i;
				}
				if (!victoria) {
					empates++;
					System.out.println("�Habeis empatado!");
				} else if (turno % 2 == 0) {
					victoriaJugador1++;
					System.out.println("�La victoria es para " + jugador1 + "!");
				} else {
					victoriaJugador2++;
					System.out.println("�Vaya, has perdido!");
				}
				System.out.println("�Quieres jugar la revancha?");
				check = false;
				do {
					System.out.println("(S) para la jugar revancha. \n(N) si no quieres seguir jugando.");
					aux = input.nextLine();
					if (aux.equals("N") || aux.equals("S")) {
						check = true;
					} else {
						check = false;
					}
					if (!check) {
						System.out.println("Introduzca una respuesta v�lida");
					}
				} while (!check);
				if (aux.equals("S")) {
					repeat = true;
				} else {
					repeat = false;
				}
			} while (repeat == true);
		}
	}

	public static boolean condicionVictoria(char[][] tablero, char ficha1, char ficha2) {
		int contador1 = 0, contador2 = 0;
		for (int i = 0; i < tablero.length; i++) {
			for (int j = 0; j < tablero.length; j++) {
				if (tablero[j][i] == ficha1) {
					contador1++;
				} else if (tablero[j][i] == ficha2) {
					contador2++;
				}
			}
			if (contador1 == 3 || contador2 == 3) {
				return true;
			}
			contador1 = 0;
			contador2 = 0;
			for (int j = 0; j < tablero.length; j++) {
				if (tablero[i][j] == ficha1) {
					contador1++;
				} else if (tablero[i][j] == ficha2) {
					contador2++;
				}
			}
			if (contador1 == 3 || contador2 == 3) {
				return true;
			}
			contador1 = 0;
			contador2 = 0;
		}
		for (int i = 0; i < tablero.length; i++) {
			if (tablero[i][i] == ficha1) {
				contador1++;
			} else if (tablero[i][i] == ficha2) {
				contador2++;
			}
		}
		if (contador1 == 3 || contador2 == 3) {
			return true;
		}
		contador1 = 0;
		contador2 = 0;
		for (int i = 0; i < tablero.length; i++) {
			if (tablero[i][tablero.length - 1 - i] == ficha1) {
				contador1++;
			} else if (tablero[i][tablero.length - 1 - i] == ficha2) {
				contador2++;
			}
		}
		if (contador1 == 3 || contador2 == 3) {
			return true;
		}
		return false;
	}

	public static void display(char[][] tablero) {
		String coordenadas = "       1     2     3 \n    ___________________\n";
		for (int i = 0; i < tablero.length; i++) {
			coordenadas += "    |     |     |     | \n" + (i + 1) + "   |";
			for (int j = 0; j < tablero.length; j++) {
				coordenadas += "  " + tablero[i][j] + "  |";
			}
			coordenadas += "\n    |_____|_____|_____|\n";
		}
		System.out.println(coordenadas);

	}

	public static int random() {
		int random = (int) (Math.random() * 4);
		return random;
	}

	public static boolean valido(String pos, char[][] tablero) {
		if (pos.length() != 5 || (pos.charAt(0) != '(') || (!(Character.isDigit(pos.charAt(1))))
				|| (pos.charAt(2) != ',') || (!(Character.isDigit(pos.charAt(3)))) || (pos.charAt(4) != ')')) {
			return false;
		} else {
			int fil = Integer.parseInt("" + pos.charAt(1));
			int col = Integer.parseInt("" + pos.charAt(3));
			if (fil < 1 || fil > 3 || col < 1 || col > 3) {
				return false;
			} else if (tablero[fil - 1][col - 1] == ' ') {
				return true;
			} else {
				return false;
			}
		}
	}

	public static void eleccion(char[][] tablero, char ficha, String pos) {
		tablero[(Integer.parseInt("" + pos.charAt(1))) - 1][Integer.parseInt("" + pos.charAt(3)) - 1] = ficha;
	}
}
