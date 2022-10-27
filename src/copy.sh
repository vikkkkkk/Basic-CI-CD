#!/bin/bash

scp cat/s21_cat grep/s21_grep tor@10.0.2.4:/home/tor
ssh tor@10.0.2.4 mv s21_cat s21_grep /usr/local/bin
