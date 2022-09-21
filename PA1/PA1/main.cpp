/**
 * ADVANTAGES/DISADVANTAGES - LINKEDLIST
 *
 * Advantage: No limit for maximum number of commands that can be stored. We can add new node for each command.
 * Disadvantage: No random access to the commands. When we are selecting a random command,
 * we have to start from the head of the list and traverse through the list to reach the command.
 */

 /**
  * ADVANTAGES/DISADVANTAGES - ARRAY
  *
  * Advantage: Random access to the player profile. When we are updating a player profile,
  * we can directly access it using its index in the array.
  * Disadvantage: Fixed array size of 100 (maximum size). This is a limit for maximum number of player profiles that can be stored.
  */


#include <iostream>
#include <fstream>
#include <string>

#include "function.cpp"

using namespace std;


struct Player
{
	string name;
	int points;
};

string name;
int points = 0;
int numberOfCommands = 0;
int numberOfPlayers = 0;
struct Player profiles[100];
linkedlist<string> li;

void playGame()
{

	int rounds;
	int index, answer;
	int order[3];
	int selected;
	string descriptions[3];

	node<string>* question;
	node<string>* option;

	while (1)
	{
		cout << "How many rounds you want to play? (between 5 and 30): ";
		cin >> rounds;
		if (rounds < 5 || rounds > 30)
		{
			cout << "Enter a number between 5 and 30 !!" << endl;
			continue;
		}
		else
		{
			for (int i = 0; i < rounds; i++)
			{
				cout << "Round " << i + 1 << endl;
				index = rand() % numberOfCommands;
				question = li.getCommand(index);
				cout << question->command << endl;

				int options = 0;
				descriptions[options++] = question->description;

				while (options < 3)
				{
					int op = rand() % numberOfCommands;
					if (op != index)
					{
						option = li.getCommand(op);
						descriptions[options++] = option->description;
					}
				}

				int perm = 0;
				int x = 0;
				while (x < 3)
				{
					int op = rand() % 3;
					int f = 0;
					for (int j = 0; j < x; j++)
					{
						if (op == order[j])
							f = 1;
					}
					if (f == 0)
					{
						order[x++] = op;
					}
				}
				cout << "Options:" << endl;
				for (int j = 0; j < x; j++)
				{
					if (order[j] == 0) //answer
					{
						answer = j + 1;
					}
					cout << j + 1 << ". " << descriptions[order[j]] << endl;
				}

				while (1)
				{
					cin >> selected;
					if (selected < 1 || selected > 3)
					{
						cout << "Enter a valid option !!" << endl;
						continue;
					}
					else
					{
						if (selected == answer)
						{
							points++;
							cout << question->command << " - " << question->description << endl;
							cout << "You have been awarded 1 point. Your point total is: " << points << endl;
						}
						else
						{
							points--;
							cout << question->command << " - " << question->description << endl;
							cout << "You have lost 1 point. Your point total is: " << points << endl;
						}
						break;
					}

				}

			}
			break;
		}
	}
	/////update player array////////
	int flag = 0;
	for (int k = 0; k < numberOfPlayers; k++)
	{
		if (profiles[k].name == name)
		{
			profiles[k].points = points;
			flag = 1;
		}
	}

	if (flag == 0)
	{
		//add new player
		profiles[numberOfPlayers].name = name;
		profiles[numberOfPlayers].points = points;
		numberOfPlayers++;
	}

}

void writeCSV(string fname, string pname)
{
	node<string>* current;
	ofstream file1(fname);
	for (int i = 0; i < numberOfCommands; i++)
	{
		current = li.getCommand(i);
		file1 << current->command << ", \"" << current->description << "\"" << endl;
	}
	file1.close();

	ofstream file(pname);
	for (int i = 0; i < numberOfPlayers; i++)
	{
		file << profiles[i].name << "," << profiles[i].points << endl;
	}
	file.close();
}

int main()
{
	string fname = "commands.csv";
	string pname = "profiles.csv";

	string line, word;
	string newCommand;
	string newDescription;

	int i;

	srand(time(0));

	fstream file(fname, ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			word.clear();
			i = 0;
			while (line[i] != ',')
			{
				word.push_back(line[i]);
				i++;
			}
			newCommand = word;
			word.clear();
			while (line[i] != '"')
			{
				i++;
			}
			i++;
			while (line[i] != '"')
			{
				word.push_back(line[i]);
				i++;
			}
			newDescription = word;
			li.addCommand(newCommand, newDescription);
			numberOfCommands++;
		}

		file.close();
	}
	else
		cout << "Could not open the file\n";


	//---------------------------------

	fstream file1(pname, ios::in);
	if (file1.is_open())
	{
		while (getline(file1, line))
		{
			word.clear();
			i = 0;
			while (line[i] != ',')
			{
				word.push_back(line[i]);
				i++;
			}
			profiles[numberOfPlayers].name = word;
			word.clear();
			i++;
			while (i < line.length())
			{
				word.push_back(line[i]);
				i++;
			}
			profiles[numberOfPlayers].points = stoi(word);
			numberOfPlayers++;
		}

		file1.close();
	}
	else
		cout << "Could not open the file\n";

	int choice;
	int flag;

	while (1)
	{
		cout << endl << "Please Select an option listed below:" << endl << endl;
		cout << "1. Game Rules" << endl << "2. Play Game" << endl << "3. Load Previous Game" << endl;
		cout << "4. Add Command" << endl << "5. Remove Command" << endl << "6. Exit" << endl;

		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "Rules:" << endl << "-----------------" << endl;
			cout << "Select the correct option describing the linux command given." << endl;
			cout << "If your answer is correct, you get 1 point." << endl;
			cout << "If it is wrong 1 point will be deducted. " << endl;
			cout << "You can play 5 to 30 rounds." << endl;
			break;

		case 2:
			cout << "Enter your name: ";
			cin >> name;
			playGame();
			break;

		case 3:
			cout << "Enter your name: ";
			//////////search in the player array 
			cin >> name;
			flag = 0;
			for (int k = 0; k < numberOfPlayers; k++)
			{
				if (profiles[k].name == name)
				{
					points = profiles[k].points;
					cout << "Your previous points:" << profiles[k].points << endl;
					flag = 1;
					break;
				}
			}

			if (flag == 0)
			{
				cout << "No previous games. Start a new game!!" << endl;
			}

			playGame();

			break;

		case 4:
			while (1)
			{
				cout << "Enter a new command: ";
				cin >> newCommand;
				cout << "Enter the description: ";
				std::getline(std::cin >> std::ws, newDescription);
				//cin >> newDescription;
				char ch;
				if (li.searchCommand(newCommand))
				{
					cout << "The command already exists." << endl;
					cout << "Do you want to quit? (Enter y for yes, n for no): ";
					cin >> ch;
					if (ch == 'y')
					{
						break;
					}
				}
				else
				{
					//insert 
					li.addCommand(newCommand, newDescription);
					numberOfCommands++;
					cout << "Command added successfully!!" << endl;
					break;
				}
			}
			break;

		case 5:
			while (1)
			{
				cout << "Enter the command to be removed: ";
				cin >> newCommand;
				char ch;
				if (!li.searchCommand(newCommand))
				{
					cout << "The command does not exists." << endl;
					cout << "Do you want to quit? (Enter y for yes, n for no): ";
					cin >> ch;
					if (ch == 'y')
					{
						break;
					}
				}
				else
				{
					//detete 
					li.removeCommand(newCommand);
					numberOfCommands--;
					cout << "Command removed successfully!!" << endl;
					break;
				}
			}
			break;

		case 6:
			// write commands and profiles to csv file
			writeCSV(fname, pname);
			return 1;

		default: cout << "Enter valid option." << endl;
		}

	}

	return 0;
}
