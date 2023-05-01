package tictactoe;

public class Classes extends Runner{

    private char playerTurn = 'X'; //shows whos turn it is


    /**
     * prints instruction for game start
     */
    public void instructions(){ // instructions
        System.out.println("Welcome to tic tac toe\n");
        System.out.println(" 1 | 2 | 3");
        System.out.println(" - + - + -");
        System.out.println(" 4 | 5 | 6");
        System.out.println(" - + - + -");
        System.out.println(" 7 | 8 | 9\n");
        System.out.println("The board looks like this!");
        System.out.println("There are two symbols X and O");
        System.out.println("Each player takes turns placing their symbol");
        System.out.println("Enter the number for the place you would like to place your symbol");
        System.out.println("Connect 3 of your symbols in a row horizontally, vertically or diagonally to win");
        System.out.println("X's will go first!");
    }
    public void setTurn(char turn) { // changes the turns 
        if(turn == 'X') {
            playerTurn = 'O';
        }else{
            playerTurn = 'X';
        }
    }
    public char getTurn() { // gets the current player turn
        return playerTurn;
    }

    /**
     * @param board
     * @param pos
     * @param user
     * takes user and desired pos to place piece
     * adds pos value to arrayList which stores each players made moves
     * change element in char[][] 2d array to the current players symbol
     * in order to reflect move made
     */
    public void placePiece(char[][] board, int pos, char user){ 
        // places the piece
        char symbol = ' ';
        Runner runner = new Runner();
        if(user == 'X'){
            symbol = 'X';
            
            runner.getXPos().add(pos); // adds the int pos to the made moves
        }else if(user == 'O'){
            symbol = 'O';
            runner.getOPos().add(pos);
        }
        switch(pos){ // adds the move to the char 2d array so it can be printed
            case 1:
                board[0][0] = symbol;
                break;
            case 2:
                board[0][2] = symbol;
                break;
            case 3:
                board[0][4] = symbol;
                break;
            case 4:
                board[2][0] = symbol;
                break;
            case 5:
                board[2][2] = symbol;
                break;
            case 6:
                board[2][4] = symbol;
                break;
            case 7:
                board[4][0] = symbol;
                break;
            case 8:
                board[4][2] = symbol;
                break;
            case 9:
                board[4][4] = symbol; 
                break;                          
            default:
                break;
        }
    }

    /**
     * @return
     * checks win by navigating through arrayList winning
     * winning ArrayList contains all winning move combinations
     * if the arrayList which stores the players made moves (Xpos or Opos)
     * contains all of an element in arrayList winning
     * then they must have 3 in a row
     */
    public boolean checkWin(){   
        Runner runner = new Runner();
        for(int i = 0; i < runner.getWinning().size(); i++) { 
            // navigates through ArrayList of lists winning
            //System.out.println(winning.get(i));
            if(runner.getXPos().containsAll(runner.getWinning().get(i))){ 
                return true;
            }else if(runner.getOPos().containsAll(runner.getWinning().get(i))){
                return true;
            }
        }
        return false;
    }
    public void printboard(char[][] board){ // prints board
        System.out.print("\n");
        for(int row = 0; row < 5; row++) { // navigates through rows
            for(int col = 0; col < 5; col++) { // navigates through cols
                System.out.print(" " + board[row][col]); // prints array elements
            }
            System.out.print("\n");
        }
        System.out.print("\n");
    }
}