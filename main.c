#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = { 10, /* TODO: fill in "n" i.e. instance sizes */ };

void fill_increasing(int *t, unsigned int n) {
    for(int i = 0; i < n; i++)
    {
      t[i] = i + 1;
    }
}

void fill_decreasing(int *t, unsigned int n) { //gdy n = 100 dobrze przypisuje od największej do najmniejszej do 51, potem jest rosnąco. Czemu ???
    int f[n];
    int g[n];
  for(i = 0; i < n; i++)
  {
    g[i] = i + 1;
  }

  for(j = 0; j < n; j++)
  {
      f[j] = g[i - 1];
      i--;
  }
}

void fill_vshape(int *t, unsigned int n) { //pierwsza największa, ostatnia druga największa (ok)
  for(int i = 0; i < n; i++)
  {
    t[i] = i + 1;
  }
  int first = t[n - 1];
  int last = t[n - 2];
  t[0] = first;
  t[n - 1] = last;

}

void selection_sort(int *t, unsigned int n) {
    int z = sizeof(t)/sizeof(int);
    int el_min;
    int el_drugi;
    for(int i = 0; i < z; i++)
    {
     el_min = i;
     
     for(int d = i + 1; d < z; d++)
     {
         el_drugi = d;
         if(t[el_drugi] < t[el_min])
         {
             int temp = t[el_min];
             t[el_min] = t[el_drugi];
             t[el_drugi] = temp;
         }   
     }
    }
}

void insertion_sort(int *t, unsigned int n) {
  int z = sizeof(t)/sizeof(int); // zmienna do wielkości tablicy
  int el; // zmienna do pobierania elementu
  int el_dwa; // zmienna do pobrania drugiego elementu do porownania
  for(int i = 1; i < n; i++)
  {
    el = t[i]; //zapamietuje wartosc, ktora jest pod t[i]
    el_dwa = i; // zapamietuje indeks i
    while(el_dwa > 0 && t[el_dwa - 1] > el) //element porownywany nie może być mniejszy niż zero i ma być większy od elementu pierwszego
  {
    t[el_dwa] = t[el_dwa - 1]; // nadpisujemy wartosc, ktora była  pod indeksem i wartoscia mniejsza po lewej stronie (i-1) dzieki czemu teraz pod t[i] jest wartosc wieksza niz pod t[i-1]
    el_dwa--; //zmniejszamy indeks o 1 (tak jakbysmy teraz patrzyli w lewo w tablice)
  }
  t[el_dwa] = el; //przypisujemy zapisana wartosc do miejsca o 1 wcześniej w tablicy,
  }

}

void quick_sort(int *t, unsigned int n) {
    // TODO: implement
}

void heap_sort(int *t, unsigned int n) {

}

void fill_random(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = rand();
    }
}

void is_random(int *t, unsigned int n) {
    return;
}

void is_increasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;

    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}

void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, unsigned int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                unsigned int n = ns[k];
                int *t = malloc(n * sizeof(*t));

                fill(t, n);
                check(t, n);

                clock_t begin = clock();
                sort(t, n);
                clock_t end = clock();
                is_sorted(t, n);

                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double) CLOCKS_PER_SEC);
                free(t);
            }
        }
    }
    return 0;
}
