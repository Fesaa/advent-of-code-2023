package main

import (
	"bufio"
	"errors"
	"fmt"
	"os"
)

func main() {

	file, err := os.Open("input.txt")
	if err != nil {
		panic(err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	sum := 0

	for scanner.Scan() {
		first, last, err := findNumbers(scanner.Text())
		if err != nil {
			panic(err)
		}
		sum += first*10 + last
	}

	if err := scanner.Err(); err != nil {
		panic(err)
	}

	fmt.Println(sum)

}

var conv map[rune]int = map[rune]int{
	'0': 0,
	'1': 1,
	'2': 2,
	'3': 3,
	'4': 4,
	'5': 5,
	'6': 6,
	'7': 7,
	'8': 8,
	'9': 9,
}

func findNumbers(s string) (int, int, error) {
	var firstNumber, secondNumber *int = nil, nil

	for _, char := range s {
		if _, ok := conv[char]; !ok {
			continue
		}
		number := conv[char]
		if firstNumber == nil {
			firstNumber = &number
		} else {
			secondNumber = &number
		}
	}

	if firstNumber == nil {
		return 0, 0, errors.New("No numbers found")
	}

	if secondNumber == nil {
		secondNumber = firstNumber
	}

	return *firstNumber, *secondNumber, nil
}
