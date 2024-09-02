#pragma once

// Класс Building - здание
class Building {
    friend class Game;
protected:
    int id; // id - идентификатор здания

    int level = 1; // уровень здания
    int width;     // ширина поля (верх - низ)
    int lenght;    // длина поля (лево - право)

    std::pair<int, int> leftup_angle_pos; // позиция левого верхнего угла здания на карте
    std::vector<std::vector<Cell>> texture; // текстура здания

public:
    static Building* CreateBuilding(int id);

    virtual std::pair<int, int> get_pos() {
        return leftup_angle_pos;
    }

    virtual std::pair<int, int> get_sizes() {
        return std::make_pair(width, lenght);
    }
};

// Класс MainBuilding - главное здание
class MainBuilding : public Building {
public:
    MainBuilding() {
        this->id = 1;
        this->leftup_angle_pos = std::make_pair(17, 50);
        this->texture = MAIN_BUILDING_LEVEL_1;

        this->width = this->texture.size();
        this->lenght = this->texture[0].size();
    }

    // Улучшить здание
    void upgrade() {
        if (level < 2) {
            ++level;
            this->texture = MAIN_BUILDING_LEVEL_2;
        }
    }
};

// Класс CargoPlatform - грузовая площадка
class CargoPlatform : public Building {
public:
    CargoPlatform() {
        this->id = 7;
        this->leftup_angle_pos = std::make_pair(6, 55);
        this->texture = CARGO_PLATFORM_LEVEL_1;

        this->width = this->texture.size();
        this->lenght = this->texture[0].size();
    }
};

// Класс SolarPlant - солчнечная электростанция
class SolarPlant : public Building {
public:
    SolarPlant() {
        this->id = 5;
        this->leftup_angle_pos = std::make_pair(45, 50);
        this->texture = SOLAR_PLANT_LEVEL_1;

        this->width = this->texture.size();
        this->lenght = this->texture[0].size();
    }

    // Улучшить здание
    void upgrade() {
        if (level < 2) {
            ++level;
            this->texture = SOLAR_PLANT_LEVEL_2;
        }
    }
};

// Класс AssemblyPlant - сборочный цех
class AssemblyPlant : public Building {
public:
    AssemblyPlant() {
        this->id = 6;
        this->leftup_angle_pos = std::make_pair(45, 81);
        this->texture = ASSEMBLY_PLANT_LEVEL_1;

        this->width = this->texture.size();
        this->lenght = this->texture[0].size();
    }
};

// Класс Farm - ферма
class Farm : public Building {
public:
    Farm() {
        this->id = 4;
        this->leftup_angle_pos = std::make_pair(16, 88);
        this->texture = FARM_LEVEL_1;

        this->width = this->texture.size();
        this->lenght = this->texture[0].size();
    }

    // Улучшить здание
    void upgrade() {
        if (level < 2) {
            ++level;
            this->texture = FARM_LEVEL_2;
        }
    }
};

// Класс ScienceCenter - научно-исследовательский центр
class ScienceCenter : public Building {
public:
    ScienceCenter() {
        this->id = 2;
        this->leftup_angle_pos = std::make_pair(9, 19);
        this->texture = SCIENCE_CENTER_LEVEL_1;

        this->width = this->texture.size();
        this->lenght = this->texture[0].size();
    }

    // Улучшить здание
    void upgrade() {
        if (level < 2) {
            ++level;
            this->texture = SCIENCE_CENTER_LEVEL_2;
        }
    }
};

// Класс MilitaryCenter - военная база
class MilitaryCenter : public Building {
public:
    MilitaryCenter() {
        this->id = 3;
        this->leftup_angle_pos = std::make_pair(32, 18);
        this->texture = MILITARY_CENTER_LEVEL_1;

        this->width = this->texture.size();
        this->lenght = this->texture[0].size();
    }

    // Óëó÷øèòü çäàíèå
    void upgrade() {
        if (level < 2) {
            ++level;
            this->texture = MILITARY_CENTER_LEVEL_2;
        }
    }
};

Building* Building::CreateBuilding(int id) {
    switch (id) {
    case 1:
        return new MainBuilding();
        break;
    case 2:
        return new ScienceCenter();
        break;
    case 3:
        return new MilitaryCenter();
        break;
    case 4:
        return new Farm();
        break;
    case 5:
        return new SolarPlant();
        break;
    case 6:
        return new AssemblyPlant();
        break;
    case 7:
        return new CargoPlatform();
        break;
    default:
        break;
    }
}
