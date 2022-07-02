import mysql.connector, sys, time
from PySide6 import QtWidgets
from PySide6.QtUiTools import QUiLoader

"""
Columns in the statistic table:
StatisticID, ClientID, FlightID, ModuleName, CategoryName, SubCategoryName, CategoryType,
MediaName, AudioName, EpisodeName, FileName, Studio, StarArtist, SubtitleLang, AudioLang, Duration, LogDate, ifetype
"""

class DbConnectionGUI:

    db = mysql.connector.connect(host="localhost", user="root", password="1234", database="desdb")

    def __init__(self):

        loader = QUiLoader()
        app = QtWidgets.QApplication(sys.argv)
        self.mainWindow = loader.load("mainWindow.ui", None)

        self.mainWindow.start_button.clicked.connect(lambda: self.start(self.mainWindow.number_of_records_box.text(), self.mainWindow.column_selection_box.currentText(), self.mainWindow.read_radio.isChecked()))

        self.mainWindow.show()
        app.exec()

    columns = ["StatisticID", "ClientID", "FlightID", "ModuleName", "CategoryName", "SubCategoryName", "CategoryType",
    "MediaName", "AudioName", "EpisodeName", "FileName", "Studio", "StarArtist", "SubtitleLang", "AudioLang", "Duration", "LogDate", "ifetype"]

    def readFromDb(self, numberOfRecords, numberOfColumns):

        selectedColumns = ""

        for i in range(int(numberOfColumns)):

            selectedColumns += self.columns[i] + ", "

        selectedColumns = selectedColumns[:-2] + " "

        cursor = self.db.cursor(buffered=True)

        query = "SELECT " + selectedColumns + "FROM statistic"

        if numberOfRecords != "0":
            query += " LIMIT " + numberOfRecords + ";"
        else:
            query += ";"

        cursor.execute(query)

    def writeToDb(self, numberOfRecords, numberOfColumns):

        selectedColumns = ""

        values = ""

        for i in range(int(numberOfColumns)):

            selectedColumns += self.columns[i] + ", "
            values +=  "'" + self.columns[i] + "'" + ", "

        selectedColumns = selectedColumns[:-2]
        values = values[:-2]

        cursor = self.db.cursor()

        query = "INSERT INTO statistic (" + selectedColumns + ") VALUES (" + values + ");"

        print(query)

        for i in range(int(numberOfRecords)):

            cursor.execute(query)
        
        self.db.commit()

    def start(self, numberOfRecords, numberOfColumns, isRead):

        start = time.time()

        if (isRead):
            self.readFromDb(numberOfRecords, numberOfColumns)
        else:
            self.writeToDb(numberOfRecords, numberOfColumns)

        end = time.time()

        self.mainWindow.time_taken.setText("Time Taken: " + str(round(end-start, 2)) + " ms")

        self.mainWindow.progress_bar.setValue(100)

gui = DbConnectionGUI()