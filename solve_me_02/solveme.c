#include <stdio.h>

/**
 * The main function to iterate through the array.
 */
void iterate(int arr[][10], int  r, int c, int currentPositionR, int currentPositionC) {
  //get current node value
  int currentVal = arr[currentPositionR][currentPositionC];

  //if we are in this node, set it to -1 so we can remap later
  arr[currentPositionR][currentPositionC] = -1;

  // East
  if (currentPositionR < r) {
    // get next East val
    int nextRVal = arr[currentPositionR + 1][currentPositionC];
    // check if we can go East
    if (nextRVal != -1 && currentVal - nextRVal <= 2 && currentVal - nextRVal >= -2) {
      // recursive
      iterate(arr, r, c, currentPositionR + 1, currentPositionC);
    }
  }

  // South
  if (currentPositionC < c) {
    int nextCVal = arr[currentPositionR][currentPositionC + 1];
    if (nextCVal != -1 && currentVal - nextCVal <= 2 && currentVal - nextCVal >= -2) {
      iterate(arr, r, c, currentPositionR, currentPositionC + 1);
    }
  }

  //North
  if (currentPositionR != 0) {
    int preRVal = arr[currentPositionR - 1][currentPositionC];
    if (preRVal != -1 && currentVal - preRVal <= 2 && currentVal - preRVal >= -2) {
      iterate(arr, r, c, currentPositionR - 1, currentPositionC);
    }
  }

  //West
  if (currentPositionC != 0) {
    int preCVal = arr[currentPositionR][currentPositionC - 1];
    if (preCVal != -1 && currentVal - preCVal <= 2 && currentVal - preCVal >= -2) {
      iterate(arr, r, c, currentPositionR, currentPositionC - 1);
    }
  }
}

/**
 * Map the recursived array to 0 and 1
 */
void remapArr(int arr[][10], int  r, int c, int currentPositionR, int currentPositionC) {
  // iterate
  iterate(arr, r, c, 0, 0);
  // map all the -1 to 1 and others to 0
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      arr[i][j] = arr[i][j] == -1 ? 1 : 0;
    }
  }
}

void printArr(int arr[][10], int  r, int c) {
  int i;
  for (i = 0; i < r; i++) {
    int j;
    for (j = 0; j < c; j++) {
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int ROW = 10;
  int COL = 10;
  int arr[10][10] = {
    {50,  51,  54,  58,  60,  60,  60,  63,  68,  71},
    {48,  52,  51,  59,  60,  60,  63,  63,  69,  70},
    {44,  48,  52,  55,  58,  61,  64,  64,  66,  69},
    {44,  46,  53,  52,  57,  60,  60,  61,  65,  68},
    {42,  45,  50,  54,  59,  61,  63,  63,  66,  70},
    {38,  42,  46,  56,  56,  63,  64,  61,  64,  62},
    {36,  40,  44,  50,  58,  60,  66,  65,  62,  61},
    {36,  39,  42,  49,  56,  62,  67,  66,  65,  60},
    {30,  36,  40,  47,  50,  64,  64,  63,  62,  60},
    {32,  34,  38,  45,  51,  53,  58,  58,  57,  57},
  };

  // 0 0 is starting point
  remapArr(arr, ROW, COL, 0, 0);

  //print it out
  printArr(arr, ROW, COL);

  return 0;
}
