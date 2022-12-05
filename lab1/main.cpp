#include "Dice.h"

int main()
{
    LinkedList<Dice> kit1;
    LinkedList<ExpectedSum> combinations1;
    Dice d1(2), d2(3), d3(4);

    kit1.push_back(d1);
    kit1.push_back(d2);
    kit1.push_back(d3);
    kit1.print();

    combinations1 = find_expected_sum_combinations(kit1);
    std::cout << "Combinations of the number of points and their probability of falling out :\n";
    combinations1.print();

    system("pause");

    LinkedList<Dice> kit2;
    LinkedList<ExpectedSum> combinations2;
    Dice d4(3), d5(4), dN;
    int n;

    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        int number;
        double dropProbability;
        std::cin >> number >> dropProbability;
        dN.add_side(number, dropProbability);
    }

    kit2.push_back(d4);
    kit2.push_back(d5);
    kit2.push_back(dN);
    kit2.merge_sort();
    kit2.print();

    combinations2 = find_expected_sum_combinations(kit2);
    std::cout << "Combinations of the number of points and their probability of falling out :\n";
    combinations2.print();

    system("pause");

    ExpectedSum sum;
    std::cout << compare(combinations1, combinations2, 4, sum) << ' ' << sum << std::endl;
    std::cout << compare(combinations1, combinations2, 8, sum) << ' ' << sum << std::endl;
    std::cout << compare(combinations1, combinations2, 100, sum) << ' ' << sum << std::endl;

    system("pause");

    return 0;
}