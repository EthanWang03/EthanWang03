package connectfour;

//import static org.junit.Assert.assertEquals;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;



public class BoardTest{
    private Board tester;

    @Before
    public void setup(){
        //set up for the test
        tester = new Board();
    }
    @Test
    public void validate(){
        tester.populateBoard();
        Assert.assertEquals(tester.validate(1),1);
        Assert.assertEquals(tester.validate(2),1);
        Assert.assertEquals(tester.validate(3),1);
        Assert.assertEquals(tester.validate(4),1);
        Assert.assertEquals(tester.validate(5),1);
        Assert.assertEquals(tester.validate(6),1);
        Assert.assertEquals(tester.validate(7),1);
        tester.makeMove(1);
        tester.makeMove(1);
        tester.makeMove(1);
        tester.makeMove(1);
        tester.makeMove(1);
        tester.makeMove(1);
        Assert.assertEquals(tester.validate(1),0);
        Assert.assertEquals(tester.validate(10),0);
        Assert.assertEquals(tester.validate(-5),0);
    }
    @Test
    public void checkWinner(){
        Assert.assertEquals(tester.loadFile("exampleboard.csv"),1);
        Assert.assertEquals(tester.checkWinner(1),0);
        Assert.assertEquals(tester.checkWinner(2),0);
        Assert.assertEquals(tester.loadFile("winVert.csv"),1);
        Assert.assertEquals(tester.checkWinner(1),0);
        Assert.assertEquals(tester.checkWinner(2),1);
        Assert.assertEquals(tester.loadFile("winHor.csv"),1);
        Assert.assertEquals(tester.checkWinner(1),1);
        Assert.assertEquals(tester.checkWinner(2),0);
        Assert.assertEquals(tester.loadFile("winleftDiag.csv"),1);
        Assert.assertEquals(tester.checkWinner(1),1);
        Assert.assertEquals(tester.checkWinner(2),0);
        Assert.assertEquals(tester.loadFile("winRightDiag.csv"),1);
        Assert.assertEquals(tester.checkWinner(1),1);
        Assert.assertEquals(tester.checkWinner(2),0);
    }
    @Test
    public void saveFile(){
        Assert.assertEquals(tester.saveFile("exampleboard.csv"),2);
        Assert.assertEquals(tester.saveFile("exampleboard"),4);
        Assert.assertEquals(tester.saveFile("apple.csv"),1);
    }
    @Test
    public void loadFile(){
        Assert.assertEquals(tester.loadFile("exampleboard.csv"),1);
        Assert.assertEquals(tester.loadFile("exampleboard"),4);
        Assert.assertEquals(tester.loadFile("applewood.csv"),3);
        Assert.assertEquals(tester.loadFile("incorrect.csv"),0);
        Assert.assertEquals(tester.loadFile("incorrect2.csv"),0);
        Assert.assertEquals(tester.loadFile("incorrect3.csv"),0);
        Assert.assertEquals(tester.loadFile("incorrect4.csv"),3);
    }
}