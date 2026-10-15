---
marp: true
theme: default
paginate: true
style: |
  section { font-size: 26px; }
  pre { font-size: 20px; }
---

# Data warehouse in Oracle

## Estensioni al linguaggio SQL per l'analisi dei dati
## Viste materializzate

Tania Cerquitelli

---

# Estensioni al linguaggio SQL per l'analisi dei dati

---

# Funzioni OLAP disponibili

- Finestre di calcolo
  - window
- Funzioni di ranking
  - rank, dense rank, ...
- Estensione della clausola group by
  - rollup, cube, ...

---

# Tabella d'esempio

- Schema tabella
  - VENDITE(Città, Data, Importo)

---

# Esempio di raggruppamento a livello fisico

- Selezionare, separatamente per ogni città, per ogni data l'importo e la media dell'importo considerando la riga corrente e le due righe che la precedono

---

# Esempio di raggruppamento a livello fisico

```sql
SELECT Città, Data, Importo, AVG(Importo)
OVER (
  PARTITION BY Città
  ORDER BY Data
  ROWS 2 PRECEDING
) AS MediaMobile
FROM Vendite
ORDER BY Città, Data;
```

---

# Esempio di raggruppamento a livello logico

- Selezionare, separatamente per ogni città, per ogni data l'importo e la media dell'importo considerando la riga corrente e le vendite avvenute nei due giorni precedenti

---

# Esempio di raggruppamento a livello logico

```sql
SELECT Città, Data, Importo, AVG(Importo) OVER
(
  PARTITION BY Città
  ORDER BY Data
  RANGE BETWEEN INTERVAL '2'
  DAY PRECEDING AND CURRENT ROW
) AS MediaUltimi3Giorni
FROM Vendite
ORDER BY Città, Data;
```

---

# Tabelle d'esempio

- Schema tabelle
  - FRN(COD_F, Nome, Sede_F, )
  - ART(COD_A, Tipo, Colore, Peso)
  - PRG(COD_P, Nome, Sede_P)
  - FAP(COD_F, COD_P, COD_A, Q)

---

# Esempio di ranking

- Selezionare per ogni articolo la quantità totale venduta e il "ranking" in funzione delle quantità totali vendute per ogni articolo

---

# Esempio di ranking

```sql
SELECT COD_A, SUM(Q) AS QTot,
RANK() OVER (
  ORDER BY SUM(Q)
) AS RankVendite
FROM FAP
GROUP BY COD_A;
```

---

# Esempio di ranking

```
COD_A    QTot    RankVendite
-----  ------  -----------
A2        300            1
A5       1100            2
A4       1300            3
A6       1300            3
A1       1900            5
A3       4500            6
```

---

# Esempio di dense ranking

```sql
SELECT COD_A, SUM(Q) AS QTot,
DENSE_RANK() OVER (
  ORDER BY SUM(Q)
) AS DenseRankVendite
FROM FAP
GROUP BY COD_A;
```

---

# Esempio di dense ranking

```
COD_A    QTot    DenseRankVendite
-----  ------  ----------------
A2        300                 1
A5       1100                 2
A4       1300                 3
A6       1300                 3
A1       1900                 4
A3       4500                 5
```

---

# Esempio di doppio ranking

- Selezionare per ogni articolo il codice, il peso, la quantità totale venduta, il ranking in funzione del peso e il ranking in funzione delle quantità totali vendute per ogni articolo

---

# Esempio di doppio ranking

```sql
SELECT ART.COD_A, ART.Peso,
SUM(Q) AS QTot,
RANK() OVER (ORDER BY ART.Peso
) AS R_Peso,
RANK() OVER (ORDER BY SUM(Q)
) AS R_Vend
FROM FAP, ART
WHERE FAP.COD_A = ART.COD_A
GROUP BY ART.COD_A, ART.Peso
ORDER BY R_Peso;
```

---

# Esempio di doppio ranking

```
COD_A  PESO  Qtot  R_Peso  R_Vend
-----  ----  ----  ------  ------
A1       12  1900       1       5
A5       12  1100       1       2
A4       14  1300       3       3
A2       17   300       4       1
A3       17  4500       4       6
A6       19  1300       6       3
```

---

# Selezione Top N nel ranking

- Se voglio solo i primi due articoli nel ranking posso usare l'interrogazione che calcola il ranking come sottointerrogazione e poi fare una selezione in base al campo di ranking
  - La sottointerrogazione è specificata tra parentesi tonde subito dopo la FROM e viene utilizzata come se fosse una tabella

---

# Selezione Top N nel ranking

```sql
SELECT * FROM
(SELECT COD_A, SUM(Q),
 RANK() OVER (ORDER BY SUM(Q))
 AS RankVendite
 FROM FAP
 GROUP BY COD_A)
WHERE RankVendite <= 2;
```

---

# Selezione Top N nel ranking

```sql
SELECT * FROM
(SELECT COD_A, SUM(Q),
 RANK() OVER (ORDER BY SUM(Q))
 AS RankVendite
 FROM FAP
 GROUP BY COD_A)
WHERE RankVendite <= 2;
```

> Viene gestita come una tabella temporanea creata a runtime ed eliminata alla conclusione dell'esecuzione della query principale

---

# Selezione Top N nel ranking

```
COD_A  SUM(Q)  RankVendite
-----  ------  -----------
A2        300            1
A5       1100            2
```

---

# ROW_NUMBER

- ROW_NUMBER
  - all'interno di ogni partizione assegna un numero progressivo ad ogni riga

---

# Esempio ROW_NUMBER

- Partizionare gli articoli in base alla tipologia ed enumerare in modo progressivo i dati all'interno di ogni partizione. All'interno di ogni partizione i dati sono ordinati in base al peso.

---

# Esempio ROW_NUMBER

```sql
SELECT Tipo, Peso, ROW_NUMBER() OVER (
  PARTITION BY Tipo
  ORDER BY Peso
) AS RowNumberPeso
FROM ART;
```

---

# Esempio ROW_NUMBER

```
Tipo         Peso  RowNumberPeso
-----------  ----  -------------
Barra          12              1   <- Partizione 1
Ingranaggio    19              1   <- Partizione 2
Vite           12              1   <- Partizione 3
Vite           14              2
Vite           16              3
Vite           16              4
Vite           16              5
Vite           16              6
Vite           17              7
Vite           17              8
Vite           18              9
Vite           20             10
```

---

# CUME_DIST

- CUME_DIST
  - all'interno di ogni partizione (gruppo) viene assegnato un peso tra 0 e 1 ad ogni riga in funzione del numero di valori che precedono il valore assunto dal campo usato per effettuare l'ordinamento all'interno delle partizioni

---

# CUME_DIST

- Data una partizione contenente N dati, per ogni riga x calcolo CUME_DIST come
  - CUME_DIST(x) = numero valori che precedono o hanno lo stesso valore assunto dal campo di ordinamento all'interno di x diviso N

---

# Esempio CUME_DIST

- Partizionare gli articoli in base alla tipologia degli articoli ed effettuare un ordinamento nei gruppi in base al peso degli articoli. Associare ad ogni riga il rispettivo valore di CUME_DIST

---

# Esempio CUME_DIST

```sql
SELECT Tipo, Peso, CUME_DIST() OVER (
  PARTITION BY Tipo
  ORDER BY Peso
) AS CumePeso
FROM ART;
```

---

# Esempio CUME_DIST

```
Tipo         Peso  CumePeso
-----------  ----  ------------------
Barra          12  1   ( = 1/1)   <- Partizione 1
Ingranaggio    19  1   ( = 1/1)   <- Partizione 2
Vite           12  .1  ( = 1/10)  <- Partizione 3
Vite           14  .2  ( = 2/10)
Vite           16  .6  ( = 6/10)
Vite           16  .6  ( = 6/10)
Vite           16  .6  ( = 6/10)
Vite           16  .6  ( = 6/10)
Vite           17  .8  ( = 8/10)
Vite           17  .8  ( = 8/10)
Vite           18  .9  ( = 9/10)
Vite           20  1   ( = 10/10)
```

---

# NTILE

- NTILE(n)
  - permette di dividere ogni partizione in n sottogruppi (se possibile) ognuno con lo stesso numero di dati/record. Ad ogni sottogruppo viene associato un numero identificativo

---

# Esempio NTILE

- Partizionare gli articoli in base alla tipologia ed effettuare un'ulteriore suddivisione in 3 sottogruppi ognuno contenente lo stesso numero di dati. All'interno di ogni partizione i dati sono ordinati in base al peso degli articoli

---

# Esempio NTILE

```sql
SELECT Tipo, Peso, NTILE(3) OVER (
  PARTITION BY Tipo
  ORDER BY Peso
) AS Ntile3Peso
FROM ART;
```

---

# Esempio NTILE

```
Tipo         Peso  Ntile3Peso
-----------  ----  ----------
Barra          12           1   <- Partizione 1
Ingranaggio    19           1   <- Partizione 2
Vite           12           1   <- Partizione 3
Vite           14           1
Vite           16           1   <- Sottogruppo 1
Vite           16           1
Vite           16           2
Vite           16           2   <- Sottogruppo 2
Vite           17           2
Vite           17           3
Vite           18           3   <- Sottogruppo 3
Vite           20           3
```
