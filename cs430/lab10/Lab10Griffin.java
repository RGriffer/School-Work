import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.net.URL;
import java.time.LocalDate;
import java.sql.*;
import java.util.ArrayList;

public class Lab10Griffin {
    public static void main(String args[]){

        Connection con = null;
        //Object[] maleFemale = {"male", "female"};
        Object[] choices = {"ISBN","Name","Author"};
        
        try {
            Statement stmt;
            ResultSet rs;

            // Register the JDBC driver for MySQL.
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Define URL of database server for
            // database named 'user' on the faure.
            String url =
                "jdbc:mysql://faure/rgriffer";

            // Get a connection to the database for a
            // user named 'user' with the password
            // 123456789.
            con = DriverManager.getConnection(
                        url,"rgriffer", "832245989");

            // Display URL and connection information
            System.out.println("URL: " + url);
            System.out.println("Connection: " + con);

            // Get a Statement object
            stmt = con.createStatement();
            //Get val
            String val = JOptionPane.showInputDialog(null, "Please enter your ID number:", "Membership prompt", JOptionPane.QUESTION_MESSAGE);
            if(val == null){
                System.out.println("Program will Exit.");
                return;
            }
            System.out.println();
            System.out.print("Verifying member " + val + "....");
            try {
                rs = stmt.executeQuery("SELECT * FROM Member");
                boolean verified = false;
                while (rs.next()) {
                    if(val.equals(rs.getString("MemberID"))){
                        verified = true;
                        System.out.println("Verified! You are " + rs.getString("firstName") + " " + rs.getString("lastName") + ".");
                        System.out.println();
                    }
                }
                if(verified == false){
                    System.out.println("Membership ID of " + val + " does not exist.");
                    int reg = JOptionPane.showConfirmDialog(null, "Would you like to register?", "Registration", JOptionPane.YES_NO_OPTION);
                    if(reg == JOptionPane.NO_OPTION) {return;}
                    if(reg == JOptionPane.YES_OPTION){
                        System.out.println("Let's get you registered.");
                        
                        //ASK USER THEIR INFORMATION
                        String fname = JOptionPane.showInputDialog(null, "What is your first name?", "Registration", JOptionPane.QUESTION_MESSAGE);
                        String lname = JOptionPane.showInputDialog(null, "What is your last name?", "Registration", JOptionPane.QUESTION_MESSAGE);
                        String dob = JOptionPane.showInputDialog(null, "What is your date of birth? (mm/)", "Registration", JOptionPane.QUESTION_MESSAGE); //UPDATE THIS TO FIT MY SCHEMA
                        //Object selmf = JOptionPane.showInputDialog(null, "What is your sex?", "Registration", JOptionPane.INFORMATION_MESSAGE,null,maleFemale,maleFemale[0]);
                        
                        //UPDATE THE DATABASE
                        String myQuery = "INSERT INTO Member (MemberID, FirstName, LastName, DOB) VALUES (?, ?, ?, ?)";
                        PreparedStatement myStatement = con.prepareStatement(myQuery);
                        //UPDATE THIS LINE TO SUPPORT MY DB
                        LocalDate locald = LocalDate.of(Integer.parseInt(dob.substring(6,10)), Integer.parseInt(dob.substring(3,5)), Integer.parseInt(dob.substring(0,2)));
                        Date date = Date.valueOf(locald);
                        myStatement.setInt(1, Integer.parseInt(val));
                        myStatement.setString(2, fname);
                        myStatement.setString(3, lname);
                        myStatement.setDate(4, date);
                        myStatement.executeUpdate();
                        System.out.println("Registration Success!");
                    }
                }
                System.out.println("Can I be of assistance?");
                //PUT CHOICE OF BOOK STUFF HERE
                Object search = JOptionPane.showInputDialog(null, "How would you like to search for books today?", "Search", JOptionPane.INFORMATION_MESSAGE,null,choices,choices[0]);
                
                if(search.equals(choices[0])){ //ISBN
                    String ISBN = JOptionPane.showInputDialog(null, "Please enter the book's ISBN:", "Search", JOptionPane.QUESTION_MESSAGE);
                    String query = "SELECT * FROM LocatedAt NATURAL JOIN Book WHERE ISBN LIKE '%" + ISBN + "%' GROUP BY Title";
                    Statement newstmt;
                    ResultSet newrs;
                    newstmt = con.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE);
                    newrs = newstmt.executeQuery(query);
                    newrs.beforeFirst();
                    boolean found = false;
                    while(newrs.next()) {
                        if(ISBN.equals(newrs.getString("ISBN"))){
                        found = true;
                            String libName = newrs.getString("LibraryName");
                            int available = newrs.getInt("Available");
                            String title = newrs.getString("Title");
                            if(available > 0) {
                                int shelf = newrs.getInt("Shelf");
                                System.out.println("There are " + available + " copies of " + title + " available on shelf " + shelf + " at " + libName);
                            }
                            if(available < 1) {
                                System.out.println("All copies of this book are checked out");
                            }
                        }
                    }
                    if(!found) {
                        System.out.println("Book not found at either library.");
                    }
                }
                
                if(search.equals(choices[1])){ //Name
                    String name = JOptionPane.showInputDialog(null, "Please enter a search term:", "Search", JOptionPane.QUESTION_MESSAGE);
                    String query = "SELECT * FROM LocatedAt NATURAL JOIN Book WHERE Title LIKE '%" + name + "%' GROUP BY Title";
                    Statement newstmt;
                    ResultSet newrs;
                    newstmt = con.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE);
                    newrs = newstmt.executeQuery(query);
                    boolean found = false;
                    //put into array list then back into array
                    int size = 0;
                    if (newrs!=null) {
                        newrs.last();
                        size = newrs.getRow();
                    }
                    Object[] arr = {};
                    newrs.beforeFirst();
                    if (size > 1) {
                        ArrayList<String> names = new ArrayList<String>();
                        while(newrs.next()) {
                            names.add(newrs.getString("Title"));
                        }
                        Object[] nameArr = new Object[names.size()];
                        nameArr = names.toArray();
                        Object titleChoice = JOptionPane.showInputDialog(null, "Results found, which would you like?", "Choose", JOptionPane.INFORMATION_MESSAGE,null,nameArr,nameArr[0]);
                        String selectedTitle = titleChoice.toString();
                        newrs.beforeFirst();
                        while(newrs.next()) {
                            if(selectedTitle.equals(newrs.getString("Title"))){
                                found = true;
                                String libName = newrs.getString("LibraryName");
                                int shelf = newrs.getInt("Shelf");
                                int available = newrs.getInt("Available");
                                if(available > 0) {
                                    System.out.println("There are " + available + " copies of " + selectedTitle + " available on shelf " + shelf + " at " + libName);
                                }
                                if(available < 1) {
                                    System.out.println("All copies of this book are checked out");
                                }
                            }
                        }
                    }
                    newrs.beforeFirst();
                    if(!found) {
                        System.out.println("Book not found at either library.");
                    }
                }
                
                if(search.equals(choices[2])){ //Author
                    String author = JOptionPane.showInputDialog(null, "Please enter the Author's name:", "Search", JOptionPane.QUESTION_MESSAGE);
                }
                
            } catch (SQLException e) {
                System.out.println("SQL-ERROR");
                e.printStackTrace();
            }

        } catch(Exception e) {
            e.printStackTrace();
    } 
}
}//end class Lab10Griffin
