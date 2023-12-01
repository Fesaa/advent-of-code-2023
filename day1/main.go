package main

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"strings"
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
		first, last, err := findNumbersPart2(scanner.Text())
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

var numbers map[string]int = map[string]int{"one": 1, "two": 2, "three": 3, "four": 4, "five": 5, "six": 6, "seven": 7, "eight": 8, "nine": 9}

func mightBeNumber(s string) (bool, bool) {
	for number := range numbers {
		if strings.HasPrefix(number, s) {
			return true, s == number
		}
	}
	return false, false
}

type Reader struct {
	str      string
	runes    []rune
	pos      int
	startPos int

	cur rune
}

func NewReader(str string) *Reader {
	runes := []rune(str)
	return &Reader{
		str:      str,
		runes:    runes,
		pos:      0,
		startPos: 0,
		cur:      runes[0],
	}
}

func (r *Reader) Next() {
	r.pos++
	if r.pos < len(r.runes) {
		r.cur = r.runes[r.pos]
	}
}

func (r *Reader) Reset() {
	r.startPos = r.startPos + 1
	r.pos = r.startPos
	if r.pos < len(r.runes) {
		r.cur = r.runes[r.pos]
	}
}

func (r *Reader) CanRead() bool {
	return r.pos < len(r.runes)
}

func (r *Reader) ReadTillNumber() *int {
	for r.CanRead() {

		if number, ok := conv[r.cur]; ok {
			r.Reset()
			return &number
		}

		sub := r.str[r.startPos : r.pos+1]
		maybe, isNumber := mightBeNumber(sub)

		if !maybe {
			r.startPos++
		}

		if isNumber {
			number := numbers[sub]
			r.Reset()
			return &number
		}

		r.Next()
	}
	return nil
}

func findNumbersPart2(line string) (int, int, error) {
	reader := NewReader(line)
	firstNumber := reader.ReadTillNumber()
	var secondNumber *int = nil
	next := reader.ReadTillNumber()

	for next != nil {
		secondNumber = next
		next = reader.ReadTillNumber()
	}

	if firstNumber == nil {
		return 0, 0, errors.New("No numbers found")
	}

	if secondNumber == nil {
		secondNumber = firstNumber
	}

	return *firstNumber, *secondNumber, nil
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
