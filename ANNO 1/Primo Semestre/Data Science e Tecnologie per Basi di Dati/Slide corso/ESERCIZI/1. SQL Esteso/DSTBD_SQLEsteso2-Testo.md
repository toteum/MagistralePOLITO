---
marp: true
theme: default
paginate: true
---

# Esercizi SQL esteso

## Testo

---

# Schema delle tabelle

Sono date le seguenti tabelle:

- **Cliente**(CodCliente, Cliente, Provincia, Regione)
- **Categoria**(CodCat, Categoria)
- **Agente**(CodAgente, Agente, Agenzia)
- **Tempo**(CodTempo, Mese, Trimestre, Semestre, Anno)
- **Fatturato**(CodTempo, CodCliente, CodCatArticolo, CodAgente, TotFatturato, NumArticoli, TotSconto)

Risolvere le seguenti interrogazioni in SQL.

---

# Esercizio 1

Visualizzare per ogni categoria di articoli:

- la categoria
- la quantità totale fatturata per la categoria in esame
- il fatturato totale associato alla categoria in esame
- il rank della categoria in funzione della quantità totale fatturata
- il rank della categoria in funzione del fatturato totale

---

# Esercizio 2

Visualizzare per ogni provincia:

- la provincia
- la regione della provincia
- il fatturato totale associato alla provincia
- il rank della provincia in funzione del fatturato totale, separato per regione

---

# Esercizio 3

Visualizzare per ogni provincia e mese:

- la provincia
- la regione della provincia
- il mese
- il fatturato totale associato alla provincia nel mese in esame
- il rank della provincia in funzione del fatturato totale, separato per mese

---

# Esercizio 4

Visualizzare per ogni regione e mese:

- la regione
- il mese
- il fatturato totale associato alla regione nel mese in esame
- l'incasso cumulativo al trascorrere dei mesi, separato per ogni regione
- l'incasso cumulativo al trascorrere dei mesi, separato per ogni anno e regione
