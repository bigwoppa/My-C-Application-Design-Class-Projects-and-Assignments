# College Major Outcomes

This C++ program displays 10 college majors with their median annual earnings and unemployment rates. It uses three arrays to store the data and a pointer to access the first income value.

## Data

The records were selected from the [College Majors dataset on Kaggle](https://www.kaggle.com/datasets/tunguz/college-majors/data). The data comes from the 2010–2012 American Community Survey.

`data.csv` has **no header**. Each row contains:

```text
Major,MedianAnnual,UnemploymentRate
```

The unemployment rate is already a percentage, such as `6.3`.

## Run

Keep `data.csv` in the folder where you run the program. Replace `main.cpp` with your C++ filename:

```powershell
g++ main.cpp -o majors
.\majors.exe
```