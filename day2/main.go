package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
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
	game := 1

	for scanner.Scan() {
		r, g, b := getRGB(scanner.Text())
		if canPlay(r, g, b) {
			sum += game
		}
		game++

	}

	if err := scanner.Err(); err != nil {
		panic(err)
	}

	fmt.Println(sum)
}

var maxR, maxG, maxB int = 12, 13, 14

func canPlay(r, g, b int) bool {
	return r <= maxR && g <= maxG && b <= maxB
}

func getRGB(line string) (int, int, int) {
	var r, g, b int = 0, 0, 0
	setLine := strings.Split(line, ":")
	sets := strings.Split(setLine[1], ";")
	for _, set := range sets {
		rgb := strings.Split(set, ",")
		for _, color := range rgb {
			color = strings.TrimSpace(color)
			subs := strings.Split(color, " ")
			amount, err := strconv.Atoi(subs[0])
			if err != nil {
				panic(err)
			}
			switch subs[1][0:1] {
			case "r":
				setIfHigher(amount, &r)
			case "g":
				setIfHigher(amount, &g)
			case "b":
				setIfHigher(amount, &b)
			}
		}
	}

	return r, g, b
}

func setIfHigher(v int, val *int) {
	if v > *val {
		*val = v
	}
}
