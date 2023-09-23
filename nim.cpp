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
        start.push_back(rocks); //добавляю новую строку в массив состояния игры
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
    int x0r = nim[0] ^ nim[1] ^ nim[2]; //ним-сумма
    for (int i = 0; i < nim.size(); ++i) { //перебираем строки
        if (nim[i] != 0) { //ищем строку, где есть камни
            if (x0r != 0) { //если ксор-сумма всех строк нулевая, выигрышной стратегии нет
                if ((x0r ^ nim[i]) < nim[i]) { //выигрышная стратегия 
                    return {i, nim[i] - (x0r ^ nim[i])};
                }
            } else return {i, 1}; //нет выгрышной стратегии, берем камень из первой ненулевой строки
        }
    }
}

vector<int> gameplay(vector<int> nim, int steps, bool game_run) { //реализация одного хода игрока/компьютера
    for (int i = 0; i < nim.size(); ++i) { //вывод состояния игры
        int numer_stroki = nim[i]; //беру каждую строку по очереди
        string design = "";
        for (int l = 0; l < numer_stroki; ++l){ //набор нужного количетва звездочек
            design += "* ";
        }
        cout << i+1 << "(" << nim[i] << "): "<< design << endl; //вывод номера строки, количества камней и звездочек
    }
    if (steps % 2 == 0) { //для игрока и компьютера действия программы одинаковы. В четные итерации цикла(первым) ходит игрок, в нечетные - компьютер
        cout << "Your turn: enter string number and count of rocks you want to remove" << endl;
        vector<int> turn = hod(nim); //реализация хода пользователя
        nim[turn[0] - 1] -= turn[1]; //изменение состояния игры, поправка на неправильный ввод номера строки
    } else {
        cout << "Computer's turn: ";
        vector<int> turn = Comp(nim); //реализация хода компьютера
        nim[turn[0]] -= turn[1]; //изменение состояния игры
        
        cout << turn[0] + 1 << " " << turn[1] << endl;
    }
    return nim;
}

int main() {
    try {
        cout << "----------------------------------------   Welcome, let's play NIM   -----------------------------------------" << endl;
        cout << "***** Attention! You should enter only numbers! If you enter something else, the game would be over *****" << endl;
        vector<int> nim = start_nim(); //задает начальное состояние игры
        bool game_run = true; 
        int steps = 0; //количество пройденных итераций игры, от него зависит, кто делает код
        while(game_run) { //проверяет, что игра еще не закончилась
            vector<int> dop = nim; //костыль для избежания рекурсивной функции gameplay
            nim = gameplay(dop, steps, game_run);  //реализация кода

            int sum = 0;
            for (int i = 0; i < nim.size(); ++i) { //проверка кол-ва камней в игре
                sum += nim[i];
            }
            if (sum < 1){ //если камни закончились
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
    } catch(exception& e) { //ловит какие-то странные ошибки
        cerr << e.what();
        return -2;
    }
}



