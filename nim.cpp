#include <std_lib_facilities.h>

vector<int> start_nim() { //функция для ввода стартового состояния игры
    cout << "Please, enter number of strings and rocks in your start version of Nim" << endl;
    int len = 3; 
    cin >> len; //ввод количества строк в игре
    if (!cin) throw runtime_error("Bad enter, you lose! I warned you about letters and signs! Try again, use only numbers"); 
       // проверка ввода на корректность. Mожно было бы разрешить пользователю играть дальше при некорректном вводе, но мне так проще выходить из тестовых запусков
    while (len < 1) {
        cout << "NOOOO, you should natural number of strings! Try again" << endl;
        cin >> len;
        if (!cin) throw runtime_error("Bad enter, you lose! I warned you about letters and signs! Try again, use only numbers"); // проверка ввода на корректность
    }

    vector<int> start;
    for (int i = 0; i < len; i++){ //ввод количества камней в каждой строке
        int rocks = 0;
        cin >> rocks;
        if (!cin) throw runtime_error("Bad enter, you lose! I warned you about letters and signs! Try again, use only numbers"); // проверка ввода на корректность
        while (rocks < 1) {
        cout << "NOOOO, you should natural number of rocks! Try again" << endl;
        cin >> rocks;
        if (!cin) throw runtime_error("Bad enter, you lose! I warned you about letters and signs! Try again, use only numbers"); // проверка ввода на корректность
    }
        start.push_back(rocks);
    }
    return start; //возврат значений в игру
}

vector<int> hod(vector<int> nim) { //функция хода игрока
    int str, rocks;
    cin >> str >> rocks;
        if (!cin) throw runtime_error("Bad enter, you lose! I warned you about letters and signs! Try again, use only numbers"); // проверка ввода на корректность
    while (((str > nim.size()) || (str < 1)) || ((rocks > nim[str-1]) || (rocks < 1))) { //обработка неправильных попыток взять несуществующий камень/из несуществующей строки
        if ((str > nim.size()) || (str < 1)) cout << "Warning! You should enter number of strings from 1 to " << nim.size() << ". Try again" << endl; // обработка ошибки ввода строки
        else cout << "Warning! You should enter number of rocks from 1 to " << nim[str-1] << " for this (" << str << ") string. Try again" << endl; //обработка ошибки ввода камней
        cin >> str >> rocks; //повторная попытка ввода хода пользователя
        if (!cin) throw runtime_error("Bad enter, you lose! I warned you about letters and signs! Try again, use only numbers"); // проверка ввода на корректность
    }
    return {str, rocks}; //передача данных пользователя игре
}

vector<int> Comp(vector<int> nim) { //функция хода компьютера
    int x0r = nim[0] ^ nim[1] ^ nim[2];
    for (int i = 0; i < nim.size(); ++i) { //перебираем строки
        if (nim[i] != 0) { //ищем строку, где есть камни
            if (x0r != 0) { //если ксор-сумма всех строк нулевая, выигрышной стратегии нет
                if ((x0r ^ nim[i]) < nim[i]) { //выигрышная стратегия 
                    return {i, nim[i] - (x0r ^ nim[i])};
                }
            } else return {i, 1};
        }
    }
}

vector<int> gameplay(vector<int> nim, int steps, bool game_run) { //реализация одного хода игрока/компьютера
    for (int i = 0; i < nim.size(); ++i) { //вывод состояния игры
        int num_pizda = nim[i]; //беру каждую строку по очереди
        string design = "";
        for (int l = 0; l < num_pizda; ++l){ //набор нужного количетва звездочек
            design += "* ";
        }
        cout << i+1 << "(" << nim[i] << "): "<< design << endl; //вывод номера строки, количества камней и звездочек
    }

    if (steps % 2 == 0) { //для игрока и компьютера действия программы одинаковы. В четные итерации цикла(первым) ходит игрок, в нечетные - компьютер
        cout << "Your turn: enter string number and count of rocks you want to remove" << endl;
        vector<int> turn = hod(nim);
        nim[turn[0] - 1] -= turn[1]; //ход игрока, поправка на неправильный ввод номера строки
    } else {
        cout << "Computer's turn: ";
        vector<int> turn = Comp(nim); 
        nim[turn[0]] -= turn[1]; //ход компьютера
        cout << turn[0] + 1 << " " << turn[1] << endl;
    }
    return nim;
}

int main() {
    try {
        cout << "----------------------------------------   Welcome, let's play NIM   -----------------------------------------" << endl;
        cout << "***** Attention! You should enter only numbers! If you enter something else, the game would be over *****" << endl;
        vector<int> nim = start_nim(); 
        bool game_run = true; 
        int steps = 0;
        while(game_run) { //проверяет, что игра еще не закончилась
            vector<int> dop = nim;
            int shag = steps;
            nim = gameplay(dop, shag, game_run);

            int sum = 0;
            for (int i = 0; i < nim.size(); ++i) { 
                sum += nim[i];
            }
            if (sum < 1){ //проверка кол-ва камней в игре
                game_run = false; //предварительная остановка игры
                cout << "GAME OVER" << endl; //сообщения об остановке игры
                if (steps % 2 == 0){ 
                    cout << "--------------------------   Congratulations, you won!   ------------------------------------" << endl;
                } else {
                    cout << "--------------------------   You lose, try again      -----------------------------------" << endl;
                }
            }
            steps++;
        }
    } catch(exception& e) {
        cerr << e.what();
        return -2;
    }
}



