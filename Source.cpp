#include <string>
#include <exception>
#include "construction_tools.h"

bool check_if_integer(std::string& str) {
	for (auto i : str) {
		if (!isdigit(i)) return false;
	}
	return true;
}

int main(int argc, char* argv[]) {
	if (argc == 3) {
		
		std::ifstream input(argv[1]);
		std::ofstream output(argv[2]);
		std::multimap<const Object, bool> Map;

		std::string str;


		try {
			if (!(input >> str)) throw std::invalid_argument("Not enough arguments\n");
			int N;
			
			if (check_if_integer(str)) N = stoi(str);
			else throw std::invalid_argument("Numbers must be unsigned int\n");
			
			for (size_t i = 0; i < N; i++) {
				size_t x(0);
				if (!(input >> str)) throw std::invalid_argument("Not enough arguments\n");

				if (check_if_integer(str)) x = stoi(str);
				else throw std::invalid_argument("Numbers must be unsigned int\n");
				
				if (!(input >> str)) throw std::invalid_argument("Not enough arguments\n");

				if (check_if_integer(str)) {
					Object obj(x, stoi(str), 'O');
					Map.insert({ obj, false });
				}
				else throw std::invalid_argument("Numbers must be unsigned int\n");
				
			}

			construct(Map);

			for (const auto& it : Map) {
				output << it.first << '\n';
			}
			std::cout << "done\n";

		}
		catch (std::exception& e) {
			std::cout << e.what();
			
		}

	}
	else std::cout << "Not enough arguments\n";
	
	system("pause");
	return 0;
}