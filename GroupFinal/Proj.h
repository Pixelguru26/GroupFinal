#pragma once
// Menu options
void requestTickets(char chart[15][30], double* sales, int& saleSize, int& saleCount);
void findTickets(char chart[15][30], double* sales, int& saleSize, int& saleCount);
void salesReport(char chart[15][30], double* sales, int& saleSize, int& saleCount);
void resetAvailability(char chart[15][30], double* sales, int& saleSize, int& saleCount);
void quitMenu(bool& running);
