#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"


void freeImageMemory(int ***image, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
            image[i][j] = NULL;
        }
        free(image[i]);
        image[i] = NULL;
    }
    free(image);
    image = NULL;
}

// TODO(albert.anghelescu): Task1.
int ***flip_horizontal(int ***image, int N, int M) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M / 2; j++) {
      for (int k = 0; k < 3; k++) {
        int aux = image[i][j][k];
        image[i][j][k] = image[i][M - 1 - j][k];
        image[i][M - 1 - j][k] = aux;
      }
    }
  }
  return image;
}

// TODO(albert.anghelescu): Task2.
int ***rotate_left(int ***image, int N, int M) {
  int ***newImage = (int ***)malloc(M * sizeof(int **));
  for (int i = 0; i < M; i++) {
    newImage[i] = (int **)malloc(N * sizeof(int *));
    for (int j = 0; j < N; j++) {
      newImage[i][j] = (int *)malloc(3 * sizeof(int));
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      for (int k = 0; k < 3; k++) {
        newImage[M - 1 - j][i][k] = image[i][j][k];
      }
    }
  }
  freeImageMemory(image, N, M);
  return newImage;
}

// TODO(albert.anghelescu): Task3.
int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
  int ***newImage = (int ***)malloc(h * sizeof(int **));
  for (int i = 0; i < h; i++) {
    newImage[i] = (int **)malloc(w * sizeof(int *));
    for (int j = 0; j < w; j++) {
      newImage[i][j] = (int *)malloc(3 * sizeof(int));
    }
  }

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      for (int k = 0; k < 3; k++) {
        newImage[i][j][k] = image[i + y][j + x][k];
      }
    }
  }
  freeImageMemory(image, N, M);
  return newImage;
}

// TODO(albert.anghelescu): Task4.
int ***extend(int ***image, int N, int M, int rows, int cols, int new_R,
              int new_G, int new_B) {
  int newHeight = N + rows * 2;
  int newWidth = M + cols * 2;
  int ***newImage = (int ***)malloc(newHeight * sizeof(int **));
  for (int i = 0; i < newHeight; i++) {
    newImage[i] = (int **)malloc(newWidth * sizeof(int *));
    for (int j = 0; j < newWidth; j++) {
      newImage[i][j] = (int *)malloc(3 * sizeof(int));
    }
  }

  for (int i = 0; i < newHeight; i++) {
    for (int j = 0; j < newWidth; j++) {
      newImage[i][j][0] = new_R;
      newImage[i][j][1] = new_G;
      newImage[i][j][2] = new_B;
    }
  }

  for (int i = rows; i < newHeight - rows; i++) {
    for (int j = cols; j < newWidth - cols; j++) {
      for (int k = 0; k < 3; k++) {
        newImage[i][j][k] = image[i - rows][j - cols][k];
      }
    }
  }
  freeImageMemory(image, N, M);
  return newImage;
}

// TODO(albert.anghelescu): Task5.
int ***paste(int ***image_dst, int N_dst, int M_dst, int ***image_src,
             int N_src, int M_src, int x, int y) {
  for (int i = y; i < N_dst; i++) {
    for (int j = x; j < M_dst; j++) {
      for (int k = 0; k < 3; k++) {
        if (i - y < N_src && j - x < M_src) {
          image_dst[i][j][k] = image_src[i - y][j - x][k];
        }
      }
    }
  }
  return image_dst;
}

// TODO(albert.anghelescu): Task6.
int ***apply_filter(int ***image, int N, int M, float **filter,
                    int filter_size) {
  int ***newImage = (int ***)malloc(N * sizeof(int **));
  if (newImage == NULL) {
    return NULL;
  }
  for (int i = 0; i < N; i++) {
    newImage[i] = (int **)malloc(M * sizeof(int *));
    if (newImage[i] == NULL) {
      return NULL;
    }
    for (int j = 0; j < M; j++) {
      newImage[i][j] = (int *)malloc(3 * sizeof(int));
      if (newImage[i][j] == NULL) {
        return NULL;
      }
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      for (int k = 0; k < 3; k++) {
        float newK = 0;
        if (filter_size == 1) {
          newK += filter[0][0] * (float)(image[i][j][k]);
        } else {
        for (int l = -filter_size / 2; l < filter_size / 2 + 1; l++) {
          for (int m = -filter_size / 2; m < filter_size / 2 + 1; m++) {
            int row = i + l;
            int col = j + m;

            if (row >= 0 && row < N && col >= 0 && col < M &&
                l + filter_size / 2 < filter_size &&
                m + filter_size / 2 < filter_size) {
              newK += (float)(image[row][col][k]) *
                      filter[l + filter_size / 2][m + filter_size / 2];
            }
          }
        }
        }
        const int maxK = 255, minK = 0;
        int newK_integer = (int)(newK);
        if (newK_integer > maxK) {
          newK_integer = maxK;
        }
        if (newK_integer < minK) {
          newK_integer = minK;
        }
        newImage[i][j][k] = newK_integer;
      }
    }
  }
  freeImageMemory(image, N, M);
  return newImage;
}
