package com.beans;

import javax.naming.InitialContext;
import javax.sql.DataSource;
import java.sql.*;

public class BookDAO {
    private static InitialContext context = null;
    private DataSource dataSource = null;

    // 根据书号查询图书信息
    public BookBean searchBook(String bookid) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rst = null;
        BookBean book = new BookBean();
        try {
            Class.forName("com.mysql.jdbc.Driver");
            String dburl = "jdbc:mysql://localhost:3306/bookstore?";
            conn = DriverManager.getConnection(dburl, "root", "123456");
            pstmt = conn.prepareStatement("SELECT * FROM books WHERE bookid=?");
            pstmt.setString(1, bookid);
            rst = pstmt.executeQuery();
            if (rst.next()) {
                book.setBookid(rst.getString("bookid"));
                book.setTitle(rst.getString("title"));
                book.setAuthor(rst.getString("author"));
                book.setPublisher(rst.getString("publisher"));
                book.setPrice(rst.getFloat("price"));
                return book;
            } else {
                return null;
            }
        } catch (Exception e) {
            return null;
        } finally {
            try {
                conn.close();
            } catch (SQLException se) {
            }
        }
    }
}