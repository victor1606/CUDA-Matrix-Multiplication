Calugaritoiu Ion-Victor 332CA

ASC

1. solver_neopt.c:
- implementarea este cea clasica folosita pentru a inmulti matrici, 
cu precizarea ca se tine cont ca matricile sunt superior triunghiulare;
- nu este folosita o matrice auxiliara pentru a calcula transpusa / produsul
tranpuselor (Bt * Bt); am extras elementele direct in ordinea corespunzatoare
si am adunat sumele obtinute la matricea intermediara (A X B X A^t);

2. solver_opt_m.c:
- implementarea are aceeasi complexitate cu cea neoptimizata;
- pentru prima inmultire de matrici (A X B) am scris algoritmul folosind
pointeri;
- am identificat constantele din buclele for si le am marcat cu keyword-ul
"register": current_sum, orig_pa;

3. solver_blas.c:
- am alocat 3 matrici auxiliare;
- pentru A X B am apelat functia cblas_dtrmm, trimitand ca parametru CblasUpper
pentru a semnala ca matricile sunt superior triunghiulare; in prealabil am
copiat continutul matricei B in matricea auxiliara AB; am stocat rezultatul
in matricea AB;
- pentru AB X At am folosit functia cblas_dgemmt trimitand ca parametri 
CblasNoTrans/CblasTrans pentru a semnala ca primul termen - AB nu trebuie
transpus si ca al doilea termen - At trebuie transpus; am stocat rezultatul
in matricea ABAt;
- pentru Bt X Bt am folosit aceeasi functie ca la inmultirea precedenta; am
stocat rezultatul in matricea BtBt;
- pentru rezultatul final am folosit functia cblas_daxpy pentru a aduna cele
doua produse obtinute anterior: ABAt + BtBt; am stocat rezultatul in ABAt;


Explicatii cachegrind:
- I refs: se remarca faptul ca numarul de instructiuni scade de la 4.6
miliarde (neopt.c) la 2.6 miliarde (opt_m.c) la 296 de mii (blas.c);
    - neopt -> opt:     1.76x mai putine instructiuni
    - opt   -> blas:    8.96x mai putine instructiuni

- D refs: rezultate asemanatoare;
    - neopt: 2.8 miliarde accese memorie
    - opt  : 909 mii accese memorie
    - blas : 110 mii accese memorie

- miss rate cache nivel 1:
    - neopt: 3.5%
    - opt  : 10.8%
    - blas : 1.7%

    - desi versiunea opt este superioara ca timp celei neopt, procentajul
    de l1 cache misses este mai ridicat;

- Branches: numarul de branches scade
    - neopt: 323 milioane
    - opt  : 132 milioane
    - blas : 4.6 milioane

    - rata de predictie gresita a branch-urilor este cea mai mare pentru
    blas - 1.5%, chit ca are cel mai mic numar de branch-uri;


Explicatii grafice: neopt vs opt_m vs blas

- se poate observa un speedup major utilizand keyword-ul register pentru
variabilele constante din bucle + implementarea algoritmului de inmultire
folosind pointeri;
- graficele se gasesc in directorul "comparisons";

Valori obtinute:

neopt
N:    Time:
200   0.126805
400   1.068493
800	  8.738095
1000	16.388884
1200	28.791945

opt_m
N:    Time:
200	  0.047110
400	  0.417832
800	  3.712468
1000	6.275701
1200	11.426621

blas
N:    Time:
200 	0.007711
400	  0.046767
800	  0.345133
1000	0.682784
1200	1.138365

Teste:
5
200 159 out1
400 123 out2
800 456 out3
1000 567 out4
1200 789 out5