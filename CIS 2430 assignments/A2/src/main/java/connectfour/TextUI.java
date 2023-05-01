package connectfour;

import java.util.Scanner;
import java.util.InputMismatchException;

/**
 * Created by Ethan Wang 1184940
 * class responsible for printing and scanning
 * prints board as well as takes user input
 * calls game methods to check player turns
*/

public class TextUI{
    private ConnectFour game = new ConnectFour();
    private Board grid = new Board();
    private int userInput;
    private String charInput;

    /**
     * updates board so it can be printed
     */
    public void updateBoard(int num) {
        grid.makeMove(num,game.getTurn());
    }

    /**
     * resets board after file load
     */
    public void clearBoard() {
        grid = new Board();
    }
    
    /**
     * @param temp
     * refresh board for when file is loaded
     * navigates though board and makes move 
     * to populate board for printing
     */
    public void refreshBoad(int[][] temp) {
        for(int row = 5; row >= 0; row--){
            for(int col = 0; col < 7; col++){
                if(temp[row][col] != 0){
                    grid.makeMove(col+1,temp[row][col]);
                }
            }
        }
    }

    /**
     * TextUI method to test toString method
     * @param num
     * @param str
     */
    public void popTextUI(int num, String str){
        this.userInput = num;
        this.charInput = str;
    }

    /*
     * toString method to print 
     */
    public String toString(){
        return userInput + " " + charInput;
    }

    /**
     * prints board
     */
    public void board() {
        System.out.print(grid.toString());
        game.setTurn();
    }

    /**
     * prints which players turn it is
     */
    public void turn() {
        if (game.getTurn() == 2) {
            System.out.println("Turn = O's");
        } else {
            // System.out.print(game.getTurn());
            System.out.println("Turn = X's");
        }
    }

    /**
     * prints board and player turn
     */
    public void boardAndTurn(){
        board();
        turn();
    }

    /**
     * prints col full
     */
    public void invalid(){
        System.out.println("Error - Invalid input.\n");
    }

    /**
     * method for scanning and validating user input
     * for which col they would like to make a move in
     * @return userInput
     * @throws InputMismatchException
     */
    public int input() {
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter your placement (1-7): ");
        System.out.print("Enter 9 to save or load game: ");
        try {
            this.userInput = scan.nextInt();

        } catch (InputMismatchException e) { // throws non int error
            System.out.println("You didn't input an integer\n");
            scan.next();
        }
        return this.userInput;
    }

    /**
     * scans name of file they would like to save as
     * store filename in charInput
     * @return charInput
     */
    public String getSaveFileName() { // no need for exception throw as files can be numbers
        Scanner scan = new Scanner(System.in);
        System.out.print("\nEnter the name of cvs file to save as: ");
        this.charInput = scan.next();
        scan.nextLine();
        System.out.println("Saving file as " + this.charInput);
        //scan.close();
        return this.charInput;
    }

    /**
     * scans name of file they would like to load from
     * store filename in charInput
     * @return charInput
     */
    public String getLoadFileName() { // no need for exception throw as files can be numbers
        Scanner scan = new Scanner(System.in);
        System.out.print("\nEnter the name of file to load: ");
        this.charInput = scan.next();
        scan.nextLine();
        System.out.println("Loading file " + this.charInput);
        return this.charInput;
    }

    /**
     * @return 1 
     * user wants to save file
     * @return 2
     * user wants to load file
     * @return 3 
     * user wants to continue play
     */
    public int saveOrLoad() {
        Scanner scan = new Scanner(System.in);
        System.out.println("\nIf you would like to save type save: ");
        System.out.println("If you would like to load type load: ");
        game.setTurn();
        while (true) {
            this.charInput = scan.next();
            scan.nextLine();

            if (this.charInput.equalsIgnoreCase("SAVE")) {
                // System.out.println("true");
                //scan.close();
                return 1;
            } else if (this.charInput.equalsIgnoreCase("LOAD")) {
                // System.out.println("true");
                //scan.close();
                return 2;
            } else {
                System.out.println("Invalid input!");
            }
        }
    }

    /*
     * @param error - error code
     * converts error codes from other methods to error message
     */
    public void getError(int error){
        //get error code for file read/write
        if(error == 0){
            System.out.println("Error with File");
        }else if(error == 2){
            System.out.println("File exists");
        }else if(error == 3){
            System.out.println("File does not exist");
        }else if(error == 4){
            System.out.println("File is incorrect format");
        }
    }

    /*
     * takes current player turn and determines who has won
     * prints winner
     */
    public void gameOver() {
        //gets which player has won
        if (game.getTurn() == 1) {
            System.out.println("Game over O's wins!");
        } else {
            System.out.println("Game over X's wins!");
        }
    }

    /*
     * takes current player turn and determines who has won
     * prints winner
     */
    public void gameOver(int turn) {
        //gets which player has won
        if (game.getTurn() == 1) {
            System.out.println("Game over X's wins!");
        } else {
            System.out.println("Game over O's wins!");
        }
    }


    /*
     * prints game draw
     */
    public void gameDraw() {
        System.out.println("Game is a draw!");
    }
}