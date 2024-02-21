#!/bin/bash
input="$1"

allProgramsWithRefers=$(cat $input | awk -F\" '$4 != "-" && $4 != "" {print $6}')

count=$(echo "$allProgramsWithRefers" | wc -l)

echo "$allProgramsWithRefers" |
  awk -F[/\(] '{print $1}'|
  grep  -v "-" |
  sort |
  uniq -c |
  sort -rn |
  awk  -F' ' -v apwrc="$count" '{n=$1; $1=""; printf "%s - %s - %.3f%%\n", $0, n, n/apwrc*100}' |
  head -n 10 |
  nl -s '.'
