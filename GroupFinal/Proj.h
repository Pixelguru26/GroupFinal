#include <vector>

#pragma once
// Menu options
void requestTicket(char chart[15][30], std::vector<std::string>& sales, double multiplier);
void requestTickets(char chart[15][30], std::vector<std::string>& sales, double multiplier);
void findTickets(char chart[15][30], std::vector<std::string>& sales, double multiplier);
void salesReport(char chart[15][30], std::vector<std::string>& sales);
void quitMenu(bool& running);
