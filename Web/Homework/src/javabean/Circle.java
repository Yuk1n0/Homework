package javabean;

public class Circle {
    private double r;    //半径
    private double p;    //周长
    private double area; //面积

    public Circle(double r) {
        this.r = r;
    }

    public void setP() {
        this.p = 2 * Math.PI * r;
    }

    public void setArea() {
        this.area = Math.PI * r * r;
    }

    public double getR() {
        return r;
    }

    public void setR(double r) {
        this.r = r;
    }

    public double getP() {
        return p;
    }

    public double getArea() {
        return area;
    }
}
