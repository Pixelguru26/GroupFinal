#pragma once
// Menu options
void requestTicket(char chart[15][30], std::string* sales, int& saleSize, int& saleCount, double multiplier);
void requestTickets(char chart[15][30], std::string* sales, int& saleSize, int& saleCount, double multiplier);
void findTickets(char chart[15][30], std::string* sales, int& saleSize, int& saleCount, double multiplier);
void salesReport(char chart[15][30], std::string* sales, int& saleSize, int& saleCount);
void resetAvailability(char chart[15][30], std::string* sales, int& saleSize, int& saleCount);
void quitMenu(bool& running);
