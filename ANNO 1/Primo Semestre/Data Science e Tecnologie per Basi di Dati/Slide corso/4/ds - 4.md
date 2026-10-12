---
marp: true
theme: default
paginate: true
---

# Data warehouse Analisi dei dati

Elena Baralis Politecnico di Torino

---

# Operazioni di analisi dei dati

• Calcolo di funzioni aggregate lungo una o più dimensioni – necessità di fornire supporto a diversi tipi di funzione aggregata (esempi: media mobile, top ten) • Operazioni di confronto, essenziali per confrontare l’andamento degli affari (esempio: confronto dei dati delle vendite in mesi diversi) – è difficile eseguire confronti utilizzando solo il linguaggio SQL • Analisi dei dati mediante tecniche di data mining

---

# Strumenti di interfaccia

L’utente può interrogare il data warehouse mediante strumenti di vario tipo:

• ambiente controllato di query

• strumenti specifici di query e generazione rapporti

• strumenti di data mining

---

# Ambiente controllato di query

![Dashboard di esempio con grafici: Highest Projected Values, Active Service Records by Category, Highest values, Open Service Records by Month, Active Service Records, Inventory Overview - Operating System](image-placeholder)

• Sono definite

– ricerche complesse con struttura prefissata (normalmente parametrica)

– procedure specifiche di analisi

– rapporti con struttura prefissata

---

# Ambiente controllato di query

• È possibile introdurre elementi specifici del settore economico considerato

• È necessario lo sviluppo di codice ad hoc

– si utilizzano stored procedures, applicazioni contenute in packages, join e aggregazioni predefinite

– sono disponibili strumenti flessibili per la gestione della reportistica, che permettono di definire layout, periodicità di pubblicazione, liste di distribuzione

---

# Ambiente di query ad hoc

• È possibile definire interrogazioni OLAP di tipo arbitrario, progettate al momento dall’utente – formulazione delle interrogazioni mediante tecniche point and click, che generano automaticamente istruzioni SQL – si possono definire interrogazioni (tipicamente) complesse – interfaccia basata sul paradigma dello spreadsheet • Una sessione di lavoro OLAP permette raffinamenti successivi della stessa interrogazione • Utile quando i rapporti predefiniti non sono adeguati

---

# OLAP

Elena Baralis Politecnico di Torino

---

# Analisi OLAP

• Operazioni di ricerca disponibili – roll up, drill down – slice and dice – pivot di tabelle – ordinamento

• Le operazioni possono essere – combinate tra loro nella stessa query – eseguite in una sequenza di raffinamenti successivi della stessa query che forma la sessione di lavoro OLAP

---

## Roll up

• Riduzione di dettaglio dei dati mediante – la riduzione del livello di dettaglio di una delle dimensioni presenti, con l’aumento di livello in una gerarchia • esempio group by negozio, mese → group by città, mese – l’eliminazione di una delle dimensioni presenti • esempio group by prodotto, città → group by prodotto

---

# Roll up

![Rappresentazione grafica del roll up: da cubo dettagliato a cubo aggregato](image-placeholder)

Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006

---

 Roll up

| Metrics | Dollar Sales |
|---|---|

---

 Roll up

| Category | Year | Metrics Customer Region | Dollar Sales North-East | Mid-Atlantic | South-East | Central | South | North-West | South-West | England | France | Germa |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Electronics | 1997 | | $138 | $1.774 | $384 | $138 | $2.346 | $2.554 | $2.184 | $566 | $199 | $ |
| Food | 1997 | | $1.184 | $4.529 | $1.892 | $7.232 | $651 | $9.488 | $476 | $2.683 | $462 | $7 |
| Gifts | 1997 | | $759 | $682 | $729 | $262 | $588 | $469 | $807 | $156 | $615 | $1 |
| Health & Beauty | 1997 | | $538 | $925 | $959 | $677 | $213 | $1.503 | $261 | $165 | $175 | $1 |
| Household | 1997 | | $2.532 | $1.355 | $1.854 | $1.413 | $2.535 | $2.132 | $1.904 | $908 | $375 | $1.0 |
| Kid's Korner | 1997 | | $1.955 | $2.785 | $2.800 | $2.695 | $1.813 | $2.844 | $1.778 | $1.158 | $717 | $6 |
| Travel | 1997 | | $6.21 | $6.40 | $1.317 | $6.47 | $588 | $754 | $654 | $143 | $292 | $31 |
| | 1998 | | $611 | $887 | $566 | $382 | $499 | $1.162 | $1.044 | $273 | $72 | |
| Household | 1997 | | $5.354 | $4.112 | $5.410 | $4.446 | $3.058 | $3.974 | $2.654 | $3.545 | $2.875 | $1.9 |
| | 1998 | | $5.787 | $5.320 | $5.416 | $6.812 | $4.334 | $5.008 | $7.588 | $2.139 | $3.649 | $2.7 |
| Kid's Korner | 1997 | | $201 | $398 | $485 | $186 | $409 | $323 | $396 | $105 | $34 | $ |
| Travel | 1997 | | $247 | $422 | $441 | $380 | $221 | $592 | $290 | $198 | $19 | |
| | 1998 | | $624 | $505 | $564 | $386 | $300 | $978 | $416 | $48 | $38 | |
| | 1998 | | $608 | $559 | $1.096 | $611 | $464 | $316 | $573 | $257 | $198 | $ |

![Freccia roll up](image-placeholder)

| Category | Metrics | Dollar Sales Year |
|---|---|---|
| Electronics | | $10.616 | $29.299 |
| Food | | $5.300 | $5.638 |
| Gifts | | $16.315 | $20.047 |
| Health & Beauty | | $6.042 | $6.665 |
| Household | | $38.383 | $50.391 |
| Kid's Korner | | $2.559 | $2.943 |
| Travel | | $4.497 | $4.792 |

Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006
Copyright - Tutti i diritti riservati
DATA WAREHOUSE: OLAP - 12

---

## Drill down

• Aumento di dettaglio dei dati mediante – l’aumento del livello di dettaglio di una delle dimensioni presenti, con la riduzione di livello in una gerarchia

• esempio: da raggruppamento per città e mese a raggruppamento per negozio e mese

– l’aggiunta di una nuova dimensione

• esempio: da raggruppamento per città, raggruppamento per città e prodotto

• Spesso il drill down opera su un sottoinsieme dei dati di partenza

---

# Drill down

![Rappresentazione grafica del drill down: da cubo aggregato a cubo dettagliato](image-placeholder)

Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006

---

Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006
Copyright – Tutti i diritti riservati
Drill down

![Freccia drill down](image-placeholder)

---

![Drill down: Database and data mining group, Politecnico di Torino. Tabella aggregata per categoria e anno, freccia, tabella dettagliata per categoria, regione cliente e anno. Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006. Copyright – Tutti i diritti riservati. DATA WAREHOUSE: OLAP - 16. Elena Baralis Politecnico di Torino](image-placeholder)

---

# Slice and dice

• Riduzione del volume dei dati da analizzare – selezione di un sottoinsieme mediante predicati

• slice: predicato di uguaglianza che seleziona una “fetta”

– esempio: Anno=2005

• dice: combinazione di predicati che seleziona un “cubetto”

– esempio: Categoria=‘Alimentari’ and Città=‘Torino’

---

Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006

![Rappresentazione grafica di slice and dice](image-placeholder)

Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006

---

 Slice and dice

| Category | Year | Metrics Customer Region | Dollar Sales North-East | Mid-Atlantic | South-East | Central | South | North-West | South-West | England | France | Germany |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Electronics | 1997 | | $138 | $1.774 | $384 | $138 | $2.346 | $2.554 | $2.184 | $566 | $199 | $ |
| | 1998 | | $1.184 | $4.529 | $1.892 | $7.232 | $651 | $9.488 | $476 | $2.683 | $462 | $7 |
| Food | 1997 | | $759 | $682 | $729 | $262 | $588 | $469 | $807 | $156 | $615 | $1 |
| | 1998 | | $538 | $925 | $959 | $677 | $213 | $1.503 | $261 | $165 | $175 | $1 |
| Gifts | 1997 | | $2.532 | $1.355 | $1.854 | $1.413 | $2.535 | $2.132 | $1.904 | $908 | $375 | $1.0 |
| | 1998 | | $1.955 | $2.785 | $2.800 | $2.695 | $1.813 | $2.844 | $1.778 | $1.158 | $717 | $6 |
| Health & Beauty | 1997 | | $624 | $640 | $1.317 | $647 | $588 | $754 | $654 | $143 | $292 | $3 |
| | 1998 | | $611 | $887 | $566 | $382 | $499 | $1.162 | $1.044 | $273 | $72 | $ |
| Household | 1997 | | $5.354 | $4.112 | $5.410 | $4.446 | $3.058 | $3.974 | $2.654 | $3.545 | $2.875 | $1.9 |
| | 1998 | | $5.787 | $5.320 | $5.416 | $6.812 | $4.334 | $5.008 | $7.588 | $2.139 | $3.649 | $2.7 |
| Kid's Korner | 1997 | | $201 | $398 | $485 | $186 | $409 | $323 | $396 | $105 | $34 | $ |
| | 1998 | | $247 | $422 | $441 | $380 | $221 | $592 | $290 | $198 | $19 | |
| Travel | 1997 | | $624 | $505 | $564 | $386 | $300 | $978 | $416 | $48 | $38 | |
| | 1998 | | $608 | $559 | $1.096 | $611 | $464 | $316 | $573 | $257 | $198 | $ |

![Freccia slice and dice](image-placeholder)

| Filer Details: Year = 1998 | Metrics | Dollar Sales | | | | | | | | | |
|---|---|---|---|---|---|---|---|---|---|---|---|
| Category | Customer Region | North-East | Mid-Atlantic | South-East | Central | South | North-West | South-West | England | France | Germany |
| Electronics | | $1.184 | $4.529 | $1.892 | $7.232 | $651 | $9.488 | $476 | $2.683 | $462 | $70 |
| Food | | $538 | $925 | $959 | $677 | $213 | $1.503 | $261 | $165 | $175 | $100 |
| Gifts | | $1.955 | $2.785 | $2.800 | $2.695 | $1.813 | $2.844 | $1.778 | $1.158 | $717 | $686 |
| Health & Beauty | | $611 | $887 | $566 | $382 | $499 | $1.162 | $1.044 | $273 | $172 | $72 |
| Household | | $1.954 | $4.112 | $5.410 | $4.446 | $3.058 | $3.974 | $2.654 | $3.545 | $2.875 | $1.9 |
| Kid's Korner | | $5.787 | $5.320 | $5.416 | $6.812 | $4.334 | $5.008 | $7.588 | $2.139 | $3.649 | $2.7 |
| Travel | | $1.997 | $1.398 | $1.485 | $1.186 | $409 | $323 | $396 | $105 | $34 | $ |
| | | $247 | $422 | $441 | $380 | $221 | $592 | $290 | $198 | $19 | |
| | | $624 | $505 | $564 | $386 | $300 | $978 | $416 | $48 | $38 | |
| | | $608 | $559 | $1.096 | $611 | $464 | $316 | $573 | $257 | $198 | $ |

Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006

---

Slice and dice

| Subcategory | Metrics Customer City | Dollar Sales Alton | Akron | Albion | Alcamela | Alka | Allagash | Alta | Altoola | Amestta | Amsterdam | Andersonville | Annap |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Audio | | | | | | $85 | | | | | | | |
| Automotive | | | | | | | | | | $30 | | | |
| Chocolate | | $42 | $42 | | $50 | | $20 | | $22 | $44 | | | $ |
| Christmas | | $30 | | | | | $25 | $30 | $15 | | | | |
| Classic Toys | | | | | | | $7 | $26 | | | | $38 | |
| Coffee | | | | $9 | | | | | | | | | |
| Comfort | | | | | $59 | | $59 | | | | | | |
| Furniture | | | | | | | | $485 | | | | | |
| Gadgets | | | | | | | | $199 | $79 | $79 | | | |
| Games & Puzzles | | | | | | | | $17 | | $45 | | | $45 |
| Gift Baskets | | | $55 | $43 | | | | | | | | | $ |
| Golf | | $25 | | | | | | | $25 | $14 | | | $25 |
| Hearth | | | | | | | | | | $15 | | | |
| Jewelry | | $75 | | $189 | | | $24 | $77 | $189 | $24 | | | |
| Kitchen | | | | | | | $55 | $21 | | $76 | | | $ |
| Lawn & Garden | | $75 | $100 | | | $15 | $63 | $100 | | $180 | $67 | $40 | $ |
| Learning | | $16 | | | | | | $37 | | | | | |
| Meat & Cheese | | | $40 | | $20 | | | $20 | | | | $25 | |
| Miscellaneous | | | $200 | $1.320 | | $200 | $139 | | | $993 | | | |
| Natural Remedies | | $13 | | | | | | | | $13 | | | |
| Pets | | $215 | | $26 | | | $30 | $68 | $115 | $25 | | $34 | $ |
| Plants & Flowers | | $65 | $65 | $65 | | | | $50 | $60 | | | | $ |
| Safety & Security | | | | | | | | | $30 | $22 | $22 | | |
| Skin Care | | | | | | | | | | | | | |
| Sleeping | | | | $18 | | | | | | | | | |
| Toys & Accessories | | | | | | | | $29 | $185 | $744 | | | $ |

![Freccia slice and dice](image-placeholder)

Filer Details:
Category = Electronics
AND
Dollar Sales > 80
AND
Customer Region = North-West
AND
Year = 1997

| Subcategory | Metrics Customer City | Dollar Sales Alta | Armstrong | Avery Heights | Lane | Mt. Everest | San Fransisco |
|---|---|---|---|---|---|---|---|
| Audio | | | $98 | | $123 | $85 | |
| Comfort | | | | $118 | | $1.495 | |
| Gadgets | | | $199 | | | | $199 |

Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006

---

# Pivot

• Riorganizzazione dell’orientamento della struttura multidimensionale senza variare il livello di dettaglio

– permette una visualizzazione più chiara delle stesse informazioni

– la rappresentazione dei dati multidimensionali rimane sotto forma di “griglia”

• due dimensioni sono gli assi principali della griglia

• varia la posizione delle dimensioni nella griglia

---

![Rappresentazione grafica del pivot](image-placeholder)

Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006 Copyright – Tutti i diritti riservati DATA WAREHOUSE: OLAP - 22

---

## Pivot

| Category | Year | Metrics | Dollar Sales |
|---|---|---|---|
| Electronics | 1997 | | $10.616 |
| | 1998 | | $29.299 |
| Food | 1997 | | $5.300 |
| | 1998 | | $5.638 |
| Gifts | 1997 | | $16.315 |
| | 1998 | | $20.047 |
| Health & Beauty | 1997 | | $6.042 |
| | 1998 | | $6.665 |
| Household | 1997 | | $38.383 |
| | 1998 | | $50.391 |
| Kid's Korner | 1997 | | $2.559 |
| | 1998 | | $2.943 |
| Travel | 1997 | | $4.497 |
| | 1998 | | $4.792 |

![Freccia pivot](image-placeholder)

| Metrics | Dollar Sales | |
|---|---|---|
| Category | Year 1997 | 1998 |
| Electronics | $10.616 | $29.299 |
| Food | $5.300 | $5.638 |
| Gifts | $16.315 | $20.047 |
| Health & Beauty | $6.042 | $6.665 |
| Household | $50.391 | $50.391 |
| Kid's Korner | $2.559 | $2.943 |
| Travel | $4.497 | $4.492 |
| | 1998 | $4.792 |

Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006

---

 Pivot

| Category | Year | Metrics Customer Region | Dollar Sales North-East | Mid-Atlantic | South-East | Central | South | North-West | South-West | England | France | Germany |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Electronics | 1997 | | $138 | $1.774 | $384 | $138 | $2.346 | $2.554 | $2.184 | $566 | $199 | $ |
| | 1998 | | $1.184 | $4.529 | $1.892 | $7.232 | $651 | $9.488 | $476 | $2.683 | $462 | $7 |
| Food | 1997 | | $759 | $682 | $729 | $262 | $588 | $469 | $807 | $156 | $615 | $1 |
| | 1998 | | $538 | $925 | $959 | $677 | $213 | $1.503 | $261 | $165 | $175 | $1 |
| Gifts | 1997 | | $2.532 | $1.355 | $1.854 | $1.413 | $2.535 | $2.132 | $1.904 | $908 | $375 | $1.0 |
| | 1998 | | $1.955 | $2.785 | $2.800 | $2.695 | $1.813 | $2.844 | $1.778 | $1.158 | $717 | $6 |
| Health & Beauty | 1997 | | $624 | $640 | $1.317 | $647 | $588 | $754 | $654 | $143 | $292 | $3 |
| | 1998 | | $611 | $887 | $566 | $382 | $499 | $1.162 | $1.044 | $273 | $72 | $ |
| Household | 1997 | | $5.354 | $4.112 | $5.410 | $4.446 | $3.058 | $3.974 | $2.654 | $3.545 | $2.875 | $1.9 |
| | 1998 | | $5.787 | $5.320 | $5.416 | $6.812 | $4.334 | $5.008 | $7.588 | $2.139 | $3.649 | $2.7 |
| Kid's Korner | 1997 | | $201 | $398 | $485 | $186 | $409 | $323 | $396 | $105 | $34 | $ |
| | 1998 | | $247 | $422 | $441 | $380 | $221 | $592 | $290 | $198 | $19 | |
| Travel | 1997 | | $624 | $505 | $564 | $386 | $300 | $978 | $416 | $48 | $38 | |
| | 1998 | | $608 | $559 | $1.096 | $611 | $464 | $316 | $573 | $257 | $198 | $ |

![Freccia pivot](image-placeholder)

| | Metrics | Dollar Sales | | | | | | | | | |
|---|---|---|---|---|---|---|---|---|---|---|---|
| Customer Region | North-East | Mid-Atlantic | South-East | Central | South | North-West | South-West | England | France | Germa |
| Year | 1997 | 1998 | 1997 | 1998 | 1997 | 1998 | 1997 | 1998 | 1997 | 1998 |
| Category | | | | | | | | | | |
| Electronics | | | | | | | | | | |
| Food | | | | | | | | | | |
| Gifts | | | | | | | | | | |
| Health & Beauty | | | | | | | | | | |
| Household | | | | | | | | | | |
| Kid's Corner | | | | | | | | | | |
| Travel | | | | | | | | | | |

---

# Estensioni del linguaggio SQL

Elena Baralis Politecnico di Torino

---

# Estensioni del linguaggio SQL

• Gli strumenti di interfaccia richiedono

– nuove funzioni aggregate

• funzioni aggregate utilizzate per le analisi economiche (media mobile, mediana, ...)

• posizione nell’ordinamento

– funzioni per la generazione di rapporti

• definizione di totali parziali e cumulativi

• Lo standard ANSI ha accettato la proposta di nuove funzioni OLAP

– incorporate nei prodotti a partire da DB2 UDB 7.1, Oracle 8i v2

---

# Estensioni del linguaggio SQL

• Gli strumenti di interfaccia richiedono – operatori per il calcolo di più raggruppamenti (group by) diversi nello stesso momento

• Lo standard SQL-99 (SQL3) ha esteso la clausola group by di SQL

---

 Base di dati di esempio

Vendite (Città, Mese, Importo)

| Città | Mese | Importo |
|---|---|---|
| Milano | 7 | 110 |
| Milano | 8 | 10 |
| Milano | 9 | 70 |
| Milano | 10 | 90 |
| Milano | 11 | 35 |
| Milano | 12 | 135 |
| Torino | 7 | 70 |
| Torino | 8 | 35 |
| Torino | 9 | 80 |
| Torino | 10 | 95 |
| Torino | 11 | 50 |
| Torino | 12 | 120 |

---

# Funzioni OLAP in SQL

• Nuova classe di funzioni aggregate (funzioni OLAP) caratterizzate da:

– finestra di calcolo, all’interno di cui è possibile specificare il calcolo di funzioni aggregate

• possibilità di calcolare totali cumulativi e media mobile

– nuove funzioni aggregate per ricavare la posizione nell’ordinamento (ranking)

---

# Finestra di calcolo

• Nuova clausola window caratterizzata da: – partizionamento: divide le righe in gruppi, senza collassarle (diverso da group by) • assenza di partizionamento: un solo gruppo – ordinamento delle righe separatamente all’interno di ogni partizione (simile a order by) – finestra di aggregazione: definisce il gruppo di righe su cui l’aggregato è calcolato, per ciascuna riga della partizione

---

## Esempio

• Visualizzare, per ogni città e mese – l’importo delle vendite – la media rispetto al mese corrente e ai due mesi precedenti, separatamente per ogni città

---

## Esempio

• Partizionamento in base alla città – il calcolo della media è azzerato ogni volta che cambia la città

• Ordinamento in base al mese per calcolare la media mobile sul mese corrente insieme ai due mesi precedenti

– senza ordinamento, il calcolo sarebbe privo di significato

• Dimensione della finestra di calcolo: riga corrente e le due righe precedenti

---

 Esempio

SELECT Città, Mese, Importo, AVG (Importo) OVER Wavg AS MediaMobile FROM Vendite WINDOW Wavg AS (PARTITION BY Città ORDER BY Mese ROWS 2 PRECEDING)

---

 Esempio

SELECT Città, Mese, Importo, AVG (Importo) OVER (PARTITION BY Città ORDER BY Mese ROWS 2 PRECEDING)

AS MediaMobile FROM Vendite

---

## Risultato

| Città | Mese | Importo | MediaMobile |
|---|---|---|---|
| Milano | 7 | 110 | 110 |
| Milano | 8 | 10 | 60 |
| Milano | 9 | 90 | 70 |
| Milano | 10 | 80 | 60 |
| Milano | 11 | 40 | 60 |
| Milano | 12 | 140 | 90 |
| Torino | 7 | 70 | 70 |
| Torino | 8 | 30 | 50 |
| Torino | 9 | 80 | 60 |
| Torino | 10 | 100 | 70 |
| Torino | 11 | 50 | 60 |
| Torino | 12 | 150 | 100 |

Partizione 1

Partizione 2

---

## Osservazioni

• E` necessario specificare l’ordinamento, perché l’aggregazione richiesta utilizza le righe in modo ordinato

– l’ordinamento indicato non corrisponde ad un ordine predefinito delle righe in output

• Quando la finestra è incompleta, il calcolo è effettuato sulla parte presente

– è possibile specificare che, se la finestra è incompleta, il risultato deve essere NULL

• E` possibile specificare più finestre di calcolo diverse

---

# Finestra di aggregazione

• La finestra mobile su cui è effettuato il calcolo dell’aggregato può essere definita

– a livello fisico, formando il gruppo mediante conteggio delle righe

• esempio: la riga corrente e le due righe precedenti

– a livello logico, formando il gruppo in base alla definizione di un intervallo intorno alla chiave di ordinamento

• esempio: il mese corrente e i due mesi precedenti

---

 Tra un estremo inferiore e la riga corrente  Tra un estremo inferiore e uno superiore  Tra l’inizio (o la fine) della partizione e la riga corrente  Tra l’inizio (o la fine) della partizione e la rica corrente

ROWS UNBOUNDED PRECEDING (O FOLLOWING)

---

# Raggruppamento fisico

• Adatto per dati che non hanno interruzioni nella sequenza

– esempio: non manca nessun mese nella sequenza

– è possibile specificare più di una chiave di ordinamento

• il raggruppamento ignora le separazioni

• esempio: ordinamento per mese e anno

– non occorrono formule per specificare come calcolare la finestra

---

# Definizione intervallo logico

• Si utilizza il costrutto range, con la stessa sintassi dell’intervallo fisico

• E` necessario definire la distanza tra gli estremi dell’intervallo e il valore corrente sulla chiave di ordinamento

• Esempio

RANGE 2 MONTH PRECEDING

---

# Raggruppamento logico

• Adatto per dati “sparsi”, che hanno interruzioni nella sequenza

– esempio: manca un mese nella sequenza

– non è possibile specificare più di una chiave di ordinamento

– è possibile utilizzare solo tipi di dato numerici o data come chiave di ordinamento (consentono di scrivere espressioni aritmetiche)

---

# Applicazioni

• Calcolo di aggregati mobili – l’aggregato è calcolato su una finestra che “scorre” sui dati – esempi: media mobile, somma mobile

• Calcolo di totali cumulativi – il totale (cumulativo) è incrementato aggiungendo una riga alla volta

• Confronto tra dati dettagliati e dati complessivi

---

# Calcolo di totali cumulativi

• Visualizzare, per ogni città e mese – l’importo delle vendite – l’importo cumulativo delle vendite al trascorrere dei mesi, separatamente per ogni città

---

# Calcolo di totali cumulativi

• Partizionamento in base alla città – il calcolo della somma cumulativa è azzerato ogni volta che cambia la città

• Ordinamento (crescente) in base al mese per calcolare la somma al passare dei mesi – senza ordinamento, il calcolo sarebbe privo di significato • Dimensione della finestra di calcolo: dalla riga iniziale della partizione alla riga corrente

---

 SELECT Città, Mese, Importo, SUM(Importo) OVER (PARTITION BY Città ORDER BY Mese ROWS UNBOUNDED PRECEDING) AS SommaCumul FROM Vendite

---

## Calcolo di totali cumulativi: risultato

| Città | Mese | Importo | SommaCumul |
|---|---|---|---|
| Milano | 7 | 110 | 110 |
| Milano | 8 | 10 | 120 |
| Milano | 9 | 90 | 210 |
| Milano | 10 | 80 | 290 |
| Milano | 11 | 40 | 330 |
| Milano | 12 | 140 | 470 |
| Torino | 7 | 70 | 70 |
| Torino | 8 | 30 | 100 |
| Torino | 9 | 80 | 180 |
| Torino | 10 | 100 | 280 |
| Torino | 11 | 50 | 330 |
| Torino | 12 | 150 | 480 |

Partizione 1

Partizione 2

---

# Confronto tra dati dettagliati e dati complessivi

• Visualizzare, per ogni città e mese – l’importo delle vendite – l’importo totale delle vendite sul periodo completo per la città corrente

---

# Confronto tra dati dettagliati e dati complessivi

• Partizionamento in base alla città – il calcolo del totale complessivo è azzerato ogni volta che cambia la città

• Non è necessario l’ordinamento – il totale complessivo è calcolato indipendentemente dall’ordinamento

• Non è necessaria la finestra di calcolo – è l’intera partizione

---

# Confronto tra dati dettagliati e dati complessivi

SELECT Città, Mese, Importo, SUM(Importo) OVER (PARTITION BY Città) AS ImpTotale FROM Vendite

---

# Confronto tra dati dettagliati e dati complessivi

| Città | Mese | Importo | ImpTotale |
|---|---|---|---|
| Milano | 7 | 110 | 470 |
| Milano | 8 | 10 | 470 |
| Milano | 9 | 90 | 470 |
| Milano | 10 | 80 | 470 |
| Milano | 11 | 40 | 470 |
| Milano | 12 | 140 | 470 |
| Torino | 7 | 70 | 480 |
| Torino | 8 | 30 | 480 |
| Torino | 9 | 80 | 480 |
| Torino | 10 | 100 | 480 |
| Torino | 11 | 50 | 480 |
| Torino | 12 | 150 | 480 |

Partizione 1

Partizione 2

---

# Confronto tra dati dettagliati e dati complessivi

• Visualizzare, per ogni città e mese – l’importo – il rapporto tra l’importo della riga corrente per le vendite e il totale complessivo – il rapporto tra l’importo della riga corrente per le vendite e il totale complesivo per città – il rapporto tra l’importo della riga corrente per le vendite e il totale complessivo per mese

---

# Confronto tra dati dettagliati e dati complessivi

• Tre finestre di calcolo diverse – totale complessivo: nessun partizionamento – totale per città: partizionamento per città – totale per mese: partizionamento per mese • Non è necessario l’ordinamento per nessuna finestra – il totale complessivo è calcolato indipendentemente dall’ordinamento • La finestra di calcolo è sempre l’intera partizione

---

 Confronto tra dati dettagliati e dati complessivi

SELECT Citt