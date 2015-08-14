#!/usr/bin/env bash

debug=0
debug=1  #uncomment this line for debugging output

usage="Converts a json atreus layout into a html document with svg enclosed.

Usage: atreus-layout-to-svg.sh mylayout.json

Output: Creates file: mylayout-svg.html"

platform='unknown'
unamestr=`uname`
if [[ "$unamestr" == 'Linux' ]]; then
   platform='Linux'
elif [[ "$unamestr" == 'Darwin' ]]; then
   platform='Darwin'
fi

argc=$#
if [ $argc -ne 1 ]; then
  echo "$usage"
  exit
fi

function rendercharacters {
  # These replacements must come in a certain order or they clobber each other.
  echo $1 | sed \
  -e 's/"//g' \
  -e 's/\[//g' \
  -e 's/\]//g' \
  -e 's/,//g' \
  -e 's/shift1/!/' \
  -e 's/shift2/@/' \
  -e 's/shift3/#/' \
  -e 's/shift4/\$/' \
  -e 's/shift5/%/' \
  -e 's/shift6/\^/' \
  -e 's/shift7/\\\&/' \
  -e 's/shift8/*/' \
  -e 's/shift9/(/' \
  -e 's/shift0/)/' \
  -e 's/shiftTILDE/~/' \
  -e 's/shiftMINUS/_/' \
  -e 's/shiftEQUAL/+/' \
  -e 's/shiftBACKSLASH/|/' \
  -e 's/shiftLEFT_BRACE/{/' \
  -e 's/shiftRIGHT_BRACE/}/' \
  -e 's/PAGE_DOWN/PgDn/' \
  -e 's/PAGE_UP/PgUp/' \
  -e 's/BACKSPACE/← BS/' \
  -e 's/COMMA/,/' \
  -e 's/DELETE/Del/' \
  -e 's/DOWN/↓/' \
  -e 's/ENTER/⏎/' \
  -e 's/EQUAL/=/' \
  -e 's/FN/fn/' \
  -e 's/INSERT/Ins/' \
  -e 's/LEFT_BRACE/[/' \
  -e 's/LEFT/←/' \
  -e 's/MINUS/-/' \
  -e 's/PERIOD/./' \
  -e "s/QUOTE/'/" \
  -e 's/RIGHT_BRACE/]/' \
  -e 's/RIGHT/→/' \
  -e 's/SEMICOLON/;/' \
  -e 's/TILDE/`/' \
  -e 's/UP/↑/' \
  -e 's/function/Layer/' \
  -e 's/BACKSLASH/\\/' \
  -e 's/SLASH/\\\//'
}

function debuglog {
  if [ $debug -eq 1 ]; then
    echo "$1"
  fi
}

layoutfile=$1
#layercount=$(./remccoms3.sed $layoutfile | jq length )
layercount=$(sed -nf remccoms3.sed $layoutfile | jq length )
htmlfile="$layoutfile.html"
if [ -e "$htmlfile" ]; then
  rm "$htmlfile"
fi

#echo "layercount = $layercount"
debuglog "layercount = $layercount"
for i in $(seq 0 $((layercount - 1)))
do
  debuglog "layer $i"
  #Join the 4 rows together into 1 array
  #layer=$(./remccoms3.sed $layoutfile | jq .[$i] | jq '.[0] + .[1] + .[2] + .[3]')
  layer=$(sed -nf remccoms3.sed $layoutfile | jq .[$i] | jq '.[0] + .[1] + .[2] + .[3]')

  #Create this layer's svg file
  layerfile="$layoutfile.layer$i.svg"
  cp atreus-layout.svg "$layerfile"

  sed -i "" -e "s/>Layer 0</>Layer $i</" "$layerfile"
  for j in {0..41}
  do
    key=$(echo "$layer" | jq -c -r .["$j"])
    key=$(rendercharacters "$key")
    debuglog "key $j = $key"
    #This OS check is dirty but works for now.  My bash-fu is weak
    if [[ "$platform" == 'Linux' ]]; then
      #cat "$layerfile" | sed -e "s/>$((j + 1))</>$key</" > "$layerfile"
      sed -i -e "s/>$((j + 1))</>$key</" "$layerfile"
    elif [[ "$platform" == 'Darwin' ]]; then
      sed -i "" -e "s/>x$((j + 1))x</>$key</" "$layerfile"
    fi
  done
  cat "$layerfile" >> "$htmlfile"
  rm "$layerfile"
done
