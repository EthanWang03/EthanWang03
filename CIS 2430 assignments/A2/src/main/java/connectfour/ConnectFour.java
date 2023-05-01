package connectfour;

/**
 * Created by Ethan Wang 1184940
 * class responsible for managing turns
 * contains main method
 * calls board and textUI methods to manage board and print messages
*/

public class ConnectFour {
    private int playerTurn;
    //private static Board grid;

    /**
     * getter for playerTurn
     */
    public int getTurn() {
        return playerTurn;
    }

    /**
     * if playerTurn is X set to O's
     * if playerTurn is O set to X's
     */
    public void setTurn() {
        //System.out.println(playerTurn);
        if(playerTurn == 1) {
            this.playerTurn = 2;
        }else {
            this.playerTurn = 1;
        }
    }

    /**
     * if playerTurn is turn change to other turn
     */
    public void setTurn(int turn) {
        if(turn == 1 || turn == 2){
            this.playerTurn = turn;
        }
    }

    /*
     * to String method to print playerTurn
     */
    public String toString(){
        return playerTurn + "";
    }
    /*
     * main
     */
    public static void main(String[] args) {
        TextUI print = new TextUI();
        Board grid = new Board();
        grid.populateBoard();
        while(true) {
            print.boardAndTurn();
            int input = print.input();
            if(input == 9){
                int save = print.saveOrLoad();
                if (save == 1) { // case for wanting to save board
                    String fileName = print.getSaveFileName();
                    while(grid.saveFile(fileName) != 1) { // case for invalid input
                        print.getError(grid.saveFile(fileName));
                        fileName = print.getSaveFileName();
                    }
                } else if (save == 2) { // case for loading file
                    String fileName = print.getLoadFileName();
                    while(grid.loadFile(fileName) != 1) { // case for invalid input
                        print.getError(grid.loadFile(fileName));
                        fileName = print.getLoadFileName();
                    }
                    print.clearBoard();
                    print.refreshBoad(grid.getBoard());
                    if(grid.checkWin() != 0){ //checks if you loaded a winning board
                        print.board();
                        print.gameOver(grid.checkWin());
                        System.exit(0);
                    }
                    grid.checkTurn();
                }
            } else {
                while(grid.validate(input) != 1) {// validates move
                    print.invalid();
                    input = print.input();
                }
                grid.makeMove(input);
                print.updateBoard(input);
                grid.setMoveCount();
            }
            if(grid.checkWinner() == 1) {
                print.board();
                print.gameOver();
                break;
            }else if(grid.getMoveCount() == 42) { // if game isnt won and turnCount is 42 game is draw
                print.board();
                print.gameDraw();
                break;
            }
        }
    }
}