import java.sql.*;

public class ConnectToDB {

    /*
    Columns in the statistic table:
    StatisticID, ClientID, FlightID, ModuleName, CategoryName, SubCategoryName, CategoryType,
    MediaName, AudioName, EpisodeName, FileName, Studio, StarArtist, SubtitleLang, AudioLang, Duration, LogDate, ifetype
     */

    private static Connection conn;

    public static void establishConnection() throws SQLException, ClassNotFoundException {
        Class.forName("com.mysql.cj.jdbc.Driver");

        conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/desdb","root", "1234");
    }

    public static void readFromDB(int recordSize, String columns) throws SQLException {

        Statement statement = conn.createStatement();

        ResultSet resultSet = statement.executeQuery("SELECT " + columns + " FROM statistic LIMIT " + recordSize + ";");

    }

    public static void writeToDB(int recordSize, String columns, String values) throws SQLException {

        Statement statement = conn.createStatement();

        for (int i = 0; i < recordSize; i++) {

            statement.executeUpdate("INSERT INTO statistic (" + columns + ") VALUES (" + values + ");");

        }

    }

    public static void readTest() throws SQLException {

        int[] recordSizeArgs = {3,100,1000,100000,800000};

        String[] columnsArgs = {"StatisticID","StatisticID, ClientID, FlightID","StatisticID, ClientID, FlightID, ModuleName, CategoryName",
                                "StatisticID, ClientID, FlightID, ModuleName, CategoryName, SubCategoryName, CategoryType",
                                "StatisticID, ClientID, FlightID, ModuleName, CategoryName, SubCategoryName, CategoryType, MediaName, AudioName, EpisodeName"};

        for (int i = 0; i < recordSizeArgs.length; i++) {

            long start = System.currentTimeMillis();

            ConnectToDB.readFromDB(recordSizeArgs[i], columnsArgs[i]);

            long end = System.currentTimeMillis();

            long elapsedTime = end-start;

            System.out.println("Total read time (" + recordSizeArgs[i] + " records | Selected Columns: " + columnsArgs[i] + "): " + elapsedTime + " ms");

        }

    }

    public static void writeTest() throws SQLException {

        int[] recordSizeArgs = {3,100,1000,100000,800000};

        String[] columnsArgs = {"StatisticID","StatisticID, ClientID, FlightID","StatisticID, ClientID, FlightID, ModuleName, CategoryName",
                "StatisticID, ClientID, FlightID, ModuleName, CategoryName, SubCategoryName, CategoryType",
                "StatisticID, ClientID, FlightID, ModuleName, CategoryName, SubCategoryName, CategoryType, MediaName, AudioName, EpisodeName"};

        String[] valuesArgs = {"StatisticID","StatisticID, ClientID, FlightID","StatisticID, ClientID, FlightID, ModuleName, CategoryName",
                "StatisticID, ClientID, FlightID, ModuleName, CategoryName, SubCategoryName, CategoryType",
                "StatisticID, ClientID, FlightID, ModuleName, CategoryName, SubCategoryName, CategoryType, MediaName, AudioName, EpisodeName"};

        for (int i = 0; i < columnsArgs.length; i++) {

            long start = System.currentTimeMillis();

            ConnectToDB.writeToDB(recordSizeArgs[i], columnsArgs[i], valuesArgs[i]);

            long end = System.currentTimeMillis();

            long elapsedTime = end-start;

            System.out.println("Total write time (" + "Selected Columns: " + columnsArgs[i] + "): " + elapsedTime + " ms");

        }

    }

    public static void main(String[] args) throws SQLException, ClassNotFoundException {

        ConnectToDB.establishConnection();

        ConnectToDB.readTest();

        System.out.println("**************************");

        ConnectToDB.writeTest();

    }

}
