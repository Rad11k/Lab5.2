#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Func(double x);

#define Data_IN "Data.txt"
#define Txt_OUT "Txt.txt"
#define fileBin_OUT "fileBin.bin"


int main() {

  float a, b, step, delta, x, put_bin;
  int N, ch;
  float **tabl = NULL, **tablBin = NULL;


  FILE *Data == NULL, *Txt == NULL, *fileBin == NULL;
  
  Data = fopen(Data_IN", "r");
               
  Txt = fopen(Txt_OUT, "w");
               
  fileBin = fopen(fileBin_OUT, "w+b");

  if(Data  == NULL || Txt_OUT == NULL || fileBin == NULL){
    printf("error open file");
    exit(0);
  }
               
  while (ch = getc(Data) != '\n');
               
  putchar(ch);
               
  fscanf(Data, " %f %f %d %f", &a, &b, &N, &step);

  delta = (b - a) / (N - 1);
               
  if (N == 0) {
    delta = step;
    N = ((b - a) / delta) + 1;
  }

               
  tabl = (int**)calloc(N, sizeof(int));
  tablBin = (int**)calloc(N, sizeof(int));
  for (int i = 0; i < N; i++) {
    tabl[i] = (int*)calloc(3, sizeof(int));
    tablBin[i] = (int*)calloc(3, sizeof(int));
  }


  printf("Function: 2 * pow((x-1000),3)- 3 * pow((x+500),2) + 4x - 5\n Start: %.0f\n End: %.0f\n Number: %d\n Delta: %.1f\n\n", a, b, N, delta);
  for (int i = 0; i < N; i++) {
    a += delta;
    x = a;
    tabl[i][0] = i + 1;
    tabl[i][1] = x;
    tabl[i][2] = Func(tabl[i][1]);
  }


  fprintf(Txt, "    N  \tx   f(x)\n");
  for (int i = 0; i < N; i++) {
    fprintf(Txt, "  %4.0f", tabl[i][0]);
    for (int j = 1; j < 3; j++) {
      fprintf(Txt, "  %4.1f", tabl[i][j]);
    }
    fprintf(Txt, "\n");
  }


  fwrite(&N, sizeof(int), 1, fileBin);
  for (int i = 0; i < N; i++) {
    for (int j = 1; j < 3; j++) {
      fwrite(&tabl[i][j], sizeof(float), 1, fileBin);
    }
  }
  fclose(fileBin);


  fileBin = fopen("fileBin.bin", "r+b");
  printf(" ---------------------\n | N |   x   |  f(x) |\n ---------------------\n");
  fread(&N, sizeof(int), 1, fileBin);
  printf("\n%d\n\n", N);
  for (int i = 0; i < N; i++) {
    int k = i + 1;
    printf("%d", k);
    for (int j = 1; j < 3; j++) {
      fread(&put_bin, sizeof(float), 1, fileBin);
      printf("   |%6.1f|", put_bin);
    }
    printf("\n");
  }
  printf("------------------------");



  fclose(Data);
  fclose(fileBin);
  fclose(Txt);
}
double Func(double x) {
  return (pow(x,3)/20)-(5*pow(x,2))+1000;
}
