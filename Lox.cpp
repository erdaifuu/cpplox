#include <fstream>
#include <iostream>
#include <sstream>

bool g_hadError = false;

void report(int line, const std::string& where, const std::string& msg)
{
	std::cout << "[line " << line << "] Error" << where << ": " << msg << std::endl;
	g_hadError = true;
}

void error(int line, const std::string& msg)
{
	report(line, "", msg);
}

void run(const std::string& source)
{
	Scanner scanner(source);
	std::vector<Token> tokens = scanner.scanTokens();

	for (const Token& token : tokens)
	{
		std::cout << token << '\n';
	}
}

void runFile(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		std::cerr << "Unable to open file: " << path << std::endl;
		return;
	}
	std::ostringstream ss;
	ss << file.rdbuf();
	std::string source = ss.str();
	run(source);

	if (g_hadError) std::exit(65);
}

void runPrompt()
{
	while (true)
	{
		std::cout << "> ";
		std::string line;
		std::getline(std::cin, line);
		if (line.empty()) break;
		run(line);
		g_hadError = false;
	}
}

int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		std::cout << "Usage: clox [script]" << std::endl;
		return 64;
	}
	if (argc == 2)
	{
		runFile(argv[1]);
	}
	else
	{
		runPrompt();
	}
	// std::cout << argc << argv[1] << '\n';
	return 0;
};
