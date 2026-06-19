#ifndef CPPLOX_LOX_H
#define CPPLOX_LOX_H

#include <string>

extern bool g_hadError;
void error(int line, const std::string& msg);
void report(int line, const std::string& where, const std::string& msg);
void run(const std::string& source);
void run_file(const std::string& path);
void run_prompt();

#endif //CPPLOX_LOX_H
