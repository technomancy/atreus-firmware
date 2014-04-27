// numbers under 100: normal keys
// numbers between 100 and 200: shifted keys
// numbers over 200: function invocations

int base_layout[ROW_COUNT][COL_COUNT] = \
  { {20, 26, 8,   21,  23,  0,  28, 24, 12, 18, 19},      \
    {4,  22, 7,   9,   10,  0,  11, 13, 14, 15, 51},      \
    {29, 27, 6,   25,  5,  104, 17, 16, 54, 55, 56},      \
    {255, 43, 108, 102, 42, 101, 44, 0,  52, 47, 40} };
// make it easy to trigger reset until we get fn sorted out, esc is 41

int fn_layout[ROW_COUNT][COL_COUNT] = \
  { {108+30, 108+31, 108+45, 108+46, 108 + 49, 0, 75, 36, 37, 38, 108+37}, \
    {108+32, 108+33, 108+38, 108+39, 53, 0, 78, 33, 34, 35, 108+48},    \
    {108 + 34, 108 + 35, 45, 46, 108+53, 104, 49, 30, 31, 32, 108+47},  \
    {255, 108 + 73, 108, 102, 0, 101, 0, 0, 8, 39, 48} };
