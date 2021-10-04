#pragma once

class menu {
	std::vector<std::string> inputText = {};
	std::vector<std::string> outputText = {};

public:
	//Text to be displayed separate from input options
	void addInput(const std::vector<std::string> inputText) {

	}

	void addText(const std::vector<std::string> outputText) {
		//outputText = NULL;
	}

	void printMenu() {
		//TODO: handle text unrelated to menu options (i.e: game rules)
		for (int i = 0; i < inputText.size(); i++) {
			std::cout << i + 1 << ": " << inputText.at(i) << '\n';
		}
		std::cout << "Input choice: ";
	}

	int getInput() {
		int input = 0;
		bool inMenu = true;
		do {
			std::cin >> input;
			if (input > inputText.size()) {
				std::cout << "Invalid option, please try again.\n";
			}
			else {
				inMenu = false;
				return input;
			}
		} while (inMenu);
	}
};