package tictactoe;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.InputMismatchException;

public class Runner{
    private static ArrayList<Integer> xPos = new ArrayList<Integer>(); 
    //array lists to store player moves
    private static ArrayList<Integer> oPos = new ArrayList<Integer>();
    private static List<List<Integer>> winning = new ArrayList<List<Integer>>(); 
    // list for winning combinations
    private static char[][] board = {
            {'1', '|', '2', '|', '3'}, 
            {'-', '+', '-', '+', '-'},
            {'4', '|', '5', '|', '6'},
            {'-', '+', '-', '+', '-'},
            {'7', '|', '8', '|', '9'}
            };
    public ArrayList<Integer> getXPos(){
        return xPos;
    }
    public ArrayList<Integer> getOPos(){
        return oPos;
    }
    public List<List<Integer>> getWinning(){
        return winning;
    }
    /**
     * populates arrayLists with posible winning move conditions
     */
    public static void createArray(){

        List<Integer> topRow = Arrays.asList(1, 2, 3); // every winning combination
        List<Integer> midRow = Arrays.asList(4, 5, 6);
        List<Integer> botRow = Arrays.asList(7, 8, 9);
        
        List<Integer> leftCol = Arrays.asList(1, 4, 7);
        List<Integer> midCol = Arrays.asList(2, 5, 8);
        List<Integer> rightCol = Arrays.asList(3, 6, 9);
        
        List<Integer> diag = Arrays.asList(1, 5, 9);
        List<Integer> antiDiag = Arrays.asList(7, 5, 3); 
        
        winning.add(topRow); // add them to the winning list
        winning.add(midRow);
        winning.add(botRow);
        
        winning.add(leftCol);
        winning.add(midCol);
        winning.add(rightCol);
        
        winning.add(diag);
        winning.add(antiDiag);
    }
    /**
     * @param args
     * main function
     * scans user input sends to method to make move and checks for win
     */
    public static void main(String[] args){
        Classes game = new Classes(); 
        createArray();
        int turnCount = 0; // counts turns to determine a draw
        Scanner scan = new Scanner(System.in);
        boolean loop = true;
        int input = 0;
        game.instructions(); // prints out start messages
        while(true) {
            game.printboard(board);
            System.out.println("Turn = " + game.getTurn()); //prints current turn
            while(loop) { // loop for invalid int inputs
                do{
                    System.out.print("Enter your placement (1-9): ");
                    try{
                        input = scan.nextInt();
                        while(input > 9 || input < 1) { 
                            // checks if input is greater than 9 or less than 1
                            System.out.print("Error - Out of Bounds: ");
                            input = scan.nextInt();
                        }
                        while(xPos.contains(input) || oPos.contains(input)) { 
                            // checks if the input has already been made before by X's or O's
                            System.out.print("Illegal Move! Try Again: ");
                            input = scan.nextInt();
                        }
                    }catch (InputMismatchException e) { // throws non int error
                        scan.next();
                    }
                }while(input > 9 || input < 1); //while input is out of bounds scan for players input
                game.placePiece(board, input, game.getTurn()); //makes move after move is validated
                turnCount = turnCount + 1;
                break;
            }
            if(game.checkWin()) {
                //prints winner
                System.out.println("winner is "+ game.getTurn() + "'s");
                scan.close();
                game.printboard(board);
                break;
            }
            if(turnCount == 9) { 
                // if there has been 9 turns and no one has won the game must be a draw
                scan.close();
                System.out.println("Game is a draw!");
                break;
            }
            game.setTurn(game.getTurn()); // changes turns
        }
    }
}