package servlet;

import javabean.Circle;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class CircleServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html; charset=utf-8");
        PrintWriter out = response.getWriter();
        double r = Double.parseDouble(request.getParameter("r"));
        Circle circle = new Circle(r);
        circle.setP();
        circle.setArea();
        out.println(" 周长 = " + circle.getP() + " 面积 = " + circle.getArea());
        out.close();
    }
}
