
On Terminal/CMD use:
curl "https://raw.githubusercontent.com/Kundan1804/LP5/rawmain/HPC/prat1.txt"


On Jupyter use:
!curl "https://raw.githubusercontent.com/Kundan1804/LP5/rawmain/HPC/prat1.txt"

For HPC Assignments 1-3
Run the program as (gcc or g++):
>> g++ filename.cpp -o filename.exe -fopenmp
>> ./filename.exe

For HPC Assignment 4
Runtime > Change Runtime Type > Select GPU from drop-down

For DL Assignments (datasets)
import requests
print(requests.get('http://github.com/Kundan1804/LP5/raw/main/DL/pract1.txt').text)
