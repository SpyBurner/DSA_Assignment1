#include "Restaurant.cpp"
#include <fstream>

void simulate(string filename, imp_res* r)
{
    ifstream ss(filename);
    string str, maxsize, name, energy, num;
    while (ss >> str)
    {
        if (str == "MAXSIZE")
        {
            ss >> maxsize;
            cout << maxsize << "-------" << endl;
            MAXSIZE = stoi(maxsize);
        }
        else if (str == "RED") // RED <NAME> <ENERGY>
        {
            ss >> name;
            ss >> energy;
            r->RED(name, stoi(energy));
        }
        else if (str == "BLUE") // BLUE <NUM>
        {
            ss >> num;
            r->BLUE(stoi(num));
        }
        else if (str == "PURPLE") // PURPLE
        {
            r->PURPLE();
        }
        else if (str == "REVERSAL") // REVERSAL
        {
            r->REVERSAL();
        }
        else if (str == "UNLIMITED_VOID") // UNLIMITED_VOID
        {
            r->UNLIMITED_VOID();
        }
        else if (str == "DOMAIN_EXPANSION") // DOMAIN_EXPANSION
        {
            r->DOMAIN_EXPANSION();
        }
        else // LIGHT <NUM>
        {
            ss >> num;
            cout << "LIGHT " << num << endl;
            r->LIGHT(stoi(num));
        }
    }

}

int main(int argc, char* argv[]) {
     _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    imp_res* r = new imp_res();
    string fileName = "test.txt";
    simulate(fileName, r);
    delete r;


     _CrtDumpMemoryLeaks();
    return 0;
}

