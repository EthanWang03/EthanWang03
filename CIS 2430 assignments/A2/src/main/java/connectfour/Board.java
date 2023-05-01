package connectfour;

import java.io.BufferedReader;
import java.io.File;
//import java.io.FileReader;
import java.io.FileWriter;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;

/**
 * Created by Ethan Wang 1184940
 * class responsible for managing board
 * saves and loads board
 * edits board
 * calls game methods to check player turns
*/

public class Board{
    private int[][] board = new int[6][7]; //board for game
    private ConnectFour game = new ConnectFour();
    private int numRow = 6;
    private int numCol = 7;
    private int rowCounter = 0;
    private int numX = 0;
    private int numO = 0;
    private int moveCount = 0;

    /*
     * to String method to print board
     */
    public String toString(){
        String string = "  1   2   3   4   5   6   7\n";
        string = string + "+ - + - + - + - + - + - + - +\n";
        for (int row = 0; row < numRow; row++) {
            string = string + "|";
            for (int col = 0; col < numCol; col++) {
                if (this.board[row][col] == 0) { // 0 = space not used
                    string = string + "   ";
                }else if (this.board[row][col] == 1) {
                    string = string + " X ";
                }else {
                    string = string + " O ";
                }
                string = string + "|";
            }
            string = string + "\n+ - + - + - + - + - + - + - +\n";
        }
        return string;
    }

    /**
     * @param numTurns
     * manual set for moveCount
     * sets moveCount to numTurms
    */
    public void setMoveCount(int numTurns) {
        this.moveCount = numTurns;
    }
        
    /**
     * setter for moveCount
    */
    public void setMoveCount() {
        this.moveCount = this.moveCount + 1;
    }
        
    /**
     * getter for moveCount
    */
    public int getMoveCount() {
        return moveCount;
    }
        
    /**
     * populate initial board
     * fills all elements of board with '0'
     * this signifies blank spaces
    */
    public void populateBoard() {
        for (int row = 0; row < board.length; row++) {
            for (int col = 0; col < board[0].length; col++) {
                board[row][col] = 0; //sets all elements as '0' or blank
            }
        }
        game.setTurn(1);
    }

    /**
     * @param temp
     * populate board when file is loaded
     * sets boards elements to that of temp
     * temp[][] stores the contents of the scanned file
    */
    public void populateBoard(int[][]temp) {
        populateBoard();
        for (int row = 0; row < board.length; row++) {
            for (int col = 0; col < board[0].length; col++) {
                board[row][col] = temp[row][col];
            }
        }
        game.setTurn();
    }

    /**
     * getter for board
    */
    public int[][] getBoard() {
        return this.board;
    }

    /**
     * @param col
     * checks if col top is empty in board
     * checks if col is valid/out of bounds
     * returns 1 if move can be made
     * returns 0 otherwise
    */
    public int validate(int col) {
        if(col <= 7 && col >= 1){
            if(board[0][col - 1] == 0) {
                return 1;
            }
        }
        return 0;
    }

    /**
     * @param col
     * makes move in col
     * finds lowest unused grid space in col
     * sets element to current players turn
     */
    public void makeMove(int col) {
        int i = 5;
        while (true) {
            if (this.board[i][col - 1] == 0) {
                //System.out.println(game.getTurn());
                this.board[i][col - 1] = game.getTurn();
                break;
            }
            i--;
        }
    }

    /**
     * @param col
     * @param turn
     * makes move in col
     * finds lowest unused grid space in col
     * sets element to given players turn
     * used by TextUI to update board
     */
    public void makeMove(int col,int turn) {
        int i = 5;
        while (true) {
            if (this.board[i][col - 1] == 0) {
                //System.out.println(game.getTurn());
                this.board[i][col - 1] = turn;
                break;
            }
            i--;
        }
    }

    /**
     * @param turn
     * @return 1 for connect 4
     * manual winner check for when you load board
     * checks if given player turn has make a connect 4
     */
    public int checkWinner(int turn) {// checks board to see if there is a connect 4
        if (checkWinnerHor(turn) == 1){
            return 1;
        }
        if (checkWinnerVert(turn) == 1){
            return 1;
        }
        if (checkWinnerDiag(turn) == 1){
            return 1;
        }
        if (checkWinnerAntiDiag(turn) == 1){
            return 1;
        }
        game.setTurn();
        return 0;
    }

    /**
     * @param turn
     * @return 1 for connect 4
     * @return 0 otherwise
     */
    public int checkWinnerHor(int turn){
        // check horizontal
        for (int row = 0; row < board.length; row++) {
            for (int col = 0; col < board[row].length - 3; col++) {
                if (board[row][col] == turn && board[row][col + 1] == turn){
                    if(board[row][col + 2] == turn && board[row][col + 3] == turn){
                        return 1;
                    }
                }
            }
        }
        return 0;
    }

    /**
     * @param turn
     * @return 1 for connect 4
     * @return 0 otherwise
     */
    public int checkWinnerVert(int turn){
        // check up and down
        for (int row = 0; row < board.length - 3; row++) {
            for (int col = 0; col < board[row].length; col++) {
                if (board[row][col] == turn && board[row + 1][col] == turn){
                    if(board[row + 2][col] == turn && board[row + 3][col] == turn) {
                        return 1;
                    }
                }
            }
        }
        return 0;
    }

    /**
     * @param turn
     * @return 1 for connect 4
     * @return 0 otherwise
     */
    public int checkWinnerDiag(int turn){
        // checks right diagonal
        for (int row = 3; row < board.length; row++) {
            for (int col = 0; col < board[row].length - 3; col++) {
                if (board[row][col] == turn && board[row - 1][col + 1] == turn){
                    if(board[row - 2][col + 2] == turn && board[row - 3][col + 3] == turn){
                        return 1;
                    }
                }
            }
        }
        return 0;
    }

    /**
     * @param turn
     * @return 1 for connect 4
     * @return 0 otherwise
     */
    public int checkWinnerAntiDiag(int turn){
        // checks left diagonal
        for (int row = 0; row < board.length - 3; row++) {
            for (int col = 0; col < board[row].length - 3; col++) {
                if (board[row][col] == turn && board[row + 1][col + 1] == turn){
                    if(board[row + 2][col + 2] == turn && board[row + 3][col + 3] == turn){
                        return 1;
                    }
                }
            }
        }
        return 0;
    }

    /**
     * @return 1 for connect 4
     * checks if the the current player has made a winning move
     */
    public int checkWinner() {// checks board to see if there is a connect 4
        if (checkWinnerHor() == 1){
            return 1;
        }
        if (checkWinnerVert() == 1){
            return 1;
        }
        if (checkWinnerDiag() == 1){
            return 1;
        }
        if (checkWinnerAntiDiag() == 1){
            return 1;
        }
        game.setTurn();
        return 0;
    }

    /**
     * @return 1 for connect 4
     * @return 0 otherwise
     */
    public int checkWinnerHor(){
        // check horizontal
        for (int row = 0; row < board.length; row++) {
            for (int col = 0; col < board[row].length - 3; col++) {
                if (board[row][col] == game.getTurn() && board[row][col + 1] == game.getTurn()){
                    if(board[row][col + 2] == game.getTurn() && board[row][col + 3] == game.getTurn()){
                        return 1;
                    }
                }
            }
        }
        return 0;
    }

    /**
     * @return 1 for connect 4
     * @return 0 otherwise
     */
    public int checkWinnerVert(){
        // check up and down
        for (int row = 0; row < board.length - 3; row++) {
            for (int col = 0; col < board[row].length; col++) {
                if (board[row][col] == game.getTurn() && board[row + 1][col] == game.getTurn()){
                    if(board[row + 2][col] == game.getTurn() && board[row + 3][col] == game.getTurn()) {
                        return 1;
                    }
                }
            }
        }
        return 0;
    }

    /**
     * @return 1 for connect 4
     * @return 0 otherwise
     */
    public int checkWinnerDiag(){
        // checks right diagonal
        for (int row = 3; row < board.length; row++) {
            for (int col = 0; col < board[row].length - 3; col++) {
                if (board[row][col] == game.getTurn() && board[row - 1][col + 1] == game.getTurn()){
                    if(board[row - 2][col + 2] == game.getTurn() && board[row - 3][col + 3] == game.getTurn()){
                        return 1;
                    }
                }
            }
        }
        return 0;
    }

    /**
     * @return 1 for connect 4
     * @return 0 otherwise
     */
    public int checkWinnerAntiDiag(){
        // checks left diagonal
        for (int row = 0; row < board.length - 3; row++) {
            for (int col = 0; col < board[row].length - 3; col++) {
                if (board[row][col] == game.getTurn() && board[row + 1][col + 1] == game.getTurn()){
                    if(board[row + 2][col + 2] == game.getTurn() && board[row + 3][col + 3] == game.getTurn()){
                        return 1;
                    }
                }
            }
        }
        return 0;
    }

    /*
     * returns which player has made a connect 4
     * returns 0 if no player has won yet
     */
    public int checkWin(){
        if (checkWinner(1) == 1){
            return 1;
        }
        if (checkWinner(2) == 1){
            return 2;
        } else {
            return 0;
        }
    }

    /**
     * @param tempBoard
     * @param intLine
     * sets row of tempboard to be intLine
     * tempboard stores the values of a loaded file
     */
    private void editBoard(int[][] tempBoard, int[] intLine) {
        for (int i = 0; i < numCol; i++) { // sets an entire row to the scanned row from file
            tempBoard[rowCounter - 1][i] = intLine[i];
            if (intLine[i] == 1) {
                numX = numX + 1;
            } else if (intLine[i] == 2) {
                numO = numO + 1;
            } else {
                game.setTurn();
            }
        }
    }

    /**
     * @param fileName
     * saves data from game board to a file
     * @return 1 for successful file creation and save
     * return 2 if file exists or file cannot be saved
     * return 4 if fileName format is invalid
     * @throws Exception
     */
    public int saveFile(String fileName) {
        if(!fileName.endsWith(".csv")){
            return 4;
        }
        File file = new File("assets/", fileName);
        if (file.exists()) {
            return 2;
        }
        try {
            FileWriter writer = new FileWriter(file);
            for (int row = 0; row < numRow; row++) {
                //writes board contents into file
                for (int col = 0; col < numCol; col++) {
                    writer.write(Integer.toString(board[row][col]));
                    if (col < numCol - 1) {
                        writer.write(",");
                    }
                }
                writer.write("\n");
            }
            writer.close();
            return 1;
        } catch (Exception e) {
            return 2;
        }
    }

    /**
     * @param fileName
     * file read and populates board with data
     * @return 0 for invalid board format and values
     * @return 1 for success
     * @return 3 for file not existing
     * @return 4 for fileName not correct format
     * @throws Exception
     */
    public int loadFile(String fileName) {
        if(!fileName.endsWith(".csv")){
            return 4;
        }
        String line = "";
        Path path = FileSystems.getDefault().getPath("assets/", fileName);
        //FileReader path = new FileReader("assets/" + fileName);
        int[] intLine = new int[numCol];
        int[][] temp = new int[numRow][numCol];
        rowCounter = 0;
        try {
            BufferedReader reader = Files.newBufferedReader(path);
            while ((line = reader.readLine()) != null) {
                rowCounter = rowCounter + 1; // counts rows
                String[] lines = line.split(","); //parse per every ,
                if (lines.length != numCol) {
                    return 0;
                }
                if (rowCounter > numRow) {
                    return 0;
                }
                for (int i = 0; i < numCol; i++) {
                    if (Integer.valueOf(lines[i]) < 0 || Integer.valueOf(lines[i]) > 2) {
                        return 0;
                    }
                    intLine[i] = Integer.valueOf(lines[i]);
                }
                editBoard(temp,intLine); // populate row of temp with line from file
            }
            reader.close();
            //validates file input
            if(rowCounter == numRow && temp[0].length == numCol){
                populateBoard(temp);
                return 1;
            }
            return 0;
        } catch (Exception e) {
            return 3;
        }
    }

    /**
     * checks which players turn it should be after a file is loaded
     */
    public void checkTurn() {
        setMoveCount(numX + numO);
        //System.out.println(numX+numO);
        //turn = amount of pieces placed
        if (numX > numO) {
            //checks whos turn it should be
            game.setTurn(1);
        } else if (numO > numX) {
            game.setTurn(2);
        }
    }
}