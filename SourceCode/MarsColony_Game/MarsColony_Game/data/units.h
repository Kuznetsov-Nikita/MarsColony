#pragma once

// Класс Unit - юнит
class Unit {
protected:
    int id;                    // id - идентификатор юнита
    int level;                 // уровень юнита
    int number;                // номер юнита в списке текущих существующих

    char symbol;               // символ юнита в консоли
    int background_color;      // цвет заднего фона юнита в консоли
    int symbol_color;          // цвет символа юнита

    std::pair<int, int> pos;   // позиция, местоположение юнита на карте поля операции

    int hp;                    // хит-поинты юнита

public:
    // Пермемстить юнита в заданном направлении
    virtual void move(char direction) {
        
    }

    // Вернуть идентификатор юнита
    virtual int GetID() {
        return id;
    }
};

// Класс Monster - юниты монстры, под контролем компьютера
class Monster : public Unit {
protected:
    int attack_strenght; // сила атаки
public:
    // Объявление фабрики монстров
    static Monster* CreateUnit(int level, int number, int id);

    // Атаковать
    void attack() {

    }
};

// Класс PlayerUnit - юниты, доступные для управления игроку
class PlayerUnit : public Unit {
public:
    // Объявление фабрики юнитов игрока
    static PlayerUnit CreateUnit(int level, int number, int id);

    virtual int GetID() {
        return id;
    }

    virtual void add_bonus(int bonus) {}
};

// Класс Explorer - исследователь
class Explorer : public PlayerUnit {
protected:
    int science_strength; // научная сила

public:
    // Конструктор
    Explorer(int level, int number) {
        this->level = level;
        this->number = number;

        this->id = 1;
        this->symbol = 'S';
        this->background_color = Blue;
        this->symbol_color = LightCyan;

        this->hp = 30 * level;
        science_strength = 5 * level;
    }

    // Исследовать
    void explore() {

    }

    void add_bonus(int bonus) override {
        this->science_strength += bonus;
    }

    ~Explorer() {}
};

// Класс Military - военный
class Military : public PlayerUnit {
protected:
    int military_strength; // военная мощь

public:
    // Конструктор
    Military(int level, int number) {
        this->level = level;
        this->number = number;

        this->id = 2;
        this->symbol = 'M';
        this->background_color = Green;
        this->symbol_color = Black;

        this->hp = 50 * level;
        military_strength = 10 * level;
    }

    // Атаковать
    void attack() {

    }

    void add_bonus(int bonus) override {
        this->military_strength += bonus;
    }

    ~Military() {}
};

// Класс Engeneer - инженер
class Engeneer : public PlayerUnit {
protected:
    int engeneering_strenght; // сила инженерного дела

public:
    // Конструктор
    Engeneer(int level, int number) {
        this->level = level;
        this->number = number;

        this->id = 3;
        this->symbol = 'I';
        this->background_color = LightMagenta;
        this->symbol_color = Brown;

        this->hp = 30 * level;
        engeneering_strenght = 5 * level;
    }

    // Построить
    void build() {

    }

    void add_bonus(int bonus) override {
        this->engeneering_strenght += bonus;
    }

    ~Engeneer() {}
};

// Класс Rover - марсоход
class Rover : public PlayerUnit {
protected:
    int science_strenght;     // научная сила
    int military_strength;    // военная мощь
    int engeneering_strenght; // сила инженерного дела

public:
    // Конструктор
    Rover(int level, int number) {
        this->level = level;
        this->number = number;

        this->id = 4;
        this->symbol = 'R';
        this->background_color = LightMagenta;
        this->symbol_color = Brown;

        this->hp = 200;
        science_strenght = 10;
        engeneering_strenght = 10;
        military_strength = 15;
    }

    // Исследовать
    void explore() {

    }

    // Построить
    void build() {

    }

    // Атаковать
    void attack() {

    }

    ~Rover() {}
};

// Класс NKWarRobot - монстр, северокорейский боевой робот
class NKWarRobot : public Monster {
public:
    // Конструктор
    NKWarRobot(int level, int number) {
        this->level = level;
        this->number = number;

        this->id = 10;
        this->symbol = 'K';
        this->background_color = LightRed;
        this->symbol_color = Blue;

        this->hp = 50;
        this->attack_strenght = 5;
    }

    ~NKWarRobot() {}
};

// Реализация фабрики монстров
Monster* Monster::CreateUnit(int level, int number, int id) {
    switch (id) {
    case 10:
        return new NKWarRobot(level, number);
        break;
    default:
        break;
    }
}

// Реализация фабрики юнитов игрока
PlayerUnit PlayerUnit::CreateUnit(int level, int number, int id) {
    switch (id) {
    case 1:
        return Explorer(level, number);
        break;
    case 2:
        return Military(level, number);
        break;
    case 3:
        return Engeneer(level, number);
        break;
    case 4:
        return Rover(level, number);
        break;
    default:
        break;
    }
}
