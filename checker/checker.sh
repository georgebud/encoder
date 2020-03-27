#!/bin/bash
#
# Codificator de șiruri (checker)
#
# Programarea calculatoarelor (2015-2016)
# Tema 1
#
# 28.11.2016
# Deadline: 19.12.2015, 23:55
#

#
# Base directory.
#
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

#
# Cheap hack used to fix double whitespaces not printing.
#
IFS='%'

#
# Array containing the name of every test.
#
TESTS=(
    "> -----------------------------------------------------------------------"
    "> INFO: 25p - Task 1 - Citire"
    "> -----------------------------------------------------------------------"
    test_00,5,0,0               # testul din enunt
    test_01,5,0,0
    test_02,5,0,0
    test_03,5,0,0
    test_04,5,0,0

    "> -----------------------------------------------------------------------"
    "> INFO: 40p - Task 2 - Codificare"
    "> -----------------------------------------------------------------------"
    "> INFO: 25p - Task 2 - a) Codificarea corectă a cuvintelor."
    "> -----------------------------------------------------------------------"
    word_len2,0,5,0             # verifica procesarea cuvintelor scurte
    word_len8,0,5,0             # verifica procesarea cuvintelor lungi
    word_00,0,5,0
    word_01,0,5,0
    word_02,0,5,0

    "> -----------------------------------------------------------------------"
    "> INFO:  5p - Task 2 - b) Codificarea corectă a caracterelor."
    "> -----------------------------------------------------------------------"

    char_simple,0,1,0           # inserarea unui caracter intr-un sir simplu
    char_multi,0,1,0            # inserarea unui caracter intr-un sir care contine
                                # caractere un numar egal de aparitii
    char_00,0,1,0
    char_01,0,1,0
    char_02,0,1,0

    "> -----------------------------------------------------------------------"
    "> INFO: 10p - Task 2 - c) Codificarea corectă a numerelor."
    "> -----------------------------------------------------------------------"
    number_neg,0,2,0            # verifica procesarea numerelor negative
    number_poz,0,2,0            # verifica procesarea numerelor pozitive
    number_00,0,2,0
    number_01,0,2,0
    number_02,0,2,0

    "> -----------------------------------------------------------------------"
    "> INFO: 25p - Task 3 - Rearanjare"
    "> -----------------------------------------------------------------------"
    combined_simple,0,0,5       # verifica procesarea tuturor tipurilor de termeni
    combined_shuffle,0,0,5      # sortarea unui sir format din termeni de toate tipurile
    word_shuffle,0,0,5          # sortarea unui sir format doar din cuvinte
    char_shuffle,0,0,5          # sortarea unui sir format doar din caractere
    number_shuffle,0,0,5        # sortarea unui sir format doar din numere

    "> -----------------------------------------------------------------------"
    "> INFO:  7p - Altele"
    "> -----------------------------------------------------------------------"
)

#
# Array containing the name of every required rule.
#
RULES=(build run clean)

#
# Points assigned for each task.
#
MAXIMUM_SCORE=97
POINTS_MAKEFILE=4
POINTS_README=3

#
# Checking if `Makefile` exists.
#
if [[ ! -f Makefile ]]; then
    echo "ERROR: \`Makefile\` does not exist!"
    exit 1
fi

#
# Checking if all required rules are defined.
#
for rule in "${RULES[@]}"; do
    if ! grep -q -E "^$rule:" Makefile; then
        echo "ERROR: Rule \`$rule\` does not exist in \`Makefile\`."
        exit 2
    fi
done

#
# Checking if -Wall is used in compiling.
#
if ! grep -q -i -- "-Wall" Makefile; then
    echo "WARN: -Wall is not used as a parameter for gcc."
fi

#
# Making sure the latest version of source is built.
# We clean the old binaries.
#
if ! make clean &>/dev/null; then
    echo "ERROR: Cleaning failed!"
    exit 3
fi

#
# Rebuilding the source.
#
echo "INFO: Building...."
if ! make &>/dev/null; then
    echo "ERROR: Building failed!"
    exit 4
fi

#
# Checking if `encoder` exists.
#
if [[ ! -f encoder ]]; then
    echo "ERROR: \`encoder\` does not exist!"
    exit 5
fi

#
# Running the tests.
#
echo "INFO: Running tests..."
total=0
for test in "${TESTS[@]}"; do

    if [[ ${test:0:1} == ">" ]]; then
        echo ${test:2}
        continue
    fi

    # The test is in CSV format: name,points_1,points_2,points_3.
    test_name=$(echo $test | cut -d',' -f1)
    # Points for task 1.
    test_points[1]=$(echo $test | cut -d',' -f2)
    # Points for task 2.
    test_points[2]=$(echo $test | cut -d',' -f3)
    # Points for task 3.
    test_points[3]=$(echo $test | cut -d',' -f4)
    # Total points.
    test_points=$((${test_points[1]} + ${test_points[2]} + ${test_points[3]}))

    # Overwrites the expected output of a test.
    # Used to generate test.
    # ./encoder < "$DIR/tests/$test_name.txt" > "$DIR/tests/$test_name.out"

    # Running the solution.
    # Timeout is used to make sure the process ends.
    if which timeout &>/dev/null; then
        timeout 3 ./encoder < "$DIR/tests/$test_name.txt" &> "$test_name.out"
    else
        ./encoder < "$DIR/tests/$test_name.txt" &> "$test_name.out"
    fi

    # Checking line-by-line.
    points=0

    for i in {1..3}; do
        exp=$(sed "${i}q;d" "$DIR/tests/$test_name.out")
        real=$(sed "${i}q;d" "$test_name.out")
        if [[ "$exp" == "$real" ]]; then
            points=$(($points + ${test_points[$i]}))
        fi
    done

    total=$(($total + $points))
    printf "INFO: %-32s ... %2d / %2d\n" "Test $test_name" $points $test_points

    # Checking the entire-file.
    # if cmp $DIR/tests/$test_name.out $test_name.out &>/dev/null; then
    #     printf "INFO: %-32s ... %2d / %2d\n" "Test $test_name" $test_points $test_points
    #     total=$(($total + $test_points))
    # else
    #     printf "WARN: %-32s ... %2d\n" "Test $test_name" 0
    # fi

    # Cleaning up...
    rm -f $test_name.out
done

#
# Adding points for `Makefile`.
#
total=$(($total+$POINTS_MAKEFILE))
printf "INFO: %-32s ... %2d / %2d\n" "Makefile" $POINTS_MAKEFILE $POINTS_MAKEFILE

#
# Adding points for read me files (if any).
#
readme_file=$(ls | grep -i -E "read[_]?me" | head -n 1)
if [[ -n $readme_file ]]; then
    if [[ -s $readme_file ]]; then
        printf "INFO: %-32s ... %2d / %2d\n" "Read me ($readme_file)" $POINTS_README $POINTS_README
        total=$(($total+$POINTS_README))
    else
        printf "WARN: %-32s ... %2d / %2d\n" "Read me ($readme_file is empty)" 0 $POINTS_README
    fi
else
    printf "WARN: %-32s ... %2d / %2d\n" "Read me not found" 0 $POINTS_README
fi

#
# Running Cppcheck.
#
if which cppcheck &>/dev/null; then
    if [[ $(cppcheck encoder.c 2>&1 | wc -l) -le 1 ]]; then
        printf "INFO: %-32s ... Excellent!\n" "Cppcheck"
    else
        printf "WARN: %-32s ... Errors were found.\n" "Cppcheck"
    fi
fi

#
# Running Valgrind.
#
if which valgrind &>/dev/null; then
    if valgrind --tool=memcheck --leak-check=full ./encoder < $DIR/tests/combined_shuffle.txt 2>&1 | grep -i -E "All heap blocks were freed|definitely lost: 0 bytes" &>/dev/null; then
        printf "INFO: %-32s ... Excellent!\n" "Valgrind"
    else
        printf "WARN: %-32s ... Not all memory was freed.\n" "Valgrind"
    fi
fi

#
# Printing final score.
#
echo "-----------------------------------------------------------------------"
printf "INFO: %-32s ... %2d / %2d\n" "TOTAL" $total $MAXIMUM_SCORE
echo
echo "INFO: Punctajul pentru coding style (3p) va fi acordat dupa verificarea"
echo "      temei de catre unul din responsabilii pentru tema."

#
# Exiting...
#
make clean &>/dev/null
exit $total
