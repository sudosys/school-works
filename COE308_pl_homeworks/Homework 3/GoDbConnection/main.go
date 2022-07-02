package main

import (
	"database/sql"
	"fmt"
	"strconv"
	"time"

	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/app"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/widget"
	_ "github.com/go-sql-driver/mysql"
)

func DbRead(recordSize string, NumOfColumns string) {
	start := time.Now()
	db, err := sql.Open("mysql", "root:root@tcp(localhost:3306)/desdb")

	columnArgs := []string{"StatisticID", "ClientID", "FlightID", "ModuleName", "CategoryName", "SubCategoryName", "CategoryType",
		"MediaName", "AudioName", "EpisodeName", "FileName", "Studio", "StarArtist", "SubtitleLang", "AudioLang", "Duration", "LogDate", "ifetype"}

	columns := ""
	integer_col, _ := strconv.Atoi(NumOfColumns)
	for i := 0; i < integer_col; i++ {
		columns += columnArgs[i] + ", "
	}

	columns = columns[:len(columns)-2] + " "
	rows, _ := db.Query("SELECT " + columns + " FROM statistic LIMIT " + recordSize + ";")

	column, err := rows.Columns()
	checkErr(err)
	values := make([]sql.RawBytes, len(column))

	scanArgs := make([]interface{}, len(values))
	for i := range values {
		scanArgs[i] = &values[i]
	}
	for rows.Next() { //read db
		rows.Scan(scanArgs...)
	}
	err = rows.Err()
	defer rows.Close()
	fmt.Println("SELECT " + columns + " FROM statistic LIMIT " + recordSize + ";")
	fmt.Println(recordSize)
	elapsed_time := time.Since(start)
	change_time := elapsed_time.Milliseconds()
	fmt.Println(change_time)
	time_r := widget.NewLabel(fmt.Sprintf("Total Time Taken: %d ms", change_time))
	time_r.Refresh()

	time_r.Move(fyne.NewPos(30, 160))
	checkErr(err)
}

func checkErr(err error) {
	if err != nil {
		panic(err)
	}
}
func DbWrite(recordSize string, numberofcolumns string, values string) {
	start_w := time.Now()
	db, err := sql.Open("mysql", "root:root@tcp(localhost:3306)/desdb")

	columnArgs_w := []string{"StatisticID", "ClientID", "FlightID", "ModuleName", "CategoryName", "SubCategoryName", "CategoryType",
		"MediaName", "AudioName", "EpisodeName", "FileName", "Studio", "StarArtist", "SubtitleLang", "AudioLang", "Duration", "LogDate", "ifetype"}

	valueArgs := []string{"StatisticID", "ClientID", "FlightID", "ModuleName", "CategoryName", "SubCategoryName", "CategoryType",
		"MediaName", "AudioName", "EpisodeName", "FileName", "Studio", "StarArtist", "SubtitleLang", "AudioLang", "Duration", "LogDate", "ifetype"}
	columns_w := ""
	integer_col, _ := strconv.Atoi(numberofcolumns)
	for i := 0; i < integer_col; i++ {
		columns_w += columnArgs_w[i] + ", "
	}
	columns_w = columns_w[:len(columns_w)-2] + " "

	value_w := ""
	integer_val, _ := strconv.Atoi(values)
	for i := 0; i < integer_val; i++ {
		value_w += valueArgs[i] + ", "
	}
	value_w = value_w[:len(value_w)-2] + " "

	for range recordSize {
		insert, _ := db.Query("INSERT INTO statistic (" + columns_w + ") VALUES (" + value_w + ");")
		defer insert.Close()
	}

	elapsed_time := time.Since(start_w)
	change_time := elapsed_time.Milliseconds()
	fmt.Println(change_time)
	time_r := widget.NewLabel(fmt.Sprintf("Total Time Taken: %d ms", change_time))
	time_r.Refresh()

	time_r.Move(fyne.NewPos(30, 160))
	defer db.Close()
	checkErr(err)
}

func layout() {

	a := app.New()

	w := a.NewWindow("Database Connection") // app's title  create window

	w.Resize(fyne.NewSize(450, 320)) // resize fyne app (width,height)

	labelX := widget.NewLabel("Number of Record") // add label
	labelX.Move(fyne.NewPos(30, 50))
	entry := widget.NewEntry()
	entry.Resize(fyne.NewSize(200, 30))
	entry.Move(fyne.NewPos(200, 50))

	labelY := widget.NewLabel("Number of Columns") // add label
	labelY.Move(fyne.NewPos(30, 100))
	column := ""
	entry_column := widget.NewSelect(
		[]string{"1", "3", "7", "11", "18"},
		func(s string) {
			column = s
		},
	)

	entry_column.Resize(fyne.NewSize(200, 30))
	entry_column.Move(fyne.NewPos(200, 100))

	progress_bar := widget.NewProgressBar()
	progress_bar.Move(fyne.NewPos(200, 200))

	time_r := widget.NewLabel("Total Time Taken: - ms")
	time_r.Refresh()
	time_r.Move(fyne.NewPos(30, 160))

	btn := widget.NewButton("Start Read", func() {
		start := time.Now()
		DbRead(entry.Text, column)
		elapsed_time := time.Since(start)
		change_time := elapsed_time.Milliseconds()
		fmt.Println(change_time)

		go func() {
			for i := 0.0; i <= 1.0; i += 0.1 {
				time.Sleep(time.Millisecond * 250)
				progress_bar.SetValue(i)
			}
		}()
		time_r.SetText(fmt.Sprintf("Total Time Taken: %d ms", change_time))

	})

	btn.Resize(fyne.NewSize(100, 30))
	btn.Move(fyne.NewPos(250, 150))

	btn_write := widget.NewButton("Start Write", func() {
		start_w := time.Now()
		DbWrite(entry.Text, column, column)
		elapsed_time_w := time.Since(start_w)
		change_time := elapsed_time_w.Milliseconds()

		go func() {
			for i := 0.0; i <= 1.0; i += 0.1 {
				time.Sleep(time.Millisecond * 250)
				progress_bar.SetValue(i)
			}
		}()
		time_r.SetText(fmt.Sprintf("Total Time Taken: %d ms", change_time))
	})

	btn_write.Resize(fyne.NewSize(100, 30))
	btn_write.Move(fyne.NewPos(250, 190))

	w.SetContent(
		container.NewWithoutLayout(
			labelX,
			entry,
			labelY,
			entry_column,
			//column_btn,
			btn,
			container.NewVBox(progress_bar),
			btn_write,
			time_r,
		),
	)

	w.CenterOnScreen()
	w.ShowAndRun() // finaly running app
}

func main() {

	fmt.Println("Go Connect to mysql")

	db, err := sql.Open("mysql", "root:root@tcp(localhost:3306)/desdb")
	defer db.Close()
	if err != nil {
		fmt.Println("error validating sql.Open arguments")
	}

	layout()
	checkErr(err)
	db.Close()

}
