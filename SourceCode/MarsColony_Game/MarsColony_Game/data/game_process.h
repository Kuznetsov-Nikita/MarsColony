#pragma once

#include "fields.h"
#include "units.h"
#include "buildings.h"

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <windows.h>

// Версия игры
const std::string VERSION = "pre-alpha 0.0.3";

const std::pair<size_t, size_t> WINDOW_SIZE = std::make_pair(200, 60);                      // размеры окна консольного приложения
const size_t MIDDLE_BORDER_LEFT = 69;                                                       // левая граница линии по середине (в линии)
const size_t MIDDLE_BORDER_RIGHT = 71;                                                      // правая граница в линии по середине (не в линии)
const std::pair<size_t, size_t> VERSION_INFO_POSITION = std::make_pair(2, 1);               // позиция информации о версии
const std::pair<size_t, size_t> MENU_OUTPUT_POSITION = std::make_pair(11, 7);               // позиция для вывода меню
const std::pair<size_t, size_t> HELP_OUTPUT_POSITION = std::make_pair(3, 3);                // позиция для вывода справки
const std::pair<size_t, size_t> HELP_COMMANDLINE_OUTPUT_POSITION = std::make_pair(3, 58);   // позиция для вывода текста куда вводить в справке
const std::pair<size_t, size_t> HELP_COMMANDLINE_INPUT_POSITION = std::make_pair(26, 58);   // позиция для ввода команд в справке
const std::pair<size_t, size_t> MENU_COMMANDLINE_INPUT_POSITION = std::make_pair(40, 42);   // позиция для командной строки в меню
const std::pair<size_t, size_t> MENU_COMMANDLINE_MESSAGE_POSITION = std::make_pair(11, 43); // позиция для сообщений после ввода команды в меню
const std::pair<size_t, size_t> INFO_OUTPUT_POSITION = std::make_pair(2, 2);                // позиция информации
const std::pair<size_t, size_t> GAME_COMMANDLINE_INPUT_POSITION = std::make_pair(36, 56);   // позиция ввода команд в игре
const std::pair<size_t, size_t> FOOD_POSITION = std::make_pair(20, 5);                      // позиция еды
const std::pair<size_t, size_t> MONEY_POSITION = std::make_pair(20, 6);                     // позиция денег
const std::pair<size_t, size_t> MONEY_GROWTH_POSITION = std::make_pair(30, 6);              // позиция прироста денег
const std::pair<size_t, size_t> ENERGY_POSITION = std::make_pair(20, 7);                    // позиция энергии
const std::pair<size_t, size_t> ENERGY_GROWTH_POSITION = std::make_pair(30, 7);             // позиция прироста энергии
const std::pair<size_t, size_t> SCIENCE_POSITION = std::make_pair(20, 8);                   // позиция науки
const std::pair<size_t, size_t> SCIENCE_GROWTH_POSITION = std::make_pair(30, 8);            // позиция прироста науки
const std::pair<size_t, size_t> DETAILS_POSITION = std::make_pair(20, 9);                   // позиция деталей
const std::pair<size_t, size_t> DETAILS_GROWTH_POSITION = std::make_pair(30, 9);            // позиция прироста деталей

// Структура для хранения ресурсов
struct Resources {
    int food;           // еда

    int money;          // деньги
    int money_growth;   // прирост денег за ход

    int energy;         // энергия
    int energy_growth;  // прирост энергии за ход

    int scince;         // наука
    int scince_growth;  // прирост науки за ход

    int details;        // детали
    int details_growth; // прирост деталей за ход

    Resources(int f = 5, int m = 100, int m_g = 10, int e = 100, int e_g = 3, int s = 0, int s_g = 1, int d = 0, int d_g = 0): food(f), money(m), money_growth(m_g), energy(e), energy_growth(e_g), scince(s), scince_growth(s_g), details(d), details_growth(d_g) {}
};

// Класс GameInfo - данные игры
class GameInfo {
private:
    Resources resources = Resources(); // ресурсы

    int unit_discount = 0;     // скидка на создание юнитов
    int building_discount = 0; // скидка на постройку и улучшение зданий

    int science_bonus = 0;     // бонус к науке юнитов
    int military_bonus = 0;    // бонус к военной мощи юнитов
    int engeneering_bonus = 0; // бонус к инженерному делу юнитов

    std::vector<PlayerUnit> units;     // список юнитов игрока
    std::map<std::string, Building*> buildings = { {"main_building", Building::CreateBuilding(1)} }; // здания игрока
    std::map<std::string, bool> exist_building = { {"main_building", true}, {"science_center", false}, {"military_center", false}, {"farm", false}, {"solar_plant", false}, {"assembly_plant", false}, {"cargo_platform", false} }; // существует ли здание на данный момент
    std::map<int, bool> technologies = { {0, true}, {1, false}, {2, false}, {3, false}, {4, false}, {5, false}, {6, false}, {7, false}, {8, false}, {9, false}, {10, false}, {11, false} }; // технологии, изучены или нет
    std::vector<int> technology_cost = {0, 10, 10, 50, 50, 50, 50, 50, 100, 100, 100, 100};
    std::vector<int> prev_technology = {0, 0, 0, 1, 1, 2, 2, 2, 3, 4, 5, 6};
public:
    // Вернуть ресурсы
    Resources GetResources() {
        return resources;
    }

    // Прирастить ресурсы
    void GrowthResources() {
        resources.money += resources.money_growth;
        resources.energy += resources.energy_growth;
        resources.scince += resources.scince_growth;
        resources.details += resources.details_growth;
    }

    // Вернуть список  юнитов игрока
    std::vector<PlayerUnit> GetUnits() {
        return units;
    }

    // Вернуть здания игрока
    std::map<std::string, Building*> GetBuildings() {
        return buildings;
    }

    // Вернуть наличие здания игрока
    std::map<std::string, bool> GetBuildingsStatus() {
        return exist_building;
    }

    // Вернуть список технологий
    std::map<int, bool> GetTechnologies() {
        return technologies;
    }

    // Вернуть список стоимостей технологий
    std::vector<int> GetTechCost() {
        return technology_cost;
    }

    // Вернуть список требуемых предыдущих технологий
    std::vector<int> GetPrevTechnologies() {
        return prev_technology;
    }

    // Вернуть количество юнитов игрока
    int units_cnt() {
        return units.size();
    }

    // Вернуть скидку на постройку юнитов
    int GetUnitDiscount() {
        return unit_discount;
    }

    // Вернуть скидку на постройку и улучшение зданий
    int GetBuildingDiscount() {
        return building_discount;
    }

    // Добавить юнита
    void add_unit(int id) {
        if (resources.food > 0 || id == 4) {
            units.push_back(PlayerUnit::CreateUnit(1, units.size() + 1, id));
            if (id != 4) {
                --resources.food;
                resources.money -= 20 - unit_discount;
            } else {
                resources.energy_growth -= 3;
                resources.money -= 80 - unit_discount;
            }
            --resources.money_growth;

            if (id == 1) {
                units[units.size() - 1].add_bonus(science_bonus);
            }
            else if (id == 2) {
                units[units.size() - 1].add_bonus(military_bonus);
            }
            else if (id == 3) {
                units[units.size() - 1].add_bonus(engeneering_bonus);
            }
        }
    }

    // Добавить здание
    void add_building(std::string building_name) {
        std::map<std::string, int> building_id = { {"main_building", 1}, {"science_center", 2}, {"military_center", 3}, {"farm", 4}, {"solar_plant", 5}, {"assembly_plant", 6}, {"cargo_platform", 7} };
        if (!exist_building[building_name]) {
            buildings[building_name] = Building::CreateBuilding(building_id[building_name]);
            exist_building[building_name] = true;

            if (building_name == "science_center") {
                resources.scince_growth += 10;
                resources.money -= 200 - building_discount;
                resources.energy_growth -= 1;
            }
            else if (building_name == "military_center") {
                resources.money -= 200 - building_discount;
                resources.energy_growth -= 1;
            }
            else if (building_name == "farm") {
                resources.food += 5;
                resources.money -= 200 - building_discount;
                resources.energy_growth -= 1;
            }
            else if (building_name == "solar_plant") {
                resources.energy_growth += 10;
                resources.money -= 150 - building_discount;
            }
            else if (building_name == "assembly_plant") {
                resources.details_growth += 5;
                resources.money -= 150 - building_discount;
                resources.energy_growth -= 1;
            }
            else if (building_name == "cargo_platform") {
                resources.money_growth += 5;
                resources.money -= 150 - building_discount;
                resources.energy_growth -= 1;
            }
        }
    }

    // Добавить бонус юнитам
    void add_units_bonus() {
        for (int i = 0; i < units.size(); ++i) {
            if (units[i].GetID() == 1) {
                units[i].add_bonus(science_bonus);
            } else if (units[i].GetID() == 2) {
                units[i].add_bonus(military_bonus);
            } else if (units[i].GetID() == 3) {
                units[i].add_bonus(engeneering_bonus);
            }
        }
    }

    // Добавить технологию
    void add_technology(int number) {
        technologies[number] = true;
        resources.scince -= technology_cost[number];

        if (number == 5) {
            unit_discount += 10;
        } else if (number == 6) {
            building_discount += 50;
        }

        if (number == 1 || number == 3) {
            science_bonus += 1;
        } else if (number == 4 || number == 9) {
            military_bonus += 1;
        } else if (number == 6 || number == 11) {
            engeneering_bonus += 1;
        }

        if (number == 1 || number == 3 || number == 4 || number == 9 || number == 6 || number == 11) {
            add_units_bonus();
        }
    }
    
    // Улучшить здание
    void upgrade_building(std::string building_name) {
        if (exist_building[building_name]) {
            if (building_name == "main_building") {
                (*dynamic_cast<MainBuilding*>(buildings[building_name])).upgrade();
                resources.money_growth += 15;
                resources.energy_growth -= 1;
                resources.money -= 500 - building_discount;
            } else if (building_name == "science_center") {
                (*dynamic_cast<ScienceCenter*>(buildings[building_name])).upgrade();
                resources.scince_growth += 20;
                resources.energy_growth -= 1;
                resources.money -= 400 - building_discount;
            } else if (building_name == "military_center") {
                (*dynamic_cast<MilitaryCenter*>(buildings[building_name])).upgrade();
                resources.energy_growth -= 1;
                resources.money -= 400 - building_discount;
            } else if (building_name == "farm") {
                (*dynamic_cast<Farm*>(buildings[building_name])).upgrade();
                resources.food += 5;
                resources.energy_growth -= 1;
                resources.money -= 400 - building_discount;
            } else if (building_name == "solar_plant") {
                (*dynamic_cast<SolarPlant*>(buildings[building_name])).upgrade();
                resources.energy_growth += 20;
                resources.money -= 300 - building_discount;
            }
        }
    }

    // Обнулить информацию об игре
    void reset() {
        for (auto it = buildings.begin(); it != buildings.end(); ++it) {
            delete (*it).second;
        }

        buildings = { {"main_building", Building::CreateBuilding(1)} };
        exist_building = { {"main_building", true}, {"science_center", false}, {"military_center", false}, {"farm", false}, {"solar_plant", false}, {"assembly_plant", false}, {"cargo_platform", false} };
    }
};

// Класс Game - процесс игры
class Game {
private:
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // консоль
    COORD position; // Позиция курсора в консольном окне

    GameInfo data;  // Информация о игре

    // Изменить позицию курсора в консоли
    void ChangeCursorPosition(size_t x, size_t y) {
        position.X = x;
        position.Y = y;
        SetConsoleCursorPosition(hConsole, position);
    }

    // Стереть левую часть окна
    void ResetLeftTile() {
        for (size_t x = 2; x < MIDDLE_BORDER_LEFT; ++x) {
            for (size_t y = 2; y < WINDOW_SIZE.second - 1; ++y) {
                ChangeCursorPosition(x, y);
                std::cout << ' ';
            }
        }
    }

    // Стереть правую часть окна
    void ResetRightTile() {
        for (size_t x = MIDDLE_BORDER_RIGHT; x < WINDOW_SIZE.first - 2; ++x) {
            for (size_t y = 2; y < WINDOW_SIZE.second - 1; ++y) {
                ChangeCursorPosition(x, y);
                std::cout << ' ';
            }
        }
    }

    // Вывести поле
    void ShowField() {
        for (size_t x = 1; x < WINDOW_SIZE.second - 1; ++x) {
            for (size_t y = MIDDLE_BORDER_RIGHT; y < WINDOW_SIZE.first - 2; ++y) {
                ChangeCursorPosition(y, x);
                SetConsoleTextAttribute(hConsole, (WORD)((BASE_FIELD[x - 1][y - MIDDLE_BORDER_RIGHT].background_color) | BASE_FIELD[x - 1][y - MIDDLE_BORDER_RIGHT].symbol_color));
                std::cout << BASE_FIELD[x - 1][y - MIDDLE_BORDER_RIGHT].symbol;
            }
        }
        SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));

        PrintBuildings(data.GetBuildings());
    }

    // Вывести сооружение
    void PrintBuildings(std::map<std::string, Building*> buildings) {
        for (auto it = buildings.begin(); it != buildings.end(); ++it) {
            for (size_t x = (*(*it).second).get_pos().first; x < (*(*it).second).get_pos().first + (*(*it).second).get_sizes().first; ++x) {
                for (size_t y = MIDDLE_BORDER_RIGHT + (*(*it).second).get_pos().second; y < MIDDLE_BORDER_RIGHT + (*(*it).second).get_pos().second + (*(*it).second).get_sizes().second; ++y) {
                    ChangeCursorPosition(y, x);
                    SetConsoleTextAttribute(hConsole, (WORD)(((*(*it).second).texture[x - (*(*it).second).get_pos().first][y - MIDDLE_BORDER_RIGHT - (*(*it).second).get_pos().second].background_color) | (*(*it).second).texture[x - (*(*it).second).get_pos().first][y - MIDDLE_BORDER_RIGHT - (*(*it).second).get_pos().second].symbol_color));
                    std::cout << (*(*it).second).texture[x - (*(*it).second).get_pos().first][y - MIDDLE_BORDER_RIGHT - (*(*it).second).get_pos().second].symbol;
                }
            }
        }
        SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
    }

    void ShowMissionField(/*const std::vector<std::vector<Cell>>& field*/) {
        for (size_t x = 1; x < WINDOW_SIZE.second - 1; ++x) {
            for (size_t y = MIDDLE_BORDER_RIGHT; y < WINDOW_SIZE.first - 2; ++y) {
                ChangeCursorPosition(y, x);
                SetConsoleTextAttribute(hConsole, (WORD)((MISSION_1_FIELD[x - 1][y - MIDDLE_BORDER_RIGHT].background_color) | MISSION_1_FIELD[x - 1][y - MIDDLE_BORDER_RIGHT].symbol_color));
                std::cout << MISSION_1_FIELD[x - 1][y - MIDDLE_BORDER_RIGHT].symbol;
            }
        }
        SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
    }

    // Стереть n символов
    void ResetNCharacters(size_t n) {
        for (size_t i = 0; i < n; ++i) {
            std::cout << ' ';
        }
    }

public:
    Game() = default;

    // Отображение экрана меню
    void ShowMenu() {
        ResetLeftTile();

        ChangeCursorPosition(VERSION_INFO_POSITION.first, VERSION_INFO_POSITION.second);
        std::cout << "MarsColony game  -  версия " << VERSION << " by NikEvKuz";

        // Выводим рамку
        for (size_t y = 0; y < WINDOW_SIZE.second; ++y) {
            ChangeCursorPosition(0, y);
            std::cout << "||";

            ChangeCursorPosition(MIDDLE_BORDER_LEFT, y);
            std::cout << "||";

            ChangeCursorPosition(WINDOW_SIZE.first - 2, y);
            std::cout << "||";
        }

        for (size_t x = 0; x < WINDOW_SIZE.first; ++x) {
            ChangeCursorPosition(x, 0);
            std::cout << '|';

            ChangeCursorPosition(x, WINDOW_SIZE.second - 1);
            std::cout << '|';
        }

        // Выводим менюшку
        std::ifstream file;
        file.open("data\\menu.txt");

        ChangeCursorPosition(MENU_OUTPUT_POSITION.first, MENU_OUTPUT_POSITION.second);

        std::string line;;
        while (getline(file, line)) {
            std::cout << line;

            ++position.Y;
            SetConsoleCursorPosition(hConsole, position);
        }
        file.close();
    }

    // Показать экран справки
    void ShowHelp() {
        ResetLeftTile();

        std::ifstream file;
        file.open("data\\help.txt");

        ChangeCursorPosition(HELP_OUTPUT_POSITION.first, HELP_OUTPUT_POSITION.second);

        std::string line;
        while (getline(file, line)) {
            std::cout << line;

            ++position.Y;
            SetConsoleCursorPosition(hConsole, position);
        }

        ChangeCursorPosition(HELP_COMMANDLINE_OUTPUT_POSITION.first, HELP_COMMANDLINE_OUTPUT_POSITION.second);
        std::cout << "Введите Q чтобы выйти: ";

        char command = '\0';
        do {
            ChangeCursorPosition(HELP_COMMANDLINE_INPUT_POSITION.first, HELP_COMMANDLINE_INPUT_POSITION.second);
            std::cin >> command;
            ChangeCursorPosition(HELP_COMMANDLINE_INPUT_POSITION.first, HELP_COMMANDLINE_INPUT_POSITION.second);
            ResetNCharacters(43);
        } while (command != 'Q');
        ShowMenu();
    }

    // Показать дерево технологий
    void ShowTechTree() {
        ResetRightTile();

        std::ifstream file;
        file.open("data\\technology_tree.txt");

        ChangeCursorPosition(MIDDLE_BORDER_RIGHT, 1);

        std::string line;
        while (getline(file, line)) {
            std::cout << line;

            ++position.Y;
            SetConsoleCursorPosition(hConsole, position);
        }

        ChangeCursorPosition(GAME_COMMANDLINE_INPUT_POSITION.first, GAME_COMMANDLINE_INPUT_POSITION.second);
        std::string command = "";
        while (command != "quit") {
            std::cin >> command;

            if (command == "research") {
                int tech_num;
                std::cin >> tech_num;

                if (data.GetResources().scince >= data.GetTechCost()[tech_num] && data.GetTechnologies()[data.GetPrevTechnologies()[tech_num]] && !data.GetTechnologies()[tech_num]) {
                    data.add_technology(tech_num);
                }
            }

            ChangeCursorPosition(GAME_COMMANDLINE_INPUT_POSITION.first, GAME_COMMANDLINE_INPUT_POSITION.second);
            ResetNCharacters(31);
            ChangeCursorPosition(GAME_COMMANDLINE_INPUT_POSITION.first, GAME_COMMANDLINE_INPUT_POSITION.second);
        }

        ShowField();
        ChangeCursorPosition(GAME_COMMANDLINE_INPUT_POSITION.first, GAME_COMMANDLINE_INPUT_POSITION.second);
    }

    // Показать игровую информацию 
    void ShowGameInfo() {
        ResetLeftTile();

        std::ifstream file;
        file.open("data\\gameinfo.txt");

        ChangeCursorPosition(INFO_OUTPUT_POSITION.first, INFO_OUTPUT_POSITION.second);

        std::string line;
        while (getline(file, line)) {
            std::cout << line;

            ++position.Y;
            SetConsoleCursorPosition(hConsole, position);
        }

        // Показать ресурсы
        Resources res = data.GetResources();

        ChangeCursorPosition(FOOD_POSITION.first, FOOD_POSITION.second);
        std::cout << res.food;

        ChangeCursorPosition(MONEY_POSITION.first, MONEY_POSITION.second);
        std::cout << res.money;
        ChangeCursorPosition(MONEY_GROWTH_POSITION.first, MONEY_GROWTH_POSITION.second);
        std::cout << res.money_growth;

        ChangeCursorPosition(ENERGY_POSITION.first, ENERGY_POSITION.second);
        std::cout << res.energy;
        ChangeCursorPosition(ENERGY_GROWTH_POSITION.first, ENERGY_GROWTH_POSITION.second);
        std::cout << res.energy_growth;

        ChangeCursorPosition(SCIENCE_POSITION.first, SCIENCE_POSITION.second);
        std::cout << res.scince;
        ChangeCursorPosition(SCIENCE_GROWTH_POSITION.first, SCIENCE_GROWTH_POSITION.second);
        std::cout << res.scince_growth;

        ChangeCursorPosition(DETAILS_POSITION.first, DETAILS_POSITION.second);
        std::cout << res.details;
        ChangeCursorPosition(DETAILS_GROWTH_POSITION.first, DETAILS_GROWTH_POSITION.second);
        std::cout << res.details_growth;

        // Показать список юнитов
        std::vector<PlayerUnit> units = data.GetUnits();
        for (size_t i = 0; i < units.size(); ++i) {
            ChangeCursorPosition(6, 13 + i);
            switch (units[i].GetID()) {
            case 1:
                std::cout << '№' << i + 1 << ": Explorer";
                break;
            case 2:
                std::cout << '№' << i + 1 << ": Military";
                break;
            case 3:
                std::cout << '№' << i + 1 << ": Engeneer";
                break;
            case 4:
                std::cout << '№' << i + 1 << ": Rover";
            default:
                break;
            }
        }

        
    }

    // Начать операцию
    void Mission(int mission_number) {
        ShowMissionField();
        ShowGameInfo();

        std::vector<int> mission_units;

        ChangeCursorPosition(GAME_COMMANDLINE_INPUT_POSITION.first, GAME_COMMANDLINE_INPUT_POSITION.second);

        std::string unit_number;
        std::cin >> unit_number;
        while (unit_number != "end") {
            mission_units.push_back(std::stoi(unit_number));

            ChangeCursorPosition(GAME_COMMANDLINE_INPUT_POSITION.first, GAME_COMMANDLINE_INPUT_POSITION.second);
            ResetNCharacters(31);
            ChangeCursorPosition(GAME_COMMANDLINE_INPUT_POSITION.first, GAME_COMMANDLINE_INPUT_POSITION.second);

            std::cin >> unit_number;
        }

        ChangeCursorPosition(GAME_COMMANDLINE_INPUT_POSITION.first, GAME_COMMANDLINE_INPUT_POSITION.second);
        ResetNCharacters(31);
        ChangeCursorPosition(GAME_COMMANDLINE_INPUT_POSITION.first, GAME_COMMANDLINE_INPUT_POSITION.second);
        
    }

    // Проинициализировать игру
    void InitGame() {
        // Создаем главное здание

        data = GameInfo();
    }

    // Прочитать ход
    void ReadMove(std::vector<std::string>& commands) {
        ChangeCursorPosition(GAME_COMMANDLINE_INPUT_POSITION.first, GAME_COMMANDLINE_INPUT_POSITION.second);
        
        std::string new_command;

        do {
            std::cin >> new_command;           

            if (new_command == "new") {
                std::string unit_type;
                std::cin >> unit_type;
                new_command = new_command + ' ' + unit_type;
            } else if (new_command == "build" || new_command == "upgrade") {
                std::string building_type;
                std::cin >> building_type;
                new_command = new_command + ' ' + building_type;
            } else if (new_command == "mission") {
                std::string mission_number;
                std::cin >> mission_number;
                new_command = new_command + ' ' + mission_number;
            }


            commands.push_back(new_command);
            
            ChangeCursorPosition(GAME_COMMANDLINE_INPUT_POSITION.first, GAME_COMMANDLINE_INPUT_POSITION.second);
            ResetNCharacters(31);
            ChangeCursorPosition(GAME_COMMANDLINE_INPUT_POSITION.first, GAME_COMMANDLINE_INPUT_POSITION.second);       
        } while (new_command != "end" && new_command != "quit");
    }

    // Совершить ход
    void MakeMove(std::vector<std::string>& commands, bool& is_in_game) {
        bool is_mission = false;
        int mission_number = 0;

        for (int i = 0; i < commands.size(); ++i) {
            if (commands[i] == "end") {
                break;
            }

            if (commands[i] == "quit") {
                data.reset();
                is_in_game = false;
                break;
            }

            if (commands[i] == "new explorer" && data.GetResources().money >= 20 - data.GetUnitDiscount()) {
                data.add_unit(1);
            } else if (commands[i] == "new military" && data.GetResources().money >= 20 - data.GetUnitDiscount()) {
                data.add_unit(2);
            } else if (commands[i] == "new engeneer" && data.GetResources().money >= 20 - data.GetUnitDiscount()) {
                data.add_unit(3);
            } else if (commands[i] == "new rover" && data.GetResources().money >= 80 - data.GetUnitDiscount() && data.GetBuildingsStatus()["assembly_plant"]) {
                data.add_unit(4);
            }

            if (commands[i] == "build science_center" && data.GetResources().money >= 200 - data.GetBuildingDiscount() && data.GetTechnologies()[1]) {
                data.add_building("science_center");
            } else if (commands[i] == "build military_center" && data.GetResources().money >= 200 - data.GetBuildingDiscount() && data.GetTechnologies()[4]) {
                data.add_building("military_center");
            } else if (commands[i] == "build farm" && data.GetResources().money >= 200 - data.GetBuildingDiscount() && data.GetTechnologies()[5]) {
                data.add_building("farm");
            } else if (commands[i] == "build solar_plant" && data.GetResources().money >= 150 - data.GetBuildingDiscount() && data.GetTechnologies()[2]) {
                data.add_building("solar_plant");
            } else if (commands[i] == "build assembly_plant" && data.GetResources().money >= 150 - data.GetBuildingDiscount() && data.GetTechnologies()[11]) {
                data.add_building("assembly_plant");
            } else if (commands[i] == "build cargo_platform" && data.GetResources().money >= 150 - data.GetBuildingDiscount() && data.GetTechnologies()[6]) {
                data.add_building("cargo_platform");
            }

            if (commands[i] == "upgrade main_building" && data.GetResources().money >= 500 - data.GetBuildingDiscount() && data.GetTechnologies()[8]) {
                data.upgrade_building("main_building");
            } else if (commands[i] == "upgrade science_center" && data.GetResources().money >= 400 - data.GetBuildingDiscount() && data.GetTechnologies()[3]) {
                data.upgrade_building("science_center");
            } else if (commands[i] == "upgrade military_center" && data.GetResources().money >= 400 - data.GetBuildingDiscount() && data.GetTechnologies()[9]) {
                data.upgrade_building("military_center");
            } else if (commands[i] == "upgrade farm" && data.GetResources().money >= 400 - data.GetBuildingDiscount() && data.GetTechnologies()[10]) {
                data.upgrade_building("farm");
            } else if (commands[i] == "upgrade solar_plant" && data.GetResources().money >= 300 - data.GetBuildingDiscount() && data.GetTechnologies()[7]) {
                data.upgrade_building("solar_plant");
            }

            if (commands[i] == "tech_tree") {
                ShowGameInfo();
                ShowTechTree();
            }

            if (commands[i].substr(0, 7) == "mission") {
                is_mission = true;
                mission_number = std::stoi(commands[i].substr(8));
            }
        }

        data.GrowthResources();

        if (is_mission) {
            Mission(mission_number);
            ShowField();
        }
    }

    // Ход компьютера
    void AIMove() {

    }

    // Процесс игры
    void PlayGame() {
        InitGame();
        ShowGameInfo();
        PrintBuildings(data.GetBuildings());

        bool is_in_game = true; // идет ли игра сейчас, не завершена ли

        while (is_in_game) {
            std::vector<std::string> commands;
            ReadMove(commands);
            ResetLeftTile();
            MakeMove(commands, is_in_game);
            ShowGameInfo();
            PrintBuildings(data.GetBuildings());
        }

        BeginGame();
    }

    // Начать игру, запустить
    void BeginGame() {
        ShowMenu();
        ShowField();

        // Принять команду
        while (true) {
            ChangeCursorPosition(MENU_COMMANDLINE_INPUT_POSITION.first, MENU_COMMANDLINE_INPUT_POSITION.second);
            char command = '\0';
            std::cin >> command;

            ChangeCursorPosition(MENU_COMMANDLINE_MESSAGE_POSITION.first, MENU_COMMANDLINE_MESSAGE_POSITION.second);
            ResetNCharacters(31);
            ChangeCursorPosition(MENU_COMMANDLINE_INPUT_POSITION.first, MENU_COMMANDLINE_INPUT_POSITION.second);
            switch (command) {
            case ('N'):
                PlayGame();
            case ('Q'):
                return;
            case ('H'):
                ShowHelp();
            default:
                if (command != 'N' && command != 'Q' && command != 'H') {
                    ChangeCursorPosition(MENU_COMMANDLINE_MESSAGE_POSITION.first, MENU_COMMANDLINE_MESSAGE_POSITION.second);
                    std::cout << "Неизвестная команда, попробуйте еще раз";
                }
                ChangeCursorPosition(MENU_COMMANDLINE_INPUT_POSITION.first, MENU_COMMANDLINE_INPUT_POSITION.second);
                ResetNCharacters(29);
            }
        }
    }
};
