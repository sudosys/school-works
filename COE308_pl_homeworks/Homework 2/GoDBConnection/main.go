package main

import (
	"database/sql"
	"fmt"
	"strconv"
	"time"

	_ "github.com/go-sql-driver/mysql"
)

func DbRead(recordSize int, columns string) {

	db, _ := sql.Open("mysql", "root:root@tcp(localhost:3306)/desdb")

	rows, _ := db.Query("SELECT " + columns + " FROM statistic LIMIT " + strconv.Itoa(recordSize) + ";")

	column, _ := rows.Columns()

	values := make([]sql.RawBytes, len(column))

	scanArgs := make([]interface{}, len(values))

	for i := range values {
		scanArgs[i] = &values[i]
	}

	for rows.Next() {
		rows.Scan(scanArgs...)
	}

	defer rows.Close()

}

func DbWrite(recordSize int, columns string, values string) {

	db, _ := sql.Open("mysql", "root:root@tcp(localhost:3306)/desdb")

	for range strconv.Itoa(recordSize) {
		insert, _ := db.Query("INSERT INTO statistic (" + columns + ") VALUES (" + values + ");")
		defer insert.Close()
	}

	defer db.Close()

}

func readWriteTest() {

	recordSizeArgs := []int{3, 100, 1000, 100000, 800000}

	columnArgs := []string{"StatisticID", "StatisticID, ClientID, FlightID", "StatisticID, ClientID, FlightID, ModuleName, CategoryName",
		"StatisticID, ClientID, FlightID, ModuleName, CategoryName, SubCategoryName, CategoryType",
		"StatisticID, ClientID, FlightID, ModuleName, CategoryName, SubCategoryName, CategoryType, MediaName, AudioName, EpisodeName"}

	values := []string{"StatisticID", "StatisticID, ClientID, FlightID", "StatisticID, ClientID, FlightID, ModuleName, CategoryName",
		"StatisticID, ClientID, FlightID, ModuleName, CategoryName, SubCategoryName, CategoryType",
		"StatisticID, ClientID, FlightID, ModuleName, CategoryName, SubCategoryName, CategoryType, MediaName, AudioName, EpisodeName"}

	for i := 0; i < len(recordSizeArgs); i++ {

		dt_read_start := time.Now()

		DbRead(recordSizeArgs[i], columnArgs[i])

		elapsedTime_read := time.Since(dt_read_start)

		fmt.Println("Read", i, ". process time is ", elapsedTime_read)

	}

	for i := 0; i < len(values); i++ {

		dt_write_start := time.Now()

		DbWrite(recordSizeArgs[i], columnArgs[i], values[i])

		elapsedTime_write := time.Since(dt_write_start)

		fmt.Println("Write ", i, ". process time is", elapsedTime_write)
	}

}

func main() {

	fmt.Println("Go Connects to MySQL")

	db, _ := sql.Open("mysql", "root:root@tcp(localhost:3306)/desdb")

	defer db.Close()

	readWriteTest()

}
