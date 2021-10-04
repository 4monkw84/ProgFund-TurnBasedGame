#pragma once

class menu {
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

	void printMenu() {
		system("CLS");

		for (int i = 0; i < outputText.size(); i++) {
			std::cout << outputText.at(i);
		}
		
		std::cout << "\n";

		for (int i = 0; i < inputOptions.size(); i++) {
			std::cout << i + 1 << ": " << inputOptions.at(i) << '\n';
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
			if (input > inputOptions.size()) {
				std::cout << "Invalid option, please try again.";
			}
			else {
				inMenu = false;
				return input;
			}
		} while (inMenu);
	}
};