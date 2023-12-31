Rezolvare task1:
Am parcurs fiecare valoare (R,G,B) a fiecarui pixel al imaginii si
am aplicat regula celor 3 pahare pentru a interschimba pixelul 
corespondent de la coada.

Rezolvare task2:
Am alocat o zona de memorie pentru o noua matrice de inaltime M si
latime N, adica invers matricei initiale, apoi am parcurs matricea pe care vrem sa o rotim si i-am asociat matricei noi 
pixelul corespunzator.

Rezolvare task3:
Am alocat o zona de memorie pentru o noua matrice cu inaltimea h si latimea w. apoi am parcurs matricea noua si am egalat pixelul de pe pozitia (i,j) cu pixelul de pe pozitia (i+y, j+x) al matricei vechi.

Rezolvare task4:
Am creat doua variabile newHeight si newWidth fiind lungimea si latimea matricei pe care vrem sa o obtinem, apoi am alocat memorie pentru noua matrice. Am parcurs fiecare pixel din matricea noua si l-am egalat cu (new_R, new_G, new_B) iar apoi am iterat de la pozitia rows pana la newHeight - rows, si pe coloane la fel si am egalat pixelului de pe pozitia (i, j) valoarea pixelului din vechea imagine cu coordonatele (i - rows, j - cols).

Rezolvare task5: 
An iterat in matricea destinatie de la pozitia y si pe coloane la fel, apoi am modificat pixelul de pe pozitia (i, j) cu valoarea pixelului din imaginea sursa de pe pozitia (i - y, j - x).

Rezolvare task6:
Am alocat memorie pentru o noua imagine si verific daca alocarea a reusit. Iterez prin fiecare pixel al imaginii originale si aplic filtru primit ca parametru. Daca dimensiunea filtrului este 1 aplic direct pe el, altfel se efectueaza o convolutie in jurul fiecarui pixel. Normalizez valorile rezultate la interavalul [0,255] si le convertesc la intregi. Eliberez memoria alocata pentru imaginea originala si returnez imaginea noua.

Rezolvare task7:
Imaginile sunt stocate într-un array (imagesArray), iar dimensiunile sunt reținute într-un alt tablou (imagesValues).
Filtrele sunt stocate într-un array (filterArray), iar dimensiunile acestora sunt reținute într-un alt array (filtersSize).
Bucle pentru gestionarea comenzilor:

Se utilizează o buclă principală pentru a citi și procesa comenzile de la utilizator până când este primită comanda de încheiere.
Comenzile sunt citite și interpretate în funcție de caracterele primite (l, s, ah, ar, ac, ae, ap, af, cf, di, df, e).
Funcții specifice fiecărei comenzi:

Există secțiuni distincte pentru încărcarea și salvarea imaginilor (l, s), precum și pentru operațiunile asupra imaginilor (ah, ar, ac, ae, ap).
De asemenea, există secțiuni pentru gestionarea filtrelor (cf, af, df).
Dealocarea memoriei:

La încheierea programului, se efectuează dealocarea memoriei alocate dinamic pentru imagini și filtre.