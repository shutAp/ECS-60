p "" SIGABRT
path=~ssdavis/60/p1

for program in "bags.cpp" "balance.cpp"; do 
  if [ -e $program ] ; then
    rm -rf temp.out error.txt warnings.txt &> /dev/null
    g++ -Wall $program -o temp.out 2>> error.txt 1>> warnings.txt
    if [ -e temp.out ] ; then
      if [ -s "warnings.txt" ] ; then
        echo -n ">> "$program" has warnings when compiled with -Wall, fix them or lose points!" 
      fi
      for file in $path/${program%%.*}*.txt ; do
        rm -rf output.txt sean.txt diff.txt error.txt warnings.txt &> /dev/null
        if [ $program == "bags.cpp" ] ; then
          random=$RANDOM
          let "random %= 10"
          let "random += 1"
        else
          random=""
        fi
        chmod u+x temp.out 
        ./temp.out $file $random 2>> error.txt 1>> output.txt
        $path/${program%%.*}.out $file $random 1>> sean.txt
        if [ $? -ne 0 ] ; then
          if [ -s error.txt ] ; then
            echo '>> Oh no! '$program' seg faulted on file '${file##*/}'! Use gdb to find out where.'
          fi
        fi
        if [ ! -e output.txt ] ; then
          echo ${file##*/} "failed"
        else
          diff -b output.txt sean.txt > diff.txt
          if [ -s diff.txt ] ; then
            echo ${file##*/} "failed"
          else
            echo ${file##*/} "passed!"
          fi
        fi
      done
    else
      echo $program "could not compile (there's g++ errors)!"
    fi
  else
    echo $program "does not exist!"
  fi
done
