---
marp: true
theme: default
paginate: true
size: 4:3
style: |
  section { font-size: 28px; }
  h1 { color: #1f4e79; }
---

# Exercise #9

- Word count problem
  - Input: (unstructured) textual file
  - Output: number of occurrences of each word appearing in the input file
- Solve the problem by using in-mapper combiners

---

# Exercise #9 - Example

- Input file

```
Toy example
file for Hadoop.
Hadoop running
example.
```

- Output pairs

```
(toy, 1)
(example, 2)
(file, 1)
(for, 1)
(hadoop, 2)
(running, 1)
```

---

# Exercise #12

- Select outliers
  - Input: a collection of (structured) textual files containing the daily value of PM10 for a set of sensors
    - Each line of the files has the following format

      `sensorId,date\tPM10 value (μg/m³)\n`
  - Output: the records with a PM10 value below a user provided threshold (the threshold is an argument of the program)

---

# Exercise #12 - Example

- Input file

```
s1,2016-01-01   20.5
s2,2016-01-01   60.2
s1,2016-01-02   30.1
s2,2016-01-02   20.4
s1,2016-01-03   55.5
s2,2016-01-03   52.5
```

- Threshold: 21
- Output

```
s1,2016-01-01   20.5
s2,2016-01-02   20.4
```
