/**
 @author    Juan Villarreal <a href="mailto:juan.villarreal1@ucalgary.ca">juan.villarreal1@ucalgary.ca</a>
 @version   1.29
 @since     1.0
 */

//NEW CHANGES

import java.util.Arrays;
import java.util.Random;    //To generate random spots for queend

public class EightQueensTest implements Cloneable {
    char[][] chessBoard;

    //Method to create clone
    public EightQueensTest clone() throws CloneNotSupportedException{
        EightQueensTest copy = (EightQueensTest)super.clone();
        copy.chessBoard = new char[this.chessBoard.length][this.chessBoard[0].length];
        for (int i = 0; i < this.chessBoard.length; i++){ //Copying each element on array
            copy.chessBoard[i] = this.chessBoard[i].clone();
        }
        return copy;
    }

    //Constructor which fills the two-dimensional array with 'o'
    public EightQueensTest(){
        chessBoard = new char[8][8];
        for (int i = 0; i < this.chessBoard.length; i++){
            Arrays.fill(this.chessBoard[i], 'o');
        }
    }

    //Getter function returns the current two-dimensional chees board array
    public char[][] getBoard(){
        return chessBoard;
    }

    //Setter function to insert a 'Q' in a certain spot
    public void setQueen(int row, int column){
        chessBoard[row - 1][column - 1] = 'Q';
    }

    //Setter function to insert a 'o' in a certain spot
    public void emptySquare(int row, int column){
        chessBoard[row - 1][column - 1] = 'o';
    }
    public static void main(String[] args) throws CloneNotSupportedException {
        EightQueensTest myBoard = new EightQueensTest();
        //myBoard.setQueen(8, 8);
        //myBoard.setQueen(3, 5);
        //myBoard.setQueen(4, 2);
        myBoard.setQueens(8);
        //EightQueensTest myBoard2 = (EightQueensTest)myBoard.clone();
        //myBoard2.emptySquare(8, 8);
        //myBoard2.setQueen(2, 3);
        display board = new display(myBoard);
        //System.out.println();
        //display board2 = new display(myBoard2);
    }

    int[] threatened = new int[64]; //Array of positions that are threatened by other queens
    //Method sets the positions as many queens as the argument says
    //If it is able to do so it returns true, otherwise false
    boolean first = true; //Boolean to add given queens in threatened array
    public boolean setQueens(int queensRemaining){
        //If queensRemaining = 0 that means we've been able to place them all correctly
        if (queensRemaining == 0){
            return true;
        }
        if (first){
            givenQueens();
            first = false;
        }
        int[] tested = new int[64]; //Array of values positions tested by such queen
        int[] rowsChecked = {1,2,3,4,5,6,7,8};
        int[] columnsChecked = {1,2,3,4,5,6,7,8};
        //Next few lines pick a random row & column and shorten the arrays of 
        //rowsChecked & columnsChecked to only keep those places that haven't been checked
        int rand = new Random().nextInt(rowsChecked.length);
        int queenRow = rowsChecked[rand];
        System.arraycopy(rowsChecked, rand + 1, rowsChecked, rand, rowsChecked.length - rand - 1);
        int[] copy = Arrays.copyOf(rowsChecked, rowsChecked.length - 1);
        rowsChecked = copy;
        rand = new Random().nextInt(columnsChecked.length);
        int queenColumn = columnsChecked[rand];
        System.arraycopy(columnsChecked, rand + 1, columnsChecked, rand, columnsChecked.length - rand - 1);
        copy = Arrays.copyOf(columnsChecked, columnsChecked.length - 1);
        columnsChecked = copy;
        //While loop checks if the spot is available
        while (!checkAvailability((8*(queenRow - 1)+queenColumn), tested)){
            //If array of columnsChecked is empty, array needs to be refreshed and another row spot is attempted
            if (columnsChecked.length < 1){
                //If rowsChecked is empty all positions have been checked
                //Returns false to go back and change the position of previous queen
                if (rowsChecked.length < 1){
                    return false;
                }
                //Changing row value
                rand = new Random().nextInt(rowsChecked.length);
                queenRow = rowsChecked[rand];
                System.arraycopy(rowsChecked, rand + 1, rowsChecked, rand, rowsChecked.length - rand - 1);
                copy = Arrays.copyOf(rowsChecked, rowsChecked.length - 1);
                rowsChecked = copy;
                //Refreshing columnsChecked array to test with different row position
                int[] num = {1,2,3,4,5,6,7,8};
                columnsChecked = num;
            }
            //Updating column value
            rand = new Random().nextInt(columnsChecked.length);
            queenColumn = columnsChecked[rand];
            System.arraycopy(columnsChecked, rand + 1, columnsChecked, rand, columnsChecked.length - rand - 1);
            copy = Arrays.copyOf(columnsChecked, columnsChecked.length - 1);
            columnsChecked = copy;
        }
        //Adding tested values to not repeat same test 
        int k = 0;
        while (tested[k] != 0){
            k++;
        }
        tested[k] = 8*(queenRow - 1)+queenColumn;
        int cut = updateThreatened(queenRow, queenColumn, 0); //Update threats at such queen position
        //fitsInPlace tell me if the next queen was able to solve the puzzle
        //Given false a new position is necessary for previous queen
        boolean fitsInPlace = setQueens(queensRemaining - 1);
        while (!fitsInPlace){
            //Removes threats that were used for tested values
            cut = updateThreatened(queenRow, queenColumn, cut);
            //Checking availability to see which position will be tested next
            while (!checkAvailability((8*(queenRow - 1)+queenColumn), tested)){
                //Same code as before to update row & column values
                if (columnsChecked.length < 1){
                    if (rowsChecked.length < 1){
                        return false;
                    }
                    rand = new Random().nextInt(rowsChecked.length);
                    queenRow = rowsChecked[rand];
                    System.arraycopy(rowsChecked, rand + 1, rowsChecked, rand, rowsChecked.length - rand - 1);
                    copy = Arrays.copyOf(rowsChecked, rowsChecked.length - 1);
                    rowsChecked = copy;
                    int[] num = {1,2,3,4,5,6,7,8};
                    columnsChecked = num;
                }
                rand = new Random().nextInt(columnsChecked.length);
                queenColumn = columnsChecked[rand];
                System.arraycopy(columnsChecked, rand + 1, columnsChecked, rand, columnsChecked.length - rand - 1);
                copy = Arrays.copyOf(columnsChecked, columnsChecked.length - 1);
                columnsChecked = copy;
            }
            k = 0;
            //Again adding tested values to not repeat same test 
            while (tested[k] != 0){
                k++;
            }
            tested[k] = 8*(queenRow - 1)+queenColumn;
            //Updating new threats with position to be tested
            cut = updateThreatened(queenRow, queenColumn, 0);
            //Recalls the function to try in fit the following queens in the board
            fitsInPlace = setQueens(queensRemaining - 1);
        }
        //If fitsInPlace is true that means the puzzle was solved
        if (fitsInPlace) {
            //Setting each queen to its position
            setQueen(queenRow, queenColumn);
            //Returns true to keep going back on our recurring function and placing the queens on their spots
            return true;
        }
        return false;
    }

    //Method updates the list containting the places that are threatened
    public int updateThreatened(int row, int column, int cut){
        if (cut == 0){ //If cut == 0, the update is about adding threats rather than removing threats from the array
            int k = 0;
            while (this.threatened[k] != 0){ //Determines first empty position in array to add more threats
                k++;
            }
            cut = k; //Cut keeps the index of the first added threat in case threats need to be removed later

            int value = (row - 1)*8 + 1; //Numeric value from 1-64 of spot where Queen will be placed
            for (int i = 0; i < 8; i++){ //for loop to complete adding threats done horizontally
                k = addToThreatened(value, k); //Method actually adds the positions at threat to array
                value++;
            }

            value = column;
            for (int i = 0; i < 8; i++){ //for loop to complete adding threats done vertically
                k = addToThreatened(value, k);
                value += 8;
            }

            //while loops to complete adding threats done diagonally
            int j = 0;
            //while loop goes to the most upper left position diagonal to the queen
            while ((row - j) > 1 && (column - j) > 1){ 
                j++;
            }
            value = (row - j - 1)*8 + (column - j);
            //while loop goes down on a negeative slope to add those compromised positions diagonally
            while ((row - j) < 9 && (column - j) < 9){
                k = addToThreatened(value, k);
                j--;
                value = (row - j - 1)*8 + (column - j);
            }
            j = 0;
            //while loop goes to the most lower left position diagonal to the queen
            while ((row - j) > 1 && (column + j) < 8){
                j++;
            }
            value = (row - j - 1)*8 + (column + j);
            //while loop goes up on a positive slope to add those compromised positions diagonally
            while ((row - j) < 9 && (column + j) > 0){
                k = addToThreatened(value, k);
                j--;
                value = (row - j - 1)*8 + (column + j);
            }
            return cut;
        }
        else { //If cut != 0 that means some values (the last ones added) that were at threat should be removed
            Arrays.fill(this.threatened, cut, 64, 0);
            return 0;
        }
    }

    //Method adds the values of square postions which are under threat of another queen
    public int addToThreatened(int value, int k) {
        boolean alreadyThere = false;
        for (int element : this.threatened){ //Checks if element is already part of the threatened list
            if (element == value){
                alreadyThere = true;
                break;
            }
        }
        if (!alreadyThere) { //If not on the list yet it is added at the appropriate index k
            this.threatened[k] = value;
            k++;
        }
        return k;
    }

    //Checks if the position that will be tested is not compromised by 
    //another queen or a place where we already checked. Returns true if available spot
    public boolean checkAvailability (int value, int[] tested) {
        for (int element : this.threatened){ //Checking threats from other queens (through threatened array)
            if (element == value){
                return false;
            }
        }
        for (int element : tested){ //Checks to see if value has already been tested
            if (element == value){
                return false;
            }
        }
        return true;
    }

    //Method updates threatened array list with the board position 
    //which are threatened by the already present queens
    public void givenQueens() {
        for (int i = 0; i < this.chessBoard.length; i++){
            for (int j = 0; j < this.chessBoard[i].length; j++){
                if (chessBoard[i][j] == 'Q'){
                    updateThreatened(i + 1, j + 1, 0);
                }
            }
        }
    }
}

class display {
    public display(){
    }

    public display(EightQueensTest myBoard){
        for (int i = 0; i < myBoard.chessBoard.length; i++){
            for (int j = 0; j < myBoard.chessBoard[0].length; j++) {
                System.out.print(" " + myBoard.chessBoard[i][j]);
            }
            System.out.println();
        }
    }

    public display(char[][] myBoard){
        for (int i = 0; i < myBoard.length; i++){
            for (int j = 0; j < myBoard[0].length; j++) {
                System.out.print(" " + myBoard[i][j]);
            }
            System.out.println();
        }
    }
}
