#pragma once

class menu {
	std::vector<std::string> inputText = {};
	std::vector<std::string> outputText = {};

public:
	//Text to be displayed separate from input options
	void setInputOptions(const std::vector<std::string> newInput) {
		inputText = newInput;
	}

	//title and/or description text to be printed
	void setOutputText(const std::vector<std::string> newOutput) {
		outputText = newOutput;
	}

	void printMenu() {
		system("CLS");

		for (int i = 0; i < outputText.size(); i++) {
			std::cout << outputText.at(i) << " " << std::endl;
		}
		
		std::cout << "\n";

		for (int i = 0; i < inputText.size(); i++) {
			std::cout << i + 1 << ": " << inputText.at(i) << '\n';
		}
	}

	int getInput() {
		int input = 0;
		bool inMenu = true;
		do {
			std::cout << "\nInput choice: ";
			std::cin >> input;

			if (std::cin.fail()) {
				std::cerr << "Invalid option, please try again.";
				std::cin.clear();
				std::cin.ignore(256, '\n');
				continue;
			}
			if (input > inputText.size()) {
				std::cout << "Invalid option, please try again.";
			}
			else {
				inMenu = false;
				return input;
			}
		} while (inMenu);
	}
};