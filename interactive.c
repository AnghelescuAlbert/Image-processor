#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "imageprocessing.h"


int main() {
  // TODO(albert.anghelescu): Task7.
  int is_Running = 1;

  int ****imagesArray = NULL;
  int imageIndex = 0;
  int **imagesValues = NULL;

  float ***filterArray = NULL;
  int filterIndex = 0;
  int *filtersSize = NULL;

  char commandName[3] = {0};
  const int Size = 100;
  while (is_Running) {
    scanf("%2s", commandName);
    if (commandName[0] == 'l') {
      int N = 0, M = 0;
      char path[Size];
      scanf("%d %d %s", &N, &M, path);

      int ***newImage = (int ***)malloc(N * sizeof(int **));
      for (int i = 0; i < N; i++) {
        newImage[i] = (int **)malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++) {
          newImage[i][j] = (int *)malloc(3 * sizeof(int));
        }
      }
      int *newValues = (int *)malloc(2 * sizeof(int));
      newValues[0] = N;
      newValues[1] = M;
      read_from_bmp(newImage, N, M, path);
      int ****tempArray = NULL;
      if (imageIndex == 0) {
        tempArray = (int ****)malloc((imageIndex + 1) * sizeof(int ***));
      } else {
        tempArray =
            (int ****)realloc(imagesArray, (imageIndex + 1) * sizeof(int ***));
      }
      imagesArray = tempArray;
      imagesArray[imageIndex] = newImage;
      int **tempValues = NULL;
      if (imageIndex == 0) {
        tempValues = (int **)malloc((imageIndex + 1) * sizeof(int *));
      } else {
        tempValues =
            (int **)realloc(imagesValues, (imageIndex + 1) * sizeof(int *));
      }
      imagesValues = tempValues;
      imagesValues[imageIndex] = newValues;

      imageIndex++;
    }

    if (commandName[0] == 's') {
      int index = 0;
      char path[Size];
      scanf("%d %s", &index, path);
      write_to_bmp(imagesArray[index], imagesValues[index][0],
                   imagesValues[index][1], path);
    }
    if (commandName[0] == 'a' && commandName[1] == 'h') {
      int index = 0;
      scanf("%d", &index);
      imagesArray[index] = flip_horizontal(
          imagesArray[index], imagesValues[index][0], imagesValues[index][1]);
    }

    if (commandName[0] == 'a' && commandName[1] == 'r') {
      int index = 0;
      scanf("%d", &index);

      int ***newImage = NULL;
      newImage = rotate_left(imagesArray[index], imagesValues[index][0],
                             imagesValues[index][1]);
      imagesArray[index] = newImage;

      int aux = 0;
      aux = imagesValues[index][0];
      imagesValues[index][0] = imagesValues[index][1];
      imagesValues[index][1] = aux;
    }

    if (commandName[0] == 'a' && commandName[1] == 'c') {
      int index = 0, x = 0, y = 0, w = 0, h = 0;
      scanf("%d %d %d %d %d", &index, &x, &y, &w, &h);
      int ***newImage = NULL;
      newImage = crop(imagesArray[index], imagesValues[index][0],
                      imagesValues[index][1], x, y, h, w);
      imagesValues[index][0] = h;
      imagesValues[index][1] = w;
      imagesArray[index] = newImage;
    }

    if (commandName[0] == 'a' && commandName[1] == 'e') {
      int index = 0, rows = 0, cols = 0, R = 0, G = 0, B = 0;
      scanf("%d %d %d %d %d %d", &index, &rows, &cols, &R, &G, &B);
      int ***newImage = NULL;
      newImage = extend(imagesArray[index], imagesValues[index][0],
                        imagesValues[index][1], rows, cols, R, G, B);
      imagesValues[index][0] += rows * 2;
      imagesValues[index][1] += cols * 2;
      imagesArray[index] = newImage;
    }

    if (commandName[0] == 'a' && commandName[1] == 'p') {
      int index_dst = 0, index_src = 0, x = 0, y = 0;
      scanf("%d%d%d%d", &index_dst, &index_src, &x, &y);
      imagesArray[index_dst] =
          paste(imagesArray[index_dst], imagesValues[index_dst][0],
                imagesValues[index_dst][1], imagesArray[index_src],
                imagesValues[index_src][0], imagesValues[index_src][1], x, y);
    }

    if (commandName[0] == 'c' && commandName[1] == 'f') {
      int size = 0;
      scanf("%d", &size);
      float **filter = (float **)malloc(size * sizeof(float *));
      for (int i = 0; i < size; i++) {
        filter[i] = (float *)malloc(size * sizeof(float));
      }
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          float nr = 0;
          scanf("%f", &nr);
          filter[i][j] = nr;
        }
      }
      if (filterIndex == 0) {
        filterArray = (float ***)malloc(sizeof(float **));
      } else {
        filterArray = (float ***)realloc(filterArray, (filterIndex + 1) *
                                                              sizeof(float **));
      }
      filterArray[filterIndex] = filter;
      int *tempFiltersSize = NULL;
      if (filterIndex == 0) {
        tempFiltersSize = (int *)malloc(sizeof(int));
      } else {
        tempFiltersSize =
            (int *)realloc(filtersSize, (filterIndex + 1) * sizeof(int));
      }
      filtersSize = tempFiltersSize;
      filtersSize[filterIndex] = size;
      filterIndex++;
    }

    if (commandName[0] == 'a' && commandName[1] == 'f') {
      int index_img = 0, index_filter = 0;
      scanf("%d%d", &index_img, &index_filter);
      int ***filteredImage = NULL;
      filteredImage =
          apply_filter(imagesArray[index_img], imagesValues[index_img][0],
                       imagesValues[index_img][1], filterArray[index_filter],
                       filtersSize[index_filter]);
      imagesArray[index_img] = filteredImage;
    }

    if (commandName[0] == 'd' && commandName[1] == 'f') {
      int index_filter = 0;
      scanf("%d", &index_filter);
      if (filterIndex == 0) {
        continue;
      }
      if (filterIndex == 1) {
        for (int j = 0; j < filtersSize[0]; j++) {
          free(filterArray[0][j]);
          filterArray[0][j] = NULL;
        }
        free(filterArray[0]);
        filterArray[0] = NULL;
        free(filterArray);
        filterArray = NULL;

        free(filtersSize);
        filtersSize = NULL;
        filterIndex--;
      } else {
        float ***newFilterArray =
            (float ***)malloc((filterIndex - 1) * sizeof(float **));
        for (int i = 0, k = 0; i < filterIndex; i++) {
          if (i != index_filter) {
            newFilterArray[k++] = filterArray[i];
          }
        }

        for (int i = 0; i < filtersSize[index_filter]; i++) {
          free(filterArray[index_filter][i]);
        }
        free(filterArray[index_filter]);
        free(filterArray);

        filterArray = newFilterArray;

        int *newFiltersSize = (int *)malloc((filterIndex - 1) * sizeof(int));
        for (int i = 0, k = 0; i < filterIndex; i++) {
          if (i != index_filter) {
            newFiltersSize[k++] = filtersSize[i];
          }
        }
        free(filtersSize);
        filtersSize = newFiltersSize;

        filterIndex--;
      }
    }

    if (commandName[0] == 'd' && commandName[1] == 'i') {
      int index_img = 0;
      scanf("%d", &index_img);
      if (imageIndex == 0) {
        continue;
      } else if (imageIndex == 1) {
        freeImageMemory(imagesArray[index_img], imagesValues[index_img][0],
                        imagesValues[index_img][1]);
        free(imagesArray);
        free(imagesValues[index_img]);
        free(imagesValues);
        imageIndex--;
      } else {
        int ****newImagesArray =
            (int ****)malloc((imageIndex - 1) * sizeof(int ***));
        int **newImagesValue = (int **)malloc((imageIndex - 1) * sizeof(int *));
        for (int i = 0, k = 0; i < imageIndex; i++) {
          if (i != index_img) {
            newImagesValue[k] = imagesValues[i];
            newImagesArray[k++] = imagesArray[i];
          }
        }

        freeImageMemory(imagesArray[index_img], imagesValues[index_img][0],
                        imagesValues[index_img][1]);
        free(imagesValues[index_img]);
        free(imagesValues);
        free(imagesArray);

        imagesArray = newImagesArray;
        imagesValues = newImagesValue;
        imageIndex--;
      }
    }

    if (commandName[0] == 'e') {
      is_Running = 0;
    }
  }
  // FREEING THE MEMORY
  if (imageIndex != 0) {
    for (int i = 0; i < imageIndex; i++) {
      freeImageMemory(imagesArray[i], imagesValues[i][0], imagesValues[i][1]);
    }
    free(imagesArray);
    imagesArray = NULL;

    for (int i = 0; i < imageIndex; i++) {
      free(imagesValues[i]);
      imagesValues[i] = NULL;
    }
    free(imagesValues);
    imagesValues = NULL;
  }
  if (filterIndex != 0) {
    for (int i = 0; i < filterIndex; i++) {
      for (int j = 0; j < filtersSize[i]; j++) {
        free(filterArray[i][j]);
      }
      free(filterArray[i]);
    }
    free(filterArray);
    free(filtersSize);
    filtersSize = NULL;
  }

  return 0;
}
