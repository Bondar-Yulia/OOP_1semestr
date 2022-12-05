#include "Dice.h"


Dice::Dice()
{
    countOfSides = 0;
    fullProbability = 0;
}

Dice::Dice(int c)
{
    if (c < 1) c = 1;
    countOfSides = c;
    fullProbability = 1;
    for (int i = 1; i <= countOfSides; i++)
    {
        Side s(i, 1.0 / c);
        sides.push_back(s);
    }
}

void Dice::add_side(int n, double dP)
{
    if (fullProbability == 1)
        return;
    Side s(n, dP);
    if (fullProbability + s.dropProbability > 1)
        s.dropProbability = 1 - fullProbability;
    fullProbability += s.dropProbability;
    sides.push_back(s);
    sides.merge_sort();
    countOfSides++;
}

std::ostream& operator<<(std::ostream& out, const Dice &d)
{
    out << "D(" << d.get_count_of_sides() << ") = ";
    auto *currentSide = d.sides.get_front();
    while (currentSide)
    {
        out << currentSide->value;
        currentSide = currentSide->next;
    }
    out << ";";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Dice::Side &s)
{
    out << "[" << s.number << ", " << s.dropProbability << "] ";
    return out;
}

bool operator< (const Dice &d1, const Dice &d2)
{
    if (d1.get_count_of_sides() != d2.get_count_of_sides())
        return d1.get_count_of_sides() < d2.get_count_of_sides();
    else
        return d1.get_full_probability() < d2.get_full_probability();
}

bool operator< (const Dice::Side &s1, const Dice::Side &s2)
{
    if (s1.number != s2.number)
        return s1.number < s2.number;
    else
        return s1.dropProbability < s2.dropProbability;
}

ExpectedSum::ExpectedSum()
{
    sumValue = 0;
    sumProbability = 1;
}

ExpectedSum::ExpectedSum(int sV, double sP)
{
    sumValue = sV;
    sumProbability = sP;
}

void ExpectedSum::update(int sV, double sP)
{
    sumValue += sV;
    sumProbability *= sP;
}

std::ostream& operator<<(std::ostream& out, const ExpectedSum &s)
{
    out << "[" << s.sumValue << ", " << s.sumProbability << "]";
    return out;
}

bool operator< (const ExpectedSum &s1, const ExpectedSum &s2)
{
    if (s1.sumValue != s2.sumValue)
        return s1.sumValue < s2.sumValue;
    else
        return s1.sumProbability < s1.sumProbability;
}

LinkedList<ExpectedSum> find_expected_sum_combinations(LinkedList<Dice> &k)
{
    LinkedList<ExpectedSum> c;
    LinkedList<ExpectedSum> buffer;
    auto *pointerCurrentDice = k.get_front();
    while(pointerCurrentDice)
    {
        Dice currentDice = pointerCurrentDice->value;
        if(buffer.is_empty())
        {
            auto *pointerCurrentSide = currentDice.get_front_side();
            while(pointerCurrentSide)
            {
                ExpectedSum s(pointerCurrentSide->value.number, pointerCurrentSide->value.dropProbability);
                buffer.push_back(s);
                pointerCurrentSide = pointerCurrentSide->next;
            }
        }
        else
        {
            auto *pointerCurrentSide = currentDice.get_front_side();
            while(pointerCurrentSide)
            {
                auto *pointerCurrentExpectedSum = buffer.get_front();
                while(pointerCurrentExpectedSum)
                {
                    ExpectedSum s(pointerCurrentExpectedSum->value.sumValue + pointerCurrentSide->value.number,
                                  pointerCurrentExpectedSum->value.sumProbability * pointerCurrentSide->value.dropProbability);
                    c.push_back(s);
                    pointerCurrentExpectedSum = pointerCurrentExpectedSum->next;
                }
                pointerCurrentSide = pointerCurrentSide->next;
            }
            while(!buffer.is_empty())
            {
                buffer.pop_back();
            }
            while(!c.is_empty())
            {
                ExpectedSum s = c.pop_front();
                buffer.push_back(s);
            }
        }
        pointerCurrentDice = pointerCurrentDice->next;
    }
    buffer.merge_sort();
    ExpectedSum prev = buffer.pop_front();
    while(!buffer.is_empty())
    {
        ExpectedSum curr = buffer.pop_front();
        if(prev.sumValue == curr.sumValue)
        {
            prev.sumProbability += curr.sumProbability;
        }
        else
        {
            c.push_back(prev);
            prev = curr;
        }
    }
    c.push_back(prev);
    return c;
}

int compare(const LinkedList<ExpectedSum> &c1, const LinkedList<ExpectedSum> &c2, int sumValue, ExpectedSum &s)
{
    ExpectedSum s1, s2;
    bool flag1 = false, flag2 = false;
    auto *currentExpectedSum1 = c1.get_front();
    auto *currentExpectedSum2 = c2.get_front();
    while((currentExpectedSum1 || currentExpectedSum2) && (!flag1 || !flag2))
    {
        if(currentExpectedSum1)
        {
            if(currentExpectedSum1->value.sumValue == sumValue)
            {
                s1.update(currentExpectedSum1->value.sumValue, currentExpectedSum1->value.sumProbability);
                flag1 = true;
            }
            currentExpectedSum1 = currentExpectedSum1->next;
        }
        if(currentExpectedSum2)
        {
            if(currentExpectedSum2->value.sumValue == sumValue)
            {
                s2.update(currentExpectedSum2->value.sumValue, currentExpectedSum2->value.sumProbability);
                flag2 = true;
            }
            currentExpectedSum2 = currentExpectedSum2->next;
        }
    }

    if (!flag1 && !flag2)
        return -1;
    if (flag1 && !flag2)
    {
        s = s1;
        return 1;
    }
    if (!flag1 && flag2)
    {
        s = s2;
        return 2;
    }

    if (s1.sumProbability > s2.sumProbability)
    {
        s = s1;
        return 1;
    }
    if (s2.sumProbability > s1.sumProbability)
    {
        s = s2;
        return 2;
    }
    else
    {
        s = s1;
        return 3;
    }
}