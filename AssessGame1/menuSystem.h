#pragma once



class menu {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	enum colours { white = 15, green = 10 };

	std::vector<std::string> inputOptions = {};
	std::vector<std::string> outputText = {};

public:
	//Text to be displayed separate from input options
	void setInputOptions(const std::vector<std::string> newInput) {
		inputOptions = newInput;
	}

	//title and/or description text to be printed
	void setOutputText(const std::vector<std::string> setOutput) {
		outputText = setOutput;
	}

	void printMenu(int targetIndex) {
		system("CLS");
		SetConsoleTextAttribute(hConsole, white);

		for (int i = 0; i < outputText.size(); i++) {
			std::cout << outputText.at(i);
		}

		std::cout << "\n";


		for (int i = 0; i < inputOptions.size(); i++) {
			if (i == targetIndex) {
				SetConsoleTextAttribute(hConsole, green);
				std::cout << " [X] ";
				SetConsoleTextAttribute(hConsole, white);
				std::cout << inputOptions.at(i) << "\n";
			}
			else
				std::cout << " [X] " << inputOptions.at(i) << '\n';
		}
	}

	int getInput() {
		int selectedIndex = 0;
		int input = 0;
		bool inMenu = true;
		enum validKeypress { up = 72, down = 80, space = 32 };
		do {
			switch (_getch()) {
			case up:
				if (selectedIndex > 0) {
					selectedIndex--;
					this->printMenu(selectedIndex);
				}
				break;
			case down:
				if (selectedIndex < (inputOptions.size() - 1)) {
					selectedIndex++;
					this->printMenu(selectedIndex);
				}
				break;
			case space:
				return selectedIndex;
			}
			/*std::cout << "\nInput choice: ";
			std::cin >> input;

			if (std::cin.fail()) {
				std::cerr << "Invalid option, please try again.";
				std::cin.clear();
				std::cin.ignore(256, '\n');
				continue;
			}
			if (input > inputOptions.size()) {
				std::cout << "Invalid option, please try again.";
			}
			else {
				inMenu = false;
				return input;
			}
			*/
		} while (inMenu);
	}
};