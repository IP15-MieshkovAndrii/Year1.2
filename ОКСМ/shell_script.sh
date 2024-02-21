#!/bin/sh

$ cat 01-tiny-access.log | head -n 5 |  cut -d " " -f 1 | > list.txt

$ cat list.txt
