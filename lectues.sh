#!/bin/sh

for i in {1..23}
do
    wget "https://www.cse.iitb.ac.in/~mythili/teaching/cs224m_autumn2017/notes/lec`printf "%02d" $i`.txt" -P ./Lectures
done
