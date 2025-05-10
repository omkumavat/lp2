#include <iostream>
#include <string>
using namespace std;

void evaluateEmployee()
{
    string evaluatorposition;
    cout << "Enter your position (only Managers can evaluate): ";
    getline(cin, evaluatorposition);

    if (evaluatorposition != "Manager")
    {
        cout << "Only Managers can evaluate employees.\n";
        return;
    }

    string name, position;
    cout << "Enter employee's name: ";
    getline(cin, name);

    cout << "Enter employee's position: ";
    getline(cin, position);

    if (position == "Manager")
    {
        cout << "Managers cannot evaluate themselves.\n";
        return;
    }

    int p, q, t, l;
    cout << "Rate punctuality (1-10): ";
    cin >> p;
    cout << "Rate work quality (1-10): ";
    cin >> q;
    cout << "Rate teamwork (1-10): ";
    cin >> t;
    cout << "Rate leadership (1-10): ";
    cin >> l;
    cin.ignore();

    float avg = (p + q + t + l) / 4.0;
    cout << "Employee " << name << " (" << position << ") has a score of " << avg << "/10.\n";

    if (avg >= 8)
        cout << "Outstanding performance!\n";
    else if (avg >= 6)
        cout << "Good, but can improve.\n";
    else
        cout << "Needs improvement. Training recommended.\n";
}

void suggestTraining()
{
    string skill;
    cout << "Enter area to improve (Leadership, Technical, Communication): ";
    getline(cin, skill);

    for (char &c : skill)
        c = tolower(c);

    if (skill == "leadership")
        cout << "Suggested: Leadership & Management Training\n";
    else if (skill == "technical")
        cout << "Suggested: Advanced Technical Skills Workshop\n";
    else if (skill == "communication")
        cout << "Suggested: Effective Communication Skills\n";
    else
        cout << "Suggested: General Professional Development\n";
}

void calculateBonus()
{
    string name, position;
    float salary, score;
    cout << "Enter employee's name: ";
    getline(cin, name);
    cout << "Enter position: ";
    getline(cin, position);
    cout << "Enter base salary: ";
    cin >> salary;
    cout << "Enter performance score (1-10): ";
    cin >> score;
    cin.ignore();

    float multiplier = 0.1;
    if (position == "Intern")
        multiplier = 0.05;
    else if (position == "Junior Developer")
        multiplier = 0.10;
    else if (position == "Senior Developer")
        multiplier = 0.15;
    else if (position == "Manager")
        multiplier = 0.20;
    else if (position == "Director")
        multiplier = 0.25;

    float bonus = (score / 10.0) * salary * multiplier;
    cout << "Bonus for " << name << ": INR " << bonus << "\n";
}

void checkPromotionEligibility()
{
    string name, position;
    int experience, lastPromo;
    float score;

    cout << "Enter employee's name: ";
    getline(cin, name);
    cout << "Enter position: ";
    getline(cin, position);
    cout << "Years of experience: ";
    cin >> experience;
    cout << "Years since last promotion: ";
    cin >> lastPromo;
    cout << "Performance score (1-10): ";
    cin >> score;
    cin.ignore();

    if (score >= 8 && experience > 3 && lastPromo > 2)
        cout << name << " is eligible for promotion.\n";
    else
        cout << name << " is not eligible for promotion yet.\n";
}

void checkWorkLifeBalance()
{
    string name;
    int hours;
    cout << "Enter employee's name: ";
    getline(cin, name);
    cout << "Enter average weekly work hours: ";
    cin >> hours;
    cin.ignore();

    if (hours > 50)
        cout << name << ", you might be overworking. Try balancing better.\n";
    else
        cout << name << ", your work-life balance is good.\n";
}

int main()
{
    cout << "Welcome to the Employee Evaluation Expert System!\n";

    while (true)
    {
        cout << "\nOptions:\n";
        cout << "1. Evaluate Performance\n";
        cout << "2. Suggest Training\n";
        cout << "3. Calculate Bonus\n";
        cout << "4. Check Promotion Eligibility\n";
        cout << "5. Check Work-Life Balance\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            evaluateEmployee();
            break;
        case 2:
            suggestTraining();
            break;
        case 3:
            calculateBonus();
            break;
        case 4:
            checkPromotionEligibility();
            break;
        case 5:
            checkWorkLifeBalance();
            break;
        case 6:
            cout << "Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
