// Tic-tac-toe
// Компьютер будет играть в крестики-нолики против пользователя
#include <string>
#include <vector>
#include <vector>
#include <iostream>
#include <locale>
using namespace std;
// глобальные переменные
const char X = 'X'; // 1 участник игры
const char O = 'O'; // 2 участник игры
const char Empty = ' '; // пустая клетка
const char Tie = 'T'; // ничейный исход
const char NO_ONE = 'N'; // в игре пока что никто не победил
// прототипы функций
void instructions(); // функция, которая будет отображать основные правила игры
char askYesNo(string question); // функция, которая задает вопрос. Ответ на который только Да/нет
int askNumber(string question, int high, int low = 0); // функция, которая запрашивает число из диапозона т.е место куда будет ходить игрок
char humanPiece(); // фукнция, которая определяет какими фигурами будет ходить первый пользователь X/O
char opponent(char piece); // зная какими фигурами будет ходить пользователь, определяет какими фигурами ходит компьютер
void displayBoard(const vector<char>& board); // отображает и получает игровое поле
char winner(const vector<char>& board); // Определяет победителя игры. Получает поле. Возвращает символ X или О
bool isLegal(const vector<char>& board, int move); // функция определяет по правилам ли сделан ход, получает поле и возвращает значение true или false
int humanMove(const vector<char>& board, char human); // Узнает ход пользоваетля, получает поле и фигуру, которой ходит пользователь. ВОзвращает ход пользователя.
int computerMove(vector<char> board, char computer); // Узнает ход компьюетра, возвращает ход компьютера
void announceWinner(char winner, char computer, char human); // Поздравляет победителя или объявляет ничью

// функция main
int main()
{
	setlocale(LC_ALL, "Russian");
	int move;
	const int NUM_SQUARES = 9; // создание секвенций
	vector<char> board(NUM_SQUARES, Empty); // создание пустого игрового поля
	instructions(); // правила игры
	char human = humanPiece(); // обращение к функции humanPiece
	char computer = opponent(human); // обращение к функции opponent 
	char turn = X; 
	displayBoard(board); // отображает и получает игровое поле
	while (winner(board) == NO_ONE)
	{
		if(turn == human)
		{
			move = humanMove(board, human); // ход человека 
			board[move] = human;
		}
		else
		{
			move = computerMove(board, computer); // ход машины
			board[move] = computer;
		}
		displayBoard(board);
		turn = opponent(turn);
	}
	announceWinner(winner(board), computer, human);
	return 0;
}

void instructions()
{
	cout << "Добро пожаловать на финальное противостояние человека и машины.\n";
	cout << "Здесь человеческий мозг противостоит кремниевому процессору.\n\n";
	cout << "Чтобы сходить сообщите о своем перемещении, введя номер 0 - 8.\n";
	cout << "Числа соответсвуют положению доски, показанной на рисунке:\n\n";
	cout << " 0 | 1 | 2\n";
	cout << "----------\n";
	cout << " 3 | 4 | 5\n";
	cout << "----------\n";
	cout << " 6 | 7 | 8\n\n";
	cout << "Приготовься, кожный мешок. Битва вот-вот начнется!\n\n";
}

char askYesNo(string question) // Программа продолжает задавать вопрос yes / no, пока пользователь не даст ответ
{
	char response;
	do
	{
		cout << question << "(y/n)";
		cin >> response;
	} while (response != 'y' && response != 'n');
	return response;
}

int askNumber(string question, int high, int low) // Программа запршивает число пользователя, в какое место ходить 
{
	int number;
	do
	{
		cout << question << " (" << low << " _ " << high << "); ";
		cin >> number;
	} while (number > high || number < low);
	return number;
}

char humanPiece() // Программа спрашивает пользователя, хочет ли он пойти первым? По традиции X ходят первыми
{
	char go_first = askYesNo("Хочешь ли ты сделать ход первым?");
	if (go_first == 'y')
	{
		cout << "\nТогда сделай ход первым.\n";
		return X;
	}
	else
	{
		cout << "\nТвоя храбрость погубит тебя... Я схожу первым.\n";
		return O;
	}
}

char opponent(char piece) 
{
	if (piece == X)
	{
		return O;
	}
	else 
	{
		return X;
	}
}

void displayBoard(const vector<char>& board) // вектор, представляющий игровое поле передается с помощью константной ссылки.
// Таким образом, передача вектора организована эффективно, он не копируется. Вектор надежно защещен, это хорошо, так как я хочу просто отобразить игровое поле.
{
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n\n";
}

char winner(const vector<char>& board)
{
	// все возможные выигрышные варианты
	const int Winning_rows[8][3] = {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{0, 3, 6},
		{1, 4, 7},
		{2, 5, 8},
		{0, 4, 8},
		{2, 4, 6} };
	/* Во - первых, вектор, который представляет игровое поле передается через константную ссылку.
	 передача вектора организована эффективно, он не копируется и он защищен от любых изменений.
	 В начальной части функции, мы определяем массив целых чисел. Эта константа называется Winning_rows.
	 В ней представлены все способы заполнить фигурами одну из трех линий и выиграть.
	*/
	const int TOTAL_ROWS = 8;
	/* Если в одном из выигрышных рядов уже присутсвуют три одинаковых значения(и они не empty),
	то победитель определился.*/

	for (int row = 0; row < TOTAL_ROWS; ++row)
	{
		if ((board[Winning_rows[row][0]] != Empty) &&
			(board[Winning_rows[row][0]] == board[Winning_rows[row][1]]) &&
			(board[Winning_rows[row][1]] == board[Winning_rows[row][2]]))
		{
			return board[Winning_rows[row][0]];
		}
	}
	/* Я перебираю все возможные способы, которыми игрок может победить, проверяя нет ли в любом
	 из выигрышных рядов трёх одинаковых символов и не равны ли они EMPTY.
	 Поскольку победитель не определяется, проверяем не наступила ли ничья
	 Остались ли на поле пустые клетки */

	if (count(board.begin(), board.end(), Empty) == 0)
		return Tie; // ничейный исход
	// Поскольку победитель не определился и ничья не наступила, игра продолжается.
	return NO_ONE; // в игру никто не победил
}

/* Данная функция (нижняя) получает игровое поле и сделанный ход. Она возвращает true,
 если ход сделан по правилам, и false - если не по правилам. Ход по правилам
 заключается во вставке символа X или О в пустую клетку. */

inline bool isLegal(int move, const vector<char>& board)
{
	return (board[move] == Empty);
}

/* Функция humanMove() получает игровое поле и ту фигуру, которой ходит пользователь.
Она возвращает номер той клетки, в которую пользователь хочет поставить свой символ.
Функция запрашивает у пользоваетеля номер клетки, в которую хочет поставить символ
и ждет пока пользователь не сходит по правилам, затем функция возвращает сделанный ход.
*/


int humanMove(const vector<char>& board, char human) // передача вектора организована через константную ссылку.
// Таким образом, передача вектора организована эффективно - он не копируется.
{
	int move = askNumber("Куда ты хочешь сходить?", (board.size() - 1));
	while (!isLegal(move, board))
	{
		cout << "\nЭта клетка уже занята, глупый ты человек!\n";
		move = askNumber("Куда ты сходишь теперь?", (board.size() - 1));
	}
	cout << "\nНормально-нормально...\n";
	return move;
}

int computerMove(vector<char> board, char computer) // Функция получает игровое поле и ту фигуру, которой ходит компьютер
{
	unsigned int move = 0;
	bool found = false;
	// если компьютер может выиграть следующим ходом, то он сделает этот ход.

	while (!found && move < board.size()) // сначала я перебираю в цикле все возможные варианты хода от 0 до 8
	{
		if (isLegal(move, board)) // Если ход допустим правилами
		{
			board[move] = computer; // ставлю фигуру компьютера в выбранную клетку.
			found = winner(board) == computer;
			board[move] = Empty;
		}
		if (!found)
		{
			++move; // если ход не дает победы, то ставлю фигуру в следующую клетку
		}
	}

	// если человек может победить следующим ходом, то блокировать этот ход

	if (!found) 
	{
		move = 0;
		char human = opponent(computer);
		while (!found && move < board.size()) // Перебираю в цикле все возможные варинаты хода от 0 до 8.
		{
			if (isLegal(move, board)) // Проверяю, не противоречит ли ход правилам. 
			{
				board[move] = human;
				found = winner(board) == human;
				board[move] = Empty;
			}
			if (!found)
			{
				++move;
			}
		}
	}

	// иначе занять следующим ходом оптимальную свободную клетку
	if (!found)
	{
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
		// выбрать оптимальную свободную клетку
		while (!found && i < board.size())
		{
			move = BEST_MOVES[i];
			if (isLegal(move, board))
			{
				found = true;
			}
			++i;
		}
	}

	cout << "Я займу клетку под номером: " << move << endl;
	return move;
}

/* 
   На данном этапе выполнения функции я нашел ход, который должен сделать компьютер.
   В зависимости от ситуации этот ход может принести победу компьютеру, не допустить победы пользователя
   или просто занять хорошее место.
*/

void announceWinner(char winner, char computer, char human)
{
	if (winner == computer)
	{
		cout << "Я победил!!!\n";
		cout << "Я снова торжествую!!!\n";
		cout << "Компьютеры превосходят людей во всех отношениях!!!\n";
	}
	else if (winner == human)
	{
		cout << "Ты победил...\n";
		cout << "Нет, нет! Этого не может быть! Каким - то образом ты обманул меня, человек.\n";
		cout << "Но больше ты никогда меня не победишь!!!\n";
	}
	else
	{
		cout << "Это ничья.\n";
		cout << "Ты не такой тупой, каким кажешься.\n";
		cout << "Празднуй, потому что это лучшее, чего ты когда-либо достигнешь!\n";
	}
}