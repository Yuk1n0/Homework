<%@ page contentType="text/html;charset=utf-8" %>
<jsp:useBean id="book" class="com.beans.BookBean" scope="session"/>
<html>
<body>
书号：
<jsp:getProperty name="book" property="bookid"/>
书名：
<jsp:getProperty name="book" property="title"/>
作者：
<jsp:getProperty name="book" property="author"/>
出版社：
<jsp:getProperty name="book" property="publisher"/>
价格：
<jsp:getProperty name="book" property="price"/>
</body>
</html>