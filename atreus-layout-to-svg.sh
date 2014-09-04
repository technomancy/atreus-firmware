#!/usr/bin/env bash

usage="Converts a json atreus layout into a html document with svg enclosed.

Usage: atreus-layout-to-svg.sh mylayout.json

Output: Creates file: mylayout-svg.html"

argc=$#
if [ $argc -ne 1 ]; then
  echo "$usage"
  exit
fi 

layoutfile=$1
layercount=$(./remccoms3.sed $layoutfile | jq length )
htmlfile="$layoutfile.html"
cat "" > "$htmlfile"

echo "layercount = $layercount"
for i in $(seq 0 $((layercount - 1)))
do
  echo "layer $i"
  #Join the 4 rows together into 1 array
  layer=$(./remccoms3.sed $layoutfile | jq .[$i] | jq '.[0] + .[1] + .[2] + .[3]')

  #Create this layer's svg file
  layerfile="$layoutfile.layer$i.svg"
  cp atreus-layout.svg "$layerfile"

  sed -i "" "s/>Layer 0</>Layer $i</" "$layerfile"
  for j in {0..41}
  do
    key=$(echo "$layer" | jq -c -r .["$j"])
    echo "key $j = $key"
    sed -i "" "s/>$j</>$key</" "$layerfile"
  done
  cat "$layerfile" >> "$htmlfile"
  rm "$layerfile"
done
