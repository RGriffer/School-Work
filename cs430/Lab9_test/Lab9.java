import java.sql.*;
import java.io.File;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class Lab9 {
    public static void main(String args[]){

        Connection con = null;

        try {
            Statement stmt;
            //ResultSet rs;

            // Register the JDBC driver for MySQL.
            Class.forName("com.mysql.jdbc.Driver");

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

            try {

                Lab9 showXML = new Lab9();
                showXML.readXML ("/s/bach/a/class/cs430dl/Current/more_assignments/LabData/Libdata.xml", stmt);
            }catch( Exception e ) {
                e.printStackTrace();

            }//end catch

            con.close();
        }catch( Exception e ) {
            e.printStackTrace();

        }//end catch

    }//end main

    public void readXML(String fileName, Statement stmt)
    {
        try {
            File file = new File(fileName);
            DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
            DocumentBuilder db = dbf.newDocumentBuilder();
            Document doc = db.parse(file);
            doc.getDocumentElement().normalize();
            NodeList nodeLst = doc.getElementsByTagName("Borrowed_by");
            ResultSet rs;

            for (int s = 0; s < nodeLst.getLength(); s++) {

                Node fstNode = nodeLst.item(s);

                if (fstNode.getNodeType() == Node.ELEMENT_NODE) {

                    Element sectionNode = (Element) fstNode;

                    NodeList memberIdElementList = sectionNode.getElementsByTagName("MemberID");
                    Element memberIdElmnt = (Element) memberIdElementList.item(0);
                    NodeList memberIdNodeList = memberIdElmnt.getChildNodes();
                    //System.out.println("MemberID : "  + ((Node) memberIdNodeList.item(0)).getNodeValue().trim());
                    String memberID = ((Node) memberIdNodeList.item(0)).getNodeValue().trim();

                    NodeList secnoElementList = sectionNode.getElementsByTagName("ISBN");
                    Element secnoElmnt = (Element) secnoElementList.item(0);
                    NodeList secno = secnoElmnt.getChildNodes();
                    //System.out.println("ISBN : "  + ((Node) secno.item(0)).getNodeValue().trim());
                    String ISBN = ((Node) secno.item(0)).getNodeValue().trim();

                    NodeList codateElementList = sectionNode.getElementsByTagName("Checkout_date");
                    Element codElmnt = (Element) codateElementList.item(0);
                    NodeList cod = codElmnt.getChildNodes();
                    //System.out.println("Checkout_date : "  + ((Node) cod.item(0)).getNodeValue().trim());
                    String checkoutDate = ((Node) cod.item(0)).getNodeValue().trim();

                    NodeList cidateElementList = sectionNode.getElementsByTagName("Checkin_date");
                    Element cidElmnt = (Element) cidateElementList.item(0);
                    NodeList cid = cidElmnt.getChildNodes();
                    //System.out.println("Checkin_date : "  + ((Node) cid.item(0)).getNodeValue().trim());
                    String checkinDate = ((Node) cid.item(0)).getNodeValue().trim();

                    NodeList libraryElementList = sectionNode.getElementsByTagName("Library");
                    Element libraryElement = (Element) libraryElementList.item(0);
                    NodeList lib = libraryElement.getChildNodes();
                    //System.out.println("library : "  + ((Node) lib.item(0)).getNodeValue().trim());
                    String library = ((Node) lib.item(0)).getNodeValue().trim();

                    if(checkinDate.length() > 5){
                        try {

                            stmt.executeUpdate("UPDATE BorrowedBy SET CheckinDate = \'" + checkinDate + "\' WHERE MemberID = " + memberID + " AND ISBN = \'" + ISBN + "\'");
                            System.out.println("Member: " + memberID + " checked in " + ISBN + " on " + checkinDate + " at " + library + " library");
                        }catch(Exception e){
                            System.out.println("Error with checkin");
                        }
                    }
                    if(checkoutDate.length() > 5){
                        String temp = "N/A";
                        try {
                            stmt.executeUpdate("INSERT INTO BorrowedBy VALUES (" + memberID + ",\'" + ISBN + "\',\'" + checkoutDate + "\',\'" + temp + "\', \'" + library + "\');");
                            System.out.println("Member: " + memberID + " checked out " + ISBN + " on " + checkoutDate + " from " + library + " library");
                        }catch(Exception e){
                            System.out.println("Error with checkout");
                        }

                    }
                }

            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        ResultSet rs;
        try{
            rs = stmt.executeQuery("SELECT * FROM BorrowedBy;");
            System.out.println();
            System.out.println("BORROWEDBY TABLE:");
            while(rs.next()){
                System.out.println("MemberID: " + rs.getString("MemberID") + " ISBN: " + rs.getString("ISBN") + " CheckoutDate: " + rs.getString("checkoutDate") + " CheckinDate: " + rs.getString("CheckinDate") + " Library: " + rs.getString("LibraryName"));
            }
        }catch( Exception e){
            System.out.println("Error in query 1");
            //e.printStackTrace();
        }

        try{
            rs = stmt.executeQuery("SELECT b.title, bb.LibraryName FROM Book b, BorrowedBy bb WHERE b.ISBN=bb.ISBN AND CheckinDate='N/A';");
            System.out.println();
            System.out.println("5b.");
            while(rs.next()){
                System.out.println("Book: " + rs.getString("Title") + " Library: " + rs.getString("LibraryName"));
            }
        }catch( Exception e){
            System.out.println("Error in query 2");
            //e.printStackTrace();
        }
    }
}
