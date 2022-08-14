#pragma once

#pragma once

class CFood
{
private:
    char* name;
    double price;
public:
    CFood(char* name, double price)
    {
        this->name = name;
        this->price = price;
    }

    ~CFood()
    {
        if (name != NULL)
        {
            free(name);
            name = NULL;
        }
    }

    const char* getName()
    {
        return this->name;
    }

    double getPrice()
    {
        return this->price;
    }
};
